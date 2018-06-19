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
    void startPlay(int deviceType, int index);
    bool isNullData();

signals:

protected slots:
    void scanMusicFilePath(int deviceType, const QString &filePath);

private:
    friend class MusicPlayerPrivate;
    QScopedPointer<MusicPlayerPrivate> m_Private;
};

#endif // MUSICPLAYER_H
