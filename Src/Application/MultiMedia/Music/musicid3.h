#ifndef MUSICID3_H
#define MUSICID3_H

#include <QString>
#include <QByteArray>
#include <QTextCodec>
#include <QDebug>
#include <QFile>
#include <QPixmap>

/**
 * MP3音乐文件的内容信息
 */
class MusicId3
{
public:
    MusicId3();
    ~MusicId3();

    struct ID3V1 {//解析歌曲详细信息
        ID3V1 () {}

        QString tag;//标记TAG ：char[3] 3个字节
        QString title;//歌曲名称 ：char[30] 30个字节
        QString artist;//作者  ：char[30] 30个字节
        QString album;//专辑名称 ：char[30] 30个字节
        QString year;//出品年代 : char[4]   4个字节
        QString comment;//备注  ：char[30] 30个字节
        int genre = 0;//歌曲类型--流派 : char[1] 1个字节：genre: 0="Blues";

        inline void clear() {
            tag = "";
            title = "";
            artist = "";
            album = "";
            year = "";
            comment = "";
            genre = 0;
        }

    } m_ID3V1;


    struct ID3V2 {
        ID3V2 () {}

        QString tag;//标记TAG char[3] 3个字节 :  /*必须为"ID3"否则认为标签不存在*/
        int version = 0; //版本号： char[1] 1个字节   /*版本号;ID3V2.3就记录03,ID3V2.4就记录04*/
        int revision = 0; //副版本号：char[1] 1个字节  /*副版本号;此版本记录为00*/
        int flag = 0;    //标志字节一般为0 : char[1] 1个字节 /*存放标志的字节，这个版本只定义了三位*/
        int size = 0;  // 标签的大小 : char[4] 4个字节：/*标签大小，包括标签帧和标签头。（不包括扩展标签头的10个字节）*/

        inline void clear() {
            tag = "";
            version = 0;
            revision = 0;
            flag = 0;
            size = 0;
        }
    } m_ID3V2;

    struct TaggedFrame
    {
        TaggedFrame() {}

        QString frameID; //  char[4]:占用4个字节  /*用四个字符标识一个帧 以T开头的字符串*/
        int size = 0;  //  char[4]: 占用4个字节   /*帧内容的大小，不包括帧头，不得小于1*/
        int flags = 0;   // char[2]: 占用2个字节  /*存放标志，只定义了6位，另外的10位为0，但大部分的情况下16位都为0就可以了*/
        int textEncode = 0;//char[1]: 占用1个字节：
        QString content; // 后面是内容：不确定长度根据size来确定 从byte[11] 第12位开始：


        inline void clear() {
            frameID = "";
            size = 0;
            flags = 0;
            textEncode = 0;
            content = "";
        }
    } m_TF;


    void decodeMusic(QString path);
    void destoryImage();
    void clear();
    QPixmap *image = NULL;
    bool isDecodeV1 = false;
    bool isDecodeImage = false;
private:
    QByteArray trimmedArray(QByteArray &array);
    void writeFile(QString path, QByteArray &content);
    int changeChar(char value);

    void decodeV2(QByteArray& info, QTextCodec *tc);
    void decodeV1(QByteArray& info, QTextCodec *tc);
    bool deocdeImage(QTextCodec *tc, QFile &readFile, QByteArray &info,
                     int startOffset, int size);
    void decodeTF(QByteArray& info, TaggedFrame &tf, QTextCodec *tc);

    const QString V1_TAG = "TAG";
    const QString V2_TAG = "ID3";
    const int V1_SIZE = 128;
    const int V2_SIZE = 10;
    const int TF_HEADER_SIZE = 10;
    const int TF_MAX_SIZE = 1024;

    const QString TF_JPEG = "image/jpeg";
    const QString TF_PNG = "image/png";


    const QString TF_TXXX = "TXXX";
    const QString TF_TALB = "TALB";//专辑
    const QString TF_TRCK = "TRCK";
    const QString TF_TPOS = "TPOS";
    const QString TF_TPE1 = "TPE1";//作者
    const QString TF_TIT2 = "TIT2";//标题
    const QString TF_TCON = "TCON";//流派
    const QString TF_TYER = "TYER";
    const QString TF_COMM = "COMM";
    const QString TF_APIC = "APIC";//图片资源
};



#endif // MUSICID3_H
