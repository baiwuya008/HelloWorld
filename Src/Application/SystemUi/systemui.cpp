#include "systemui.h"


SystemuiPrivate::SystemuiPrivate(Systemui *parent)
    : q_ptr(parent)
{
    mBackground = NULL;
    mBtnTest = NULL;
}

void SystemuiPrivate::initializeBasicWidget(QWidget *parent)
{
  Q_Q(Systemui);

    mBackground = new BmpWidget(parent); //设置背景图片
    mBackground->setBackgroundBmpPath(QString(":/Res/drawable/test/radio.png"));
    mBackground->setFixedSize(QSize(800, 480));

    mBtnTest= new BmpButton(parent);
    mBtnTest->setNormalBmpPath(QString(":/Res/drawable/test/btn_n.png"));
    mBtnTest->setPressBmpPath(QString(":/Res/drawable/test/btn_p.png"));
    mBtnTest->setGeometry(600,425,195,50);

   q->connect(mBtnTest,SIGNAL(released()),this,SLOT(onBtnTestRelease()));

}

void SystemuiPrivate::onBtnTestRelease()
{
  Q_Q(Systemui);
  q->startApplication(T_Setting);
}

//----------------------------------

Systemui::Systemui(QObject *parent):
 Activity(parent),
 d_ptr(new SystemuiPrivate(this))
{

}

void Systemui::onCreate(QWidget *parent)
{
    Q_D(Systemui);
    centralWidget = new QWidget(parent);
    d->initializeBasicWidget(centralWidget);

    setContentView(centralWidget);
}
void Systemui::onStart()
{

}
void Systemui::onResume()
{

}
void Systemui::onPause()
{

}
void Systemui::onStop()
{

}
void Systemui::onDestroy()
{

}

bool Systemui::onBackPressed()
{

return false;
}

void Systemui::onLanguageChanged()
{

}

void Systemui::onReceiveBroadcast(AppType appType,OMessage &msg)
{

}

void Systemui::onReceiveCmd(AppType appType,OMessage &msg)
{

}


