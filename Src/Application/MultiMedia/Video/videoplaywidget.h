#ifndef VIDEOPLAYWIDGET_H
#define VIDEOPLAYWIDGET_H

#include <QWidget>
#include "Src/Application/MultiMedia/Music/musicclickwidget.h"
#include "Src/Application/MultiMedia/Music/musicprogresswidget.h"
#include <QDebug>
#include <QVideoWidget>
#include <QVBoxLayout>
#include "Src/Framework/MultimediaService/player.h"
#include <QTimer>
#include <QResizeEvent>
#include <QMouseEvent>


class VideoPlayWidgetPrivate;
class VideoPlayWidget : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(VideoPlayWidget)
public:
    explicit VideoPlayWidget(QWidget *parent = NULL);
    ~VideoPlayWidget();

    void setPlayPath(QString path, const qint64 duration);
    void setPlayStatus(bool isPlay);
    void setProgress(const qint64 currentPosition, const qint64 duration);

    QVideoWidget* getVideoWidget();

protected:
    void resizeEvent(QResizeEvent* event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

signals:
    void onSwitchStatus(bool isPlay);
    void onSwitchIndex(bool isNext);
    void onSeekTo(int progress);

    void videoFullScreen();
    void videoNormalScreen();

private:
    Q_DECLARE_PRIVATE(VideoPlayWidget)
    VideoPlayWidgetPrivate* const d_ptr;
};

class VideoPlayWidgetPrivate : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(VideoPlayWidgetPrivate)
public:
    explicit VideoPlayWidgetPrivate(VideoPlayWidget *parent);
    ~VideoPlayWidgetPrivate();

protected:
    void mousePressEvent();
    void mouseReleaseEvent();

private slots:
    void onTimeout();
    void onSliderPress();
    void onSliderRelease();

private:
    Q_DECLARE_PUBLIC(VideoPlayWidget)
    VideoPlayWidget* const q_ptr;
    void initializeBasicWidget(QWidget *parent);
    void initializeClickView(QWidget *parent);
    void initializeProgressView(QWidget *parent);
    void initializeVideoView(QWidget *parent);
    void initializeTimer();
    void connectAllSlots();

    void updatePlayPath(QString path, qint64 duration);
    void updateProgress(qint64 currentPosition, qint64 duration);
    void updatePlayStatus(bool isPlay);

    void stopTimerOut();
    void startTimerOut(int msec);
    void showFullView(bool isFull);

    QVBoxLayout *mVideoLayout = NULL;
    QWidget *mVideoContainer = NULL;
    QVideoWidget *mVideoWidget = NULL;
    bool isFullShow = false;
    int mPressIndex = 0;
    bool isReleaseEvent = true;
    bool isShortTime = false;
    const int LONG_TIME_OUT = 7*1000;
    const int SHORT_TIME_OUT = 1000;

    MusicClickWidget *mVideoClickWidget = NULL;
    MusicProgressWidget *mVideoProgressWidget = NULL;
    QWidget *mProgressContainer = NULL;
    QString mCurrentPlayPath;
    QTimer *mQTimer = NULL;
};

#endif // VIDEOPLAYWIDGET_H
