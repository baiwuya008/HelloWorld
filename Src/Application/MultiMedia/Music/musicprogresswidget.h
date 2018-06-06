#ifndef MUSICPROGRESSWIDGET_H
#define MUSICPROGRESSWIDGET_H

#include <QWidget>


enum SLIDER_MODE {
    MUSIC = 1, //播放音乐的进度条显示
    VIDEO = 2, //播放视频的进度条显示
    BT_MUSIC = 3 //播放蓝牙音乐进度条显示
};

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
    explicit MusicProgressWidget(QWidget *parent, SLIDER_MODE mode);
    ~MusicProgressWidget();

signals:
    void onSeekTo(int value);
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
