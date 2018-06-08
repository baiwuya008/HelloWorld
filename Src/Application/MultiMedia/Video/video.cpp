#include "video.h"


VideoPrivate::VideoPrivate(Video *parent)
    : QObject(),q_ptr(parent)
{
    mBackground = NULL;
    mBtnTest = NULL;
}

void VideoPrivate::initializeBasicWidget(QWidget *parent)
{
    //    mBackground = new BmpWidget(parent); //设置背景图片
    //    mBackground->setBackgroundBmpPath(QString(":/Res/drawable/test/video.png"));
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
    initializeVideoPlay(parent);
    initializeVideoList(parent);

    setCurrentPageView(0);
}


void VideoPrivate::setWidgetBackground(QWidget *widget, QString path) {
    //设置背景图片
    widget->setAutoFillBackground(true); // 这句要加上, 否则可能显示不出背景图.
    QPalette palette = widget->palette();
    palette.setBrush(QPalette::Window,
                     QBrush(QPixmap(path).scaled(widget->size(),
                                                 Qt::IgnoreAspectRatio,
                                                 Qt::SmoothTransformation)));
    widget->setPalette(palette);
}


void VideoPrivate::setCurrentPageView(int tabIndex) {
    mStackedWidget->setCurrentIndex(tabIndex);
}


void VideoPrivate::initializeToolsWidget(QWidget *parent) {
    QList<QString> list;
    list.append("视频");
    list.append("列表");
    mMediaToolsWidget = new MediaToolsWidget(parent, list);
    connect(mMediaToolsWidget, SIGNAL(onItemClick(int)), this, SLOT(setCurrentPageView(int)));
}

void VideoPrivate::initializeVideoList(QWidget *parent)
{
    mVideoListWidget = new MusicListWidget(parent);
    connect(mVideoListWidget, SIGNAL(selectItem(QString,int)), this, SLOT(onSelectItem(QString,int)));
    mStackedWidget->insertWidget(1, mVideoListWidget);
}


void VideoPrivate::onSelectItem(QString filePath, int index) {
    qDebug() << "VideoPrivate onSelectItem filePath = " << filePath
             << "; index = " << index;
}

void VideoPrivate::initializeVideoPlay(QWidget *parent)
{
    mVideoPlayWidget = new VideoPlayWidget(parent);
    mStackedWidget->insertWidget(0, mVideoPlayWidget);
}

void VideoPrivate::onBtnTestRelease()
{
    Q_Q(Video);
    q->startApplication(T_USBDiskImage);
}

//----------------------------------

Video::Video(QObject *parent):
    Activity(parent),
    d_ptr(new VideoPrivate(this))
{

}

void Video::onCreate(QWidget *parent)
{
    Q_D(Video);
    d->initializeBasicWidget(parent);

}
void Video::onStart()
{

}
void Video::onResume()
{

}
void Video::onPause()
{

}
void Video::onStop()
{

}
void Video::onDestroy()
{

}

bool Video::onBackPressed()
{

    return false;
}

void Video::onLanguageChanged()
{

}

void Video::onReceiveBroadcast(AppType appType,OMessage &msg)
{

}

void Video::onReceiveCmd(AppType appType,OMessage &msg)
{

}


