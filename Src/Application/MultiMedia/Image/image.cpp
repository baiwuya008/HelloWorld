#include "image.h"


ImagePrivate::ImagePrivate(Image *parent)
    : q_ptr(parent)
{
    mBackground = NULL;
    mBtnTest = NULL;
}

void ImagePrivate::initializeBasicWidget(QWidget *parent)
{
  Q_Q(Image);

    mBackground = new BmpWidget(parent); //设置背景图片
    mBackground->setBackgroundBmpPath(QString(":/Res/drawable/test/radio.png"));
    mBackground->setFixedSize(QSize(800, 480));

    mBtnTest= new BmpButton(parent);
    mBtnTest->setNormalBmpPath(QString(":/Res/drawable/test/btn_n.png"));
    mBtnTest->setPressBmpPath(QString(":/Res/drawable/test/btn_p.png"));
    mBtnTest->setGeometry(600,425,195,50);

   q->connect(mBtnTest,SIGNAL(released()),this,SLOT(onBtnTestRelease()));

}

void ImagePrivate::onBtnTestRelease()
{
  Q_Q(Image);
  q->startApplication(T_Setting);
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
    centralWidget = new QWidget(parent);
    d->initializeBasicWidget(centralWidget);

    setContentView(centralWidget);
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


