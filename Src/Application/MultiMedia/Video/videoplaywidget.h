#ifndef VIDEOPLAYWIDGET_H
#define VIDEOPLAYWIDGET_H

#include <QWidget>
#include "Src/Application/MultiMedia/Music/musicclickwidget.h"
#include "Src/Application/MultiMedia/Music/musicprogresswidget.h"
#include <QDebug>
#include <QVideoWidget>
#include <QHBoxLayout>
#include "Src/Framework/MultimediaService/player.h"



class VideoPlayWidgetPrivate;
class VideoPlayWidget : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(VideoPlayWidget)
public:
    explicit VideoPlayWidget(QWidget *parent = NULL);
    ~VideoPlayWidget();
    void setPlayStatus(bool isPlay);
    void playVideo(QString path, const qint64 duration);
    void preparedPlay(QString path, qint64 duration);
    void updateProgress(const qint64 currentPosition, const qint64 duration);

signals:
    void onSwitchStatus(bool isPlay);
    void onSwitchIndex(bool isNext);
    void onSwitchMode(int mode);
    void onSeekTo(int value);

    void onBackFinish();

public slots:
private slots:

private:
    Q_DECLARE_PRIVATE(VideoPlayWidget)
    VideoPlayWidgetPrivate* const d_ptr;
};

class VideoPlayWidgetPrivate : public Player
{
    Q_OBJECT
    Q_DISABLE_COPY(VideoPlayWidgetPrivate)
public:
    explicit VideoPlayWidgetPrivate(VideoPlayWidget *parent);
    ~VideoPlayWidgetPrivate();
private slots:
protected slots:
    void backPositionChanged(int mediaType, qint64 position, qint64 duration);
    void backPlay(int mediaType, int index, QString path, qint64 duration);
    void backResume(int mediaType);
    void backPause(int mediaType);
    void backFinish(int mediaType, bool isError);

private:
    Q_DECLARE_PUBLIC(VideoPlayWidget)
    VideoPlayWidget* const q_ptr;
    void initializeBasicWidget(QWidget *parent);
    void initializeClickView(QWidget *parent);
    void initializeProgressView(QWidget *parent);
    void initializeVideoView(QWidget *parent);
    void connectAllSlots();

    void updatePlayStatus(bool play);
    void updateCurrentPlay(QString path, qint64 duration);
    void updateCurrentProgress(qint64 currentPosition, qint64 duration);

    QVideoWidget *mVideoWidget = NULL;

    MusicClickWidget *mVideoClickWidget = NULL;
    MusicProgressWidget *mVideoProgressWidget = NULL;
    QWidget *mProgressContainer = NULL;
    QString mCurrentPlayPath;
};

#endif // VIDEOPLAYWIDGET_H
