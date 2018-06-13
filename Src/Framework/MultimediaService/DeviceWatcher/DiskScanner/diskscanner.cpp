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
    void initialize();
    void scanFinish();
    void startScanThread();
    void closeScanThread();
    void handleResults(const QString &);
    void recursionScan(const QString& path);
    void scanFile(QFileInfo &file);

    QTimer *mQTimer = NULL;
    QString mPath = NULL;
    bool isContinueScan = false;
    QMap<int, QStringList> mFilterMapList;
    int mDeviceType = MultimediaUtils::DWT_Undefined;

protected:
    void onRun() Q_DECL_OVERRIDE;
private:
    DiskScanner *m_Parent;
    CustomThread *mCustomThread = NULL;
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

void DiskScannerPrivate::startScanThread()
{
    if (isContinueScan) {
        return;
    }

    qDebug() << "DiskScannerPrivate::startScanThread() ";
    isContinueScan = true;
    if (NULL == mCustomThread) {
        mCustomThread = new CustomThread;
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
    isContinueScan = false;
    if (mCustomThread != NULL) {
        delete mCustomThread;
        mCustomThread = NULL;
    }
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
    for (QMap< int, QStringList >::iterator suffixIter = mFilterMapList.begin();
         suffixIter != mFilterMapList.end(); suffixIter++) {
        if (suffixIter.value().contains(suffix)) {
            emit m_Parent->scanFilePath(mDeviceType, suffixIter.key(), file.absoluteFilePath());
        }
    }
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

void DiskScanner::startScanner(const QString &path)
{
    if (!m_Private->mQTimer->isActive()) {
        m_Private->mQTimer->start();
    }
    m_Private->mPath = path;
    m_Private->startScanThread();
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
