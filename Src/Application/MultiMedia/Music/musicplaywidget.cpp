#include "musicplaywidget.h"
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "musiclistitem.h"
#include "musicprogresswidget.h"
#include "musicclickwidget.h"
#include "Src\CommonUserWidget\rotatewidget.h"
#include <QDebug>
#include <QList>


class MusicPlayWidgetPrivate {
    Q_DISABLE_COPY(MusicPlayWidgetPrivate)
public:
    explicit MusicPlayWidgetPrivate(MusicPlayWidget *parent);
    ~MusicPlayWidgetPrivate();
private:
    Q_DECLARE_PUBLIC(MusicPlayWidget)
    MusicPlayWidget* const q_ptr;
    void initializeBasicWidget(QWidget *parent);
    void initializeListView(QWidget *parent);
    void initializeRightView(QWidget *parent);
    void initializeProgressView(QWidget *parent);
    void initializeClickView(QWidget *parent);

    MusicListItem *mFileItem = NULL;
    MusicListItem *mAlbumItem = NULL;
    MusicListItem *mSingerItem = NULL;
    MusicListItem *mSongItem = NULL;
    RotateWidget *mMusicPlayIcon =NULL;
    RotateWidget *mMusicPlayAni = NULL;


    PLAY_MODE mCurrentPlayMode = LOOP;
    void setCurrentPlayMode(int mode);

    void onPlay();
    void onPause();
};


MusicPlayWidgetPrivate::MusicPlayWidgetPrivate(MusicPlayWidget *parent)
    : q_ptr(parent)
{
    initializeBasicWidget(parent);
}


MusicPlayWidget::MusicPlayWidget(QWidget *parent)
    : QWidget(parent)
    , d_ptr(new MusicPlayWidgetPrivate(this))
{
    setFixedSize(QSize(800, 435));
    //    setStyleSheet("background-color:blue;");
}

void MusicPlayWidgetPrivate::initializeListView(QWidget *parent) {
    int top = 59;
    mFileItem = new MusicListItem(parent);
    mFileItem->setFixedSize(QSize(300, 30));
    mFileItem->setItemInfo(":/Res/drawable/multimedia/music_file_icon.png", "Happier.MP3");
    mFileItem->setGeometry(41, top, 0, 0);
    top += 30 + 20;

    mAlbumItem = new MusicListItem(parent);
    mAlbumItem->setFixedSize(QSize(300, 30));
    mAlbumItem->setItemInfo(":/Res/drawable/multimedia/music_album_icon.png", "<<music_album>>");
    mAlbumItem->setGeometry(41, top, 0, 0);
    top += 30 + 20;


    mSingerItem = new MusicListItem(parent);
    mSingerItem->setFixedSize(QSize(300, 30));
    mSingerItem->setItemInfo(":/Res/drawable/multimedia/music_singer_icon.png", "music_singer");
    mSingerItem->setGeometry(41, top, 0, 0);
    top += 30 + 20;


    mSongItem = new MusicListItem(parent);
    mSongItem->setFixedSize(QSize(300, 30));
    mSongItem->setItemInfo(":/Res/drawable/multimedia/music_song_icon.png", "music_song_normal");
    mSongItem->setGeometry(41, top, 0, 0);

}


void MusicPlayWidgetPrivate::initializeRightView(QWidget *parent) {
    mMusicPlayIcon = new RotateWidget(parent);
    mMusicPlayIcon->setFixedSize(QSize(219, 219));
    mMusicPlayIcon->setGeometry(528, 48, 0, 0);
    mMusicPlayIcon->init(":/Res/drawable/multimedia/music_play_icon.png");

    mMusicPlayAni = new RotateWidget(parent);
    mMusicPlayAni->setFixedSize(QSize(110, 95));
    mMusicPlayAni->setGeometry(622, 0, 0, 0);

    QList<QString> list;
    list.append(":/Res/drawable/multimedia/music_play_0.png");
    list.append(":/Res/drawable/multimedia/music_play_1.png");
    list.append(":/Res/drawable/multimedia/music_play_2.png");
    list.append(":/Res/drawable/multimedia/music_play_3.png");
    list.append(":/Res/drawable/multimedia/music_play_4.png");
    list.append(":/Res/drawable/multimedia/music_play_5.png");
    list.append(":/Res/drawable/multimedia/music_play_6.png");
    list.append(":/Res/drawable/multimedia/music_play_7.png");
    list.append(":/Res/drawable/multimedia/music_play_8.png");
    list.append(":/Res/drawable/multimedia/music_play_9.png");
    list.append(":/Res/drawable/multimedia/music_play_10.png");
    list.append(":/Res/drawable/multimedia/music_play_11.png");
    list.append(":/Res/drawable/multimedia/music_play_12.png");
    list.append(":/Res/drawable/multimedia/music_play_13.png");
    list.append(":/Res/drawable/multimedia/music_play_14.png");
    list.append(":/Res/drawable/multimedia/music_play_15.png");
    list.append(":/Res/drawable/multimedia/music_play_16.png");

    mMusicPlayAni->init(list);
}

void MusicPlayWidgetPrivate::initializeProgressView(QWidget *parent) {
    MusicProgressWidget *mMusicProgressWidget = new MusicProgressWidget(parent, SLIDER_MODE::MUSIC);
    mMusicProgressWidget->setFixedSize(QSize(730, 36));
    mMusicProgressWidget->setGeometry(40, 283, 0, 0);


    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(mMusicProgressWidget, SIGNAL(switchPlayMode(int)), parent, SLOT(onSwitchPlayMode(int)), type);
}

void MusicPlayWidget::onSwitchPlayMode(int mode) {
    Q_D(MusicPlayWidget);
    d->setCurrentPlayMode(mode);
}

void MusicPlayWidgetPrivate::setCurrentPlayMode(int mode) {
    this->mCurrentPlayMode = mode;
}

void MusicPlayWidgetPrivate::onPlay()
{
    mMusicPlayIcon->start();
    mMusicPlayAni->start();
}

void MusicPlayWidgetPrivate::onPause()
{
    mMusicPlayIcon->stop();
    mMusicPlayAni->stop();
}


void MusicPlayWidgetPrivate::initializeClickView(QWidget *parent) {
    MusicClickWidget *mMusicClickWidget = new MusicClickWidget(parent);
    mMusicClickWidget->setFixedSize(QSize(800, 60));
    mMusicClickWidget->setGeometry(0, 324, 0, 0);


    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(mMusicClickWidget, SIGNAL(changeStatus(bool)), parent, SLOT(onSwitchStatus(bool)), type);
    QObject::connect(mMusicClickWidget, SIGNAL(switchIndex(bool)), parent, SLOT(onSwitchIndex(bool)), type);
}


void MusicPlayWidget::onSwitchIndex(bool isNext) {
    qDebug() << "onSwitchIndex = " << isNext;
}


void MusicPlayWidget::onSwitchStatus(bool isPlay) {
    qDebug() << "onSwitchStatus = " << isPlay;
    Q_D(MusicPlayWidget);
    if (isPlay) {
        d->onPlay();
    }else {
        d->onPause();
    }
}

void MusicPlayWidgetPrivate::initializeBasicWidget(QWidget *parent) {
    initializeListView(parent);
    initializeRightView(parent);
    initializeProgressView(parent);
    initializeClickView(parent);
}


void MusicPlayWidget::resizeEvent(QResizeEvent *event) {
}

MusicPlayWidgetPrivate::~MusicPlayWidgetPrivate(){

}

MusicPlayWidget::~MusicPlayWidget() {

}
