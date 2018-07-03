#include "btmusicwidget.h"
#include <QDebug>
#include "Src/Application/MultiMedia/Music/musicclickwidget.h"
#include "Src/Application/MultiMedia/Music/musicprogresswidget.h"
#include "Src/Application/MultiMedia/Music/rotatewidget.h"
#include "Src/Application/MultiMedia/multimedia.h"
#include "Src/Application/MultiMedia/Tools/mediautils.h"
#include "Src/Application/MultiMedia/Tools/mediatoolswidget.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QFont>
#include <QPalette>


class BtMusicWidgetPrivate {
    Q_DISABLE_COPY(BtMusicWidgetPrivate)
public:
    explicit BtMusicWidgetPrivate(BtMusicWidget *parent);
    ~BtMusicWidgetPrivate();

private:
    Q_DECLARE_PUBLIC(BtMusicWidget)
    BtMusicWidget* const q_ptr;
    void initializeBasicWidget(QWidget *parent);
    void initializeToolsWidget(QWidget *parent);
    void initializeAniView(QWidget *parent);
    void initializeClickView(QWidget *parent);
    void initializeTitleView(QWidget *parent);
    void connectAllSlots();

    void updatePlayStatus(bool isPlay);
    void updatePlayInfo(QString title);

    MediaToolsWidget *mMediaToolsWidget = NULL;
    RotateWidget *mBtMusicPlayIcon = NULL;
    QLabel *mTitleName = NULL;
    QWidget *mTitleWidget = NULL;
    QHBoxLayout  *mTitleLayout = NULL;
    MusicClickWidget *mMusicClickWidget = NULL;
};

BtMusicWidget::BtMusicWidget(QWidget *parent)
    : QWidget(parent)
    , d_ptr(new BtMusicWidgetPrivate(this))
{
}

BtMusicWidget::~BtMusicWidget()
{

}

void BtMusicWidget::backPlay(const int mediaType, const int index, QString path, const qint64 duration)
{
    if (mediaType != MediaUtils::BT_MUSIC) {
        return;
    }

    Q_D(BtMusicWidget);
    d->updatePlayInfo(path);
}

void BtMusicWidget::backPause(const int mediaType)
{
    if (mediaType != MediaUtils::BT_MUSIC) {
        return;
    }
    Q_D(BtMusicWidget);
    d->updatePlayStatus(false);
}

void BtMusicWidget::backResume(const int mediaType)
{
    if (mediaType != MediaUtils::BT_MUSIC) {
        return;
    }
    Q_D(BtMusicWidget);
    d->updatePlayStatus(true);
}

void BtMusicWidget::backStop(const int mediaType, bool isError)
{
    if (mediaType != MediaUtils::BT_MUSIC) {
        return;
    }
    Q_D(BtMusicWidget);
    d->updatePlayStatus(false);
}

BtMusicWidgetPrivate::BtMusicWidgetPrivate(BtMusicWidget *parent) : q_ptr(parent)
{
    initializeBasicWidget(parent);
}

BtMusicWidgetPrivate::~BtMusicWidgetPrivate()
{

}

void BtMusicWidgetPrivate::initializeBasicWidget(QWidget *parent)
{
    MediaUtils::setWidgetBackground(parent, ":/img/Common/img_wap_bg.png");
    initializeToolsWidget(parent);
    initializeAniView(parent);
    initializeClickView(parent);
    initializeTitleView(parent);
}

void BtMusicWidgetPrivate::initializeToolsWidget(QWidget *parent) {
    QList<QString> list;
    list.append("蓝牙音乐");
    mMediaToolsWidget = new MediaToolsWidget(parent, list);
}

void BtMusicWidgetPrivate::initializeAniView(QWidget *parent)
{
    mBtMusicPlayIcon = new RotateWidget(parent);
    mBtMusicPlayIcon->setFixedSize(QSize(184, 184));
    mBtMusicPlayIcon->setGeometry(308, 75, 0, 0);
    mBtMusicPlayIcon->setAniTime(500);

    QList<QString> list;
    list.append(":/Res/drawable/multimedia/bt_music_icon_1.png");
    list.append(":/Res/drawable/multimedia/bt_music_icon_2.png");
    list.append(":/Res/drawable/multimedia/bt_music_icon_3.png");

    mBtMusicPlayIcon->init(list);
}

void BtMusicWidgetPrivate::initializeClickView(QWidget *parent) {
    mMusicClickWidget = new MusicClickWidget(parent);
    mMusicClickWidget->setFixedSize(QSize(800, 60));
    mMusicClickWidget->setGeometry(0, 374, 0, 0);
}


void BtMusicWidgetPrivate::initializeTitleView(QWidget *parent)
{
    mTitleWidget = new QWidget(parent);
    mTitleWidget->setFixedSize(QSize(800, 40));
    mTitleWidget->setGeometry(0, 271, 0, 0);
    mTitleLayout = new QHBoxLayout();
    mTitleLayout->setContentsMargins(0, 0, 0, 0);
    mTitleWidget->setLayout(mTitleLayout);

    mTitleName = new QLabel(parent);
    MediaUtils::setLabText(mTitleName, 24);
    mTitleName->setText("歌曲名称");

    mTitleLayout->addWidget(mTitleName, 0, Qt::AlignCenter);
}

void BtMusicWidgetPrivate::connectAllSlots()
{
    Q_Q(BtMusicWidget);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(mMusicClickWidget, SIGNAL(switchStatus(bool)), q, SLOT(setPlayStatus(bool)), type);
    QObject::connect(mMusicClickWidget, SIGNAL(switchIndex(bool)), q, SLOT(setPlayIndex(bool)), type);


    QObject::connect(g_Multimedia, SIGNAL(onPlay(int,int,QString,qint64)), q, SLOT(backPlay(int,int,QString,qint64)), type);
    QObject::connect(g_Multimedia, SIGNAL(onPause(int)), q, SLOT(backPause(int)), type);
    QObject::connect(g_Multimedia, SIGNAL(onResume(int)), q, SLOT(backResume(int)), type);
    QObject::connect(g_Multimedia, SIGNAL(onStop(int,bool)), q, SLOT(backStop(int,bool)), type);
}

void BtMusicWidgetPrivate::updatePlayStatus(bool isPlay)
{
    mMusicClickWidget->setPlayStatus(isPlay);
    if (isPlay) {
        mBtMusicPlayIcon->start();
    }else {
        mBtMusicPlayIcon->stop();
    }
}

void BtMusicWidgetPrivate::updatePlayInfo(QString title)
{
    mTitleName->setText(title);
}

void BtMusicWidget::setPlayIndex(bool isNext) {
    QString next = "";
    if (isNext) {
        next = "true";
    }else {
        next = "false";
    }

    g_Multimedia->setPlayPath(MediaUtils::BT_MUSIC, MediaUtils::DWT_USBDisk, next);
}


void BtMusicWidget::setPlayStatus(bool isPlay) {
    g_Multimedia->setPlayStatus(MediaUtils::BT_MUSIC, isPlay);
}
