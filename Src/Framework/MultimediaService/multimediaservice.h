#ifndef MULTIMEDIASERVICE_H
#define MULTIMEDIASERVICE_H

#include <QObject>
#include <QScopedPointer>
#include <QVideoWidget>


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
    void onPlay(const int mediaType, const int index, QString path, const qint64 duration);
    void onResume(const int mediaType);
    void onPause(const int mediaType);
    void onStop(const int mediaType, bool isError);
    void onSetPlayMode(const int mediaType, const int playMode);
    void onUpdateProgress(const int mediaType, const qint64 currentPosition, const qint64 duration);
    void onScanFilesPath(QString xml);

public slots://提供给外部界面操作的接口
    void setPlayDeviceType(const int deviceType, const int mediaType);
    void setPlayPath(const int mediaType, const int deviceType, QString filePath);
    void setPlayStatus(const int mediaType, const bool isPlay);
    void seekTo(const int mediaType, const int progress);
    qint64 getCurrentPosition(const int mediaType);
    qint64 getDuration(const int mediaType);
    bool isPlaying(const int mediaType);
    void setPlayMode(const int mediaType, const int playMode);
    int getPlayMode(const int mediaType);
    void exitPlayer(const int mediaType);
    QString queyMediaFiles(int deviceType, int mediaType, int queryMode, QString dirPath);
    void setVideoWidget(QVideoWidget *videoWidget);


private slots:
    void onScanFilesFinish(int deviceType, int mediaType, int queryMode, QString dirPath);
    void onStartScanFiles(int deviceType, int mediaType);

    void backPlay(int mediaType, int index, QString &path, qint64 duration);
    void backResume(const int mediaType);
    void backPause(const int mediaType);
    void backStop(const int mediaType, bool isError);

private:
    friend class MultimediaServicePrivate;
    QScopedPointer<MultimediaServicePrivate> m_Private;


    bool isYY = false;
};

#endif // MULTIMEDIASERVICE_H
