#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QObject>
#include "Src/Framework/MultimediaService/player.h"
#include <QScopedPointer>

class MusicPlayerPrivate;
class MusicPlayer : public Player
{
    Q_OBJECT
public:
    explicit MusicPlayer(QObject *parent = NULL);
    ~MusicPlayer();

    QStringList* getPathList(int deviceType);
    void clearPathList(int deviceType);
    void startPlay(int deviceType, QString path);
    QString getPlayPath(int deviceType, int index);
    void setDeviceType(int deviceType);
    int getMode();
    void setMode(int mode);
    int getScanStatus();
    void setScanStatus(int status);


signals:
    void requestLrc(int deviceType, QString filePath);

protected slots:
    void scanMusicFilePath(int deviceType, const QString &filePath);
private:
    void playFinish(int mediaType) override;

private:
    friend class MusicPlayerPrivate;
    QScopedPointer<MusicPlayerPrivate> m_Private;
};

#endif // MUSICPLAYER_H
