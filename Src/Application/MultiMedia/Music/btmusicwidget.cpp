#include "btmusicwidget.h"
#include <QDebug>
#include "musicclickwidget.h"
#include "musicprogresswidget.h"
#include "Src/CommonUserWidget/rotatewidget.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QFont>
#include <QPalette>


class BtMusicWidgetPrivate {
    Q_DISABLE_COPY(BtMusicWidgetPrivate)
public:
    explicit BtMusicWidgetPrivate(BtMusicWidget *parent);
    ~BtMusicWidgetPrivate();
private slots:
    void onPlay();
    void onPause();
private:
    Q_DECLARE_PUBLIC(BtMusicWidget)
    BtMusicWidget* const q_ptr;
    void initializeBasicWidget(QWidget *parent);
    void initializeAniView(QWidget *parent);
    void initializeClickView(QWidget *parent);
    void initializeProgressView(QWidget *parent);
    void initializeSongView(QWidget *parent);

    RotateWidget *mMusicPlayIcon = NULL;
    QLabel *mSongName = NULL;
};

BtMusicWidget::BtMusicWidget(QWidget *parent)
    : QWidget(parent)
    , d_ptr(new BtMusicWidgetPrivate(this))
{
    setFixedSize(QSize(800, 435));
}

BtMusicWidget::~BtMusicWidget()
{

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
    initializeAniView(parent);
    initializeClickView(parent);
    initializeProgressView(parent);
    initializeSongView(parent);

}

void BtMusicWidgetPrivate::initializeAniView(QWidget *parent)
{
    mMusicPlayIcon = new RotateWidget(parent);
    mMusicPlayIcon->setFixedSize(QSize(184, 184));
    mMusicPlayIcon->setGeometry(308, 21, 0, 0);
    mMusicPlayIcon->setAniTime(500);

    QList<QString> list;
    list.append(":/Res/drawable/multimedia/bt_music_icon_1.png");
    list.append(":/Res/drawable/multimedia/bt_music_icon_2.png");
    list.append(":/Res/drawable/multimedia/bt_music_icon_3.png");

    mMusicPlayIcon->init(list);

}

void BtMusicWidgetPrivate::onPlay()
{
    mMusicPlayIcon->start();
}

void BtMusicWidgetPrivate::onPause()
{
    mMusicPlayIcon->stop();
}

void BtMusicWidgetPrivate::initializeClickView(QWidget *parent) {
    MusicClickWidget *mMusicClickWidget = new MusicClickWidget(parent);
    mMusicClickWidget->setFixedSize(QSize(800, 60));
    mMusicClickWidget->setGeometry(0, 324, 0, 0);


    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(mMusicClickWidget, SIGNAL(changeStatus(bool)), parent, SLOT(onSwitchStatus(bool)), type);
    QObject::connect(mMusicClickWidget, SIGNAL(switchIndex(bool)), parent, SLOT(onSwitchIndex(bool)), type);
}


void BtMusicWidgetPrivate::initializeProgressView(QWidget *parent) {
    MusicProgressWidget *mMusicProgressWidget = new MusicProgressWidget(parent, MediaUtils::MEDIA_TYPE::BT_MUSIC);
    mMusicProgressWidget->setFixedSize(QSize(730, 36));
    mMusicProgressWidget->setGeometry(75, 273, 0, 0);
}

void BtMusicWidgetPrivate::initializeSongView(QWidget *parent)
{
    QWidget *songWidget = new QWidget(parent);
    songWidget->setFixedSize(QSize(800, 40));
    songWidget->setGeometry(0, 221, 0, 0);
    QHBoxLayout  *songLayout = new QHBoxLayout();
    songLayout->setContentsMargins(0, 0, 0, 0);
    songWidget->setLayout(songLayout);



    mSongName = new QLabel(parent);

    //设置字号
    QFont ft("Microsoft YaHei");
    ft.setPointSize(24);
    mSongName->setFont(ft);
    //设置颜色
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);
    mSongName->setPalette(pa);

    mSongName->setText("歌曲名称");

    songLayout->addWidget(mSongName, 0, Qt::AlignCenter);
}

void BtMusicWidget::onSwitchIndex(bool isNext) {
    qDebug() << "BtMusicWidget onSwitchIndex = " << isNext;
}


void BtMusicWidget::onSwitchStatus(bool isPlay) {
    qDebug() << "BtMusicWidget onSwitchStatus = " << isPlay;
    Q_D(BtMusicWidget);
    if (isPlay) {
        d->onPlay();
    }else {
        d->onPause();
    }
}
