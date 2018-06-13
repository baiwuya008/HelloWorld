#include "multimediaservice.h"
#include "multimediautils.h"
#include "Src/Framework/MultimediaService/DeviceWatcher/devicewatcher.h"
#include "Src/Framework/MultimediaService/MusicPlayer/musicplayer.h"
#include <QDebug>

class MultimediaServicePrivate
{
    Q_DISABLE_COPY(MultimediaServicePrivate)
public:
    explicit MultimediaServicePrivate(MultimediaService* parent);
    ~MultimediaServicePrivate();
    void initialize();
    void connectAllSlots();

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



void MultimediaService::setPlayToggle(const int mediaType)
{
    if (isYY) {
        isYY = false;
        m_Private->mDeviceWatcher->stopScan();
    }else {
        isYY = true;
        m_Private->mDeviceWatcher->startScan();
    }

}

void MultimediaService::prev(const int mediaType)
{

}

void MultimediaService::next(const int mediaType)
{

}

void MultimediaService::setPlayMode(const int mediaType, const int playMode)
{

}

int MultimediaService::getPlayMode(const int mediaType)
{
    return 0;
}

void MultimediaService::playIndex(const int mediaType, const int index)
{

}

void MultimediaService::exitPlayer(const int mediaType)
{

}

void MultimediaService::seekTo(const int mediaType, const int millesimal)
{

}

long MultimediaService::getCurrentPosition(const int mediaType)
{
    return 0;
}

long MultimediaService::getDuration(const int mediaType)
{
    return 0;
}

bool MultimediaService::isPlaying(const int mediaType)
{
    return false;
}


void MultimediaServicePrivate::initialize()
{
    mDeviceWatcher = new DeviceWatcher;
    mMusicPlayer = new MusicPlayer;
}

void MultimediaServicePrivate::connectAllSlots()
{
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(mDeviceWatcher, SIGNAL(onMusicFilePath(int,QString)), mMusicPlayer, SLOT(scanMusicFilePath(int,QString)), type);
}


MultimediaServicePrivate::~MultimediaServicePrivate()
{
}

MultimediaService::~MultimediaService() {

}
