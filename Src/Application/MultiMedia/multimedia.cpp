#include "multimedia.h"
#include "Src/Framework/MultimediaService/multimediaservice.h"

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
    QObject::connect(mMultimediaService, SIGNAL(onPlay(int, int, QString, long)), m_Parent, SLOT(onPlayT(int, int, QString, long)), type);
    QObject::connect(mMultimediaService, SIGNAL(onResume(int)), m_Parent, SLOT(onResumeT(int)), type);
}


void Multimedia::setPlayToggle(const int mediaType)
{
    qDebug() << "setPlayToggle mediaType = " << mediaType;
     m_Private->mMultimediaService->setPlayToggle(mediaType);
}

void Multimedia::prev(const int mediaType)
{

}

void Multimedia::next(const int mediaType)
{

}

void Multimedia::setPlayMode(const int mediaType, const int playMode)
{

}

int Multimedia::getPlayMode(const int mediaType)
{
    return 0;
}

void Multimedia::playIndex(const int mediaType, const int index)
{

}

void Multimedia::exitPlayer(const int mediaType)
{

}

void Multimedia::seekTo(const int mediaType, const int millesimal)
{

}

long Multimedia::getCurrentPosition(const int mediaType)
{
    return 0;
}

long Multimedia::getDuration(const int mediaType)
{
    return 0;
}

bool Multimedia::isPlaying(const int mediaType)
{
    return false;
}

void Multimedia::onPlayT(const int mediaType, const int index, const QString &fileName, const long endTime)
{
    emit onPlay(mediaType, index, fileName, endTime);
}

void Multimedia::onUpdateMusicT(const int mediaType, const QString &title, const QString &artist, const QString &album)
{
    emit onUpdateMusic(mediaType, title, artist, album);
}

void Multimedia::onResumeT(const int mediaType)
{
    emit onResume(mediaType);
}

void Multimedia::onPauseT(const int mediaType)
{
    emit onPause(mediaType);
}

void Multimedia::onStopT(const int mediaType)
{
    emit onStop(mediaType);
}

void Multimedia::onSetPlayModeT(const int mediaType, const int playMode)
{
    emit onSetPlayMode(mediaType, playMode);
}

void Multimedia::onUpdateProgressT(const int mediaType, const long currentPosition, const long duration)
{
    emit onUpdateProgress(mediaType, currentPosition, duration);
}



MultimediaPrivate::~MultimediaPrivate()
{
}



Multimedia::~Multimedia()
{
}
