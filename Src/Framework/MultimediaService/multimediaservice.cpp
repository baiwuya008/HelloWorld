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
    void initialize();
    void connectAllSlots();

    QString createFilesPathXml(int deviceType, int mediaType, QStringList* pathList);
    void readFilesPathXml(QString& data);

    DeviceWatcher *mDeviceWatcher = NULL;
    MusicPlayer *mMusicPlayer = NULL;

private:
    MultimediaService* m_Parent;

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
    if (m_Private->mMusicPlayer->isNullData()) {
        m_Private->mDeviceWatcher->startScan(MultimediaUtils::DWT_USBDisk, mediaType);
    }else {
        m_Private->mMusicPlayer->setPlayStatus(isPlay);
    }
}

void MultimediaService::setPlayMode(const int mediaType, const int playMode)
{
}

int MultimediaService::getPlayMode(const int mediaType)
{
    return 0;
}

void MultimediaService::setPlayIndex(const int mediaType, const int deviceType, const int index)
{
    qDebug() << "MultimediaService::setPlayIndex index = " << index
             << "; deviceType = " << deviceType;
    switch (mediaType) {
    case MultimediaUtils::MUSIC:
        m_Private->mMusicPlayer->startPlay(deviceType, index);
        break;
    case MultimediaUtils::VIDEO:
        break;
    case MultimediaUtils::BT_MUSIC:
        break;
    }
}

void MultimediaService::exitPlayer(const int mediaType)
{

}

void MultimediaService::seekTo(const int mediaType, const int msec)
{

}

qint64 MultimediaService::getCurrentPosition(const int mediaType)
{
    return 0;
}

qint64 MultimediaService::getDuration(const int mediaType)
{
    return 0;
}

bool MultimediaService::isPlaying(const int mediaType)
{
    return false;
}

void MultimediaServicePrivate::initialize()
{
    mDeviceWatcher = new DeviceWatcher();
    mMusicPlayer = new MusicPlayer();
}

void MultimediaServicePrivate::connectAllSlots()
{
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(mDeviceWatcher, SIGNAL(onMusicFilePath(int,QString)), mMusicPlayer, SLOT(scanMusicFilePath(int,QString)), type);
    QObject::connect(mDeviceWatcher, SIGNAL(onScanFilesFinish(int,int)), m_Parent, SLOT(onScanFilesFinish(int,int)), type);
    QObject::connect(mMusicPlayer, &MusicPlayer::onPositionChanged, m_Parent, &MultimediaService::onUpdateProgress, type);
    QObject::connect(mMusicPlayer, &MusicPlayer::onPlay, m_Parent, &MultimediaService::onPlay, type);
    QObject::connect(mMusicPlayer, &MusicPlayer::onResume, m_Parent, &MultimediaService::onResume, type);
    QObject::connect(mMusicPlayer, &MusicPlayer::onPause, m_Parent, &MultimediaService::onPause, type);
}


void MultimediaService::onStartScanFiles(int deviceType, int mediaType)
{
    qDebug() << "MultimediaService::onStartScanFiles deviceType = " << deviceType
             << "; mediaType = " << mediaType;
    switch (mediaType) {
    case MultimediaUtils::ALL_MEDIA:
        break;
    case MultimediaUtils::MUSIC:
        m_Private->mMusicPlayer->clearPathList(deviceType);
        break;
    case MultimediaUtils::VIDEO:
        break;
    case MultimediaUtils::IMAGE:
        break;
    }
}

void MultimediaService::onScanFilesFinish(int deviceType, int mediaType)
{
    qDebug() << "MultimediaService::onScanFilesFinish deviceType = " << deviceType
             << "; mediaType = " << mediaType;
    switch (mediaType) {
    case MultimediaUtils::ALL_MEDIA:
        break;
    case MultimediaUtils::MUSIC:
        emit onScanFilesPath(m_Private->createFilesPathXml(deviceType, mediaType,
                                                           m_Private->mMusicPlayer->getPathList(deviceType)));
        break;
    case MultimediaUtils::VIDEO:
        break;
    case MultimediaUtils::IMAGE:
        break;
    }
}

QString MultimediaServicePrivate::createFilesPathXml(int deviceType, int mediaType, QStringList *pathList)
{
    QDomDocument doc;
    QDomElement root = doc.createElement(QString("MediaPathList"));//创建根节点
    doc.appendChild(root);//添加根节点

    root.setAttribute("DeviceType", deviceType);//添加跟节点的属性
    root.setAttribute("MediaType", mediaType);

    QDomElement child;
    int size = pathList->size();
    for (int i = 0; i < size; i++) {
        child = doc.createElement(QString("Path"));
        child.appendChild(doc.createTextNode(pathList->at(i)));
        root.appendChild(child);//把子节点添加到根节点中
    }

    return doc.toString();
}

void MultimediaServicePrivate::readFilesPathXml(QString& data)
{
    QDomDocument doc;
    if (!doc.setContent(data)) {
        return;
    }

    QDomElement root = doc.documentElement();
    if (root.tagName().compare("MediaPathList")) {
        return;
    }

    int deviceType = root.attribute("DeviceType").toInt();
    int mediaType = root.attribute("MediaType").toInt();
    if (-1 == deviceType || -1 == mediaType) {
        return;
    }


    QStringList pathList;
    QDomNode n = root.firstChild();
    while(!n.isNull()) {
        QDomElement e = n.toElement();
        if(!e.isNull() && !e.tagName().compare("Path")) {
            pathList.append(e.text());
        }
        n = n.nextSibling();
    }
}


MultimediaServicePrivate::~MultimediaServicePrivate()
{
}

MultimediaService::~MultimediaService() {

}


