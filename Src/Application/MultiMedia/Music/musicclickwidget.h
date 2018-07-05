#ifndef MUSICCLICKWIDGET_H
#define MUSICCLICKWIDGET_H

#include <QWidget>


class MusicClickWidgetPrivate;
class MusicClickWidget : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(MusicClickWidget)
public:
    explicit MusicClickWidget(QWidget *parent = NULL);
    ~MusicClickWidget();
    void setPlayStatus(bool play);
    bool isPlaying();

signals:
    void switchIndex(bool isNext);
    void switchStatus(bool isPlay);

public slots:


private slots:
    void prev();
    void next();
    void changeStatus();

private:
    Q_DECLARE_PRIVATE(MusicClickWidget)
    MusicClickWidgetPrivate* const d_ptr;

};

#endif // MUSICCLICKWIDGET_H
