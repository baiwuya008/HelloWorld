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

    void setPlay(const QString &fileName, const long endTime);

    void updateMusicInfo(const QString& title, const QString& artist, const QString& album);
    void updateProgress(const qint64 currentPosition, const qint64 duration);
    void updateScanFile(int index, QString path);

protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

signals:

public slots:
 void onSwitchPlayMode(int mode);
 void onSwitchStatus(bool isPlay);
private slots:
 void onSwitchIndex(bool isNext);
private:
    Q_DECLARE_PRIVATE(MusicPlayWidget)
    MusicPlayWidgetPrivate* const d_ptr;
};

#endif // MUSICPLAYWIDGET_H
