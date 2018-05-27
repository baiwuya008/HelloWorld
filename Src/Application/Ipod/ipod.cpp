#include "ipod.h"


IpodPrivate::IpodPrivate(Ipod *parent)
    : QObject(),q_ptr(parent)
{
    mBackground = NULL;
    mBtnTest = NULL;
}

void IpodPrivate::initializeBasicWidget(QWidget *parent)
{
  Q_Q(Ipod);

    mBackground = new BmpWidget(parent); //设置背景图片
    mBackground->setBackgroundBmpPath(QString(":/Res/drawable/test/logo01.png"));
    mBackground->setFixedSize(QSize(800, 480));

    mBtnTest= new BmpButton(parent);
    mBtnTest->setNormalBmpPath(QString(":/Res/drawable/test/btn_n.png"));
    mBtnTest->setPressBmpPath(QString(":/Res/drawable/test/btn_p.png"));
    mBtnTest->setGeometry(600,425,195,50);

   q->connect(mBtnTest,SIGNAL(released()),this,SLOT(onBtnTestRelease()));

}

void IpodPrivate::onBtnTestRelease()
{
  Q_Q(Ipod);
  q->startApplication(T_Home);
}

//----------------------------------

Ipod::Ipod(QObject *parent):
 Activity(parent),
 d_ptr(new IpodPrivate(this))
{

}

void Ipod::onCreate(QWidget *parent)
{
    Q_D(Ipod);
    //centralWidget = new QWidget(parent);
    d->initializeBasicWidget(parent);

    //setContentView(centralWidget);
}
void Ipod::onStart()
{

}
void Ipod::onResume()
{

}
void Ipod::onPause()
{

}
void Ipod::onStop()
{

}
void Ipod::onDestroy()
{

}

bool Ipod::onBackPressed()
{

return false;
}

void Ipod::onLanguageChanged()
{

}

void Ipod::onReceiveBroadcast(AppType appType,OMessage &msg)
{

}

void Ipod::onReceiveCmd(AppType appType,OMessage &msg)
{

}


