#include "btmusic.h"

BtmusicPrivate::BtmusicPrivate(Btmusic *parent)
    : QObject(),q_ptr(parent)
{
    mBackground = NULL;
    mBtnTest = NULL;
}

void BtmusicPrivate::initializeBasicWidget(QWidget *parent)
{
  Q_Q(Btmusic);

    mBackground = new BmpWidget(parent); //设置背景图片
    mBackground->setBackgroundBmpPath(QString(":/Res/drawable/test/logo01.png"));
    mBackground->setFixedSize(QSize(800, 480));

    mBtnTest= new BmpButton(parent);
    mBtnTest->setNormalBmpPath(QString(":/Res/drawable/test/btn_n.png"));
    mBtnTest->setPressBmpPath(QString(":/Res/drawable/test/btn_p.png"));
    mBtnTest->setGeometry(600,425,195,50);

   q->connect(mBtnTest,SIGNAL(released()),this,SLOT(onBtnTestRelease()));

}

void BtmusicPrivate::onBtnTestRelease()
{
  Q_Q(Btmusic);
  q->startApplication(T_Setting);
}

//----------------------------------

Btmusic::Btmusic(QObject *parent):
 Activity(parent),
 d_ptr(new BtmusicPrivate(this))
{

}

void Btmusic::onCreate(QWidget *parent)
{
    Q_D(Btmusic);
    //centralWidget = new QWidget(parent);
    d->initializeBasicWidget(parent);

    //setContentView(centralWidget);
}
void Btmusic::onStart()
{

}
void Btmusic::onResume()
{

}
void Btmusic::onPause()
{

}
void Btmusic::onStop()
{

}
void Btmusic::onDestroy()
{

}

bool Btmusic::onBackPressed()
{

return false;
}

void Btmusic::onLanguageChanged()
{

}

void Btmusic::onReceiveBroadcast(AppType appType,OMessage &msg)
{

}

void Btmusic::onReceiveCmd(AppType appType,OMessage &msg)
{

}


