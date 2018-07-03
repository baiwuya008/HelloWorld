#include "imageplayer.h"


class ImagePlayerPrivate {
    Q_DISABLE_COPY(ImagePlayerPrivate)
public:
    explicit ImagePlayerPrivate(ImagePlayer *parent);
    ~ImagePlayerPrivate();
    void initialize();
    int computePathIndex(QStringList *list, QString path);

    QStringList* mUsbPathList = NULL;
    int mDeviceType = MultimediaUtils::DWT_Undefined;
    int mCurrentIndex = -1;
    int mCurrentScanStatus = -1;

private:
    ImagePlayer *m_Parent;

};

ImagePlayer::ImagePlayer(QObject *parent, int type)
    : QObject(parent)
    , m_Private(new ImagePlayerPrivate(this))
{

}

QString ImagePlayer::getPlayPath(int deviceType, int index)
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


void ImagePlayer::scanImageFilePath(int deviceType, const QString &filePath)
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


int ImagePlayer::getScanStatus()
{
    return m_Private->mCurrentScanStatus;
}

void ImagePlayer::setScanStatus(int status)
{
    m_Private->mCurrentScanStatus = status;
}

void ImagePlayer::startPlay(int deviceType, QString path)
{
    int index = -1;
    switch (deviceType) {
    case MultimediaUtils::DWT_Undefined:
        break;
    case MultimediaUtils::DWT_USBDisk:
        index = m_Private->computePathIndex(m_Private->mUsbPathList, path);
        if (index >= 0 && index < m_Private->mUsbPathList->size()) {
            m_Private->mCurrentIndex = index;
        }
        break;
    case MultimediaUtils::DWT_SDDisk:
        break;
    }
}


int ImagePlayerPrivate::computePathIndex(QStringList *list, QString path)
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


void ImagePlayer::setDeviceType(int deviceType)
{
    m_Private->mDeviceType = deviceType;
}

void ImagePlayer::clearPathList(int deviceType)
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


QStringList* ImagePlayer::getPathList(int deviceType)
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

ImagePlayer::~ImagePlayer()
{

}

ImagePlayerPrivate::ImagePlayerPrivate(ImagePlayer *parent) : m_Parent(parent)
{
    initialize();
}

ImagePlayerPrivate::~ImagePlayerPrivate()
{

}

void ImagePlayerPrivate::initialize()
{
    mUsbPathList = new QStringList();
}
