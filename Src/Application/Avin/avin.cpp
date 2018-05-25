#include "avin.h"

AvinPrivate::AvinPrivate(Avin *parent)
    : q_ptr(parent)
{
    mBackground = NULL;
    mBtnTest = NULL;
}

void AvinPrivate::initializeBasicWidget(QWidget *parent)
{
  Q_Q(Avin);

    mBackground = new BmpWidget(parent); //设置背景图片
    mBackground->setBackgroundBmpPath(QString(":/Res/drawable/test/radio.png"));
    mBackground->setFixedSize(QSize(800, 480));

    mBtnTest= new BmpButton(parent);
    mBtnTest->setNormalBmpPath(QString(":/Res/drawable/test/btn_n.png"));
    mBtnTest->setPressBmpPath(QString(":/Res/drawable/test/btn_p.png"));
    mBtnTest->setGeometry(600,425,195,50);

   q->connect(mBtnTest,SIGNAL(released()),this,SLOT(onBtnTestRelease()));

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
    centralWidget = new QWidget(parent);
    d->initializeBasicWidget(centralWidget);

    setContentView(centralWidget);
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


