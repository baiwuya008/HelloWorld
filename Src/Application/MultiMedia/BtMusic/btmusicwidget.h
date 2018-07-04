#ifndef BTMUSICWIDGET_H
#define BTMUSICWIDGET_H

#include <QWidget>


class BtMusicWidgetPrivate;
class BtMusicWidget : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(BtMusicWidget)
public:
    explicit BtMusicWidget(QWidget *parent = NULL);
    ~BtMusicWidget();

signals:

public slots:
private slots:
    void backPlay(const int mediaType, const int index, QString path, const qint64 duration);
    void backPause(const int mediaType);
    void backResume(const int mediaType);
    void backStop(const int mediaType, bool isError);
    void backProgress(const int mediaType, const qint64 currentPosition, const qint64 duration);

    void setPlayStatus(bool isPlay);
    void setPlayIndex(bool isNext);
private:
    Q_DECLARE_PRIVATE(BtMusicWidget)
    BtMusicWidgetPrivate* const d_ptr;
};

#endif // BTMUSICWIDGET_H
