#include "radio.h"

RadioPrivate::RadioPrivate(Radio *parent)
    : QObject(),q_ptr(parent)
{
    mBackground = NULL;
    mBtnTest = NULL;
}

void RadioPrivate::initializeBasicWidget(QWidget *parent)
{
  Q_Q(Radio);

    mBackground = new BmpWidget(parent); //设置背景图片
    mBackground->setBackgroundBmpPath(QString(":/Res/drawable/test/radio.png"));
    mBackground->setFixedSize(QSize(800, 480));

    mBtnTest= new BmpButton(parent);
    mBtnTest->setNormalBmpPath(QString(":/Res/drawable/test/btn_n.png"));
    mBtnTest->setPressBmpPath(QString(":/Res/drawable/test/btn_p.png"));
    mBtnTest->setGeometry(600,425,195,50);

   q->connect(mBtnTest,SIGNAL(released()),this,SLOT(onBtnTestRelease()));

}

void RadioPrivate::onBtnTestRelease()
{
  Q_Q(Radio);
  q->startApplication(T_Setting);
}

//----------------------------------

Radio::Radio(QObject *parent):
 Activity(parent),
 d_ptr(new RadioPrivate(this))
{

}

void Radio::onCreate(QWidget *parent)
{
    Q_D(Radio);
    centralWidget = new QWidget(parent);
    d->initializeBasicWidget(centralWidget);

    setContentView(centralWidget);
}
void Radio::onStart()
{

}
void Radio::onResume()
{

}
void Radio::onPause()
{

}
void Radio::onStop()
{

}
void Radio::onDestroy()
{

}

bool Radio::onBackPressed()
{

return false;
}

void Radio::onLanguageChanged()
{

}

void Radio::onReceiveBroadcast(AppType appType,OMessage &msg)
{

}

void Radio::onReceiveCmd(AppType appType,OMessage &msg)
{

}


