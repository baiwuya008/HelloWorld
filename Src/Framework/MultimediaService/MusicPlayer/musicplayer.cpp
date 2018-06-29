#include "musicplayer.h"
#include <QStringList>
#include "Src/Framework/MultimediaService/multimediautils.h"
#include <QDebug>
#include <QTime>

class MusicPlayerPrivate {
    Q_DISABLE_COPY(MusicPlayerPrivate)
public:
    explicit MusicPlayerPrivate(MusicPlayer *parent);
    ~MusicPlayerPrivate();
    void initialize();
    void continuePlay(int count);
    int computePathIndex(QStringList *list, QString path);
    void playPath(int deviceType, int index);

    QStringList* mUsbPathList = NULL;
    int mDeviceType = MultimediaUtils::DWT_Undefined;
    int mPlayMode = MultimediaUtils::LOOP;
    int mCurrentIndex = -1;
    int mCurrentScanStatus = -1;

private:
    MusicPlayer *m_Parent;

};

MusicPlayer::MusicPlayer(QObject *parent)
    : Player(parent)
    , m_Private(new MusicPlayerPrivate(this))
{

}


MusicPlayerPrivate::MusicPlayerPrivate(MusicPlayer *parent)
    : m_Parent(parent)
{
    initialize();
}

void MusicPlayerPrivate::initialize() {
    mUsbPathList = new QStringList();
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(m_Parent, SIGNAL(onFinish(int,bool)), m_Parent, SLOT(playFinish(int,bool)), type);
}

void MusicPlayer::scanMusicFilePath(int deviceType, const QString &filePath)
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

void MusicPlayer::playFinish(int mediaType, bool isError)
{
    if (MultimediaUtils::MUSIC == mediaType) {
        switch (m_Private->mDeviceType) {
        case MultimediaUtils::DWT_Undefined:
            break;
        case MultimediaUtils::DWT_USBDisk:
            m_Private->continuePlay(m_Private->mUsbPathList->size());
            break;
        case MultimediaUtils::DWT_SDDisk:
            break;
        }
    }
}

void MusicPlayerPrivate::continuePlay(int count)
{
    bool isPlay = false;
    switch (mPlayMode) {
    case MultimediaUtils::LOOP:
        mCurrentIndex++;
        mCurrentIndex = mCurrentIndex%count;
        isPlay = true;
        break;
    case MultimediaUtils::ORDER:
        if (mCurrentIndex < (count-1)) {
            mCurrentIndex++;
            isPlay = true;
        }
        break;
    case MultimediaUtils::SINGLE_LOOP:
        isPlay = true;
        break;
    case MultimediaUtils::RANDOM:
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        mCurrentIndex = qrand()%count;
        isPlay = true;
        break;
    }

    if (isPlay) {
        playPath(mDeviceType, mCurrentIndex);
    }
}

int MusicPlayerPrivate::computePathIndex(QStringList *list, QString path)
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

void MusicPlayerPrivate::playPath(int deviceType, int index)
{
    switch (deviceType) {
    case MultimediaUtils::DWT_Undefined:
        break;
    case MultimediaUtils::DWT_USBDisk:
        if (index >= 0 && index < mUsbPathList->size()) {
            m_Parent->startPlay(deviceType, mUsbPathList->at(index));
        }
        break;
    case MultimediaUtils::DWT_SDDisk:
        break;
    }
}

void MusicPlayer::startPlay(int deviceType, QString path)
{
    int index = -1;
    switch (deviceType) {
    case MultimediaUtils::DWT_Undefined:
        break;
    case MultimediaUtils::DWT_USBDisk:
        index = m_Private->computePathIndex(m_Private->mUsbPathList, path);
        if (index >= 0 && index < m_Private->mUsbPathList->size()) {
            m_Private->mCurrentIndex = index;
            play(index, path);
            emit requestLrc(m_Private->mDeviceType, path);
        }
        break;
    case MultimediaUtils::DWT_SDDisk:
        break;
    }
}

QString MusicPlayer::getPlayPath(int deviceType, int index)
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

void MusicPlayer::setDeviceType(int deviceType)
{
    m_Private->mDeviceType = deviceType;
}

int MusicPlayer::getMode()
{
    return m_Private->mPlayMode;
}

void MusicPlayer::setMode(int mode)
{
    m_Private->mPlayMode = mode;
}

int MusicPlayer::getScanStatus()
{
    return m_Private->mCurrentScanStatus;
}

void MusicPlayer::setScanStatus(int status)
{
    m_Private->mCurrentScanStatus = status;
}

QStringList* MusicPlayer::getPathList(int deviceType)
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

void MusicPlayer::clearPathList(int deviceType)
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


MusicPlayerPrivate::~MusicPlayerPrivate()
{
    if (mUsbPathList != NULL) {
        delete mUsbPathList;
        mUsbPathList = NULL;
    }
}

MusicPlayer::~MusicPlayer() {

}




