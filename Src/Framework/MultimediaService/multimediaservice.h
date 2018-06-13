#ifndef MULTIMEDIASERVICE_H
#define MULTIMEDIASERVICE_H

#include <QObject>
#include <QScopedPointer>


class MultimediaServicePrivate;
class MultimediaService : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(MultimediaService)
    //       Q_CLASSINFO("D-Bus Interface", "Local.DbusServer.Multimedia")
public:
    explicit MultimediaService(QObject *parent = 0);
    ~MultimediaService();

signals:
    void onPlay(const int mediaType, const int index,
                const QString &fileName, const long endTime);
    void onUpdateMusic(const int mediaType, const QString& title,
                       const QString& artist, const QString& album);
    void onResume(const int mediaType);
    void onPause(const int mediaType);
    void onStop(const int mediaType);
    void onSetPlayMode(const int mediaType, const int playMode);
    void onUpdateProgress(const int mediaType, const long currentPosition, const long duration);

public slots:
    void setPlayToggle(const int mediaType);
    void prev(const int mediaType);
    void next(const int mediaType);
    void setPlayMode(const int mediaType, const int playMode);
    int getPlayMode(const int mediaType);
    void playIndex(const int mediaType, const int index);
    void exitPlayer(const int mediaType);
    void seekTo(const int mediaType, const int millesimal);
    long getCurrentPosition(const int mediaType);
    long getDuration(const int mediaType);
    bool isPlaying(const int mediaType);


private:
    friend class MultimediaServicePrivate;
    QScopedPointer<MultimediaServicePrivate> m_Private;

    bool isYY = false;
};

#endif // MULTIMEDIASERVICE_H
