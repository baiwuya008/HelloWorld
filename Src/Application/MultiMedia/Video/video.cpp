#include "video.h"


VideoPrivate::VideoPrivate(Video *parent)
    : QObject(),q_ptr(parent)
{
    mBackground = NULL;
    mBtnTest = NULL;
}

void VideoPrivate::initializeBasicWidget(QWidget *parent)
{
  Q_Q(Video);

    mBackground = new BmpWidget(parent); //设置背景图片
    mBackground->setBackgroundBmpPath(QString(":/Res/drawable/test/video.png"));
    mBackground->setFixedSize(QSize(800, 435));

//    mBtnTest= new BmpButton(parent);
//    mBtnTest->setNormalBmpPath(QString(":/Res/drawable/test/btn_n.png"));
//    mBtnTest->setPressBmpPath(QString(":/Res/drawable/test/btn_p.png"));
//    mBtnTest->setGeometry(600,300,195,50);

//   q->connect(mBtnTest,SIGNAL(released()),this,SLOT(onBtnTestRelease()));

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


