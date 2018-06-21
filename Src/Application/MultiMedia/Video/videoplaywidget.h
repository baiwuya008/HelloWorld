#ifndef VIDEOPLAYWIDGET_H
#define VIDEOPLAYWIDGET_H

#include <QWidget>


class VideoPlayWidgetPrivate;
class VideoPlayWidget : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(VideoPlayWidget)
public:
    explicit VideoPlayWidget(QWidget *parent = NULL);
    ~VideoPlayWidget();
    void setPlayStatus(bool isPlay);

signals:
    void onSwitchStatus(bool isPlay);
    void onSwitchIndex(bool isNext);
    void onSwitchMode(int mode);
    void onSeekTo(int value);

public slots:
private slots:

private:
    Q_DECLARE_PRIVATE(VideoPlayWidget)
    VideoPlayWidgetPrivate* const d_ptr;
};

#endif // VIDEOPLAYWIDGET_H
