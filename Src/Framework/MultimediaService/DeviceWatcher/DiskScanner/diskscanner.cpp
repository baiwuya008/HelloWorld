#include "diskscanner.h"
#include <QMap>
#include <QStringList>
#include "Src/Framework/MultimediaService/CustomThread/customthread.h"
#include "Src/Framework/MultimediaService/multimediautils.h"
#include <QTimer>
#include <QDebug>
#include <QDir>
#include <QFileInfoList>

class DiskScannerPrivate : public CustomThreadListener
{
    Q_DISABLE_COPY(DiskScannerPrivate)
public:
    explicit DiskScannerPrivate(DiskScanner *parent);
    ~DiskScannerPrivate();
    void scanFinish();
    void startScanThread(const int mediaType, const QString &path);
    void closeScanThread();
    void handleResults(const QString &);



    QTimer *mQTimer = NULL;
    QString mPath = NULL;
    int mMediaType = MultimediaUtils::ALL_MEDIA;
    bool isContinueScan = false;
    QMap<int, QStringList> mFilterMapList;
    int mDeviceType = MultimediaUtils::DWT_Undefined;

protected:
    void onRun() Q_DECL_OVERRIDE;
private:
    DiskScanner *m_Parent;
    CustomThread *mCustomThread = NULL;

    void initialize();
    void recursionScan(const QString& path);
    void scanFile(QFileInfo &file);
    QString changeWindowsPath(QString &filePath);

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

    qDebug() << "DiskScannerPrivate::startScanThread() ";
    isContinueScan = true;

    emit m_Parent->startScanFiles(mDeviceType, mediaType);
    if (!mQTimer->isActive()) {
        mQTimer->start();
    }
    mPath = path;
    mMediaType = mediaType;

    if (NULL == mCustomThread) {
        mCustomThread = new CustomThread();
        mCustomThread->setListener(this);
        Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
        QObject::connect(mCustomThread, SIGNAL(resultReady(QString)), m_Parent, SLOT(threadHandleResults(QString)), type);
        QObject::connect(mCustomThread, SIGNAL(onFinish()), m_Parent, SLOT(threadFinish()), type);
    }
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
    qDebug() << "DiskScannerPrivate::scanFinish() ";
    if (mCustomThread != NULL) {
        delete mCustomThread;
        mCustomThread = NULL;
    }

    emit m_Parent->scanFilesFinish(mDeviceType, mMediaType);
    isContinueScan = false;
}


void DiskScannerPrivate::handleResults(const QString &result)
{
    qDebug() << "DiskScannerPrivate::handleResults() result = " << result;
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
    recursionScan(mPath);
}

void DiskScannerPrivate::recursionScan(const QString &path)
{
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
                QString a0 = file.absoluteFilePath();
                QString aa = changeWindowsPath(a0);
                emit m_Parent->scanFilePath(mDeviceType, suffixIter.key(), aa);
            }
        }
    }else {
        QMap< int, QStringList >::iterator suffixIter =  mFilterMapList.find(mMediaType);
        if (suffixIter.value().contains(suffix)) {
            QString b0 = file.absoluteFilePath();
            QString bb = changeWindowsPath(b0);
            emit m_Parent->scanFilePath(mDeviceType, suffixIter.key(), bb);
        }
    }
}

QString DiskScannerPrivate::changeWindowsPath(QString &filePath)
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
    qDebug() << "DiskScanner::onTimeout()---------";
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
