#include "launcher.h"

LauncherPrivate::LauncherPrivate(Launcher *parent)
    :QObject(),q_ptr(parent)

{
    mBackground = NULL;
}

void LauncherPrivate::initializeBasicWidget(QWidget *parent)
{
  Q_Q(Launcher);

  const int icon_first = 88;
  const int icon_step = 175;
  const int first_line_y = 80;
  const int second_line_y = 254;
  const int icon_size = 100;

   mBackground = new BmpWidget(parent); //设置背景图片
   mBackground->setBackgroundBmpPath(QString(":/Res/drawable/test/media_home.png"));
   mBackground->setFixedSize(QSize(800, 435));


   mBtnFm = new BmpButton(parent);
   mBtnFm->setNormalBmpPath(QString(":/Res/drawable/simulation/simulation_da_btn_normal.png"));
   mBtnFm->setPressBmpPath(QString(":/Res/drawable/simulation/simulation_da_btn_pressed.png"));
   mBtnFm->setGeometry(icon_first,first_line_y,icon_size,icon_size);
   q->connect(mBtnFm,SIGNAL(released()),this,SLOT(onBtnFmRelease()));

   mBtnAm = new BmpButton(parent);
   mBtnAm->setNormalBmpPath(QString(":/Res/drawable/simulation/simulation_da_btn_normal.png"));
   mBtnAm->setPressBmpPath(QString(":/Res/drawable/simulation/simulation_da_btn_pressed.png"));
   mBtnAm->setGeometry(icon_first+icon_step,first_line_y,icon_size,icon_size);
   q->connect(mBtnAm,SIGNAL(released()),this,SLOT(onBtnAmRelease()));

   mBtnMusic = new BmpButton(parent);
   mBtnMusic->setNormalBmpPath(QString(":/Res/drawable/simulation/simulation_da_btn_normal.png"));
   mBtnMusic->setPressBmpPath(QString(":/Res/drawable/simulation/simulation_da_btn_pressed.png"));
   mBtnMusic->setGeometry(icon_first+icon_step*2,first_line_y,icon_size,icon_size);
   q->connect(mBtnMusic,SIGNAL(released()),this,SLOT(onBtnMusicRelease()));

   mBtnVideo = new BmpButton(parent);
   mBtnVideo->setNormalBmpPath(QString(":/Res/drawable/simulation/simulation_da_btn_normal.png"));
   mBtnVideo->setPressBmpPath(QString(":/Res/drawable/simulation/simulation_da_btn_pressed.png"));
   mBtnVideo->setGeometry(icon_first+icon_step*3,first_line_y,icon_size,icon_size);
   q->connect(mBtnVideo,SIGNAL(released()),this,SLOT(onBtnVideoRelease()));

   mBtnElink = new BmpButton(parent);
   mBtnElink->setNormalBmpPath(QString(":/Res/drawable/simulation/simulation_da_btn_normal.png"));
   mBtnElink->setPressBmpPath(QString(":/Res/drawable/simulation/simulation_da_btn_pressed.png"));
   mBtnElink->setGeometry(icon_first,second_line_y,icon_size,icon_size);
   q->connect(mBtnElink,SIGNAL(released()),this,SLOT(onBtnElinkRelease()));

   mBtnBlueTooth = new BmpButton(parent);
   mBtnBlueTooth->setNormalBmpPath(QString(":/Res/drawable/simulation/simulation_da_btn_normal.png"));
   mBtnBlueTooth->setPressBmpPath(QString(":/Res/drawable/simulation/simulation_da_btn_pressed.png"));
   mBtnBlueTooth->setGeometry(icon_first+icon_step,second_line_y,icon_size,icon_size);
   q->connect(mBtnBlueTooth,SIGNAL(released()),this,SLOT(onBtnBlueToothRelease()));

   mBtnImage = new BmpButton(parent);
   mBtnImage->setNormalBmpPath(QString(":/Res/drawable/simulation/simulation_da_btn_normal.png"));
   mBtnImage->setPressBmpPath(QString(":/Res/drawable/simulation/simulation_da_btn_pressed.png"));
   mBtnImage->setGeometry(icon_first+icon_step*2,second_line_y,icon_size,icon_size);
   q->connect(mBtnImage,SIGNAL(released()),this,SLOT(onBtnImagetRelease()));

   mBtnSettings = new BmpButton(parent);
   mBtnSettings->setNormalBmpPath(QString(":/Res/drawable/simulation/simulation_da_btn_normal.png"));
   mBtnSettings->setPressBmpPath(QString(":/Res/drawable/simulation/simulation_da_btn_pressed.png"));
   mBtnSettings->setGeometry(icon_first+icon_step*3,second_line_y,icon_size,icon_size);
   q->connect(mBtnSettings,SIGNAL(released()),this,SLOT(onBtnSettingsRelease()));

//   mBtnAvin = new BmpButton(parent);
//   mBtnAvin->setNormalBmpPath(QString(":/Res/drawable/test/btn_n.png"));
//   mBtnAvin->setPressBmpPath(QString(":/Res/drawable/test/btn_p.png"));
//   mBtnAvin->setGeometry(600,425,90,90);
//   q->connect(mBtnAvin,SIGNAL(released()),this,SLOT(onBtnAvinRelease()));



}


void LauncherPrivate::onBtnFmRelease()
{
  Q_Q(Launcher);
  q->startApplication(T_Radio);
}

void LauncherPrivate::onBtnAmRelease()
{
  Q_Q(Launcher);
  q->startApplication(T_RadioAm);
}

void LauncherPrivate::onBtnMusicRelease()
{
  Q_Q(Launcher);
  q->startApplication(T_USBDiskMusic);
}

void LauncherPrivate::onBtnVideoRelease()
{
  Q_Q(Launcher);
  q->startApplication(T_USBDiskVideo);
}

void LauncherPrivate::onBtnElinkRelease()
{
  //Q_Q(Launcher);
  //q->startApplication(T_Link);
}

void LauncherPrivate::onBtnBlueToothRelease()
{
  Q_Q(Launcher);
  q->startApplication(T_Bluetooth);
}

void LauncherPrivate::onBtnImagetRelease()
{
  Q_Q(Launcher);
  q->startApplication(T_USBDiskImage);
}

void LauncherPrivate::onBtnSettingsRelease()
{
  Q_Q(Launcher);
  q->startApplication(T_Setting);
}

void LauncherPrivate::onBtnAvinRelease()
{
  Q_Q(Launcher);
  q->startApplication(T_AVIN);
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
    d->initializeBasicWidget(parent);
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

