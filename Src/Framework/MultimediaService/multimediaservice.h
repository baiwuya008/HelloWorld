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
    explicit MultimediaService(QObject *parent = NULL);
    ~MultimediaService();

signals:
    void onPlay(const int mediaType, const int index,
                const QString filePath, const qint64 duration);
    void onResume(const int mediaType);
    void onPause(const int mediaType);
    void onStop(const int mediaType, bool isError);
    void onSetPlayMode(const int mediaType, const int playMode);
    void onUpdateProgress(const int mediaType, const qint64 currentPosition, const qint64 duration);
    void onUpdateMusic(const QString filePath, const QString title, const QString artist, const QString album);
    void onScanFilesPath(QString xml);

public slots://提供给外部界面操作的接口
    void setPlayStatus(const int mediaType, const bool isPlay);
    void setPlayIndex(const int mediaType, const int deviceType, const int index);
    void seekTo(const int mediaType, const int progress);
    qint64 getCurrentPosition(const int mediaType);
    qint64 getDuration(const int mediaType);
    bool isPlaying(const int mediaType);
    void setPlayMode(const int mediaType, const int playMode);
    int getPlayMode(const int mediaType);
    void exitPlayer(const int mediaType);

private slots:
    void onScanFilesFinish(int deviceType, int mediaType, QString dirPath);
    void onStartScanFiles(int deviceType, int mediaType);


private:
    friend class MultimediaServicePrivate;
    QScopedPointer<MultimediaServicePrivate> m_Private;


    bool isYY = false;
};

#endif // MULTIMEDIASERVICE_H
