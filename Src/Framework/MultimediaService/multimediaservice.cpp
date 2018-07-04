#include "multimediaservice.h"
#include "multimediautils.h"

#include "Src/Framework/MultimediaService/DeviceWatcher/devicewatcher.h"
#include "Src/Framework/MultimediaService/MusicPlayer/musicplayer.h"
#include "Src/Framework/MultimediaService/VideoPlayer/videoplayer.h"
#include "Src/Framework/MultimediaService/ImagePlayer/imageplayer.h"
#include "Src/Framework/MultimediaService/BtMusicPlayer/btmusicplayer.h"
#include <QDebug>
#include <QDomDocument>

class MultimediaServicePrivate
{
    Q_DISABLE_COPY(MultimediaServicePrivate)
public:
    explicit MultimediaServicePrivate(MultimediaService* parent);
    ~MultimediaServicePrivate();
    QString createFilesPathXml(int deviceType, int mediaType, int queryMode, QString dirPath, QStringList* pathList);
    QString queryFileList(int deviceType, int mediaType, int queryMode, QString dirPath);
    void setCurrentPlay(int mediaType);

    DeviceWatcher *mDeviceWatcher = NULL;
    MusicPlayer *mMusicPlayer = NULL;
    VideoPlayer *mVideoPlayer = NULL;
    ImagePlayer *mImagePlayer = NULL;
    BtMusicPlayer *mBtMusicPlayer = NULL;
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
    switch (mediaType) {
    case MultimediaUtils::MUSIC:
        if (MultimediaUtils::SCAN_Undefined == m_Private->mMusicPlayer->getScanStatus()) {
            m_Private->mDeviceWatcher->startScan(MultimediaUtils::DWT_USBDisk, mediaType,
                                                 m_Private->USB_ROOT_DIR);
        }else {
            m_Private->mMusicPlayer->setPlayStatus(isPlay);
        }
        break;
    case MultimediaUtils::VIDEO:
        if (MultimediaUtils::SCAN_Undefined == m_Private->mVideoPlayer->getScanStatus()) {
            m_Private->mDeviceWatcher->startScan(MultimediaUtils::DWT_USBDisk, mediaType,
                                                 m_Private->USB_ROOT_DIR);
        }else {
            m_Private->mVideoPlayer->setPlayStatus(isPlay);
        }
        break;
    case MultimediaUtils::IMAGE:
        if (MultimediaUtils::SCAN_Undefined == m_Private->mImagePlayer->getScanStatus()) {
            m_Private->mDeviceWatcher->startScan(MultimediaUtils::DWT_USBDisk, mediaType,
                                                 m_Private->USB_ROOT_DIR);
        }
        break;
    case MultimediaUtils::BT_MUSIC:
        m_Private->mBtMusicPlayer->setPlayStatus(isPlay);
        break;
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
        m_Private->mVideoPlayer->setDeviceType(deviceType);
        break;
    case MultimediaUtils::IMAGE:
        m_Private->mImagePlayer->setDeviceType(deviceType);
        break;
    case MultimediaUtils::BT_MUSIC:
        break;
    }
}

void MultimediaService::setPlayPath(const int mediaType, const int deviceType, QString filePath)
{
    setPlayDeviceType(deviceType, mediaType);
    switch (mediaType) {
    case MultimediaUtils::MUSIC:
        m_Private->mMusicPlayer->startPlay(deviceType, filePath);
        break;
    case MultimediaUtils::VIDEO:
        m_Private->mVideoPlayer->startPlay(deviceType, filePath);
        break;
    case MultimediaUtils::IMAGE:
        m_Private->mImagePlayer->startPlay(deviceType, filePath);
        break;
    case MultimediaUtils::BT_MUSIC:
        if (!filePath.compare("true")) {
            m_Private->mBtMusicPlayer->next();
        }else if (!filePath.compare("false")) {
            m_Private->mBtMusicPlayer->previous();
        }
        break;
    }
}

void MultimediaService::exitPlayer(const int mediaType)
{
    switch (mediaType) {
    case MultimediaUtils::MUSIC:
        break;
    case MultimediaUtils::VIDEO:
        break;
    case MultimediaUtils::IMAGE:
        break;
    case MultimediaUtils::BT_MUSIC:
        break;
    }
}

