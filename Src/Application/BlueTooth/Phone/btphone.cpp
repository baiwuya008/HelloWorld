#include "btphone.h"

BtphonePrivate::BtphonePrivate(Btphone *parent)
    : q_ptr(parent)
{
    mBackground = NULL;
    mBtnTest = NULL;
}

void BtphonePrivate::initializeBasicWidget(QWidget *parent)
{
  Q_Q(Btphone);

    mBackground = new BmpWidget(parent); //设置背景图片
    mBackground->setBackgroundBmpPath(QString(":/Res/drawable/test/bt_phone.png"));
    mBackground->setFixedSize(QSize(800, 435));

//    mBtnTest= new BmpButton(parent);
//    mBtnTest->setNormalBmpPath(QString(":/Res/drawable/test/btn_n.png"));
//    mBtnTest->setPressBmpPath(QString(":/Res/drawable/test/btn_p.png"));
//    mBtnTest->setGeometry(600,300,195,50);

//   q->connect(mBtnTest,SIGNAL(released()),this,SLOT(onBtnTestRelease()));

}

void BtphonePrivate::onBtnTestRelease()
{
  Q_Q(Btphone);
  q->startApplication(T_USBDiskMusic);
}

//----------------------------------

Btphone::Btphone(QObject *parent):
 Activity(parent),
 d_ptr(new BtphonePrivate(this))
{

}

void Btphone::onCreate(QWidget *parent)
{
    Q_D(Btphone);
    d->initializeBasicWidget(parent);
}
void Btphone::onStart()
{

}
void Btphone::onResume()
{

}
void Btphone::onPause()
{

}
void Btphone::onStop()
{

}
void Btphone::onDestroy()
{

}

bool Btphone::onBackPressed()
{

return false;
}

void Btphone::onLanguageChanged()
{

}

void Btphone::onReceiveBroadcast(AppType appType,OMessage &msg)
{

}

void Btphone::onReceiveCmd(AppType appType,OMessage &msg)
{

}


