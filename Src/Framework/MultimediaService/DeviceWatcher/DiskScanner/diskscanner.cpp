#include "diskscanner.h"
#include <QMap>
#include <QStringList>
#include "Src/Framework/MultimediaService/CustomThread/customthread.h"
#include "Src/Framework/MultimediaService/multimediautils.h"
#include "Src/Framework/MultimediaService/MediaDb/mediadb.h"
#include <QTimer>
#include <QDebug>
#include <QDir>
#include <QFileInfoList>
#include <QDateTime>
#include <QFile>

class DiskScannerPrivate : public CustomThreadListener
{
    Q_DISABLE_COPY(DiskScannerPrivate)
public:
    explicit DiskScannerPrivate(DiskScanner *parent);
    ~DiskScannerPrivate();
    void scanFinish();
    void startScanThread(const int mediaType, const QString &path);
    void scanLrcThread(QString &filePath, QString &scanDir, QString &scanName);
    void scanLrc();
    void decodeLrc(QString &path);
    void handleResults(const QString &);
    void createScanThread();
    void destoryScanThread();
    void closeScanThread();



    QTimer *mQTimer = NULL;
    int mMediaType = MultimediaUtils::ALL_MEDIA;
    bool isContinueScan = false;
    QMap<int, QStringList> mFilterMapList;
    int mDeviceType = MultimediaUtils::DWT_Undefined;

    QString mPath = NULL;
    QString mScanDirPath;
    QString mScanName;
    bool isScanLrc = false;

protected:
    void onRun() Q_DECL_OVERRIDE;
private:
    DiskScanner *m_Parent;
    CustomThread *mCustomThread = NULL;

    void initialize();
    void recursionScan(const QString& path);
    void scanFile(QFileInfo &file);
    void insertMediaDb(int deviceType, int mediaType, QFileInfo file);
    QString changeWindowsPath(QString filePath);

};

DiskScanner::DiskScanner(QObject *parent)
    : QObject(parent)
    , m_Private(new DiskScannerPrivate(this))
{

}

DiskScannerPrivate::DiskScannerPrivate(DiskScanner *parent) : m_Parent(parent)
{
    initialize();
}

void DiskScannerPrivate::initialize()
{
    isContinueScan = false;
    mQTimer = new QTimer(m_Parent);
    mQTimer->setSingleShot(true);//这个设置触发单次调用
    mQTimer->setInterval(3000);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(mQTimer, SIGNAL(timeout()), m_Parent, SLOT(onTimeout()), type);

}

void DiskScannerPrivate::startScanThread(const int mediaType, const QString &path)
{
    if (isContinueScan) {
        return;
    }

    isContinueScan = true;
    isScanLrc = false;
    emit m_Parent->startScanFiles(mDeviceType, mediaType);
    if (!mQTimer->isActive()) {
        mQTimer->start();
    }
    mPath = path;
    mMediaType = mediaType;
    g_MediaDb->deleteData(mDeviceType);
    createScanThread();
    mCustomThread->start();
}

void DiskScannerPrivate::createScanThread()
{
    if (NULL == mCustomThread) {
        mCustomThread = new CustomThread();
        mCustomThread->setListener(this);
        Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
        QObject::connect(mCustomThread, SIGNAL(resultReady(QString)), m_Parent, SLOT(threadHandleResults(QString)), type);
        QObject::connect(mCustomThread, SIGNAL(onFinish()), m_Parent, SLOT(threadFinish()), type);
    }
}

void DiskScannerPrivate::destoryScanThread()
{
    if (mCustomThread != NULL) {
        delete mCustomThread;
        mCustomThread = NULL;
    }
}

void DiskScannerPrivate::scanLrcThread(QString &filePath, QString &scanDir, QString &scanName)
{
    if (isContinueScan) {
        return;
    }

    isContinueScan = true;
    isScanLrc = true;
    mPath = filePath;
    mScanDirPath = scanDir;
    mScanName = scanName;
    createScanThread();
    mCustomThread->start();
}

void DiskScannerPrivate::closeScanThread()
{
    if (mCustomThread != NULL && mCustomThread->isRunning()) {
        mCustomThread->stop();
    }
}

void DiskScannerPrivate::scanFinish()
{  
    destoryScanThread();
    if (!isScanLrc) {
        emit m_Parent->scanFilesFinish(mDeviceType, mMediaType, mPath);
    }
    isContinueScan = false;
    isScanLrc = false;
    mScanName = "";
    mScanDirPath = "";
    mPath = "";
}


void DiskScannerPrivate::handleResults(const QString &result)
{
    //    qDebug() << "DiskScannerPrivate::handleResults() result = " << result;
}



void DiskScanner::threadHandleResults(const QString &result)
{
    m_Private->handleResults(result);
}

void DiskScanner::threadFinish()
{
    m_Private->scanFinish();
}

void DiskScannerPrivate::onRun()
{
    if (isScanLrc) {
        scanLrc();
    }else {
        recursionScan(mPath);
    }
}


