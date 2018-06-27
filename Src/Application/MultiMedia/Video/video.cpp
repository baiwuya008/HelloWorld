#include "video.h"


VideoPrivate::VideoPrivate(Video *parent)
    : QObject(),q_ptr(parent)
{
    mBackground = NULL;
    mBtnTest = NULL;
}

void VideoPrivate::initializeBasicWidget(QWidget *parent)
{
    MediaUtils::setWidgetBackground(parent, ":/img/Common/img_wap_bg.png");
    mStackedWidget = new QStackedWidget(parent);
    mStackedWidget->setFixedSize(QSize(800, 435));
    mStackedWidget->setGeometry(0, 50, 0, 0);

    initializeToolsWidget(parent);
    initializeVideoPlay(parent);
    initializeVideoList(parent);
    connectAllSlots();

    setCurrentPageView(0);
}

void VideoPrivate::setCurrentPageView(int tabIndex) {
    mStackedWidget->setCurrentIndex(tabIndex);
}

void VideoPrivate::setPlayItem(int deviceType, QString filePath)
{
    mVideoPlayWidget->preparedPlay(filePath, 0);
    g_Multimedia->setPlayPath(MediaUtils::VIDEO, deviceType, filePath);
}

void VideoPrivate::setPlayStatus(bool isPlay)
{
    mVideoPlayWidget->setPlayStatus(isPlay);
    g_Multimedia->setPlayStatus(MediaUtils::VIDEO, isPlay);
}

void VideoPrivate::setPlayIndex(bool isNext)
{
    mVideoListWidget->setPlayNext(isNext);
}

void VideoPrivate::setPlaySeek(int progress)
{
    g_Multimedia->seekTo(MediaUtils::VIDEO, progress);
}

void VideoPrivate::playVideo(const int mediaType, const int index, const QString &filePath, const qint64 duration)
{
    if (mediaType != MediaUtils::VIDEO) {
        return;
    }

    mVideoListWidget->refreshItem(index);
    mVideoPlayWidget->playVideo(filePath, duration);
}

void VideoPrivate::pauseVideo(const int mediaType)
{
    if (mediaType != MediaUtils::VIDEO) {
        return;
    }

    mVideoPlayWidget->setPlayStatus(false);
}

void VideoPrivate::resumeVideo(const int mediaType)
{
    if (mediaType != MediaUtils::VIDEO) {
        return;
    }
    mVideoPlayWidget->setPlayStatus(true);
}

void VideoPrivate::stopVideo(const int mediaType, bool isError)
{
    if (mediaType != MediaUtils::VIDEO) {
        return;
    }

    mVideoPlayWidget->setPlayStatus(false);
}

void VideoPrivate::updateProgress(const int mediaType, const qint64 currentPosition, const qint64 duration)
{
    if (mediaType != MediaUtils::VIDEO) {
        return;
    }
    mVideoPlayWidget->updateProgress(currentPosition, duration);
}

void VideoPrivate::scanVideoFiles(int deviceType, int queryMode, QString dirPath, QStringList &pathList)
{
    this->mCurrentDeviceType = deviceType;
    mVideoListWidget->updateList(deviceType, queryMode, dirPath, pathList);
}

void VideoPrivate::backFinish()
{

}


void VideoPrivate::initializeToolsWidget(QWidget *parent) {
    QList<QString> list;
    list.append("视频");
    list.append("列表");
    mMediaToolsWidget = new MediaToolsWidget(parent, list);
    connect(mMediaToolsWidget, SIGNAL(onItemClick(int)), this, SLOT(setCurrentPageView(int)));
}

void VideoPrivate::initializeVideoList(QWidget *parent)
{
    mVideoListWidget = new MusicListWidget(parent, MediaUtils::VIDEO_LIST);

    mStackedWidget->insertWidget(1, mVideoListWidget);
}

void VideoPrivate::connectAllSlots()
{
    connect(g_Multimedia, SIGNAL(onPlay(int, int, QString, qint64)), this, SLOT(playVideo(int,int,QString,qint64)));
    connect(g_Multimedia, SIGNAL(onPause(int)), this, SLOT(pauseVideo(int)));
    connect(g_Multimedia, SIGNAL(onResume(int)), this, SLOT(resumeVideo(int)));
    connect(g_Multimedia, SIGNAL(onStop(int,bool)), this, SLOT(stopVideo(int,bool)));
    connect(g_Multimedia, SIGNAL(onUpdateProgress(int,qint64,qint64)), this, SLOT(updateProgress(int,qint64,qint64)));
    connect(g_Multimedia, SIGNAL(onScanVideoFiles(int,int,QString,QStringList&)), this, SLOT(scanVideoFiles(int,int,QString,QStringList&)));


    connect(mVideoPlayWidget, SIGNAL(onSwitchStatus(bool)), this, SLOT(setPlayStatus(bool)));
    connect(mVideoPlayWidget, SIGNAL(onSwitchIndex(bool)), this, SLOT(setPlayIndex(bool)));
    connect(mVideoPlayWidget, SIGNAL(onSeekTo(int)), this, SLOT(setPlaySeek(int)));

    connect(mVideoPlayWidget, SIGNAL(onBackFinish()), this, SLOT(backFinish()));

    connect(mVideoListWidget, SIGNAL(selectItem(int,QString)), this, SLOT(setPlayItem(int,QString)));
    connect(mVideoListWidget, &MusicListWidget::queryFiles, g_Multimedia, &Multimedia::queryMediaFiles);
}


void VideoPrivate::initializeVideoPlay(QWidget *parent)
{
    mVideoPlayWidget = new VideoPlayWidget(parent);
    mStackedWidget->insertWidget(0, mVideoPlayWidget);
}

void VideoPrivate::onBtnTestRelease()
{
    Q_Q(Video);
    q->startApplication(T_USBDiskImage);
}

//----------------------------------

Video::Video(QObject *parent):
    Activity(parent),
    d_ptr(new VideoPrivate(this))
{

}

void Video::onCreate(QWidget *parent)
{
    Q_D(Video);
    d->initializeBasicWidget(parent);

}
void Video::onStart()
{

}
void Video::onResume()
{

}
void Video::onPause()
{

}
void Video::onStop()
{

}
void Video::onDestroy()
{

}

bool Video::onBackPressed()
{

    return false;
}

void Video::onLanguageChanged()
{

}

void Video::onReceiveBroadcast(AppType appType,OMessage &msg)
{

}

void Video::onReceiveCmd(AppType appType,OMessage &msg)
{

}


