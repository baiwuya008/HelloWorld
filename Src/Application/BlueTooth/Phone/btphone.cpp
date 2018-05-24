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
    mBackground->setBackgroundBmpPath(QString(":/Res/drawable/test/radio.png"));
    mBackground->setFixedSize(QSize(800, 480));

    mBtnTest= new BmpButton(parent);
    mBtnTest->setNormalBmpPath(QString(":/Res/drawable/test/btn_n.png"));
    mBtnTest->setPressBmpPath(QString(":/Res/drawable/test/btn_p.png"));
    mBtnTest->setGeometry(600,425,195,50);

   q->connect(mBtnTest,SIGNAL(released()),this,SLOT(onBtnTestRelease()));

}

void BtphonePrivate::onBtnTestRelease()
{
  Q_Q(Btphone);
  q->startApplication(T_Setting);
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
    centralWidget = new QWidget(parent);
    d->initializeBasicWidget(centralWidget);

    setContentView(centralWidget);
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


