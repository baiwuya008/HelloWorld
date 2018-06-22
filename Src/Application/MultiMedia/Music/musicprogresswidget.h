#ifndef MUSICPROGRESSWIDGET_H
#define MUSICPROGRESSWIDGET_H

#include <QWidget>
#include "Src/Application/MultiMedia/Tools/mediautils.h"

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
    void setPrepare(bool isPrepare);

signals:
    void seekTo(int progress);
    void switchPlayMode(int mode);
    void sliderSwitchStatus(bool isPlay);

protected:
   bool eventFilter(QObject *watched, QEvent *event);

public slots:
    void setPlayMode(int mode);
private slots:
    void onSliderPressed();
    void onSliderReleased();
    void onSliderMove(int progress);
    void onValueChanged(int progress);
    void onActionTriggered(int action);
    void onClick();

private:
    Q_DECLARE_PRIVATE(MusicProgressWidget)
    MusicProgressWidgetPrivate* const d_ptr;
};

#endif // MUSICPROGRESSWIDGET_H
