#include "player.h"


class PlayerPrivate {
    Q_DISABLE_COPY(PlayerPrivate)
public:
    explicit PlayerPrivate(Player *parent, int type);
    ~PlayerPrivate();


    void connectAllSlots();
    void deleteMediaPlayer();
    void startPlay(int index, QString path);
    void switchPlayStatus(bool isPlay);
    void setVideoWidget(QVideoWidget *videoWidget);

    QVideoWidget *mVideoWidget = NULL;
    QMediaPlayer *mMediaPlayer = NULL;
    int mPlayType = -1;
    qint64 mDuration = 0;
    int mCurrentIndex = -1;
    QString mPath;
    QMediaPlayer::State mCurrentStatus = QMediaPlayer::StoppedState;
    QTimer *mQTimer = NULL;
    bool isContinuePlay = false;

private:
    Player* m_Parent;

};


Player::Player(QObject *parent, int type)
    : QObject(parent)
    , m_Private(new PlayerPrivate(this, type))
{

}

PlayerPrivate::PlayerPrivate(Player *parent, int type)
    : m_Parent(parent)
{
    this->mPath = "";
    this->isContinuePlay = false;
    this->mPlayType = type;
    this->mQTimer = new QTimer(m_Parent);
    mQTimer->setSingleShot(true);//这个设置触发单次调用
    Qt::ConnectionType connectType = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(mQTimer, SIGNAL(timeout()), parent, SLOT(onTimeout()), connectType);
}


void Player::play(int index, QString path)
{
    m_Private->startPlay(index, path);
}

void PlayerPrivate::startPlay(int index, QString path) {
    mPath = path;
    isContinuePlay = true;
    mCurrentIndex = index;
    deleteMediaPlayer();
    if (NULL == mMediaPlayer) {
        mMediaPlayer = new QMediaPlayer();
        connectAllSlots();
    }

    mMediaPlayer->setMedia(QUrl::fromLocalFile(MultimediaUtils::changeWindowsPath(path)));
    if (mVideoWidget != NULL) {
        mMediaPlayer->setVideoOutput(mVideoWidget);
    }

    mMediaPlayer->play();
    mQTimer->start(500);
}

void Player::seekTo(int progress)
{
    if (m_Private->mMediaPlayer != NULL && m_Private->mCurrentStatus != QMediaPlayer::StoppedState) {
        m_Private->mMediaPlayer->setPosition((progress*m_Private->mDuration)/100);
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

void Player::setPlayStatus(bool isPlay)
{
    m_Private->switchPlayStatus(isPlay);
}

void Player::play()
{
    m_Private->switchPlayStatus(true);
}

void Player::pause()
{
    m_Private->switchPlayStatus(false);
}


void Player::setVideoWidget(QVideoWidget *videoWidget)
{
    m_Private->setVideoWidget(videoWidget);
}

void PlayerPrivate::setVideoWidget(QVideoWidget *videoWidget) {
    this->mVideoWidget = videoWidget;
}

void PlayerPrivate::connectAllSlots()
{
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(mMediaPlayer, SIGNAL(positionChanged(qint64)), m_Parent, SLOT(onUpdatePosition(qint64)), type);
    QObject::connect(mMediaPlayer, SIGNAL(audioAvailableChanged(bool)), m_Parent, SLOT(onPrepared(bool)), type);
    QObject::connect(mMediaPlayer, SIGNAL(error(QMediaPlayer::Error)), m_Parent, SLOT(onError(QMediaPlayer::Error)), type);
    QObject::connect(mMediaPlayer, SIGNAL(stateChanged(QMediaPlayer::State)), m_Parent, SLOT(onStatusChanged(QMediaPlayer::State)), type);
}


void Player::onPrepared(bool available) {
//    qDebug() << "onPrepared available = " << available;
    if (available) {
        m_Private->mCurrentStatus = QMediaPlayer::PlayingState;
        m_Private->mDuration = m_Private->mMediaPlayer->duration();
        emit onPlay(m_Private->mPlayType, m_Private->mCurrentIndex, m_Private->mPath, m_Private->mDuration);
    }
}


void Player::onError(QMediaPlayer::Error error) {
    onCompletion(true);
}

void Player::onCompletion(bool isError) {
    if (!isError && (m_Private->mCurrentStatus == QMediaPlayer::StoppedState
                     || m_Private->isContinuePlay)) {
        return;
    }

//    qDebug() << "onCompletion -----isError = " << isError;
    m_Private->mCurrentStatus = QMediaPlayer::StoppedState;
    emit onFinish(m_Private->mPlayType, isError);
}

void Player::onTimeout()
{
    m_Private->isContinuePlay = false;
}

void PlayerPrivate::switchPlayStatus(bool isPlay)
{
    if (NULL == mMediaPlayer || QMediaPlayer::StoppedState == mCurrentStatus) {
        return;
    }

    if (isPlay && QMediaPlayer::PausedState == mCurrentStatus) {
        mMediaPlayer->play();
    }else if (!isPlay && QMediaPlayer::PlayingState == mCurrentStatus) {
        mMediaPlayer->pause();
    }
}

void Player::onStatusChanged(QMediaPlayer::State status) {
//    qDebug() << "onStatusChanged status = " << status
//             << "; m_Private->mCurrentStatus = " << m_Private->mCurrentStatus;
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
        onCompletion(false);
        break;
    }

    m_Private->mCurrentStatus = status;
}



void Player::onUpdatePosition(qint64 position) {
    emit onPositionChanged(m_Private->mPlayType, position, m_Private->mDuration);
}


void PlayerPrivate::deleteMediaPlayer()
{
    if (mMediaPlayer != NULL) {
        if (mCurrentStatus != QMediaPlayer::StoppedState) {
            mMediaPlayer->stop();
        }
        delete mMediaPlayer;
        mMediaPlayer = NULL;
    }
}


PlayerPrivate::~PlayerPrivate()
{
    deleteMediaPlayer();
}

Player::~Player()
{

}


