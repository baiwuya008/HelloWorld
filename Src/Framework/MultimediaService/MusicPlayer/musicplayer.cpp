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

    QStringList mUsbPathList;
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
    mUsbPathList.clear();
}

void MusicPlayer::scanMusicFilePath(int deviceType, const QString &filePath)
{

    qDebug() << "scanMusicFilePath deviceType = " << deviceType;
    switch (deviceType) {
    case MultimediaUtils::DWT_Undefined:
        break;
    case MultimediaUtils::DWT_USBDisk:
        m_Private->mUsbPathList.append(filePath);
        break;
    case MultimediaUtils::DWT_SDDisk:
        break;
    }
}


MusicPlayerPrivate::~MusicPlayerPrivate()
{

}


MusicPlayer::~MusicPlayer() {

}



