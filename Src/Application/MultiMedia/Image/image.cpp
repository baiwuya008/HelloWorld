#include "image.h"


ImagePrivate::ImagePrivate(Image *parent)
    : QObject(),q_ptr(parent)
{
    mBackground = NULL;
    mBtnTest = NULL;
}

void ImagePrivate::initializeBasicWidget(QWidget *parent)
{
  Q_Q(Image);

    mBackground = new BmpWidget(parent); //设置背景图片
    mBackground->setBackgroundBmpPath(QString(":/Res/drawable/test/image.png"));
    mBackground->setFixedSize(QSize(800, 435));

//    mBtnTest= new BmpButton(parent);
//    mBtnTest->setNormalBmpPath(QString(":/Res/drawable/test/btn_n.png"));
//    mBtnTest->setPressBmpPath(QString(":/Res/drawable/test/btn_p.png"));
//    mBtnTest->setGeometry(600,300,195,50);

//   q->connect(mBtnTest,SIGNAL(released()),this,SLOT(onBtnTestRelease()));

}

void ImagePrivate::onBtnTestRelease()
{
  Q_Q(Image);
  q->startApplication(T_Home);
}

//----------------------------------

Image::Image(QObject *parent):
 Activity(parent),
 d_ptr(new ImagePrivate(this))
{

}

void Image::onCreate(QWidget *parent)
{
    Q_D(Image);
    d->initializeBasicWidget(parent);
}
void Image::onStart()
{

}
void Image::onResume()
{

}
void Image::onPause()
{

}
void Image::onStop()
{

}
void Image::onDestroy()
{

}

bool Image::onBackPressed()
{

return false;
}

void Image::onLanguageChanged()
{

}

void Image::onReceiveBroadcast(AppType appType,OMessage &msg)
{

}

void Image::onReceiveCmd(AppType appType,OMessage &msg)
{

}


