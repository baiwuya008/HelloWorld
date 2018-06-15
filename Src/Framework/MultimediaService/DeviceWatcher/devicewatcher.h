#ifndef DEVICEWATCHER_H
#define DEVICEWATCHER_H

#include <QObject>


class DeviceWatcherPrivate;
class DeviceWatcher : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(DeviceWatcher)
public:
    explicit DeviceWatcher(QObject *parent = 0);
    ~DeviceWatcher();

signals:
    void onMusicFilePath(int deviceType, const QString &filePath);
    void onVideoFilePath(int deviceType, const QString &filePath);
    void onImageFilePath(int deviceType, const QString &filePath);
    void onStartScanFiles(int deviceType, int mediaType);
    void onScanFilesFinish(int deviceType, int mediaType);

private slots:
    void onScanFilePath(int deviceType, int mediaType, const QString &filePath);


public slots:
    void startScan(int deviceType, int mediaType);
    void startScan(int deviceType, int mediaType, QString dir);
    void stopScan();
private:
    friend class DeviceWatcherPrivate;
    QScopedPointer<DeviceWatcherPrivate> m_Private;
};

#endif // DEVICEWATCHER_H
