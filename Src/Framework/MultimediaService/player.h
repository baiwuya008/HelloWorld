#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include "multimediautils.h"
#include <QMediaPlayer>
#include <QDebug>

class PlayerPrivate;
class Player : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Player)
public:
    explicit Player(QObject *parent = NULL, MultimediaType type = MultimediaUtils::MUSIC);
    ~Player();
    static QString changeDuration(qint64 duration);

signals:
    void onPositionChanged(MultimediaType type, qint64 duration, qint64 position);
    void onPlay(MultimediaType type, QString path, qint64 duration);
    void onResume(MultimediaType type);
    void onPause(MultimediaType type);
    void onFinish(MultimediaType type, bool isError);

public slots:
    void play(QString path);
    void play();
    void pause();
    void seekTo(int position);
    qint64 getCurrentPosition();
    qint64 getDuration();
    bool isPlaying();

private slots:
    void onPrepared(bool available);
    void onError(QMediaPlayer::Error error);
    void onCompletion();
    void onPositionChanged(qint64 position);
    void onStatusChanged(QMediaPlayer::State status);

private:
    friend class PlayerPrivate;
    QScopedPointer<PlayerPrivate> m_Private;
};

#endif // PLAYER_H
