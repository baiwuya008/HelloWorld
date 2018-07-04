#ifndef BTMUSICPLAYER_H
#define BTMUSICPLAYER_H

#include <QObject>
#include "Src/Framework/MultimediaService/multimediautils.h"

class BtMusicPlayerPrivate;
class BtMusicPlayer : public QObject
{
    Q_OBJECT
public:
    explicit BtMusicPlayer(QObject *parent = NULL, int type = MultimediaUtils::MUSIC);
    ~BtMusicPlayer();

    void previous();
    void next();
    void play();
    void pause();
    void setPlayStatus(bool isPlay);
    bool isPlaying();
    void mute();
    void unmute();
    bool isConnect();
    void getInfo();
    //音乐半音 用于GPS出声时混音处理
    void gpsBackground();
    //音乐恢复正常 配合半音处理GPS出声时混音处理
    void gpsNormal();

signals:
    void onPositionChanged(int mediaType, qint64 position, qint64 duration);
    void onPlay(int mediaType, int index, QString &path, qint64 duration);
    void onResume(int mediaType);
    void onPause(int mediaType);
    void onFinish(int mediaType, bool isError);

private slots:
    void onHfpConnected();
    void onHfpDisconnected();
    void onA2dpConnected();
    void onA2dpDisconnected();
    void onResume();
    void onStop();
    void onVoiceConnected();
    void onVoiceDisconnected();
    void onInfo(QString music, QString artist,QString album,int duration,int pos,int total);
    void onPos(int current,int total);


private:
    friend class BtMusicPlayerPrivate;
    QScopedPointer<BtMusicPlayerPrivate> m_Private;
};

#endif // BTMUSICPLAYER_H
