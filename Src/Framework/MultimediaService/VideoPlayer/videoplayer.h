#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QObject>
#include "Src/Framework/MultimediaService/player.h"
#include <QScopedPointer>

class VideoPlayerPrivate;
class VideoPlayer : public Player
{
    Q_OBJECT
    Q_DISABLE_COPY(VideoPlayer)
public:
    explicit VideoPlayer(QObject *parent = NULL, int type = MultimediaUtils::VIDEO);
    ~VideoPlayer();

    QStringList* getPathList(int deviceType);
    void clearPathList(int deviceType);
    void startPlay(int deviceType, QString path);
    QString getPlayPath(int deviceType, int index);
    void setDeviceType(int deviceType);
    int getScanStatus();
    void setScanStatus(int status);

signals:

protected slots:
    void scanVideoFilePath(int deviceType, const QString &filePath);

public slots:

private:
    friend class VideoPlayerPrivate;
    QScopedPointer<VideoPlayerPrivate> m_Private;
};

#endif // VIDEOPLAYER_H
