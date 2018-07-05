#include "musicprogresswidget.h"
#include <QSlider>
#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>
#include "Src/CommonUserWidget/BmpButton.h"
#include "Src/Application/MultiMedia/Tools/mediautils.h"
#include <QMouseEvent>
#include <QCommonStyle>
#include <QtMath>


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
    void switchSliderMode();
    void switchPlayMode();
    void switchPlayModeView();
    void setCurrentProgress(qint64 currentPosition, qint64 duration);
    QString changeDuration(qint64 msec);
    bool filterSliderClick(QObject *watched, QEvent *event);

    bool isOnClick = false;
    bool isDragSlider = false;
    qint64 mDuration = 0;
    bool isSwitchMode = false;

    QHBoxLayout *mainLayout = NULL;
    QSlider *horizontalSlider = NULL;
    QLabel *startTimeLabel = NULL;
    QLabel *endTimeLabel = NULL;
    BmpButton *modeBtn = NULL;
    MediaUtils::MEDIA_TYPE mMediaType;
    int mPlayMode = MediaUtils::LOOP;
};


MusicProgressWidgetPrivate::MusicProgressWidgetPrivate(MusicProgressWidget *parent, MediaUtils::MEDIA_TYPE type)
    : q_ptr(parent)
{
    this->mMediaType = type;
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
    MediaUtils::setLabText(startTimeLabel, 15);
    startTimeLabel->setFixedSize(QSize(55, 15));
    mainLayout->addWidget(startTimeLabel, Qt::AlignVCenter);


    initializeSlider(parent);

    endTimeLabel = new QLabel(parent);
    endTimeLabel->setText("00:00/00:00");
    MediaUtils::setLabText(endTimeLabel, 15);
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
    if (!isSwitchMode) {
        return;
    }

    switch (mPlayMode) {
    case MediaUtils::ORDER:
        mPlayMode = MediaUtils::LOOP;
        break;

    case MediaUtils::RANDOM:
        //        mPlayMode = ORDER;
        mPlayMode = MediaUtils::LOOP;
        break;
    case MediaUtils::LOOP:
        //        mPlayMode = SINGLE_LOOP;
        mPlayMode = MediaUtils::RANDOM;
        break;

    case MediaUtils::SINGLE_LOOP:
        mPlayMode = MediaUtils::RANDOM;
        break;
    }

    switchPlayModeView();


    Q_Q(MusicProgressWidget);
    emit q->switchPlayMode(mPlayMode);
}

void MusicProgressWidgetPrivate::switchPlayModeView() {
    switch (mPlayMode) {
    case MediaUtils::ORDER:
        break;
    case MediaUtils::RANDOM:
        modeBtn->setNormalBmpPath(":/Res/drawable/multimedia/music_mode_random_normal.png");
        modeBtn->setPressBmpPath(":/Res/drawable/multimedia/music_mode_random_focus.png");
        break;
    case MediaUtils::LOOP:
        modeBtn->setNormalBmpPath(":/Res/drawable/multimedia/music_mode_loop_normal.png");
        modeBtn->setPressBmpPath(":/Res/drawable/multimedia/music_mode_loop_focus.png");
        modeBtn->update();
        break;
    case MediaUtils::SINGLE_LOOP:
        break;
    }
}



void MusicProgressWidgetPrivate::switchSliderMode() {
    switch (mMediaType) {
    case MediaUtils::MUSIC:
        startTimeLabel->setVisible(false);
        modeBtn->setVisible(true);
        modeBtn->setGeometry(680, 8, 0, 0);
        break;
    case MediaUtils::VIDEO:
        endTimeLabel->setText("00:00");
        modeBtn->setVisible(false);
        startTimeLabel->setVisible(true);
        break;
    case MediaUtils::BT_MUSIC:
        modeBtn->setVisible(false);
        startTimeLabel->setVisible(false);
        break;
    }

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
    horizontalSlider->installEventFilter(parent);
    mainLayout->addWidget(horizontalSlider, Qt::AlignVCenter);

    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(horizontalSlider, SIGNAL(sliderMoved(int)), parent, SLOT(onSliderMove(int)), type);
    QObject::connect(horizontalSlider, SIGNAL(valueChanged(int)), parent, SLOT(onValueChanged(int)), type);
    QObject::connect(horizontalSlider, SIGNAL(actionTriggered(int)), parent, SLOT(onActionTriggered(int)), type);
    QObject::connect(horizontalSlider, SIGNAL(sliderPressed()), parent, SLOT(onSliderPressed()), type);
    QObject::connect(horizontalSlider, SIGNAL(sliderReleased()), parent, SLOT(onSliderReleased()), type);
}

