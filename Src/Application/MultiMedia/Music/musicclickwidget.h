#ifndef MUSICCLICKWIDGET_H
#define MUSICCLICKWIDGET_H

#include <QWidget>


class MusicClickWidgetPrivate;
class MusicClickWidget : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(MusicClickWidget)
public:
    explicit MusicClickWidget(QWidget *parent = nullptr);
    ~MusicClickWidget();



signals:
    void switchIndex(bool isNext);
    void changeStatus(bool isPlay);


public slots:
    void setStatus(bool play);
    void prevT();
    void nextT();


private slots:
    void switchStatus();


private:
    Q_DECLARE_PRIVATE(MusicClickWidget)
    MusicClickWidgetPrivate* const d_ptr;

};

#endif // MUSICCLICKWIDGET_H
