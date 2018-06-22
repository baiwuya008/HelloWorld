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

    QStringList* mUsbPathList = NULL;
    int mDeviceType = MultimediaUtils::DWT_Undefined;
    int mPlayMode = MultimediaUtils::LOOP;
    int mCurrentIndex = -1;

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

void MusicPlayer::playFinish(int mediaType)
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
        m_Parent->startPlay(mDeviceType, mCurrentIndex);
    }
}

void MusicPlayer::startPlay(int deviceType, int index)
{
    switch (deviceType) {
    case MultimediaUtils::DWT_Undefined:
        break;
    case MultimediaUtils::DWT_USBDisk:
        if (index >= 0 && index < m_Private->mUsbPathList->size()) {
            m_Private->mCurrentIndex = index;
            play(index, m_Private->mUsbPathList->at(index));
            emit requestLrc(m_Private->mDeviceType, m_Private->mUsbPathList->at(index));
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

bool MusicPlayer::isNullData()
{
    if (m_Private->mUsbPathList->size() < 1) {
        return true;
    }

    return false;
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




