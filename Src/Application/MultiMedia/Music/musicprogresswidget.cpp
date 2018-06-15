#include "musicprogresswidget.h"
#include <QSlider>
#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>
#include "Src/CommonUserWidget/BmpButton.h"
#include "Src/Application/MultiMedia/Tools/mediautils.h"


class MusicProgressWidgetPrivate {
    Q_DISABLE_COPY(MusicProgressWidgetPrivate)
public:
    explicit MusicProgressWidgetPrivate(MusicProgressWidget *parent,
                                        MediaUtils::MEDIA_TYPE type = MediaUtils::MUSIC);
    ~MusicProgressWidgetPrivate();

private slots:

private:
    Q_DECLARE_PUBLIC(MusicProgressWidget)
    MusicProgressWidget* const q_ptr;
    void initializeBasicWidget(QWidget *parent);
    void initializeSlider(QWidget *parent);
    void initLabText(QLabel *text);
    void switchSliderMode();
    void switchPlayMode();
    void switchPlayModeView();

    bool currentOnClick = false;

    QHBoxLayout *mainLayout = NULL;
    QSlider *horizontalSlider = NULL;
    QLabel *startTimeLabel = NULL;
    QLabel *endTimeLabel = NULL;
    BmpButton *modeBtn = NULL;
    MediaUtils::MEDIA_TYPE mSliderType;
    PLAY_MODE mPlayMode = LOOP;
};


MusicProgressWidgetPrivate::MusicProgressWidgetPrivate(MusicProgressWidget *parent, MediaUtils::MEDIA_TYPE type)
    : q_ptr(parent)
{
    this->mSliderType = type;
    initializeBasicWidget(parent);
}

MusicProgressWidget::MusicProgressWidget(QWidget *parent, MediaUtils::MEDIA_TYPE type)
    : QWidget(parent)
    , d_ptr(new MusicProgressWidgetPrivate(this, type))
{

}

void MusicProgressWidgetPrivate::initializeBasicWidget(QWidget *parent) {
    mainLayout = new QHBoxLayout(parent);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    parent->setLayout(mainLayout);



    startTimeLabel = new QLabel(parent);
    startTimeLabel->setText("00:00");
    initLabText(startTimeLabel);
    startTimeLabel->setFixedSize(QSize(55, 15));
    mainLayout->addWidget(startTimeLabel, Qt::AlignVCenter);


    initializeSlider(parent);

    endTimeLabel = new QLabel(parent);
    endTimeLabel->setText("00:00/00:00");
    initLabText(endTimeLabel);
    mainLayout->addWidget(endTimeLabel, Qt::AlignVCenter);
    endTimeLabel->setContentsMargins(5, 0, 0, 0);


    modeBtn = new BmpButton(parent);
    modeBtn->setObjectName("music_play_mode");
    modeBtn->setFixedSize(QSize(36, 23));
    modeBtn->setNormalBmpPath(":/Res/drawable/multimedia/music_mode_loop_normal.png");
    modeBtn->setPressBmpPath(":/Res/drawable/multimedia/music_mode_loop_focus.png");
    modeBtn->setGeometry(680, 8, 0, 0);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(modeBtn, SIGNAL(released()), parent, SLOT(onClick()), type);



    switchSliderMode();
}

void MusicProgressWidget::setPlayMode(int mode) {
    Q_D(MusicProgressWidget);
    d->mPlayMode = mode;
    d->switchPlayModeView();
}

void MusicProgressWidget::onClick() {
    Q_D(MusicProgressWidget);
    d->switchPlayMode();
}

void MusicProgressWidgetPrivate::switchPlayMode() {
    switch (mPlayMode) {
    case ORDER:
        mPlayMode = LOOP;
        break;

    case RANDOM:
        //        mPlayMode = ORDER;
        mPlayMode = LOOP;
        break;
    case LOOP:
        //        mPlayMode = SINGLE_LOOP;
        mPlayMode = RANDOM;
        break;

    case SINGLE_LOOP:
        mPlayMode = RANDOM;
        break;
    }

    switchPlayModeView();


    Q_Q(MusicProgressWidget);
    emit q->switchPlayMode(mPlayMode);
}

