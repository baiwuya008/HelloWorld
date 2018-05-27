#include "systemui.h"


SystemuiPrivate::SystemuiPrivate(Systemui *parent)
    :QObject(), q_ptr(parent)
{
    mBackground = NULL;
}

void SystemuiPrivate::initializeBasicWidget(QWidget *parent)
{
  Q_Q(Systemui);

    mBackground = new BmpWidget(parent); //设置背景图片
    mBackground->setBackgroundBmpPath(QString(":/Res/drawable/test/topbar_bg.png"));
    mBackground->setFixedSize(QSize(800, 45));

#if (STATEBAR_WITH_BACK == 1 && STATEBAR_WITH_HOME == 1)
    mBtnHome= new BmpButton(parent);
    mBtnHome->setNormalBmpPath(QString(":/Res/drawable/test/home.png"));
    mBtnHome->setPressBmpPath(QString(":/Res/drawable/test/home_pressed.png"));
    mBtnHome->setGeometry(10,5,40,32);
    q->connect(mBtnBack,SIGNAL(released()),this,SLOT(onBtnHomeRelease()));

    mBtnBack= new BmpButton(parent);
    mBtnBack->setNormalBmpPath(QString(":/Res/drawable/test/back.png"));
    mBtnBack->setPressBmpPath(QString(":/Res/drawable/test/back_pressed.png"));
    mBtnBack->setGeometry(60,5,32,32);
    q->connect(mBtnBack,SIGNAL(released()),this,SLOT(onBtnBackRelease()));

#else
    #if (STATEBAR_WITH_BACK == 1)
    mBtnBack= new BmpButton(parent);
    mBtnBack->setNormalBmpPath(QString(":/Res/drawable/test/back.png"));
    mBtnBack->setPressBmpPath(QString(":/Res/drawable/test/back_pressed.png"));
    mBtnBack->setGeometry(10,5,32,32);
    q->connect(mBtnBack,SIGNAL(released()),this,SLOT(onBtnBackRelease()));
    #endif
    #if (STATEBAR_WITH_HOME == 1)
    mBtnHome= new BmpButton(parent);
    mBtnHome->setNormalBmpPath(QString(":/Res/drawable/test/home.png"));
    mBtnHome->setPressBmpPath(QString(":/Res/drawable/test/home_pressed.png"));
    mBtnHome->setGeometry(10,5,40,32);
    q->connect(mBtnBack,SIGNAL(released()),this,SLOT(onBtnHomeRelease()));
    #endif
#endif

}

void SystemuiPrivate::onBtnBackRelease()
{
    Q_Q(Systemui);
    q->callBack();
}

void SystemuiPrivate::onBtnHomeRelease()
{
  Q_Q(Systemui);
  q->startApplication(T_Home);
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
    //centralWidget = new QWidget(parent);
    d->initializeBasicWidget(parent);

    //setContentView(centralWidget);
}
void Systemui::onStart()
{

}
void Systemui::onResume()
{

}

void Systemui::onDestroy()
{

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


