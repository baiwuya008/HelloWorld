#include "multimedia.h"
#include "Src/Framework/MultimediaService/multimediaservice.h"
#include "Src/Application/MultiMedia/Tools/mediautils.h"
#include <QDomDocument>

class MultimediaPrivate
{
    Q_DISABLE_COPY(MultimediaPrivate)
public:
    explicit MultimediaPrivate(Multimedia* parent);
    ~MultimediaPrivate();
    void initializeProxy();
    void connectAllSlots();
    MultimediaService *mMultimediaService = NULL;
private:
    Multimedia* m_Parent;
};


Multimedia::Multimedia(QObject *parent)
    : QObject(parent)
    , m_Private(NULL)
{
    initializePrivate();
}

void Multimedia::initializePrivate()
{
    if (NULL == m_Private) {
        m_Private.reset(new MultimediaPrivate(this));
    }
}



MultimediaPrivate::MultimediaPrivate(Multimedia *parent)
    : m_Parent(parent)
{
    mMultimediaService = new MultimediaService;
    initializeProxy();
    connectAllSlots();
}

void MultimediaPrivate::initializeProxy()
{
}

void MultimediaPrivate::connectAllSlots()
{
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(mMultimediaService, &MultimediaService::onPlay, m_Parent, &Multimedia::onPlay, type);
    QObject::connect(mMultimediaService, &MultimediaService::onResume, m_Parent, &Multimedia::onResume, type);
    QObject::connect(mMultimediaService, &MultimediaService::onPause, m_Parent, &Multimedia::onPause, type);
    QObject::connect(mMultimediaService, &MultimediaService::onStop, m_Parent, &Multimedia::onStop, type);
    QObject::connect(mMultimediaService, &MultimediaService::onSetPlayMode, m_Parent, &Multimedia::onSetPlayMode, type);
    QObject::connect(mMultimediaService, &MultimediaService::onUpdateProgress, m_Parent, &Multimedia::onUpdateProgress, type);
    QObject::connect(mMultimediaService, SIGNAL(onScanFilesPath(QString)), m_Parent, SLOT(readFilesPathXml(QString)), type);
}


void Multimedia::readFilesPathXml(QString xml)
{
    QDomDocument doc;
    if (!doc.setContent(xml)) {
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

    switch (mediaType) {
    case MediaUtils::MUSIC:
        emit onScanMusicFiles(deviceType, pathList);
        break;
    case MediaUtils::VIDEO:
        emit onScanVideoFiles(deviceType, pathList);
        break;
    case MediaUtils::IMAGE:
        emit onScanImageFiles(deviceType, pathList);
        break;
    }
}

void Multimedia::setPlayStatus(const int mediaType, bool isPlay)
{
    m_Private->mMultimediaService->setPlayStatus(mediaType, isPlay);
}

void Multimedia::setPlayMode(const int mediaType, const int playMode)
{
    m_Private->mMultimediaService->setPlayMode(mediaType, playMode);
}

int Multimedia::getPlayMode(const int mediaType)
{
    return m_Private->mMultimediaService->getPlayMode(mediaType);
}

void Multimedia::setPlayIndex(const int mediaType, const int deviceType, const int index)
{
    return m_Private->mMultimediaService->setPlayIndex(mediaType, deviceType, index);
}

void Multimedia::seekTo(const int mediaType, const int msec )
{
    return m_Private->mMultimediaService->seekTo(mediaType, msec);
}

qint64 Multimedia::getCurrentPosition(const int mediaType)
{
    return m_Private->mMultimediaService->getCurrentPosition(mediaType);
}

qint64 Multimedia::getDuration(const int mediaType)
{
    return m_Private->mMultimediaService->getDuration(mediaType);
}

bool Multimedia::isPlaying(const int mediaType)
{
    return m_Private->mMultimediaService->isPlaying(mediaType);
}

void Multimedia::exitPlayer(const int mediaType)
{
    m_Private->mMultimediaService->exitPlayer(mediaType);
}

MultimediaPrivate::~MultimediaPrivate()
{
}



Multimedia::~Multimedia()
{
}
