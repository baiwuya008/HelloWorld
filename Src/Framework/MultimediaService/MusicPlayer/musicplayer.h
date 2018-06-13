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
    explicit MusicPlayer(QObject *parent = nullptr);
    ~MusicPlayer();

signals:

protected slots:
    void scanMusicFilePath(int deviceType, const QString &filePath);

public slots:
private:
    friend class MusicPlayerPrivate;
    QScopedPointer<MusicPlayerPrivate> m_Private;
};

#endif // MUSICPLAYER_H
