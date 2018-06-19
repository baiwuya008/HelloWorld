#ifndef MUSICPROGRESSWIDGET_H
#define MUSICPROGRESSWIDGET_H

#include <QWidget>
#include "Src/Application/MultiMedia/Tools/mediautils.h"

typedef enum {
    ORDER = 1, //顺序播放模式
    RANDOM = 2, //随机播放模式
    LOOP = 3, //循环播放模式
    SINGLE_LOOP = 4 //单曲循环播放模式
} PLAY_MODE;
#define PLAY_MODE int

class MusicProgressWidgetPrivate;
class MusicProgressWidget : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(MusicProgressWidget)
public:
    explicit MusicProgressWidget(QWidget *parent,
                                 MediaUtils::MEDIA_TYPE type = MediaUtils::MUSIC);
    ~MusicProgressWidget();
    void setProgress(qint64 currentPosition, qint64 duration);

signals:
    void seekTo(int value);
    void switchPlayMode(int mode);

public slots:
    void setPlayMode(int mode);
private slots:
    void onSliderMove(int progress);
    void onValueChanged(int value);
    void onActionTriggered(int action);
    void onClick();

private:
    Q_DECLARE_PRIVATE(MusicProgressWidget)
    MusicProgressWidgetPrivate* const d_ptr;
};

#endif // MUSICPROGRESSWIDGET_H
