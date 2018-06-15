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


signals:
    void onPlay(const int mediaType, const int index,
                const QString &fileName, const qint64 endTime);
    void onUpdateMusic(const int mediaType, const QString& title,
                       const QString& artist, const QString& album);
    void onResume(const int mediaType);
    void onPause(const int mediaType);
    void onStop(const int mediaType);
    void onSetPlayMode(const int mediaType, const int playMode);
    void onUpdateProgress(const int mediaType, const qint64 currentPosition, const qint64 duration);

    void onScanMusicFiles(int deviceType, QStringList& pathList);
    void onScanVideoFiles(int deviceType, QStringList& pathList);
    void onScanImageFiles(int deviceType, QStringList& pathList);

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
