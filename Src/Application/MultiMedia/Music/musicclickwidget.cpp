#include "musicclickwidget.h"
#include "Src/CommonUserWidget/BmpButton.h"


class MusicClickWidgetPrivate {
    Q_DISABLE_COPY(MusicClickWidgetPrivate)
public:
    explicit MusicClickWidgetPrivate(MusicClickWidget *parent);
    ~MusicClickWidgetPrivate();

private:
    Q_DECLARE_PUBLIC(MusicClickWidget)
    MusicClickWidget* const q_ptr;
    void initializeBasicWidget(QWidget *parent);
    void refreshStatusView(bool play);
    bool isCurrentPlay = false;


    BmpButton *prevBtn = NULL;
    BmpButton *playBtn = NULL;
    BmpButton *nextBtn = NULL;
};

MusicClickWidget::MusicClickWidget(QWidget *parent)
    : QWidget(parent)
    , d_ptr(new MusicClickWidgetPrivate(this))
{

}

MusicClickWidgetPrivate::MusicClickWidgetPrivate(MusicClickWidget *parent)
    : q_ptr(parent)
{
    initializeBasicWidget(parent);
}


void MusicClickWidgetPrivate::initializeBasicWidget(QWidget *parent)
{
    prevBtn = new BmpButton(parent);
    prevBtn->setFixedSize(QSize(266, 60));
    prevBtn->setNormalBmpPath(":/Res/drawable/multimedia/music_prev_normal.png");
    prevBtn->setPressBmpPath(":/Res/drawable/multimedia/music_prev_focus.png");
    prevBtn->setGeometry(0, 0, 0, 0);


    playBtn = new BmpButton(parent);
    playBtn->setFixedSize(QSize(268, 60));
    playBtn->setNormalBmpPath(":/Res/drawable/multimedia/music_play_normal.png");
    playBtn->setPressBmpPath(":/Res/drawable/multimedia/music_play_focus.png");
    playBtn->setGeometry(267, 0, 0, 0);

    nextBtn = new BmpButton(parent);
    nextBtn->setFixedSize(QSize(266, 60));
    nextBtn->setNormalBmpPath(":/Res/drawable/multimedia/music_next_normal.png");
    nextBtn->setPressBmpPath(":/Res/drawable/multimedia/music_next_focus .png");
    nextBtn->setGeometry(536, 0, 0, 0);


    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(prevBtn, SIGNAL(released()), parent, SLOT(prev()), type);
    QObject::connect(nextBtn, SIGNAL(released()), parent, SLOT(next()), type);
    QObject::connect(playBtn, SIGNAL(released()), parent, SLOT(changeStatus()), type);


    isCurrentPlay = false;
    refreshStatusView(isCurrentPlay);
}


void MusicClickWidget::prev()
{
    emit switchIndex(false);
}

void MusicClickWidget::next()
{
    emit switchIndex(true);
}

void MusicClickWidget::changeStatus()
{
    Q_D(MusicClickWidget);
    emit switchStatus(!(d->isCurrentPlay));
}

void MusicClickWidget::setPlayStatus(bool play)
{
    Q_D(MusicClickWidget);
    d->refreshStatusView(play);
}

bool MusicClickWidget::isPlaying()
{
    Q_D(MusicClickWidget);
    return d->isCurrentPlay;
}

void MusicClickWidgetPrivate::refreshStatusView(bool play) {
    this->isCurrentPlay = play;
    if (isCurrentPlay) {
        playBtn->setNormalBmpPath(":/Res/drawable/multimedia/music_pause_normal.png");
        playBtn->setPressBmpPath(":/Res/drawable/multimedia/music_pause_focus.png");
    }else {
        playBtn->setNormalBmpPath(":/Res/drawable/multimedia/music_play_normal.png");
        playBtn->setPressBmpPath(":/Res/drawable/multimedia/music_play_focus.png");
    }
}

MusicClickWidget::~MusicClickWidget()
{

}

MusicClickWidgetPrivate::~MusicClickWidgetPrivate()
{

}


