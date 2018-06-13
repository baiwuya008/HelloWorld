#include "videoplaywidget.h"
#include "Src/Application/MultiMedia/Music/musicclickwidget.h"
#include "Src/Application/MultiMedia/Music/musicprogresswidget.h"
#include <QDebug>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>

class VideoPlayWidgetPrivate {
    Q_DISABLE_COPY(VideoPlayWidgetPrivate)
public:
    explicit VideoPlayWidgetPrivate(VideoPlayWidget *parent);
    ~VideoPlayWidgetPrivate();
private slots:
    void onPlay();
    void onPause();
private:
    Q_DECLARE_PUBLIC(VideoPlayWidget)
    VideoPlayWidget* const q_ptr;
    void initializeBasicWidget(QWidget *parent);
    void initializeClickView(QWidget *parent);
    void initializeProgressView(QWidget *parent);
    void initializeVideoView(QWidget *parent);
    void playVideo();


    QMediaPlayer *player = NULL;
    QMediaPlaylist *playlist = NULL;
    QVideoWidget *videoWidget = NULL;
};


VideoPlayWidget::VideoPlayWidget(QWidget *parent)
    : QWidget(parent)
    , d_ptr(new VideoPlayWidgetPrivate(this))
{

}

VideoPlayWidgetPrivate::VideoPlayWidgetPrivate(VideoPlayWidget *parent)
    : q_ptr(parent)
{
    initializeBasicWidget(parent);
}


void VideoPlayWidgetPrivate::initializeBasicWidget(QWidget *parent)
{
    initializeVideoView(parent);
    initializeClickView(parent);
    initializeProgressView(parent);
}


void VideoPlayWidgetPrivate::initializeProgressView(QWidget *parent) {
    MusicProgressWidget *mMusicProgressWidget = new MusicProgressWidget(parent, MediaUtils::VIDEO);
    mMusicProgressWidget->setFixedSize(QSize(730, 36));
    mMusicProgressWidget->setGeometry(75, 283, 0, 0);
}

void VideoPlayWidgetPrivate::initializeVideoView(QWidget *parent)
{
//    player = new QMediaPlayer;
////    player->setMedia(QUrl::fromLocalFile(QStringLiteral("D:\\QT\\media\\video_2.avi")));
//     player->setMedia(QUrl::fromLocalFile(QStringLiteral("D:\\QT\\media\\video_4.mp4")));



//    videoWidget = new QVideoWidget(parent);
//    videoWidget->setFixedSize(QSize(800, 285));
//    videoWidget->setGeometry(50, 0, 0, 0);
//    player->setVideoOutput(videoWidget);
}

void VideoPlayWidgetPrivate::playVideo()
{
//    player->play();
}


void VideoPlayWidgetPrivate::initializeClickView(QWidget *parent) {
    MusicClickWidget *mMusicClickWidget = new MusicClickWidget(parent);
    mMusicClickWidget->setFixedSize(QSize(800, 60));
    mMusicClickWidget->setGeometry(0, 324, 0, 0);


    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(mMusicClickWidget, SIGNAL(changeStatus(bool)), parent, SLOT(onSwitchStatus(bool)), type);
    QObject::connect(mMusicClickWidget, SIGNAL(switchIndex(bool)), parent, SLOT(onSwitchIndex(bool)), type);
}



void VideoPlayWidget::onSwitchIndex(bool isNext)
{
    qDebug() << "VideoPlayWidget onSwitchIndex = " << isNext;
}

void VideoPlayWidget::onSwitchStatus(bool isPlay)
{
    qDebug() << "VideoPlayWidget onSwitchStatus = " << isPlay;
    Q_D(VideoPlayWidget);
    if (isPlay) {
        d->onPlay();
    }else {
        d->onPause();
    }
}

void VideoPlayWidgetPrivate::onPlay()
{
    playVideo();
}

void VideoPlayWidgetPrivate::onPause()
{

}




VideoPlayWidget::~VideoPlayWidget()
{

}


VideoPlayWidgetPrivate::~VideoPlayWidgetPrivate()
{

}
