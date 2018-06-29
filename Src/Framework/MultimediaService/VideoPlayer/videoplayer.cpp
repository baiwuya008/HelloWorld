#include "videoplayer.h"


class VideoPlayerPrivate {
    Q_DISABLE_COPY(VideoPlayerPrivate)
public:
    explicit VideoPlayerPrivate(VideoPlayer *parent);
    ~VideoPlayerPrivate();
    void initialize();
    int computePathIndex(QStringList *list, QString path);

    QStringList* mUsbPathList = NULL;
    int mDeviceType = MultimediaUtils::DWT_Undefined;
    int mCurrentScanStatus = -1;
    int mCurrentIndex = -1;

private:
    VideoPlayer *m_Parent;

};

VideoPlayer::VideoPlayer(QObject *parent)
    : QObject(parent)
    , m_Private(new VideoPlayerPrivate(this))
{

}

VideoPlayer::~VideoPlayer()
{

}


QStringList* VideoPlayer::getPathList(int deviceType)
{
    switch (deviceType) {
    case MultimediaUtils::DWT_Undefined:
        break;
    case MultimediaUtils::DWT_USBDisk:
        return m_Private->mUsbPathList;
    case MultimediaUtils::DWT_SDDisk:
        break;
    }

    return NULL;
}

void VideoPlayer::clearPathList(int deviceType)
{
    switch (deviceType) {
    case MultimediaUtils::DWT_Undefined:
        break;
    case MultimediaUtils::DWT_USBDisk:
        m_Private->mUsbPathList->clear();
        break;
    case MultimediaUtils::DWT_SDDisk:
        break;
    }
}

int VideoPlayerPrivate::computePathIndex(QStringList *list, QString path)
{
    int size = list->size();
    QString info;
    for (int i = 0; i < size; i++) {
        info = list->at(i);
        if (!info.compare(path)) {
            return i;
        }
    }
}

int VideoPlayer::getScanStatus()
{
    return m_Private->mCurrentScanStatus;
}

void VideoPlayer::scanVideoFilePath(int deviceType, const QString &filePath)
{
    switch (deviceType) {
    case MultimediaUtils::DWT_Undefined:
        break;
    case MultimediaUtils::DWT_USBDisk:
        m_Private->mUsbPathList->append(filePath);
        break;
    case MultimediaUtils::DWT_SDDisk:
        break;
    }
}

void VideoPlayer::setScanStatus(int status)
{
    m_Private->mCurrentScanStatus = status;
}

void VideoPlayer::setDeviceType(int deviceType)
{
    m_Private->mDeviceType = deviceType;
}

QString VideoPlayer::getPlayPath(int deviceType, int index)
{
    switch (deviceType) {
    case MultimediaUtils::DWT_Undefined:
        break;
    case MultimediaUtils::DWT_USBDisk:
        if (index >= 0 && index < m_Private->mUsbPathList->size()) {
            return m_Private->mUsbPathList->at(index);
        }
        break;
    case MultimediaUtils::DWT_SDDisk:
        break;
    }

    return "";
}

void VideoPlayer::startPlay(int deviceType, QString path)
{
    int index = -1;
    switch (deviceType) {
    case MultimediaUtils::DWT_Undefined:
        break;
    case MultimediaUtils::DWT_USBDisk:
        index = m_Private->computePathIndex(m_Private->mUsbPathList, path);
        if (index >= 0 && index < m_Private->mUsbPathList->size()) {
            m_Private->mCurrentIndex = index;
//            play(index, path);
        }
        break;
    case MultimediaUtils::DWT_SDDisk:
        break;
    }
}

VideoPlayerPrivate::VideoPlayerPrivate(VideoPlayer *parent) : m_Parent(parent)
{
    initialize();
}

VideoPlayerPrivate::~VideoPlayerPrivate()
{

}

void VideoPlayerPrivate::initialize()
{
    mUsbPathList = new QStringList();
}