QString MultimediaService::queyMediaFiles(int deviceType, int mediaType, int queryMode, QString dirPath)
{
    return m_Private->queryFileList(deviceType, mediaType, queryMode, dirPath);
}

void MultimediaService::setVideoWidget(QVideoWidget *videoWidget)
{
    m_Private->mVideoPlayer->setVideoWidget(videoWidget);
}

QString MultimediaServicePrivate::queryFileList(int deviceType, int mediaType, int queryMode, QString dirPath)
{
    bool isOtherSan = false;
    switch (mediaType) {
    case MultimediaUtils::MUSIC:
        if (MultimediaUtils::SCAN_Finish == mMusicPlayer->getScanStatus()) {
            if (MultimediaUtils::QUERY_All_Files == queryMode) {
                emit m_Parent->onScanFilesPath(createFilesPathXml(deviceType, mediaType, queryMode, dirPath,
                                                                  mMusicPlayer->getPathList(deviceType)));
            }else {
                isOtherSan = true;
            }
        }
        break;
    case MultimediaUtils::VIDEO:
        if (MultimediaUtils::SCAN_Finish == mVideoPlayer->getScanStatus()) {
            if (MultimediaUtils::QUERY_All_Files == queryMode) {
                emit m_Parent->onScanFilesPath(createFilesPathXml(deviceType, mediaType, queryMode, dirPath,
                                                                  mVideoPlayer->getPathList(deviceType)));
            }else {
                isOtherSan = true;
            }
        }
        break;
    case MultimediaUtils::IMAGE:
        if (MultimediaUtils::SCAN_Finish == mImagePlayer->getScanStatus()) {
            if (MultimediaUtils::QUERY_All_Files == queryMode) {
                emit m_Parent->onScanFilesPath(createFilesPathXml(deviceType, mediaType, queryMode, dirPath,
                                                                  mImagePlayer->getPathList(deviceType)));
            }else {
                isOtherSan = true;
            }
        }
        break;
    }

    if (isOtherSan) {
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


    return "";
}

void MultimediaServicePrivate::setCurrentPlay(int mediaType)
{
    switch (mediaType) {
    case MultimediaUtils::MUSIC:
        mVideoPlayer->setPlayStatus(false);
        mBtMusicPlayer->setPlayStatus(false);
        break;
    case MultimediaUtils::VIDEO:
        mMusicPlayer->setPlayStatus(false);
        mBtMusicPlayer->setPlayStatus(false);
        break;
    case MultimediaUtils::BT_MUSIC:
        mVideoPlayer->setPlayStatus(false);
        mMusicPlayer->setPlayStatus(false);
        break;
    }
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
        m_Private->mVideoPlayer->seekTo(progress);
        if (!m_Private->mVideoPlayer->isPlaying()) {
            m_Private->mVideoPlayer->play();
        }
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
        return m_Private->mVideoPlayer->getCurrentPosition();
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
        return m_Private->mVideoPlayer->getDuration();
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
        return m_Private->mVideoPlayer->isPlaying();
    case MultimediaUtils::BT_MUSIC:
        return m_Private->mBtMusicPlayer->isPlaying();
    }
    return false;
}

void MultimediaServicePrivate::initialize()
{
    mDeviceWatcher = new DeviceWatcher();

    mMusicPlayer = new MusicPlayer();
    mMusicPlayer->setScanStatus(MultimediaUtils::SCAN_Undefined);

    mVideoPlayer = new VideoPlayer();
    mVideoPlayer->setScanStatus(MultimediaUtils::SCAN_Undefined);

    mImagePlayer = new ImagePlayer();
    mImagePlayer->setScanStatus(MultimediaUtils::SCAN_Undefined);

    mBtMusicPlayer = new BtMusicPlayer();
}

