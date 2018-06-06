#include "musicclickwidget.h"
#include "Src\CommonUserWidget\BmpButton.h"


class MusicClickWidgetPrivate {
    Q_DISABLE_COPY(MusicClickWidgetPrivate)
public:
    explicit MusicClickWidgetPrivate(MusicClickWidget *parent);
    ~MusicClickWidgetPrivate();
private slots:
    void switchStatus(bool play);
private:
    Q_DECLARE_PUBLIC(MusicClickWidget)
    MusicClickWidget* const q_ptr;
    void initializeBasicWidget(QWidget *parent);


    BmpButton *prevBtn = NULL;
    BmpButton *playBtn = NULL;
    BmpButton *nextBtn = NULL;

    bool isPlay = false;
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
    playBtn->setGeometry(268, 0, 0, 0);

    nextBtn = new BmpButton(parent);
    nextBtn->setFixedSize(QSize(266, 60));
    nextBtn->setNormalBmpPath(":/Res/drawable/multimedia/music_next_normal.png");
    nextBtn->setPressBmpPath(":/Res/drawable/multimedia/music_next_focus .png");
    nextBtn->setGeometry(538, 0, 0, 0);


    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(prevBtn, SIGNAL(released()), parent, SLOT(prevT()), type);
    QObject::connect(nextBtn, SIGNAL(released()), parent, SLOT(nextT()), type);
    QObject::connect(playBtn, SIGNAL(released()), parent, SLOT(switchStatus()), type);
}


MusicClickWidget::~MusicClickWidget()
{

}



void MusicClickWidget::prevT()
{
    emit switchIndex(false);
}

void MusicClickWidget::nextT()
{
    emit switchIndex(true);
}

void MusicClickWidget::setStatus(bool play)
{
    Q_D(MusicClickWidget);
    d->switchStatus(play);
}

void MusicClickWidget::switchStatus()
{
    Q_D(MusicClickWidget);
    d->switchStatus(!d->isPlay);
    emit changeStatus(d->isPlay);
}


void MusicClickWidgetPrivate::switchStatus(bool play) {
    this->isPlay = play;

    if (isPlay) {
        playBtn->setNormalBmpPath(":/Res/drawable/multimedia/music_pause_normal.png");
        playBtn->setPressBmpPath(":/Res/drawable/multimedia/music_pause_focus.png");
    }else {
        playBtn->setNormalBmpPath(":/Res/drawable/multimedia/music_play_normal.png");
        playBtn->setPressBmpPath(":/Res/drawable/multimedia/music_play_focus.png");
    }
}
MusicClickWidgetPrivate::~MusicClickWidgetPrivate()
{

}


