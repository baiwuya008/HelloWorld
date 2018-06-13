#include "player.h"


class PlayerPrivate {
    Q_DISABLE_COPY(PlayerPrivate)
public:
    explicit PlayerPrivate(Player *parent, MultimediaType type);
    ~PlayerPrivate();


    void connectAllSlots();
    void deleteMediaPlayer();
    void startPlay(QString path);

    QMediaPlayer *mMediaPlayer = NULL;
    MultimediaType mPlayType;
    qint64 mDuration = 0;
    QMediaPlayer::State mCurrentStatus = QMediaPlayer::StoppedState;
    QString mPath;

private:
    Player* m_Parent;

};


Player::Player(QObject *parent, MultimediaType type)
    : QObject(parent)
    , m_Private(new PlayerPrivate(this, type))
{

}

PlayerPrivate::PlayerPrivate(Player *parent, MultimediaType type)
    : m_Parent(parent)
{
    this->mPlayType = type;
}


void Player::play(QString path)
{
    m_Private->startPlay(path);
}

void PlayerPrivate::startPlay(QString path) {
    deleteMediaPlayer();
    mPath = path;
    mMediaPlayer = new QMediaPlayer;
    connectAllSlots();
    mMediaPlayer->setMedia(QUrl::fromLocalFile(path));
    mMediaPlayer->play();
}


void Player::play()
{
    if (m_Private->mMediaPlayer != NULL) {
        m_Private->mMediaPlayer->play();
    }
}

void Player::pause()
{
    if (m_Private->mMediaPlayer != NULL) {
        m_Private->mMediaPlayer->pause();
    }
}

void Player::seekTo(int position)
{
    if (m_Private->mMediaPlayer != NULL && m_Private->mCurrentStatus != QMediaPlayer::StoppedState) {
        m_Private->mMediaPlayer->setPosition((position*m_Private->mDuration)/100);
    }
}

qint64 Player::getCurrentPosition()
{
    if (m_Private->mMediaPlayer != NULL && m_Private->mCurrentStatus != QMediaPlayer::StoppedState) {
        return m_Private->mMediaPlayer->position();
    }

    return 0;
}

qint64 Player::getDuration()
{
    return m_Private->mDuration;

}

bool Player::isPlaying()
{
    if (QMediaPlayer::PlayingState == m_Private->mCurrentStatus) {
        return true;
    }

    return false;
}

void PlayerPrivate::connectAllSlots()
{
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(mMediaPlayer, SIGNAL(positionChanged(qint64)), m_Parent, SLOT(onPositionChanged(qint64)), type);
    QObject::connect(mMediaPlayer, SIGNAL(audioAvailableChanged(bool)), m_Parent, SLOT(onPrepared(bool)), type);
    QObject::connect(mMediaPlayer, SIGNAL(error(QMediaPlayer::Error)), m_Parent, SLOT(onError(QMediaPlayer::Error)), type);
    QObject::connect(mMediaPlayer, SIGNAL(stateChanged(QMediaPlayer::State)), m_Parent, SLOT(onStatusChanged(QMediaPlayer::State)), type);
}


void Player::onPrepared(bool available) {
    qDebug() << "onPrepared available = " << available;
    if (available) {
        m_Private->mCurrentStatus = QMediaPlayer::PlayingState;
        m_Private->mDuration = m_Private->mMediaPlayer->duration();
        emit onPlay(m_Private->mPlayType, m_Private->mPath, m_Private->mDuration);
    }
}


void Player::onError(QMediaPlayer::Error error) {
    qDebug() << "onError -----error = " << error;
    m_Private->mCurrentStatus = QMediaPlayer::StoppedState;
    emit onFinish(m_Private->mPlayType, true);
}

void Player::onCompletion() {
    qDebug() << "onCompletion -----";
    m_Private->mCurrentStatus = QMediaPlayer::StoppedState;
    emit onFinish(m_Private->mPlayType, false);
}

void Player::onStatusChanged(QMediaPlayer::State status) {
    qDebug() << "onStatusChanged status = " << status;
    switch (status) {
    case QMediaPlayer::PlayingState:
        if (m_Private->mCurrentStatus != QMediaPlayer::StoppedState) {
            emit onResume(m_Private->mPlayType);
        }
        break;
    case QMediaPlayer::PausedState:
        emit onPause(m_Private->mPlayType);
        break;
    case QMediaPlayer::StoppedState:
        break;
    }

    m_Private->mCurrentStatus = status;
}

void Player::onPositionChanged(qint64 position) {
    qDebug() << "onPositionChanged position = " << position;
    emit onPositionChanged(m_Private->mPlayType, m_Private->mDuration, position);
}


QString Player::changeDuration(qint64 duration) {
    duration = duration / 1000;// 转换成秒

    int minute = (int) (duration / 60);
    int sec = (int) (duration % 60);
    QString seconds;
    QString min;
    if (sec < 10) {
        seconds = "0" + QString::number(sec);
    } else {
        seconds = "" + QString::number(sec);
    }

    if (minute < 10) {
        min = "0" + QString::number(minute);
    } else {
        min = "" + QString::number(minute);
    }

    return min + ":" + seconds;
}

void PlayerPrivate::deleteMediaPlayer()
{
    if (mMediaPlayer != NULL) {
        if (mMediaPlayer->isAvailable()) {
            mMediaPlayer->stop();
        }
        delete mMediaPlayer;
        mMediaPlayer = NULL;
    }
}

PlayerPrivate::~PlayerPrivate()
{

}





Player::~Player()
{

}


