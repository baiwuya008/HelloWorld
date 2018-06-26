#include "multimediaservice.h"
#include "multimediautils.h"
#include "Src/Framework/MultimediaService/DeviceWatcher/devicewatcher.h"
#include "Src/Framework/MultimediaService/MusicPlayer/musicplayer.h"
#include <QDebug>
#include <QDomDocument>

class MultimediaServicePrivate
{
    Q_DISABLE_COPY(MultimediaServicePrivate)
public:
    explicit MultimediaServicePrivate(MultimediaService* parent);
    ~MultimediaServicePrivate();
    QString createFilesPathXml(int deviceType, int mediaType, int queryMode, QString dirPath, QStringList* pathList);
    void scanLrc(int deviceType, QString filePath);
    QString queryFileList(int deviceType, int mediaType, int queryMode, QString dirPath);

    DeviceWatcher *mDeviceWatcher = NULL;
    MusicPlayer *mMusicPlayer = NULL;
//    const QString USB_ROOT_DIR = "D:\\QT\\DA_project\\res";
    const QString USB_ROOT_DIR = "D:/QT/DA_project/res";

private:
    MultimediaService* m_Parent;
    void initialize();
    void connectAllSlots();

};

MultimediaService::MultimediaService(QObject *parent)
    : QObject(parent)
    , m_Private(new MultimediaServicePrivate(this))
{
}

MultimediaServicePrivate::MultimediaServicePrivate(MultimediaService* parent)
    : m_Parent(parent)
{
    initialize();
    connectAllSlots();
}



void MultimediaService::setPlayStatus(const int mediaType, const bool isPlay)
{
    if (MultimediaUtils::SCAN_Undefined == m_Private->mMusicPlayer->getScanStatus()) {
        m_Private->mDeviceWatcher->startScan(MultimediaUtils::DWT_USBDisk, mediaType,
                                             m_Private->USB_ROOT_DIR);
    }else {
        m_Private->mMusicPlayer->setPlayStatus(isPlay);
    }
}

void MultimediaService::setPlayMode(const int mediaType, const int playMode)
{
    switch (mediaType) {
    case MultimediaUtils::MUSIC:
        m_Private->mMusicPlayer->setMode(playMode);
        break;
    case MultimediaUtils::VIDEO:
        break;
    case MultimediaUtils::BT_MUSIC:
        break;
    }
}

int MultimediaService::getPlayMode(const int mediaType)
{
    switch (mediaType) {
    case MultimediaUtils::MUSIC:
        return m_Private->mMusicPlayer->getMode();
    case MultimediaUtils::VIDEO:
        break;
    case MultimediaUtils::BT_MUSIC:
        break;
    }

    return MultimediaUtils::LOOP;
}


void MultimediaService::setPlayDeviceType(const int deviceType, const int mediaType)
{
    switch (mediaType) {
    case MultimediaUtils::MUSIC:
        m_Private->mMusicPlayer->setDeviceType(deviceType);
        break;
    case MultimediaUtils::VIDEO:
        break;
    case MultimediaUtils::BT_MUSIC:
        break;
    }
}

void MultimediaService::setPlayPath(const int mediaType, const int deviceType, QString filePath)
{
    //    qDebug() << "MultimediaService::setPlayIndex index = " << index
    //             << "; deviceType = " << deviceType;
    switch (mediaType) {
    case MultimediaUtils::MUSIC:
        setPlayDeviceType(deviceType, mediaType);
        m_Private->mMusicPlayer->startPlay(deviceType, filePath);
        break;
    case MultimediaUtils::VIDEO:
        break;
    case MultimediaUtils::BT_MUSIC:
        break;
    }
}

void MultimediaServicePrivate::scanLrc(int deviceType, QString filePath)
{
    if (filePath.length() > 1) {
        mDeviceWatcher->scanLrc(deviceType, filePath);
    }
}


void MultimediaService::exitPlayer(const int mediaType)
{
    switch (mediaType) {
    case MultimediaUtils::MUSIC:
        break;
    case MultimediaUtils::VIDEO:
        break;
    case MultimediaUtils::BT_MUSIC:
        break;
    }
}

QString MultimediaService::queyMediaFiles(int deviceType, int mediaType, int queryMode, QString dirPath)
{
    return m_Private->queryFileList(deviceType, mediaType, queryMode, dirPath);
}

QString MultimediaServicePrivate::queryFileList(int deviceType, int mediaType, int queryMode, QString dirPath)
{
    switch (mediaType) {
    case MultimediaUtils::MUSIC:
        if (MultimediaUtils::SCAN_Finish == mMusicPlayer->getScanStatus()) {
            if (MultimediaUtils::QUERY_All_Files == queryMode) {
                emit m_Parent->onScanFilesPath(createFilesPathXml(deviceType, mediaType, queryMode, dirPath,
                                                                  mMusicPlayer->getPathList(deviceType)));
            }else {
                if (MultimediaUtils::QUERY_Main_Dir == queryMode) {
                    dirPath = USB_ROOT_DIR;
                }
                QStringList *pathList = mDeviceWatcher->queryFileList(deviceType, mediaType, dirPath);
                emit m_Parent->onScanFilesPath(createFilesPathXml(deviceType, mediaType, queryMode, dirPath, pathList));
                if (pathList != NULL) {
                    pathList->clear();
                    delete pathList;
                    pathList = NULL;
                }
            }
        }
        break;
    case MultimediaUtils::VIDEO:
        break;
    case MultimediaUtils::BT_MUSIC:
        break;
    }

    return "";
}


