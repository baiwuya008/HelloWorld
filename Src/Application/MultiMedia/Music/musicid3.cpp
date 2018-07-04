#include "musicid3.h"

MusicId3::MusicId3()
{
}

MusicId3::~MusicId3()
{
    clear();
    destoryImage();
}

void MusicId3::decodeMusic(QString path)
{
    QFile readFile(path);
    if (!readFile.open(QIODevice::ReadOnly)) {
        return;
    }

    long fileLength = readFile.size();
    if (fileLength < (V1_SIZE+V2_SIZE)) {
        return;
    }

    QTextCodec *tc = QTextCodec::codecForName("GBK");
    QByteArray info;
    info.clear();

    readFile.seek(fileLength-V1_SIZE);
    info = readFile.read(V1_SIZE);
    decodeV1(info, tc);
    info.clear();

    readFile.seek(0);
    info = readFile.read(V2_SIZE);
    decodeV2(info, tc);
    info.clear();

    if (m_ID3V2.size < 1) {
        return;
    }


    qint64 totalLength = m_ID3V2.size + V2_SIZE;
    qint64 offset = V2_SIZE;
    while(totalLength > offset)
    {
        readFile.seek(offset);
        info = readFile.read(TF_HEADER_SIZE);
        decodeTF(info, m_TF, tc);
        offset += TF_HEADER_SIZE;

        if (m_TF.size > 0) {
            info.clear();
            readFile.seek(offset);
            if (m_TF.size > TF_MAX_SIZE) {
                info = readFile.read(TF_MAX_SIZE);
            }else {
                info = readFile.read(m_TF.size);
                offset += m_TF.size;
            }


            if (!m_TF.frameID.compare(TF_TCON)) {//流派信息
                m_TF.textEncode = info.at(0);//看数据总是\x01
                //"\x01\xFF\xFE"  前面3个字节大多包含这个,
                m_TF.content = tc->toUnicode(trimmedArray(info.mid(3)));
            }else if (!m_TF.frameID.compare(TF_APIC)) {
                bool result = deocdeImage(tc, readFile, info, offset, m_TF.size);
                if (result) {
                    offset += m_TF.size;
                    break;
                }
                info.clear();
            }
        }


        m_TF.clear();
        info.clear();
    }


    tc = NULL;
    info.clear();
    readFile.close();
}

bool MusicId3::deocdeImage(QTextCodec *tc, QFile &readFile, QByteArray &info,
                           int startOffset, int size)
{
    //图片开始和结束的标志，连续两个
    int startTag_1 = 0;
    int startTag_2 = 0;
    int endTag_1 = 0;
    int endTag_2 = 0;

    bool isStartWrite = false;
    bool isEndWrite = false;
    int imageOffset = 0;
    QByteArray writeArray;
    if (!tc->toUnicode(trimmedArray(info.mid(0, TF_JPEG.length()+1))).compare(TF_JPEG)) {
        startTag_1 = 0xFF;// xFF;
        startTag_2 = 0xD8;// xD8
        endTag_1 = 0xFF;// xFF
        endTag_2 = 0xD9;// xD9
        imageOffset = TF_JPEG.length()+1;
    }else if (!tc->toUnicode(trimmedArray(info.mid(0, TF_PNG.length()+1))).compare(TF_PNG)) {
        startTag_1 = 0x89;
        startTag_2 = 0x50;
        endTag_1 = 0x4E;
        imageOffset = TF_PNG.length()+1;
    }

    for (int i = imageOffset; i < info.size()-1; i++) {
        if (!isStartWrite && (startTag_1 == changeChar(info[i]) && startTag_2 == changeChar(info[i+1]))) {
            isStartWrite = true;
            imageOffset = info.size();
            writeArray.clear();
            writeArray.append(info.mid(i, (info.size()-i)));
            info.clear();
            break;
        }
    }

    while(imageOffset < size) {
        readFile.seek(startOffset+imageOffset);
        info.clear();

        if ((imageOffset+TF_MAX_SIZE) <= size) {
            info = readFile.read(TF_MAX_SIZE);
            imageOffset += TF_MAX_SIZE;
        }else {
            info = readFile.read(size-imageOffset);
            imageOffset = size;
            isEndWrite = true;
            //            if ((endTag_1 == changeChar(info.at(info.size()-2))
            //                 && endTag_2 == changeChar(info.at(info.size()-1)))) {
            //                isEndWrite = true;
            //            }
        }
        writeArray.append(info);
    }
    info.clear();

    if (isStartWrite && isEndWrite) {
        destoryImage();
        image = new QPixmap();
        image->loadFromData(writeArray);
        writeArray.clear();
        isDecodeImage = true;
        return true;
    }

    writeArray.clear();
    return false;
}

