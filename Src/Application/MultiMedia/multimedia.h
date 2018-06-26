#ifndef MULTIMEDIA_H
#define MULTIMEDIA_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QCoreApplication>
#include "Src/Application/MultiMedia/Tools/mediautils.h"

class MultimediaPrivate;
class Multimedia : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Multimedia)
#define g_Multimedia (Multimedia::instance())
public:
    inline static Multimedia* instance() {
        static Multimedia* multimedia(new Multimedia(qApp));
        return multimedia;
    }


public://界面操作的接口
    void setPlayStatus(const int mediaType, bool isPlay);
    void setPlayMode( const int mediaType, const int playMode);
    int getPlayMode(const int mediaType);
    void setPlayPath(const int mediaType, const int deviceType, QString filePath);
    void exitPlayer(const int mediaType);
    void seekTo(const int mediaType, const int msec);
    qint64 getCurrentPosition(const int mediaType);
    qint64 getDuration(const int mediaType);
    bool isPlaying(const int mediaType);
    void queryMediaFiles(int deviceType, int mediaType, int queryMode, QString dirPath);


signals:
    void onPlay(const int mediaType, const int index,
                const QString filePath, const qint64 duration);
    void onResume(const int mediaType);
    void onPause(const int mediaType);
    void onStop(const int mediaType, bool isError);
    void onSetPlayMode(const int mediaType, const int playMode);
    void onUpdateProgress(const int mediaType, const qint64 currentPosition, const qint64 duration);

    void onScanMusicFiles(int deviceType, int queryMode, QString dirPath, QStringList& pathList);
    void onScanVideoFiles(int deviceType, int queryMode, QString dirPath, QStringList& pathList);
    void onScanImageFiles(int deviceType, int queryMode, QString dirPath, QStringList& pathList);
    void onUpdateMusicInfo(const QString filePath, const QString title, const QString artist, const QString album);

private slots:
    void readFilesPathXml(QString xml);


private:
    explicit Multimedia(QObject* parent = NULL);
    ~Multimedia();
    void initializePrivate();
    friend class MultimediaPrivate;
    QScopedPointer<MultimediaPrivate> m_Private;
};

#endif // MULTIMEDIA_H