void MultimediaService::seekTo(const int mediaType, const int progress)
{
    switch (mediaType) {
    case MultimediaUtils::MUSIC:
        m_Private->mMusicPlayer->seekTo(progress);
        if (!m_Private->mMusicPlayer->isPlaying()) {
            m_Private->mMusicPlayer->play();
        }
        break;
    case MultimediaUtils::VIDEO:
        break;
    case MultimediaUtils::BT_MUSIC:
        break;
    }
}

qint64 MultimediaService::getCurrentPosition(const int mediaType)
{
    switch (mediaType) {
    case MultimediaUtils::MUSIC:
        return m_Private->mMusicPlayer->getCurrentPosition();
    case MultimediaUtils::VIDEO:
        break;
    case MultimediaUtils::BT_MUSIC:
        break;
    }
    return 0;
}

qint64 MultimediaService::getDuration(const int mediaType)
{
    switch (mediaType) {
    case MultimediaUtils::MUSIC:
        return m_Private->mMusicPlayer->getDuration();
    case MultimediaUtils::VIDEO:
        break;
    case MultimediaUtils::BT_MUSIC:
        break;
    }
    return 0;
}

bool MultimediaService::isPlaying(const int mediaType)
{
    switch (mediaType) {
    case MultimediaUtils::MUSIC:
        return m_Private->mMusicPlayer->isPlaying();
    case MultimediaUtils::VIDEO:
        break;
    case MultimediaUtils::BT_MUSIC:
        break;
    }
    return false;
}

void MultimediaServicePrivate::initialize()
{
    mDeviceWatcher = new DeviceWatcher();
    mMusicPlayer = new MusicPlayer();
    mMusicPlayer->setScanStatus(MultimediaUtils::SCAN_Undefined);
}

void MultimediaServicePrivate::connectAllSlots()
{
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(mDeviceWatcher, SIGNAL(onStartScanFiles(int,int)), m_Parent, SLOT(onStartScanFiles(int,int)), type);
    QObject::connect(mDeviceWatcher, SIGNAL(onMusicFilePath(int,QString)), mMusicPlayer, SLOT(scanMusicFilePath(int,QString)), type);
    QObject::connect(mDeviceWatcher, SIGNAL(onScanFilesFinish(int,int,int,QString)), m_Parent, SLOT(onScanFilesFinish(int,int,int,QString)), type);
    QObject::connect(mDeviceWatcher, &DeviceWatcher::onScanLrcInfo, m_Parent, &MultimediaService::onUpdateMusic, type);
    QObject::connect(mMusicPlayer, &MusicPlayer::onPositionChanged, m_Parent, &MultimediaService::onUpdateProgress, type);
    QObject::connect(mMusicPlayer, &MusicPlayer::onPlay, m_Parent, &MultimediaService::onPlay, type);
    QObject::connect(mMusicPlayer, &MusicPlayer::onResume, m_Parent, &MultimediaService::onResume, type);
    QObject::connect(mMusicPlayer, &MusicPlayer::onPause, m_Parent, &MultimediaService::onPause, type);
    QObject::connect(mMusicPlayer, &MusicPlayer::onFinish, m_Parent, &MultimediaService::onStop, type);
    QObject::connect(mMusicPlayer, SIGNAL(requestLrc(int,QString)), m_Parent, SLOT(onScanLrc(int,QString)), type);
}


void MultimediaService::onStartScanFiles(int deviceType, int mediaType)
{
    switch (mediaType) {
    case MultimediaUtils::ALL_MEDIA:
        break;
    case MultimediaUtils::MUSIC:
        m_Private->mMusicPlayer->setScanStatus(MultimediaUtils::SCAN_Busy);
        setPlayDeviceType(deviceType, mediaType);
        m_Private->mMusicPlayer->clearPathList(deviceType);
        break;
    case MultimediaUtils::VIDEO:
        break;
    case MultimediaUtils::IMAGE:
        break;
    }
}

void MultimediaService::onScanLrc(int deviceType, QString filePath)
{
    m_Private->scanLrc(deviceType, filePath);
}

void MultimediaService::onScanFilesFinish(int deviceType, int mediaType, int queryMode, QString dirPath)
{
    switch (mediaType) {
    case MultimediaUtils::ALL_MEDIA:
        break;
    case MultimediaUtils::MUSIC:
        emit onScanFilesPath(m_Private->createFilesPathXml(deviceType, mediaType, queryMode, dirPath,
                                                           m_Private->mMusicPlayer->getPathList(deviceType)));
        m_Private->mMusicPlayer->setScanStatus(MultimediaUtils::SCAN_Finish);
        break;
    case MultimediaUtils::VIDEO:
        break;
    case MultimediaUtils::IMAGE:
        break;
    }
}

QString MultimediaServicePrivate::createFilesPathXml(int deviceType, int mediaType, int queryMode, QString dirPath, QStringList *pathList)
{
    QDomDocument doc;
    QDomElement root = doc.createElement(QString("MediaPathList"));//创建根节点
    doc.appendChild(root);//添加根节点

    root.setAttribute("DeviceType", deviceType);//添加跟节点的属性
    root.setAttribute("MediaType", mediaType);
    root.setAttribute("QueryMode", queryMode);
    root.setAttribute("dirPath", dirPath);

    if (pathList != NULL) {
        QDomElement child;
        int size = pathList->size();
        for (int i = 0; i < size; i++) {
            child = doc.createElement(QString("Path"));
            child.appendChild(doc.createTextNode(pathList->at(i)));
            root.appendChild(child);//把子节点添加到根节点中
        }
    }

    return doc.toString();
}




MultimediaServicePrivate::~MultimediaServicePrivate()
{
}

MultimediaService::~MultimediaService() {

}





