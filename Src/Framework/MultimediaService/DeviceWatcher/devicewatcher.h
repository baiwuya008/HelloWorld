#ifndef DEVICEWATCHER_H
#define DEVICEWATCHER_H

#include <QObject>


class DeviceWatcherPrivate;
class DeviceWatcher : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(DeviceWatcher)
public:
    explicit DeviceWatcher(QObject *parent = NULL);
    ~DeviceWatcher();

    void startScan(int deviceType, int mediaType);
    void startScan(int deviceType, int mediaType, QString dir);
    void stopScan();
    void scanLrc(int deviceType, QString filePath);

signals:
    void onMusicFilePath(int deviceType, const QString &filePath);
    void onVideoFilePath(int deviceType, const QString &filePath);
    void onImageFilePath(int deviceType, const QString &filePath);
    void onStartScanFiles(int deviceType, int mediaType);
    void onScanFilesFinish(int deviceType, int mediaType, QString path);
    void onScanLrcInfo(QString filePath, QString title, QString artist, QString album);

private slots:
    void onScanFilePath(int deviceType, int mediaType, const QString &filePath);

private:
    friend class DeviceWatcherPrivate;
    QScopedPointer<DeviceWatcherPrivate> m_Private;
};

#endif // DEVICEWATCHER_H
