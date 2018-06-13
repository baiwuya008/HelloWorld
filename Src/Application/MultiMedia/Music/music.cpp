#include "music.h"


MusicPrivate::MusicPrivate(Music *parent)
    : QObject(),q_ptr(parent)
{
    mBackground = NULL;
    mBtnTest = NULL;
}

void MusicPrivate::initializeBasicWidget(QWidget *parent)
{
    Q_Q(Music);

    //    mBackground = new BmpWidget(parent); //设置背景图片
    //    mBackground->setBackgroundBmpPath(QString(":/Res/drawable/test/music.png"));
    //    mBackground->setFixedSize(QSize(800, 435));

    //    mBtnTest= new BmpButton(parent);
    //    mBtnTest->setNormalBmpPath(QString(":/Res/drawable/test/btn_n.png"));
    //    mBtnTest->setPressBmpPath(QString(":/Res/drawable/test/btn_p.png"));
    //    mBtnTest->setGeometry(600,300,195,50);

    //   q->connect(mBtnTest,SIGNAL(released()),this,SLOT(onBtnTestRelease()));

    setWidgetBackground(parent, ":/img/Common/img_wap_bg.png");

    mStackedWidget = new QStackedWidget(parent);
    mStackedWidget->setFixedSize(QSize(800, 435));
    mStackedWidget->setGeometry(0, 50, 0, 0);

    initializeToolsWidget(parent);
    initializePlayView(parent);
    initializeListView(parent);

    connectMultimediaSlots();

    setCurrentPageView(0);
}

void MusicPrivate::setWidgetBackground(QWidget *widget, QString path) {
    //设置背景图片
    widget->setAutoFillBackground(true); // 这句要加上, 否则可能显示不出背景图.
    QPalette palette = widget->palette();
    palette.setBrush(QPalette::Window,
                     QBrush(QPixmap(path).scaled(widget->size(),
                                                 Qt::IgnoreAspectRatio,
                                                 Qt::SmoothTransformation)));
    widget->setPalette(palette);
}


void MusicPrivate::initializeToolsWidget(QWidget *parent) {
    QList<QString> list;
    list.append("音乐");
    list.append("列表");
    mMediaToolsWidget = new MediaToolsWidget(parent, list);
    connect(mMediaToolsWidget, SIGNAL(onItemClick(int)), this, SLOT(setCurrentPageView(int)));
}

void MusicPrivate::setCurrentPageView(int tabIndex) {
    mStackedWidget->setCurrentIndex(tabIndex);
}



void MusicPrivate::initializePlayView(QWidget *parent) {
    mMusicPlayWidget = new MusicPlayWidget(parent);
    mStackedWidget->insertWidget(0, mMusicPlayWidget);
}



void MusicPrivate::initializeListView(QWidget *parent) {
    mMusicListWidget = new MusicListWidget(parent);
    mStackedWidget->insertWidget(1, mMusicListWidget);
    connect(mMusicListWidget, SIGNAL(selectItem(QString,int)), this, SLOT(onSelectItem(QString,int)));
}

void MusicPrivate::connectMultimediaSlots()
{
 connect(g_Multimedia, SIGNAL(onPlay(int, int, QString, long)), this, SLOT(setPlayMusic(int, int, QString, long)));
}



void MusicPrivate::setPlayMusic(const int mediaType, const int index, const QString &fileName, const long endTime)
{
    if (mediaType != MediaUtils::MUSIC) {
        return;
    }


    qDebug() << " MusicPrivate::setPlayMusic fileName = " << fileName
             << "; endTime = " << endTime
             << "; index = " << index;
    mMusicListWidget->setPlayIndex(index);
    mMusicPlayWidget->setPlay(fileName, endTime);
}

void MusicPrivate::onSelectItem(QString filePath, int index) {
    qDebug() << "onSelectItem filePath = " << filePath
             << "; index = " << index;
}
void MusicPrivate::onBtnTestRelease()
{
    Q_Q(Music);
    q->startApplication(T_USBDiskVideo);
}

//----------------------------------

Music::Music(QObject *parent):
    Activity(parent),
    d_ptr(new MusicPrivate(this))
{
    //    setFixedSize(QSize(800, 435));
}

void Music::onCreate(QWidget *parent)
{
    Q_D(Music);
    //centralWidget = new QWidget(parent);
    d->initializeBasicWidget(parent);

    //setContentView(centralWidget);
}
void Music::onStart()
{

}
void Music::onResume()
{

}
void Music::onPause()
{

}
void Music::onStop()
{

}
void Music::onDestroy()
{

}

bool Music::onBackPressed()
{

    return false;
}

void Music::onLanguageChanged()
{

}

void Music::onReceiveBroadcast(AppType appType,OMessage &msg)
{

}

void Music::onReceiveCmd(AppType appType,OMessage &msg)
{

}