void MultimediaServicePrivate::connectAllSlots()
{
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(mDeviceWatcher, SIGNAL(onStartScanFiles(int,int)), m_Parent, SLOT(onStartScanFiles(int,int)), type);
    QObject::connect(mDeviceWatcher, SIGNAL(onMusicFilePath(int,QString)), mMusicPlayer, SLOT(scanMusicFilePath(int,QString)), type);
    QObject::connect(mDeviceWatcher, SIGNAL(onVideoFilePath(int,QString)), mVideoPlayer, SLOT(scanVideoFilePath(int,QString)), type);
    QObject::connect(mDeviceWatcher, SIGNAL(onImageFilePath(int,QString)), mImagePlayer, SLOT(scanImageFilePath(int,QString)), type);
    QObject::connect(mDeviceWatcher, SIGNAL(onScanFilesFinish(int,int,int,QString)), m_Parent, SLOT(onScanFilesFinish(int,int,int,QString)), type);

    QObject::connect(mMusicPlayer, SIGNAL(onPlay(int,int,QString&,qint64)), m_Parent, SLOT(backPlay(int,int,QString&,qint64)), type);
    QObject::connect(mMusicPlayer, SIGNAL(onResume(int)), m_Parent, SLOT(backResume(int)), type);
    QObject::connect(mMusicPlayer, SIGNAL(onPause(int)), m_Parent, SLOT(backPause(int)), type);
    QObject::connect(mMusicPlayer, SIGNAL(onFinish(int,bool)), m_Parent, SLOT(backStop(int,bool)), type);
    QObject::connect(mMusicPlayer, &MusicPlayer::onPositionChanged, m_Parent, &MultimediaService::onUpdateProgress, type);

    QObject::connect(mVideoPlayer, &VideoPlayer::onPositionChanged, m_Parent, &MultimediaService::onUpdateProgress, type);
    QObject::connect(mVideoPlayer, SIGNAL(onPlay(int,int,QString&,qint64)), m_Parent, SLOT(backPlay(int,int,QString&,qint64)), type);
    QObject::connect(mVideoPlayer, SIGNAL(onResume(int)), m_Parent, SLOT(backResume(int)), type);
    QObject::connect(mVideoPlayer, SIGNAL(onPause(int)), m_Parent, SLOT(backPause(int)), type);
    QObject::connect(mVideoPlayer, SIGNAL(onFinish(int,bool)), m_Parent, SLOT(backStop(int,bool)), type);

    QObject::connect(mBtMusicPlayer, &BtMusicPlayer::onPositionChanged, m_Parent, &MultimediaService::onUpdateProgress, type);
    QObject::connect(mBtMusicPlayer, SIGNAL(onPlay(int,int,QString&,qint64)), m_Parent, SLOT(backPlay(int,int,QString&,qint64)), type);
    QObject::connect(mBtMusicPlayer, SIGNAL(onResume(int)), m_Parent, SLOT(backResume(int)), type);
    QObject::connect(mBtMusicPlayer, SIGNAL(onPause(int)), m_Parent, SLOT(backPause(int)), type);
    QObject::connect(mBtMusicPlayer, SIGNAL(onFinish(int,bool)), m_Parent, SLOT(backStop(int,bool)), type);
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
        m_Private->mVideoPlayer->setScanStatus(MultimediaUtils::SCAN_Busy);
        setPlayDeviceType(deviceType, mediaType);
        m_Private->mVideoPlayer->clearPathList(deviceType);
        break;
    case MultimediaUtils::IMAGE:
        m_Private->mImagePlayer->setScanStatus(MultimediaUtils::SCAN_Busy);
        setPlayDeviceType(deviceType, mediaType);
        m_Private->mImagePlayer->clearPathList(deviceType);
        break;
    }
}

void MultimediaService::backPlay(int mediaType, int index, QString &path, qint64 duration)
{
    emit onPlay(mediaType, index, path, duration);
    m_Private->setCurrentPlay(mediaType);
}

void MultimediaService::backResume(const int mediaType)
{
    emit onResume(mediaType);
    m_Private->setCurrentPlay(mediaType);
}

void MultimediaService::backPause(const int mediaType)
{
    emit onPause(mediaType);
}

void MultimediaService::backStop(const int mediaType, bool isError)
{
    emit onStop(mediaType, isError);
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
        emit onScanFilesPath(m_Private->createFilesPathXml(deviceType, mediaType, queryMode, dirPath,
                                                           m_Private->mVideoPlayer->getPathList(deviceType)));
        m_Private->mVideoPlayer->setScanStatus(MultimediaUtils::SCAN_Finish);
        break;
    case MultimediaUtils::IMAGE:
        emit onScanFilesPath(m_Private->createFilesPathXml(deviceType, mediaType, queryMode, dirPath,
                                                           m_Private->mImagePlayer->getPathList(deviceType)));
        m_Private->mImagePlayer->setScanStatus(MultimediaUtils::SCAN_Finish);
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

