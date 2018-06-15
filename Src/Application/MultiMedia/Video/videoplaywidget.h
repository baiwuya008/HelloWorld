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

signals:

public slots:
private slots:
private slots:
 void onSwitchIndex(bool isNext);
 void onSwitchStatus(bool isPlay);
private:
    Q_DECLARE_PRIVATE(VideoPlayWidget)
    VideoPlayWidgetPrivate* const d_ptr;
};

#endif // VIDEOPLAYWIDGET_H
