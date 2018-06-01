#include "avin.h"

AvinPrivate::AvinPrivate(Avin *parent)
    : QObject(),q_ptr(parent)
{
    mBackground = NULL;
    mBtnTest = NULL;
}

void AvinPrivate::initializeBasicWidget(QWidget *parent)
{
  Q_Q(Avin);

//    mBackground = new BmpWidget(parent); //设置背景图片
//    mBackground->setBackgroundBmpPath(QString(":/Res/drawable/test/logo01.png"));
//    mBackground->setFixedSize(QSize(800, 435));

//    mBtnTest= new BmpButton(parent);
//    mBtnTest->setNormalBmpPath(QString(":/Res/drawable/test/btn_n.png"));
//    mBtnTest->setPressBmpPath(QString(":/Res/drawable/test/btn_p.png"));
//    mBtnTest->setGeometry(600,300,195,50);

//   q->connect(mBtnTest,SIGNAL(released()),this,SLOT(onBtnTestRelease()));

}

void AvinPrivate::onBtnTestRelease()
{
  Q_Q(Avin);
  q->startApplication(T_Setting);
}

//----------------------------------

Avin::Avin(QObject *parent):
 Activity(parent),
 d_ptr(new AvinPrivate(this))
{

}

void Avin::onCreate(QWidget *parent)
{
    Q_D(Avin);
    d->initializeBasicWidget(parent);
}
void Avin::onStart()
{

}
void Avin::onResume()
{

}
void Avin::onPause()
{

}
void Avin::onStop()
{

}
void Avin::onDestroy()
{

}

bool Avin::onBackPressed()
{

return false;
}

void Avin::onLanguageChanged()
{

}

void Avin::onReceiveBroadcast(AppType appType,OMessage &msg)
{

}

void Avin::onReceiveCmd(AppType appType,OMessage &msg)
{

}