void MusicId3::clear()
{
    isDecodeV1 = false;
    isDecodeImage = false;
    m_ID3V1.clear();
    m_ID3V2.clear();
    m_TF.clear();
}

int MusicId3::changeChar(char value)
{
    if (value < 0) {
        return (0xFF - (~value));
    }

    return value;
}

void MusicId3::destoryImage()
{
    if (image != NULL) {
        delete image;
        image = NULL;
    }
}

void MusicId3::decodeTF(QByteArray &info, TaggedFrame &tf, QTextCodec *tc)
{
    tf.frameID = tc->toUnicode(trimmedArray(info.mid(0, 4)));
    //前面的byte表示高位
    tf.size = (info[4] << 24 | info[5] << 16 | info[6] << 8 | info[7]);
    tf.flags = (info[8] << 8 | info[9]);

    if (tf.size < 0) {
        tf.size = (changeChar(info[4]) << 24 | changeChar(info[5]) << 16
                                                                      | changeChar(info[6]) << 8 | changeChar(info[7]));
    }
}

void MusicId3::writeFile(QString path, QByteArray &content) {
    QFile file(path);

    //用读写方式打开文件，如果文件不存在会自动创建文件
    if(file.open(QIODevice::ReadWrite)){
        qint64 pos;
        pos = file.size();
        file.seek(pos);

        qint64 length = -1;
        length = file.write(content);
        file.close();
    }
}

void MusicId3::decodeV2(QByteArray &info, QTextCodec *tc)
{
    m_ID3V2.tag = tc->toUnicode(trimmedArray(info.mid(0, 3)));//ID3
    if (m_ID3V2.tag.compare(V2_TAG)) {//不相等, 就不是该协议
        m_ID3V2.tag = "";
        return;
    }
    m_ID3V2.version = info.at(3);
    m_ID3V2.revision = info.at(4);
    m_ID3V2.flag = info.at(5);
    m_ID3V2.size = (info[6] << 21 | info[7] << 14 | info[8] << 7 | info[9]);
}

void MusicId3::decodeV1(QByteArray &info, QTextCodec *tc)
{
    m_ID3V1.tag = tc->toUnicode(trimmedArray(info.mid(0, 3)));
    if (m_ID3V1.tag.compare(V1_TAG)) {//不相等, 就不是该协议
        m_ID3V1.tag = "";
        return;
    }

    m_ID3V1.title= tc->toUnicode(trimmedArray(info.mid(3, 30)));
    m_ID3V1.artist = tc->toUnicode(trimmedArray(info.mid(33, 30)));
    m_ID3V1.album = tc->toUnicode(trimmedArray(info.mid(63, 30)));
    //    m_ID3V1.year = tc->toUnicode(trimmedArray(info.mid(93, 4)));
    //    m_ID3V1.comment = tc->toUnicode(trimmedArray(info.mid(97, 30)));
    //    m_ID3V1.genre = info.at(127);
    isDecodeV1 = true;
}

QByteArray MusicId3::trimmedArray(QByteArray array)
{
    QByteArray data;
    int size = array.size();
    for (int i = 0; i < size; i++) {
        if (array.at(i)) {
            data.append(array.at(i));
        }
    }
    return data;
}
