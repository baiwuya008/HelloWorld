#include "devicewatcher.h"
#include "Src/Framework/MultimediaService/DeviceWatcher/DiskScanner/diskscanner.h"
#include "Src/Framework/MultimediaService/multimediautils.h"
#include "Src/Framework/MultimediaService/MediaDb/mediadb.h"
#include <QDebug>

class DeviceWatcherPrivate {
    Q_DISABLE_COPY(DeviceWatcherPrivate)
public:
    explicit DeviceWatcherPrivate(DeviceWatcher *parent);
    ~DeviceWatcherPrivate();
    void initialize();

    DiskScanner *mUSBDiskScanner = NULL;
    const QString USB_ROOT_DIR = "D:\\QT\\DA_project\\res";
private:
    DeviceWatcher* m_Parent;
};


DeviceWatcher::DeviceWatcher(QObject *parent)
    : QObject(parent)
    , m_Private(new DeviceWatcherPrivate(this))
{

}

DeviceWatcherPrivate::DeviceWatcherPrivate(DeviceWatcher *parent) : m_Parent(parent)
{
    initialize();
}

DeviceWatcherPrivate::~DeviceWatcherPrivate()
{

}

void DeviceWatcherPrivate::initialize()
{
    g_MediaDb->initialize();

    QStringList m_MusicSuffix;
    m_MusicSuffix.clear();
    m_MusicSuffix.append(QString(".MP2"));
    m_MusicSuffix.append(QString(".MP3"));
    m_MusicSuffix.append(QString(".WMA"));
    m_MusicSuffix.append(QString(".M4A"));
    m_MusicSuffix.append(QString(".FLAC"));
    m_MusicSuffix.append(QString(".APE"));
    m_MusicSuffix.append(QString(".OGG"));
    m_MusicSuffix.append(QString(".AC3"));
    m_MusicSuffix.append(QString(".AAC"));
    m_MusicSuffix.append(QString(".WAV"));
    m_MusicSuffix.append(QString(".AMR"));
    m_MusicSuffix.append(QString(".RA"));
    m_MusicSuffix.append(QString(".AU"));
    m_MusicSuffix.append(QString(".MMF"));

    QStringList m_ImageSuffix;
    m_ImageSuffix.clear();
    m_ImageSuffix.append(QString(".JPG"));
    m_ImageSuffix.append(QString(".BMP"));
    m_ImageSuffix.append(QString(".JPEG"));
    m_ImageSuffix.append(QString(".PNG"));
    m_ImageSuffix.append(QString(".GIF"));
    QStringList m_VideoSuffix;
    m_VideoSuffix.clear();
    m_VideoSuffix.append(QString(".AVI"));
    m_VideoSuffix.append(QString(".MP4"));
    m_VideoSuffix.append(QString(".MPG"));
    m_VideoSuffix.append(QString(".M4V"));
    m_VideoSuffix.append(QString(".MKV"));
    m_VideoSuffix.append(QString(".3GP"));
    m_VideoSuffix.append(QString(".ASF"));
    m_VideoSuffix.append(QString(".MOV"));
    m_VideoSuffix.append(QString(".MPEG"));
    m_VideoSuffix.append(QString(".VOB"));
    m_VideoSuffix.append(QString(".TS"));
    m_VideoSuffix.append(QString(".WMV"));
    m_VideoSuffix.append(QString(".RM"));
    m_VideoSuffix.append(QString(".RMVB"));
    m_VideoSuffix.append(QString(".DIVX"));
    m_VideoSuffix.append(QString(".FLV"));
    m_VideoSuffix.append(QString(".SWF"));
    m_VideoSuffix.append(QString(".OGM"));
    m_VideoSuffix.append(QString(".DAT"));

    mUSBDiskScanner = new DiskScanner(m_Parent);
    mUSBDiskScanner->setMinimumScanTime(3000);
    QMap<int, QStringList> map;
    map.insert(MultimediaUtils::MUSIC, m_MusicSuffix);
    map.insert(MultimediaUtils::IMAGE, m_ImageSuffix);
    map.insert(MultimediaUtils::VIDEO, m_VideoSuffix);
    mUSBDiskScanner->setScannerSuffixMap(map);
    mUSBDiskScanner->setDeviceType(MultimediaUtils::DWT_USBDisk);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(mUSBDiskScanner, SIGNAL(scanFilePath(int,int,QString)), m_Parent, SLOT(onScanFilePath(int,int,QString)), type);
    QObject::connect(mUSBDiskScanner, &DiskScanner::scanFilesFinish, m_Parent, &DeviceWatcher::onScanFilesFinish, type);
    QObject::connect(mUSBDiskScanner, &DiskScanner::startScanFiles, m_Parent, &DeviceWatcher::onStartScanFiles, type);
    QObject::connect(mUSBDiskScanner, &DiskScanner::scanLrcInfo, m_Parent, &DeviceWatcher::onScanLrcInfo, type);
}

DeviceWatcher::~DeviceWatcher()
{

}

void DeviceWatcher::onScanFilePath(int deviceType, int mediaType, const QString &filePath)
{
    switch (mediaType) {
    case MultimediaUtils::MUSIC:
        emit onMusicFilePath(deviceType, filePath);
        break;
    case MultimediaUtils::VIDEO:
        emit onVideoFilePath(deviceType, filePath);
        break;
    case MultimediaUtils::IMAGE:
        emit onImageFilePath(deviceType, filePath);
        break;
    }
}

void DeviceWatcher::startScan(int deviceType, int mediaType)
{
    startScan(deviceType, mediaType, m_Private->USB_ROOT_DIR);
}


void DeviceWatcher::startScan(int deviceType, int mediaType, QString dir)
{
    switch (deviceType) {
    case MultimediaUtils::DWT_USBDisk:
        m_Private->mUSBDiskScanner->startScanner(mediaType, dir);
        break;
    }
}

void DeviceWatcher::scanLrc(int deviceType, QString &filePath)
{
    MediaDbEntity *entity = g_MediaDb->query(filePath);
    if (entity != NULL) {
        switch (deviceType) {
        case MultimediaUtils::DWT_USBDisk:
            m_Private->mUSBDiskScanner->scanLrc(filePath, entity->dirPath, entity->name);
            break;
        }
        delete entity;
        entity = NULL;
    }
}

void DeviceWatcher::stopScan()
{
    m_Private->mUSBDiskScanner->stopScanner();
}