bool MusicProgressWidget::eventFilter(QObject *watched, QEvent *event)
{
    Q_D(MusicProgressWidget);
    d->filterSliderClick(watched, event);
    return QObject::eventFilter(watched, event);
}

bool MusicProgressWidgetPrivate::filterSliderClick(QObject *watched, QEvent *event)
{
    if (QEvent::MouseButtonPress == event->type()) {
        Q_Q(MusicProgressWidget);
        q->sliderMousePress();

        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        //        int dur = horizontalSlider->maximum() - horizontalSlider->minimum();
        //        int value = horizontalSlider->minimum() + dur * ((double)mouseEvent->x() / horizontalSlider->width());
        QCommonStyle style;
        int value = style.sliderValueFromPosition(horizontalSlider->minimum(),
                                                  horizontalSlider->maximum(),
                                                  mouseEvent->pos().x(),
                                                  horizontalSlider->width());

        if(value != horizontalSlider->sliderPosition() && value <= 100) {
            Q_Q(MusicProgressWidget);
            emit q->seekTo(value);
            horizontalSlider->setValue(value);
            return true;
        }
    }else if (QEvent::MouseButtonRelease == event->type()) {
        Q_Q(MusicProgressWidget);
        q->sliderMouseRelease();
    }

    return false;
}


void MusicProgressWidget::onSliderPressed()
{
}

void MusicProgressWidget::onSliderReleased() {
    Q_D(MusicProgressWidget);
    if (d->isDragSlider) {
        d->isDragSlider = false;
        emit seekTo(d->horizontalSlider->value());
    }
}

void MusicProgressWidget::onSliderMove(int progress) {
}
void MusicProgressWidget::onValueChanged(int progress) {
    Q_D(MusicProgressWidget);
    if (d->isOnClick) {
        d->isOnClick = false;
        if (d->mDuration > 0) {
            emit seekTo(progress);
        }
    }
}

void MusicProgressWidget::onActionTriggered(int action){
    Q_D(MusicProgressWidget);
    if (3 == action || 4 == action) {//点击改变进度条进度, 不会触发sliderPressed和sliderReleased事件
        d->isOnClick = true;
    }else if (7 == action) {//拖动进度条, 会触发sliderPressed和sliderReleased事件
        if (!d->isDragSlider) {
            d->isDragSlider = true;
            emit sliderSwitchStatus(false);
        }
    }
}

MusicProgressWidget::~MusicProgressWidget() {

}

void MusicProgressWidget::setProgress(qint64 currentPosition, qint64 duration)
{
    Q_D(MusicProgressWidget);
    d->setCurrentProgress(currentPosition, duration);
}

void MusicProgressWidget::setPrepare(bool isPrepare)
{
    Q_D(MusicProgressWidget);
    d->isSwitchMode = isPrepare;
}



void MusicProgressWidgetPrivate::setCurrentProgress(qint64 currentPosition, qint64 duration)
{
    this->mDuration = duration;
    QString totalDuration = changeDuration(duration);
    QString currentDuration = changeDuration(currentPosition);
    int progress = (int) round((1.0 * currentPosition * 100) / duration);

    horizontalSlider->setValue(progress);
    switch (mMediaType) {
    case MediaUtils::BT_MUSIC:
    case MediaUtils::MUSIC:
        endTimeLabel->setText(currentDuration+"/"+totalDuration);
        break;
    case MediaUtils::VIDEO:
        startTimeLabel->setText(currentDuration);
        endTimeLabel->setText(totalDuration);
        break;
    }
}

QString MusicProgressWidgetPrivate::changeDuration(qint64 msec) {
    if (msec < 1000) {
        return "00:00";
    }

    msec = msec / 1000;// 转换成秒

    int minute = (int) (msec / 60);
    int sec = (int) (msec % 60);
    QString seconds = NULL;
    QString min = NULL;
    if (sec < 10) {
        seconds = "0" +  QString::number(sec);
    } else {
        seconds = "" +  QString::number(sec);
    }

    if (minute < 10) {
        min = "0" + QString::number(minute);
    } else {
        min = "" + QString::number(minute);
    }

    return min + ":" + seconds;
}



