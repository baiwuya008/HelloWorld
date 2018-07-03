#include "musicplaywidget.h"
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "musiclistitem.h"
#include "musicprogresswidget.h"
#include "musicclickwidget.h"
#include "Src/CommonUserWidget/rotatewidget.h"
#include <QDebug>
#include <QList>
#include "musicid3.h"


class MusicPlayWidgetPrivate {
    Q_DISABLE_COPY(MusicPlayWidgetPrivate)
public:
    explicit MusicPlayWidgetPrivate(MusicPlayWidget *parent);
    ~MusicPlayWidgetPrivate();

private:
    Q_DECLARE_PUBLIC(MusicPlayWidget)
    MusicPlayWidget* const q_ptr;
    void connectAllSlots();
    void initializeBasicWidget(QWidget *parent);
    void initializeListView(QWidget *parent);
    void initializeRightView(QWidget *parent);
    void initializeProgressView(QWidget *parent);
    void initializeClickView(QWidget *parent);

    void decodeMusicInfo(QString path);

    void updatePlayInfo(QString title, QString artist, QString album);
    void updatePlayPath(QString path, qint64 duration);
    void updateProgress(qint64 currentPosition, qint64 duration);
    void updatePlayStatus(bool isPlay);

    MusicListItem *mFileItem = NULL;
    MusicListItem *mTitleItem = NULL;
    MusicListItem *mArtistItem = NULL;
    MusicListItem *mAlbumItem = NULL;
    RotateWidget *mMusicPlayIcon =NULL;
    RotateWidget *mMusicPlayAni = NULL;
    MusicId3 *mMusicId3 = NULL;

    MusicProgressWidget *mMusicProgressWidget = NULL;
    MusicClickWidget *mMusicClickWidget = NULL;
    QString mCurrentPlayPath;
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
    mFileItem->setFixedSize(QSize(400, 30));
    mFileItem->initItem("nothing", ":/Res/drawable/multimedia/music_file_icon.png");
    mFileItem->setGeometry(41, top, 0, 0);
    top += 30 + 20;

    mTitleItem = new MusicListItem(parent);
    mTitleItem->setFixedSize(QSize(400, 30));
    mTitleItem->initItem("unknown", ":/Res/drawable/multimedia/music_album_icon.png");
    mTitleItem->setGeometry(41, top, 0, 0);
    top += 30 + 20;


    mArtistItem = new MusicListItem(parent);
    mArtistItem->setFixedSize(QSize(400, 30));
    mArtistItem->initItem("unknown", ":/Res/drawable/multimedia/music_singer_icon.png");
    mArtistItem->setGeometry(41, top, 0, 0);
    top += 30 + 20;


    mAlbumItem = new MusicListItem(parent);
    mAlbumItem->setFixedSize(QSize(400, 30));
    mAlbumItem->initItem("unknown", ":/Res/drawable/multimedia/music_song_icon.png");
    mAlbumItem->setGeometry(41, top, 0, 0);

    updatePlayInfo("","","");
}


void MusicPlayWidgetPrivate::initializeRightView(QWidget *parent) {
    mMusicPlayIcon = new RotateWidget(parent);
    mMusicPlayIcon->setFixedSize(QSize(219, 219));
    mMusicPlayIcon->setGeometry(524, 48, 0, 0);
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
    mMusicProgressWidget = new MusicProgressWidget(parent);
    mMusicProgressWidget->setFixedSize(QSize(730, 36));
    mMusicProgressWidget->setGeometry(40, 283, 0, 0);
}

void MusicPlayWidgetPrivate::initializeClickView(QWidget *parent) {
    mMusicClickWidget = new MusicClickWidget(parent);
    mMusicClickWidget->setFixedSize(QSize(800, 60));
    mMusicClickWidget->setGeometry(0, 324, 0, 0);
}


