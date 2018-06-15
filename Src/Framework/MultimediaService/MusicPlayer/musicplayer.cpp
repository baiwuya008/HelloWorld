#include "musicplayer.h"
#include <QStringList>
#include "Src/Framework/MultimediaService/multimediautils.h"
#include <QDebug>

class MusicPlayerPrivate {
    Q_DISABLE_COPY(MusicPlayerPrivate)
public:
    explicit MusicPlayerPrivate(MusicPlayer *parent);
    ~MusicPlayerPrivate();
    void initialize();

    QStringList* mUsbPathList = NULL;
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