void DiskScannerPrivate::scanLrc()
{
    if (mScanDirPath.length() < 1) {
        return;
    }

    QDir dir(mScanDirPath);
    if (!dir.exists()) {
        return;
    }
    dir.setFilter(QDir::AllEntries|QDir::NoDotAndDotDot);
    QFileInfoList dirList = dir.entryInfoList();
    int size = dirList.size();
    QFileInfo file;
    QString suffix;
    QString name;
    for (int i = 0; i < size; i++) {
        file = dirList.at(i);
        suffix = file.suffix().toUpper().toLocal8Bit().data();
        name = file.baseName().toLocal8Bit().data();
        if (file.isFile() && !suffix.compare("LRC") && name.compare(mScanName)) {
            decodeLrc(file.absoluteFilePath());
            break;
        }
    }
}

void DiskScannerPrivate::decodeLrc(QString &path)
{
    QFile file(path);
    if(file.open(QIODevice::ReadOnly)){
        QString title = "[ti:";//歌曲名
        QString artist = "[ar:";//歌手名
        QString album = "[al:";//专辑名

        QTextStream stream(&file);
        int readLineNumber = 0;
        int readIndex = 0;
        QString data;
        while (!stream.atEnd() ) {
            data = stream.readLine().toUtf8();
            if (0 == readLineNumber && data.contains(title)) {
                title = data.mid(title.length());
                title = title.left(title.length()-1);
                readIndex++;
            }else if (1 == readLineNumber && data.contains(artist)) {
                artist = data.mid(artist.length());
                artist = artist.left(artist.length()-1);
                readIndex++;
            }else if (2 == readLineNumber && data.contains(album)) {
                album = data.mid(album.length());
                album = album.left(album.length()-1);
                readIndex++;
            }

            if (readLineNumber >= 3) {
                break;
            }
            readLineNumber++;
        }
        file.close();

        if (readIndex >= 3) {
            emit m_Parent->scanLrcInfo(mPath, title, artist, album);
        }
    }
}

void DiskScannerPrivate::recursionScan(const QString &path)
{
    if (path.length() < 1) {
        return;
    }

    QDir dir(path);
    if (!dir.exists()) {
        return;
    }

    dir.setFilter(QDir::AllEntries|QDir::NoDotAndDotDot);
    //     dir.setSorting(QDir::Time);
    QFileInfoList dirList = dir.entryInfoList();
    int size = dirList.size();
    QFileInfo file;
    for (int i = 0; i < size; i++) {
        file = dirList.at(i);
        if (file.isFile()) {
            scanFile(file);
        }else if (file.isDir()) {
            recursionScan(file.absoluteFilePath());
        }
    }
}

void DiskScannerPrivate::scanFile(QFileInfo &file)
{
    QString suffix = ("."+file.suffix().toUpper()).toLocal8Bit().data();
    if (mMediaType == MultimediaUtils::ALL_MEDIA) {
        for (QMap< int, QStringList >::iterator suffixIter = mFilterMapList.begin();
             suffixIter != mFilterMapList.end(); suffixIter++) {
            if (suffixIter.value().contains(suffix)) {
                insertMediaDb(mDeviceType, suffixIter.key(), file);
                emit m_Parent->scanFilePath(mDeviceType, suffixIter.key(), changeWindowsPath(file.absoluteFilePath()));
            }
        }
    }else {
        QMap< int, QStringList >::iterator suffixIter =  mFilterMapList.find(mMediaType);
        if (suffixIter.value().contains(suffix)) {
            insertMediaDb(mDeviceType, suffixIter.key(), file);
            emit m_Parent->scanFilePath(mDeviceType, suffixIter.key(), changeWindowsPath(file.absoluteFilePath()));
        }
    }
}

void DiskScannerPrivate::insertMediaDb(int deviceType, int mediaType, QFileInfo file)
{
    g_MediaDb->insert(deviceType, mediaType, file);
}

QString DiskScannerPrivate::changeWindowsPath(QString filePath)
{
    QStringList list = filePath.split("/");
    QString path;
    int size = list.size();
    for (int i = 0; i < size; i++) {
        if (i == size-1) {
            path.append(list.at(i));
        }else {
            path.append(list.at(i)+"\\");
        }
    }

    return path;
}

void DiskScanner::setScannerSuffixMap(const QMap<int, QStringList> &mapList)
{
    m_Private->mFilterMapList = mapList;
}

void DiskScanner::onTimeout()
{
    //    if (!m_Private->mCustomThread->isRunning()) {
    //        m_Private->scanFinish();
    //    }
}

void DiskScanner::setMinimumScanTime(const int msec)
{
    m_Private->mQTimer->setInterval(msec);
}

void DiskScanner::startScanner(const int mediaType, const QString &path)
{
    m_Private->startScanThread(mediaType, path);
}

void DiskScanner::stopScanner()
{
    m_Private->mPath.clear();
    if (m_Private->mQTimer->isActive()) {
        m_Private->mQTimer->stop();
    }
    m_Private->closeScanThread();
}

void DiskScanner::scanLrc(QString filePath, QString scanDir, QString scanName)
{
    m_Private->scanLrcThread(filePath, scanDir, scanName);
}

void DiskScanner::setDeviceType(int deviceType)
{
    m_Private->mDeviceType = deviceType;
}

DiskScannerPrivate::~DiskScannerPrivate()
{

}

DiskScanner::~DiskScanner()
{

}
