#ifndef MUSICPLAYWIDGET_H
#define MUSICPLAYWIDGET_H

#include <QWidget>


class MusicPlayWidgetPrivate;
class MusicPlayWidget : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(MusicPlayWidget)
public:
    explicit MusicPlayWidget(QWidget *parent = NULL);
    ~MusicPlayWidget();

    void updateScanFile(QString path);
    void updateProgress(const qint64 currentPosition, const qint64 duration);
    void preparedPlay(QString path, qint64 duration);
    void playMusic(QString path, const qint64 duration);

    void setPlayStatus(bool isPlay);
    void setPlayMode(int mode);

signals:
    void onSwitchStatus(bool isPlay);
    void onSwitchIndex(bool isNext);
    void onSwitchMode(int mode);
    void onSeekTo(int progress);

private slots:

private:
    Q_DECLARE_PRIVATE(MusicPlayWidget)
    MusicPlayWidgetPrivate* const d_ptr;
};

#endif // MUSICPLAYWIDGET_H
