#include "launcher.h"

LauncherPrivate::LauncherPrivate(Launcher *parent)
    :QObject(),q_ptr(parent)

{
    mBackground = NULL;
    mBtnTest = NULL;
}

void LauncherPrivate::initializeBasicWidget(QWidget *parent)
{
  Q_Q(Launcher);

   mBackground = new BmpWidget(parent); //设置背景图片
   mBackground->setBackgroundBmpPath(QString(":/Res/drawable/test/media_home.png"));
   mBackground->setFixedSize(QSize(800, 480));

   mBtnTest = new BmpButton(parent);
   mBtnTest->setNormalBmpPath(QString(":/Res/drawable/test/btn_n.png"));
   mBtnTest->setPressBmpPath(QString(":/Res/drawable/test/btn_p.png"));
   mBtnTest->setGeometry(600,425,195,50);

   q->connect(mBtnTest,SIGNAL(released()),this,SLOT(onBtnTestRelease()));

}

void LauncherPrivate::onBtnTestRelease()
{
  Q_Q(Launcher);
  q->startApplication(T_Radio);
}

//----------------------------------



Launcher::Launcher(QObject *parent):
 Activity(parent),
 d_ptr(new LauncherPrivate(this))
{
}

void Launcher::onCreate(QWidget *parent)
{
    Q_D(Launcher);
    //centralWidget = new QWidget(parent);
    d->initializeBasicWidget(parent);

    //setContentView(centralWidget);

}
void Launcher::onStart()
{

}
void Launcher::onResume()
{

}
void Launcher::onPause()
{

}
void Launcher::onStop()
{

}
void Launcher::onDestroy()
{

}

bool Launcher::onBackPressed()
{

return false;
}

void Launcher::onLanguageChanged()
{

}

void Launcher::onReceiveBroadcast(AppType appType,OMessage &msg)
{

}

void Launcher::onReceiveCmd(AppType appType,OMessage &msg)
{

}

