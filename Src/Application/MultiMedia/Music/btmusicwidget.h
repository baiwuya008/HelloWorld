#ifndef BTMUSICWIDGET_H
#define BTMUSICWIDGET_H

#include <QWidget>


class BtMusicWidgetPrivate;
class BtMusicWidget : public QWidget
{
    Q_OBJECT
     Q_DISABLE_COPY(BtMusicWidget)
public:
    explicit BtMusicWidget(QWidget *parent = nullptr);
    ~BtMusicWidget();

signals:

public slots:
private slots:
    void onSwitchIndex(bool isNext);
    void onSwitchStatus(bool isPlay);
private:
    Q_DECLARE_PRIVATE(BtMusicWidget)
    BtMusicWidgetPrivate* const d_ptr;
};

#endif // BTMUSICWIDGET_H
