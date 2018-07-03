#include "videoplaywidget.h"


VideoPlayWidget::VideoPlayWidget(QWidget *parent)
    : QWidget(parent)
    , d_ptr(new VideoPlayWidgetPrivate(this))
{

}

VideoPlayWidgetPrivate::VideoPlayWidgetPrivate(VideoPlayWidget *parent)
    : QObject(parent)
    , q_ptr(parent)
{
    initializeBasicWidget(parent);
}


void VideoPlayWidgetPrivate::initializeBasicWidget(QWidget *parent)
{
    initializeVideoView(parent);
    initializeProgressView(parent);
    initializeClickView(parent);

    initializeTimer();
    connectAllSlots();
}


void VideoPlayWidgetPrivate::initializeProgressView(QWidget *parent) {
    mProgressContainer = new QWidget(parent);
    mProgressContainer->setFixedSize(QSize(800, 44));
    mProgressContainer->setGeometry(0, 280, 0, 0);
    mProgressContainer->setStyleSheet("background-color:"+QString::number(0x17171a) + ";");

    mVideoProgressWidget = new MusicProgressWidget(mProgressContainer, MediaUtils::VIDEO);
    mVideoProgressWidget->setFixedSize(QSize(730, 36));
    mVideoProgressWidget->setGeometry(70, 4, 0, 0);
}

void VideoPlayWidgetPrivate::initializeClickView(QWidget *parent) {
    mVideoClickWidget = new MusicClickWidget(parent);
    mVideoClickWidget->setFixedSize(QSize(800, 60));
    mVideoClickWidget->setGeometry(0, 324, 0, 0);
}

void VideoPlayWidgetPrivate::initializeVideoView(QWidget *parent) {
    mVideoContainer = new QWidget(parent);
    mVideoContainer->setFixedSize(800, 280);
    mVideoLayout = new QVBoxLayout();
    mVideoLayout->setContentsMargins(0, 0, 0, 0);
    mVideoContainer->setLayout(mVideoLayout);

    mVideoWidget = new QVideoWidget(parent);
    mVideoWidget->setFixedSize(800, 280);
    mVideoLayout->addWidget(mVideoWidget, 0, Qt::AlignCenter);
}

void VideoPlayWidgetPrivate::initializeTimer()
{
    mQTimer = new QTimer();
    mQTimer->setSingleShot(true);//这个设置触发单次调用
    connect(mQTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

void VideoPlayWidgetPrivate::onTimeout()
{
    showFullView(true);
}

void VideoPlayWidgetPrivate::onSliderPress()
{
    showFullView(false);
}

void VideoPlayWidgetPrivate::onSliderRelease()
{
    startTimerOut(TIME_OUT);
}

void VideoPlayWidgetPrivate::stopTimerOut()
{
    if (mQTimer != NULL && mQTimer->isActive()) {
        mQTimer->stop();
    }
}

void VideoPlayWidgetPrivate::startTimerOut(int msec)
{
    stopTimerOut();
    if (mQTimer != NULL) {
        if (msec > 1) {
            mQTimer->start(msec);
        }else {
            mQTimer->start();
        }
    }
}

void VideoPlayWidgetPrivate::showFullView(bool isFull)
{
    if (isFull && !isFullShow && mVideoClickWidget->isPlaying()) {
        isFullShow = true;
        mVideoWidget->setFixedSize(800, 384);
        mVideoContainer->setFixedSize(800, 384);
        mVideoClickWidget->setVisible(false);
        mProgressContainer->setVisible(false);
    }else if (!isFull && isFullShow){
        isFullShow = false;
        mVideoContainer->setFixedSize(800, 280);
        mVideoWidget->setFixedSize(800, 280);
        mVideoClickWidget->setVisible(true);
        mProgressContainer->setVisible(true);
    }
}

void VideoPlayWidgetPrivate::connectAllSlots()
{
    connect(mVideoProgressWidget, SIGNAL(sliderMousePress()), this, SLOT(onSliderPress()));
    connect(mVideoProgressWidget, SIGNAL(sliderMouseRelease()), this, SLOT(onSliderRelease()));


    Q_Q(VideoPlayWidget);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(mVideoClickWidget, &MusicClickWidget::switchStatus, q, &VideoPlayWidget::onSwitchStatus, type);
    QObject::connect(mVideoClickWidget, &MusicClickWidget::switchIndex, q, &VideoPlayWidget::onSwitchIndex, type);
    QObject::connect(mVideoProgressWidget, &MusicProgressWidget::seekTo, q, &VideoPlayWidget::onSeekTo, type);
    QObject::connect(mVideoProgressWidget, &MusicProgressWidget::sliderSwitchStatus, q, &VideoPlayWidget::onSwitchStatus, type);
}

void VideoPlayWidgetPrivate::updatePlayStatus(bool play)
{
    if (play) {
        mVideoClickWidget->setPlayStatus(true);
        startTimerOut(TIME_OUT);
    }else {
        showFullView(false);
        mVideoClickWidget->setPlayStatus(false);
    }
}

void VideoPlayWidgetPrivate::updatePlayPath(QString path, qint64 duration)
{
    mCurrentPlayPath = path;
    updateProgress(0, duration);
    if (duration > 0) {
        updatePlayStatus(true);
    }
}

void VideoPlayWidgetPrivate::updateProgress(qint64 currentPosition, qint64 duration)
{
    mVideoProgressWidget->setProgress(currentPosition, duration);
}

void VideoPlayWidget::setPlayStatus(bool isPlay)
{
    Q_D(VideoPlayWidget);
    d->mVideoClickWidget->setPlayStatus(isPlay);
}

void VideoPlayWidget::setPlayPath(QString path, const qint64 duration)
{
    Q_D(VideoPlayWidget);
    d->updatePlayPath(path, duration);
}

void VideoPlayWidget::setProgress(const qint64 currentPosition, const qint64 duration)
{
    Q_D(VideoPlayWidget);
    d->updateProgress(currentPosition, duration);
}

QVideoWidget *VideoPlayWidget::getVideoWidget()
{
    Q_D(VideoPlayWidget);
    return d->mVideoWidget;
}

void VideoPlayWidget::resizeEvent(QResizeEvent *event)
{
    //    qDebug() << "VideoPlayWidget resizeEvent size().width() = " << event->size().width()
    //             << "; size().height() = " << event->size().height();
}

void VideoPlayWidget::mousePressEvent(QMouseEvent *event)
{
    Q_D(VideoPlayWidget);
    d->showFullView(false);
}

void VideoPlayWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_D(VideoPlayWidget);
    d->startTimerOut(d->TIME_OUT);
}



VideoPlayWidget::~VideoPlayWidget()
{

}


VideoPlayWidgetPrivate::~VideoPlayWidgetPrivate()
{

}




