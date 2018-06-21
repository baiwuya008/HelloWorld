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


class MusicPlayWidgetPrivate {
    Q_DISABLE_COPY(MusicPlayWidgetPrivate)
public:
    explicit MusicPlayWidgetPrivate(MusicPlayWidget *parent);
    ~MusicPlayWidgetPrivate();

private slots:
    void onPlay();
    void onPause();

private:
    Q_DECLARE_PUBLIC(MusicPlayWidget)
    MusicPlayWidget* const q_ptr;
    void connectAllSlots();
    void initializeBasicWidget(QWidget *parent);
    void initializeListView(QWidget *parent);
    void initializeRightView(QWidget *parent);
    void initializeProgressView(QWidget *parent);
    void initializeClickView(QWidget *parent);

    void updateCurrentInfo(QString title, QString artist, QString album, QString path);
    void updateCurrentPlay(QString path, qint64 duration);
    void updateCurrentProgress(qint64 currentPosition, qint64 duration);

    MusicListItem *mFileItem = NULL;
    MusicListItem *mTitleItem = NULL;
    MusicListItem *mArtistItem = NULL;
    MusicListItem *mAlbumItem = NULL;
    RotateWidget *mMusicPlayIcon =NULL;
    RotateWidget *mMusicPlayAni = NULL;

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
    mFileItem->setFixedSize(QSize(300, 30));
    mFileItem->initItem("nothing", ":/Res/drawable/multimedia/music_file_icon.png");
    mFileItem->setGeometry(41, top, 0, 0);
    top += 30 + 20;

    mTitleItem = new MusicListItem(parent);
    mTitleItem->setFixedSize(QSize(300, 30));
    mTitleItem->initItem("未知", ":/Res/drawable/multimedia/music_album_icon.png");
    mTitleItem->setGeometry(41, top, 0, 0);
    top += 30 + 20;


    mArtistItem = new MusicListItem(parent);
    mArtistItem->setFixedSize(QSize(300, 30));
    mArtistItem->initItem("未知", ":/Res/drawable/multimedia/music_singer_icon.png");
    mArtistItem->setGeometry(41, top, 0, 0);
    top += 30 + 20;


    mAlbumItem = new MusicListItem(parent);
    mAlbumItem->setFixedSize(QSize(300, 30));
    mAlbumItem->initItem("未知", ":/Res/drawable/multimedia/music_song_icon.png");
    mAlbumItem->setGeometry(41, top, 0, 0);
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
    mMusicProgressWidget = new MusicProgressWidget(parent);
    mMusicProgressWidget->setFixedSize(QSize(730, 36));
    mMusicProgressWidget->setGeometry(40, 283, 0, 0);
}

void MusicPlayWidgetPrivate::onPlay()
{
    mMusicPlayIcon->start();
    mMusicPlayAni->start();
    mMusicClickWidget->setPlayStatus(true);
}

void MusicPlayWidgetPrivate::onPause()
{
    mMusicPlayIcon->stop();
    mMusicPlayAni->stop();
    mMusicClickWidget->setPlayStatus(false);
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
    if (isPlay) {
        d->onPlay();
    }else {
        d->onPause();
    }
}

void MusicPlayWidget::setPlayMode(int mode)
{
    Q_D(MusicPlayWidget);
    d->mMusicProgressWidget->setPlayMode(mode);
}

void MusicPlayWidgetPrivate::initializeBasicWidget(QWidget *parent) {
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

void MusicPlayWidget::updateScanFile(QString path)
{
    Q_D(MusicPlayWidget);
    if (d->mCurrentPlayPath.size() < 2) {
        d->updateCurrentPlay(path, 0);
    }
}

void MusicPlayWidgetPrivate::updateCurrentInfo(QString title, QString artist, QString album, QString path)
{
    mTitleItem->setName(title);
    mArtistItem->setName(artist);
    mAlbumItem->setName(album);
    if (path.length() > 1) {
        mFileItem->setName(MediaUtils::getLastToName(path));
    }
}

void MusicPlayWidgetPrivate::updateCurrentPlay(QString path, qint64 duration)
{
    mCurrentPlayPath = path;
    mFileItem->setName(MediaUtils::getLastToName(path));
    updateCurrentProgress(0, duration);
    if (duration > 0) {
        onPlay();
    }
}

void MusicPlayWidgetPrivate::updateCurrentProgress(qint64 currentPosition, qint64 duration)
{
    mMusicProgressWidget->setProgress(currentPosition, duration);
}

void MusicPlayWidget::updateProgress(const qint64 currentPosition, const qint64 duration)
{
    Q_D(MusicPlayWidget);
    d->updateCurrentProgress(currentPosition, duration);
}

void MusicPlayWidget::updatePlayInfo(const QString &filePath, const QString &title, const QString &artist, const QString &album)
{
    Q_D(MusicPlayWidget);
    d->updateCurrentInfo(title, artist, album, "");
}

void MusicPlayWidget::updatePlayFile(QString path, qint64 duration)
{
    Q_D(MusicPlayWidget);
    d->updateCurrentPlay(path, duration);
}


