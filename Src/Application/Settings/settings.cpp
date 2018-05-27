#include "settings.h"


SettingsPrivate::SettingsPrivate(Settings *parent)
    : QObject(),q_ptr(parent)
{
    mBackground = NULL;
    mBtnTest = NULL;
}

void SettingsPrivate::initializeBasicWidget(QWidget *parent)
{
  Q_Q(Settings);

    mBackground = new BmpWidget(parent); //设置背景图片
    mBackground->setBackgroundBmpPath(QString(":/Res/drawable/test/settings.png"));
    mBackground->setFixedSize(QSize(800, 480));

    mBtnTest= new BmpButton(parent);
    mBtnTest->setNormalBmpPath(QString(":/Res/drawable/test/btn_n.png"));
    mBtnTest->setPressBmpPath(QString(":/Res/drawable/test/btn_p.png"));
    mBtnTest->setGeometry(600,425,195,50);

   q->connect(mBtnTest,SIGNAL(released()),this,SLOT(onBtnTestRelease()));

}

void SettingsPrivate::onBtnTestRelease()
{
  Q_Q(Settings);
  q->startApplication(T_Bluetooth);
}

//----------------------------------

Settings::Settings(QObject *parent):
 Activity(parent),
 d_ptr(new SettingsPrivate(this))
{

}

void Settings::onCreate(QWidget *parent)
{
    Q_D(Settings);
    //centralWidget = new QWidget(parent);
    d->initializeBasicWidget(parent);

    //setContentView(centralWidget);
}
void Settings::onStart()
{

}
void Settings::onResume()
{

}
void Settings::onPause()
{

}
void Settings::onStop()
{

}
void Settings::onDestroy()
{

}

bool Settings::onBackPressed()
{

return false;
}

void Settings::onLanguageChanged()
{

}

void Settings::onReceiveBroadcast(AppType appType,OMessage &msg)
{

}

void Settings::onReceiveCmd(AppType appType,OMessage &msg)
{

}