void MusicPlayWidgetPrivate::connectAllSlots()
{
    Q_Q(MusicPlayWidget);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(mMusicClickWidget, &MusicClickWidget::switchStatus, q, &MusicPlayWidget::onSwitchStatus, type);
    QObject::connect(mMusicClickWidget, &MusicClickWidget::switchIndex, q, &MusicPlayWidget::onSwitchIndex, type);
    QObject::connect(mMusicProgressWidget, &MusicProgressWidget::switchPlayMode, q, &MusicPlayWidget::onSwitchMode, type);
    QObject::connect(mMusicProgressWidget, &MusicProgressWidget::seekTo, q, &MusicPlayWidget::onSeekTo, type);
    QObject::connect(mMusicProgressWidget, &MusicProgressWidget::sliderSwitchStatus, q, &MusicPlayWidget::onSwitchStatus, type);
}

void MusicPlayWidget::setPlayStatus(bool isPlay)
{
    Q_D(MusicPlayWidget);
    d->updatePlayStatus(isPlay);
}

void MusicPlayWidget::setPlayMode(int mode)
{
    Q_D(MusicPlayWidget);
    d->mMusicProgressWidget->setPlayMode(mode);
}

void MusicPlayWidgetPrivate::initializeBasicWidget(QWidget *parent) {
    mMusicId3 = new MusicId3();
    initializeListView(parent);
    initializeRightView(parent);
    initializeProgressView(parent);
    initializeClickView(parent);
    connectAllSlots();
}

MusicPlayWidgetPrivate::~MusicPlayWidgetPrivate(){

}

MusicPlayWidget::~MusicPlayWidget() {

}

void MusicPlayWidgetPrivate::updatePlayInfo(QString title, QString artist, QString album)
{
    if (title.length() > 0) {
        mTitleItem->setName(title);
    }else {
        mTitleItem->setName("未知");
    }

    if (artist.length() > 0) {
        mArtistItem->setName(artist);
    }else {
        mArtistItem->setName("未知");
    }

    if (album.length() > 0) {
        mAlbumItem->setName(album);
    }else {
        mAlbumItem->setName("未知");
    }
}

void MusicPlayWidgetPrivate::updatePlayPath(QString path, qint64 duration)
{  
    updateProgress(0, duration);
    if (duration > 0) {
        updatePlayStatus(true);
    }

    if (mCurrentPlayPath.length() > 1 && !mCurrentPlayPath.compare(path)) {
        return;
    }

    mCurrentPlayPath = path;
    mFileItem->setName(MediaUtils::getLastToName(path));
    decodeMusicInfo(path);
}

void MusicPlayWidgetPrivate::updateProgress(qint64 currentPosition, qint64 duration)
{
    mMusicProgressWidget->setProgress(currentPosition, duration);
}

void MusicPlayWidgetPrivate::updatePlayStatus(bool isPlay)
{
    mMusicClickWidget->setPlayStatus(isPlay);
    if (isPlay) {
        mMusicPlayIcon->start();
        mMusicPlayAni->start();
    }else {
        mMusicPlayIcon->stop();
        mMusicPlayAni->stop();
    }
}

void MusicPlayWidgetPrivate::decodeMusicInfo(QString path)
{
    if (mMusicId3 != NULL && path.length() > 2) {
        mMusicId3->decodeMusic(path);
        if (mMusicId3->isDecodeV1) {
            updatePlayInfo(mMusicId3->m_ID3V1.title,
                           mMusicId3->m_ID3V1.artist,
                           mMusicId3->m_ID3V1.album);
        }

        if (mMusicId3->isDecodeImage) {
            mMusicPlayIcon->setPixmap(mMusicId3->image);
        }else {
            mMusicPlayIcon->init(":/Res/drawable/multimedia/music_play_icon.png");
            mMusicId3->destoryImage();
        }

        if (mMusicClickWidget->isPlaying()) {
            mMusicPlayIcon->start();
        }
        mMusicId3->clear();
    }
}

void MusicPlayWidget::setProgress(const qint64 currentPosition, const qint64 duration)
{
    Q_D(MusicPlayWidget);
    d->updateProgress(currentPosition, duration);
}

void MusicPlayWidget::setPlayPath(QString path, const qint64 duration)
{
    Q_D(MusicPlayWidget);
    d->updatePlayPath(path, duration);
}
