#include "videoplaywidget.h"


VideoPlayWidget::VideoPlayWidget(QWidget *parent)
    : QWidget(parent)
    , d_ptr(new VideoPlayWidgetPrivate(this))
{

}

VideoPlayWidgetPrivate::VideoPlayWidgetPrivate(VideoPlayWidget *parent)
    : Player(parent)
    , q_ptr(parent)
{
    initializeBasicWidget(parent);
}


void VideoPlayWidgetPrivate::initializeBasicWidget(QWidget *parent)
{
    initializeVideoView(parent);
    initializeClickView(parent);
    initializeProgressView(parent);
    connectAllSlots();
}


void VideoPlayWidgetPrivate::initializeProgressView(QWidget *parent) {
    mProgressContainer = new QWidget(parent);
    mProgressContainer->setFixedSize(QSize(800, 50));
    mProgressContainer->setGeometry(0, 283, 0, 0);
    mProgressContainer->setStyleSheet("background-color:"+QString::number(0x17171a) + ";");

    mVideoProgressWidget = new MusicProgressWidget(mProgressContainer, MediaUtils::VIDEO);
    mVideoProgressWidget->setFixedSize(QSize(730, 36));
    mVideoProgressWidget->setGeometry(70, 5, 0, 0);
}

void VideoPlayWidgetPrivate::initializeClickView(QWidget *parent) {
    mVideoClickWidget = new MusicClickWidget(parent);
    mVideoClickWidget->setFixedSize(QSize(800, 60));
    mVideoClickWidget->setGeometry(0, 324, 0, 0);
}

void VideoPlayWidgetPrivate::initializeVideoView(QWidget *parent) {
    mVideoWidget = new QVideoWidget(parent);
    mVideoWidget->setFixedSize(800, 324);
    mVideoWidget->setGeometry(0, 0, 0, 0);
    setVideoWidget(mVideoWidget);
}

void VideoPlayWidgetPrivate::connectAllSlots()
{
    Q_Q(VideoPlayWidget);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(mVideoClickWidget, &MusicClickWidget::switchStatus, q, &VideoPlayWidget::onSwitchStatus, type);
    QObject::connect(mVideoClickWidget, &MusicClickWidget::switchIndex, q, &VideoPlayWidget::onSwitchIndex, type);
    QObject::connect(mVideoProgressWidget, &MusicProgressWidget::seekTo, q, &VideoPlayWidget::onSeekTo, type);
    QObject::connect(mVideoProgressWidget, &MusicProgressWidget::sliderSwitchStatus, q, &VideoPlayWidget::onSwitchStatus, type);

    connect(this, SIGNAL(onPlay(int,int,QString,qint64)), this, SLOT(backPlay(int,int,QString,qint64)));
    connect(this, SIGNAL(onResume(int)), this, SLOT(backResume(int)));
    connect(this, SIGNAL(onPause(int)), this, SLOT(backPause(int)));
    connect(this, SIGNAL(onFinish(int,bool)), this, SLOT(backFinish(int,bool)));
    connect(this, SIGNAL(onPositionChanged(int,qint64,qint64)), this, SLOT(backPositionChanged(int,qint64,qint64)));
}

void VideoPlayWidgetPrivate::updatePlayStatus(bool play)
{
    if (play) {
        mVideoClickWidget->setPlayStatus(true);
    }else {
        mVideoClickWidget->setPlayStatus(false);
    }
}

void VideoPlayWidgetPrivate::updateCurrentPlay(QString path, qint64 duration)
{
    mCurrentPlayPath = path;
    updateCurrentProgress(0, duration);
    if (duration > 0) {
        updatePlayStatus(true);
    }
}

void VideoPlayWidgetPrivate::updateCurrentProgress(qint64 currentPosition, qint64 duration)
{
    mVideoProgressWidget->setProgress(currentPosition, duration);
}

void VideoPlayWidget::setPlayStatus(bool isPlay)
{
    Q_D(VideoPlayWidget);
    d->setPlayStatus(isPlay);
}

void VideoPlayWidget::playVideo(QString path, const qint64 duration)
{
    Q_D(VideoPlayWidget);
    d->updateCurrentPlay(path, duration);
}

void VideoPlayWidget::preparedPlay(QString path, qint64 duration)
{
    Q_D(VideoPlayWidget);
    d->updateCurrentPlay(path, duration);
    d->play(0, path);
}

void VideoPlayWidget::updateProgress(const qint64 currentPosition, const qint64 duration)
{
    Q_D(VideoPlayWidget);
    d->updateCurrentProgress(currentPosition, duration);
}

void VideoPlayWidgetPrivate::backPositionChanged(int mediaType, qint64 position, qint64 duration)
{
    updateCurrentProgress(position, duration);
}

void VideoPlayWidgetPrivate::backPlay(int mediaType, int index, QString path, qint64 duration)
{
    updateCurrentPlay(path, duration);
}

void VideoPlayWidgetPrivate::backResume(int mediaType)
{
    updatePlayStatus(true);
}

void VideoPlayWidgetPrivate::backPause(int mediaType)
{
    updatePlayStatus(false);
}

void VideoPlayWidgetPrivate::backFinish(int mediaType, bool isError)
{
    updatePlayStatus(false);
    Q_Q(VideoPlayWidget);
    emit q->onBackFinish();
}

VideoPlayWidget::~VideoPlayWidget()
{

}


VideoPlayWidgetPrivate::~VideoPlayWidgetPrivate()
{

}


