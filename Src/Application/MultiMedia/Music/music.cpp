#include "music.h"


MusicPrivate::MusicPrivate(Music *parent)
    : QObject(),q_ptr(parent)
{
    mBackground = NULL;
    mBtnTest = NULL;
}

void MusicPrivate::initializeBasicWidget(QWidget *parent)
{
    Q_Q(Music);
    MediaUtils::setWidgetBackground(parent, ":/img/Common/img_wap_bg.png");

    mStackedWidget = new QStackedWidget(parent);
    mStackedWidget->setFixedSize(QSize(800, 435));
    mStackedWidget->setGeometry(0, 50, 0, 0);

    initializeToolsWidget(parent);
    initializePlayView(parent);
    initializeListView(parent);

    connectAllSlots();

    setCurrentPageView(0);
}


void MusicPrivate::initializeToolsWidget(QWidget *parent) {
    QList<QString> list;
    list.append("音乐");
    list.append("列表");
    mMediaToolsWidget = new MediaToolsWidget(parent, list);
    connect(mMediaToolsWidget, SIGNAL(onItemClick(int)), this, SLOT(setCurrentPageView(int)));
}

void MusicPrivate::setCurrentPageView(int tabIndex) {
    if (1 == tabIndex) {
        mMusicListWidget->showAllList();
    }

    mStackedWidget->setCurrentIndex(tabIndex);
}

void MusicPrivate::initializePlayView(QWidget *parent) {
    mMusicPlayWidget = new MusicPlayWidget(parent);
    mStackedWidget->insertWidget(0, mMusicPlayWidget);
}

void MusicPrivate::initializeListView(QWidget *parent) {
    mMusicListWidget = new MusicListWidget(parent);
    mStackedWidget->insertWidget(1, mMusicListWidget);
}

void MusicPrivate::connectAllSlots()
{
    connect(g_Multimedia, SIGNAL(onPlay(int, int, QString, qint64)), this, SLOT(playMusic(int, int, QString, qint64)));
    connect(g_Multimedia, SIGNAL(onPause(int)), this, SLOT(pauseMusic(int)));
    connect(g_Multimedia, SIGNAL(onResume(int)), this, SLOT(resumeMusic(int)));
    connect(g_Multimedia, SIGNAL(onStop(int,bool)), this, SLOT(stopMusic(int,bool)));
    connect(g_Multimedia, SIGNAL(onSetPlayMode(int,int)), this, SLOT(setPlayModeMusic(int,int)));
    connect(g_Multimedia, SIGNAL(onUpdateProgress(int,qint64,qint64)), this, SLOT(updateProgressMusic(int,qint64,qint64)));
    connect(g_Multimedia, SIGNAL(onScanMusicFiles(int,int,QString,QStringList&)), this, SLOT(scanMusicFiles(int,int,QString,QStringList&)));


    connect(mMusicPlayWidget, SIGNAL(onSwitchStatus(bool)), this, SLOT(setPlayStatus(bool)));
    connect(mMusicPlayWidget, SIGNAL(onSwitchMode(int)), this, SLOT(setPlayMode(int)));
    connect(mMusicPlayWidget, SIGNAL(onSwitchIndex(bool)), this, SLOT(setPlayIndex(bool)));
    connect(mMusicPlayWidget, SIGNAL(onSeekTo(int)), this, SLOT(setPlaySeek(int)));
    connect(mMusicListWidget, SIGNAL(selectItem(int,QString)), this, SLOT(setPlayItem(int,QString)));

    connect(mMusicListWidget, &MusicListWidget::queryFiles, g_Multimedia, &Multimedia::queryMediaFiles);
}

void MusicPrivate::setPlayItem(int deviceType, QString filePath) {
    mMusicPlayWidget->preparedPlay(filePath, 0);
    g_Multimedia->setPlayPath(MediaUtils::MUSIC, deviceType, filePath);
}

void MusicPrivate::setPlayIndex(bool isNext)
{
    mMusicListWidget->setPlayNext(isNext);
}

void MusicPrivate::setPlaySeek(int progress)
{
    g_Multimedia->seekTo(MediaUtils::MUSIC, progress);
}

void MusicPrivate::setPlayStatus(bool isPlay)
{
    g_Multimedia->setPlayStatus(MediaUtils::MUSIC, isPlay);
}

void MusicPrivate::setPlayMode(int mode)
{
    g_Multimedia->setPlayMode(MediaUtils::MUSIC, mode);
}

void MusicPrivate::scanMusicFiles(int deviceType, int queryMode, QString dirPath, QStringList& pathList)
{
    this->mCurrentDeviceType = deviceType;
    mMusicListWidget->updateList(deviceType, queryMode, dirPath, pathList);
    if (pathList.size() > 0) {
        mMusicPlayWidget->updateScanFile(pathList.at(0));
    }
}

void MusicPrivate::playMusic(const int mediaType, const int index, const QString &filePath, const qint64 duration)
{
    if (mediaType != MediaUtils::MUSIC) {
        return;
    }

    mMusicListWidget->refreshItem(index);
    mMusicPlayWidget->playMusic(filePath, duration);
}

void MusicPrivate::pauseMusic(const int mediaType)
{
    if (mediaType != MediaUtils::MUSIC) {
        return;
    }

    mMusicPlayWidget->setPlayStatus(false);
}

void MusicPrivate::resumeMusic(const int mediaType)
{
    if (mediaType != MediaUtils::MUSIC) {
        return;
    }
    mMusicPlayWidget->setPlayStatus(true);
}

void MusicPrivate::stopMusic(const int mediaType, bool isError)
{
    if (mediaType != MediaUtils::MUSIC) {
        return;
    }

    mMusicPlayWidget->setPlayStatus(false);
}

void MusicPrivate::setPlayModeMusic(const int mediaType, const int playMode)
{
    if (mediaType != MediaUtils::MUSIC) {
        return;
    }
    mMusicPlayWidget->setPlayMode(playMode);
}

void MusicPrivate::updateProgressMusic(const int mediaType, const qint64 currentPosition, const qint64 duration)
{
    if (mediaType != MediaUtils::MUSIC) {
        return;
    }
    mMusicPlayWidget->updateProgress(currentPosition, duration);
}

void MusicPrivate::onBtnTestRelease()
{
    Q_Q(Music);
    q->startApplication(T_USBDiskVideo);
}

//----------------------------------

Music::Music(QObject *parent):
    Activity(parent),
    d_ptr(new MusicPrivate(this))
{
    //    setFixedSize(QSize(800, 435));
}

void Music::onCreate(QWidget *parent)
{
    Q_D(Music);
    //centralWidget = new QWidget(parent);
    d->initializeBasicWidget(parent);

    //setContentView(centralWidget);
}
void Music::onStart()
{

}
void Music::onResume()
{

}
void Music::onPause()
{

}
void Music::onStop()
{

}
void Music::onDestroy()
{

}

bool Music::onBackPressed()
{

    return false;
}

void Music::onLanguageChanged()
{

}

void Music::onReceiveBroadcast(AppType appType,OMessage &msg)
{

}

void Music::onReceiveCmd(AppType appType,OMessage &msg)
{

}