void MusicProgressWidgetPrivate::switchPlayModeView() {
    switch (mPlayMode) {
    case ORDER:
        break;
    case RANDOM:
        modeBtn->setNormalBmpPath(":/Res/drawable/multimedia/music_mode_random_normal.png");
        modeBtn->setPressBmpPath(":/Res/drawable/multimedia/music_mode_random_focus.png");
        break;
    case LOOP:
        modeBtn->setNormalBmpPath(":/Res/drawable/multimedia/music_mode_loop_normal.png");
        modeBtn->setPressBmpPath(":/Res/drawable/multimedia/music_mode_loop_focus.png");
        modeBtn->update();
        break;
    case SINGLE_LOOP:
        break;
    }
}

void MusicProgressWidgetPrivate::switchSliderMode() {
    switch (mSliderType) {
    case MediaUtils::MUSIC:
        startTimeLabel->setVisible(false);
        modeBtn->setVisible(true);
        modeBtn->setGeometry(680, 8, 0, 0);
        break;
    case MediaUtils::VIDEO:
        endTimeLabel->setText("60:00");
        modeBtn->setVisible(false);
        startTimeLabel->setVisible(true);
        break;
    case MediaUtils::BT_MUSIC:
        modeBtn->setVisible(false);
        startTimeLabel->setVisible(false);
        break;
    }

}

void MusicProgressWidgetPrivate::initLabText(QLabel *text) {
    //设置字号
    QFont ft("Microsoft YaHei");
    ft.setPointSize(15);
    text->setFont(ft);
    //设置颜色
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);
    text->setPalette(pa);
}

void MusicProgressWidgetPrivate::initializeSlider(QWidget *parent) {
    horizontalSlider = new QSlider();
    horizontalSlider->setObjectName(QString::fromUtf8("music_horizontalSlider"));
    horizontalSlider->setMaximum(100);
    horizontalSlider->setOrientation(Qt::Horizontal);
    horizontalSlider->setFixedSize(QSize(540, 16));

    horizontalSlider->setStyleSheet("QSlider::groove:horizontal {  "
                                    "border: 1px solid #00000000;"
                                    "background: #03d396;"
                                    "height: 5px;border-radius: 1px;"
                                    "padding-left:-1px;padding-right:-1px;}"

                                    "QSlider::add-page:horizontal { "
                                    "background: #595858;"
                                    "border: 0px solid #777;"
                                    "height: 14px;"
                                    "border-radius: 2px;}"

                                    "QSlider::handle:horizontal { "
                                    "background-image:url(:/Res/drawable/multimedia/music_slider_point.png);  "
                                    "width: 14px; height: 14px;"
                                    "margin-top: -4px; margin-bottom: -5px; }"
                                    );



    horizontalSlider->setValue(0);


    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(horizontalSlider, SIGNAL(sliderMoved(int)), parent, SLOT(onSliderMove(int)), type);
    QObject::connect(horizontalSlider, SIGNAL(valueChanged(int)), parent, SLOT(onValueChanged(int)), type);
    QObject::connect(horizontalSlider, SIGNAL(actionTriggered(int)), parent, SLOT(onActionTriggered(int)), type);
    mainLayout->addWidget(horizontalSlider, Qt::AlignVCenter);
}


void MusicProgressWidget::onSliderMove(int progress) {

}
void MusicProgressWidget::onValueChanged(int value) {
    Q_D(MusicProgressWidget);
    if (d->currentOnClick) {
        d->currentOnClick = false;
        emit onSeekTo(value);
    }
}

void MusicProgressWidget::onActionTriggered(int action){
    Q_D(MusicProgressWidget);
    d->currentOnClick = true;
}

MusicProgressWidget::~MusicProgressWidget() {

}

void MusicProgressWidget::setProgress(qint64 currentPosition, qint64 duration)
{
    Q_D(MusicProgressWidget);
}
