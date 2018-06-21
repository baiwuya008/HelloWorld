#ifndef DISKSCANNER_H
#define DISKSCANNER_H

#include <QObject>
#include <QScopedPointer>


class DiskScannerPrivate;
class DiskScanner : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(DiskScanner)
public:
    explicit DiskScanner(QObject *parent = NULL);
    ~DiskScanner();

    void setScannerSuffixMap(const QMap<int, QStringList> &mapList);
    void setMinimumScanTime(const int msec);
    void startScanner(const int mediaType, const QString &path);
    void stopScanner();
    void scanLrc(QString filePath, QString scanDir, QString scanName);
    void setDeviceType(int deviceType);
signals:
    void scanFilePath(int deviceType, int mediaType, const QString &filePath);
    void scanFilesFinish(int deviceType, int mediaType, QString path);
    void startScanFiles(int deviceType, int mediaType);
    void scanLrcInfo(QString filePath, QString title, QString artist, QString album);

public slots:
private slots:
    void onTimeout();
    void threadHandleResults(const QString &result);
    void threadFinish();
private:
    friend class DiskScannerPrivate;
    QScopedPointer<DiskScannerPrivate> m_Private;
};

#endif // DISKSCANNER_H
