#include "radio_am.h"

RadioAmPrivate::RadioAmPrivate(RadioAm *parent)
    : QObject(),q_ptr(parent)
{
    mBackground = NULL;
    mBtnTest = NULL;
}

void RadioAmPrivate::initializeBasicWidget(QWidget *parent)
{
  Q_Q(RadioAm);

//    mBackground = new BmpWidget(parent); //设置背景图片
//    mBackground->setBackgroundBmpPath(QString(":/Res/drawable/test/raido_am.png"));
//    mBackground->setFixedSize(QSize(800, 435));

//    mBtnTest= new BmpButton(parent);
//    mBtnTest->setNormalBmpPath(QString(":/Res/drawable/test/btn_n.png"));
//    mBtnTest->setPressBmpPath(QString(":/Res/drawable/test/btn_p.png"));
//    mBtnTest->setGeometry(600,300,195,50);

//   q->connect(mBtnTest,SIGNAL(released()),this,SLOT(onBtnTestRelease()));

}

void RadioAmPrivate::onBtnTestRelease()
{
  Q_Q(RadioAm);
  q->startApplication(T_Setting);
}

//----------------------------------

RadioAm::RadioAm(QObject *parent):
 Activity(parent),
 d_ptr(new RadioAmPrivate(this))
{

}

void RadioAm::onCreate(QWidget *parent)
{
    Q_D(RadioAm);
    d->initializeBasicWidget(parent);
}
void RadioAm::onStart()
{

}
void RadioAm::onResume()
{

}
void RadioAm::onPause()
{

}
void RadioAm::onStop()
{

}
void RadioAm::onDestroy()
{

}

bool RadioAm::onBackPressed()
{

return false;
}

void RadioAm::onLanguageChanged()
{

}

void RadioAm::onReceiveBroadcast(AppType appType,OMessage &msg)
{

}

void RadioAm::onReceiveCmd(AppType appType,OMessage &msg)
{

}


