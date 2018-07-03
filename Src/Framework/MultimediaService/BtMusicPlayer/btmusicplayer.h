#ifndef BTMUSICPLAYER_H
#define BTMUSICPLAYER_H

#include <QObject>

class BtMusicPlayer : public QObject
{
    Q_OBJECT
public:
    explicit BtMusicPlayer(QObject *parent = nullptr);

signals:

public slots:
};

#endif // BTMUSICPLAYER_H