#include "aux.h"

AuxPrivate::AuxPrivate(Aux *parent)
    : q_ptr(parent)
{
    mBackground = NULL;
    mBtnTest = NULL;
}

void AuxPrivate::initializeBasicWidget(QWidget *parent)
{
  Q_Q(Aux);

    mBackground = new BmpWidget(parent); //设置背景图片
    mBackground->setBackgroundBmpPath(QString(":/Res/drawable/test/home_page_1.png"));
    mBackground->setFixedSize(QSize(800, 480));

    mBtnTest= new BmpButton(parent);
    mBtnTest->setNormalBmpPath(QString(":/Res/drawable/test/btn_n.png"));
    mBtnTest->setPressBmpPath(QString(":/Res/drawable/test/btn_p.png"));
    mBtnTest->setGeometry(600,425,195,50);

   q->connect(mBtnTest,SIGNAL(released()),this,SLOT(onBtnTestRelease()));

}

void AuxPrivate::onBtnTestRelease()
{
  Q_Q(Aux);
  q->startApplication(T_Ipod);
}

//----------------------------------

Aux::Aux(QObject *parent):
 Activity(parent),
 d_ptr(new AuxPrivate(this))
{

}

void Aux::onCreate(QWidget *parent)
{
    Q_D(Aux);
    centralWidget = new QWidget(parent);
    d->initializeBasicWidget(centralWidget);

    setContentView(centralWidget);
}
void Aux::onStart()
{

}
void Aux::onResume()
{

}
void Aux::onPause()
{

}
void Aux::onStop()
{

}
void Aux::onDestroy()
{

}

bool Aux::onBackPressed()
{

return false;
}

void Aux::onLanguageChanged()
{

}

void Aux::onReceiveBroadcast(AppType appType,OMessage &msg)
{

}

void Aux::onReceiveCmd(AppType appType,OMessage &msg)
{

}


