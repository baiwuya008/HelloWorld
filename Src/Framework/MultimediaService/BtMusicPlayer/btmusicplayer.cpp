#include "btmusicplayer.h"
#include "Src/Framework/Manager/BluetoothManagerGoc.h"

class BtMusicPlayerPrivate {
    Q_DISABLE_COPY(BtMusicPlayerPrivate)
public:
    explicit BtMusicPlayerPrivate(BtMusicPlayer *parent, int type);
    ~BtMusicPlayerPrivate();
    void initialize();
    bool isBtConnect();
    bool isPlaying = false;
    bool isConnect = false;
    int mPlayType = -1;


private:
    BtMusicPlayer *m_Parent;

};

BtMusicPlayer::BtMusicPlayer(QObject *parent, int type)
    : QObject(parent)
    , m_Private(new BtMusicPlayerPrivate(this, type))
{

}

BtMusicPlayerPrivate::BtMusicPlayerPrivate(BtMusicPlayer *parent, int type)
    : m_Parent(parent)
{
    this->mPlayType = type;
    initialize();
}

void BtMusicPlayerPrivate::initialize()
{
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(gBluetoothManager, SIGNAL(callOnHfpConnected()), m_Parent, SLOT(onHfpConnected()), type);
    QObject::connect(gBluetoothManager, SIGNAL(callOnHfpDisconnected()), m_Parent, SLOT(onHfpDisconnected()), type);
    QObject::connect(gBluetoothManager, SIGNAL(callOnA2dpConnected()), m_Parent, SLOT(onA2dpConnected()), type);
    QObject::connect(gBluetoothManager, SIGNAL(callOnMusicPlaying()), m_Parent, SLOT(onResume()), type);
    QObject::connect(gBluetoothManager, SIGNAL(callOnMusicStopped()), m_Parent, SLOT(onStop()), type);
    QObject::connect(gBluetoothManager, SIGNAL(callOnVoiceConnected()), m_Parent, SLOT(onVoiceConnected()), type);
    QObject::connect(gBluetoothManager, SIGNAL(callOnVoiceDisconnected()), m_Parent, SLOT(onVoiceDisconnected()), type);
    QObject::connect(gBluetoothManager, SIGNAL(callOnMusicInfo(QString,QString,QString,int,int,int)), m_Parent, SLOT(onInfo(QString,QString,QString,int,int,int)), type);
    QObject::connect(gBluetoothManager, SIGNAL(callOnMusicPos(int,int)), m_Parent, SLOT(onPos(int,int)), type);

}



BtMusicPlayer::~BtMusicPlayer()
{

}

void BtMusicPlayer::previous()
{
    gBluetoothManager->musicPrevious();
}

void BtMusicPlayer::next()
{
    gBluetoothManager->musicNext();
}

void BtMusicPlayer::play()
{
    gBluetoothManager->musicPlay();
}

void BtMusicPlayer::pause()
{
    gBluetoothManager->musicPause();
}

void BtMusicPlayer::setPlayStatus(bool isPlay)
{
    if (isPlay) {
        play();
    }else {
        pause();
    }
}

bool BtMusicPlayer::isPlaying()
{
    return m_Private->isPlaying;
}

bool BtMusicPlayer::isConnect()
{
    return m_Private->isBtConnect();
}

bool BtMusicPlayerPrivate::isBtConnect()
{
    return isConnect;
}

void BtMusicPlayer::mute()
{
    gBluetoothManager->musicMute();
}

void BtMusicPlayer::unmute()
{
    gBluetoothManager->musicUnmute();
}


void BtMusicPlayer::getInfo()
{
    gBluetoothManager->getMusicInfo();
}

void BtMusicPlayer::gpsBackground()
{
    gBluetoothManager->musicBackground();
}

void BtMusicPlayer::gpsNormal()
{
    gBluetoothManager->musicNormal();
}

void BtMusicPlayer::onHfpConnected()
{

}

void BtMusicPlayer::onHfpDisconnected()
{

}

void BtMusicPlayer::onA2dpConnected()
{

}

void BtMusicPlayer::onA2dpDisconnected()
{

}

void BtMusicPlayer::onVoiceConnected()
{

}

void BtMusicPlayer::onVoiceDisconnected()
{

}

void BtMusicPlayer::onResume()
{
    m_Private->isPlaying = true;
    emit onResume(m_Private->mPlayType);
}

void BtMusicPlayer::onStop()
{
    m_Private->isPlaying = false;
    emit onPause(m_Private->mPlayType);
}


void BtMusicPlayer::onInfo(QString music, QString artist, QString album, int duration, int pos, int total)
{

}

void BtMusicPlayer::onPos(int current, int total)
{

}



BtMusicPlayerPrivate::~BtMusicPlayerPrivate()
{

}


