#include "music.h"


MusicPrivate::MusicPrivate(Music *parent)
    : QObject(),q_ptr(parent)
{
    mBackground = NULL;
    mBtnTest = NULL;
}

void MusicPrivate::initializeBasicWidget(QWidget *parent)
{
  Q_Q(Music);

    mBackground = new BmpWidget(parent); //设置背景图片
    mBackground->setBackgroundBmpPath(QString(":/Res/drawable/test/music.png"));
    mBackground->setFixedSize(QSize(800, 480));

    mBtnTest= new BmpButton(parent);
    mBtnTest->setNormalBmpPath(QString(":/Res/drawable/test/btn_n.png"));
    mBtnTest->setPressBmpPath(QString(":/Res/drawable/test/btn_p.png"));
    mBtnTest->setGeometry(600,425,195,50);

   q->connect(mBtnTest,SIGNAL(released()),this,SLOT(onBtnTestRelease()));

}

void MusicPrivate::onBtnTestRelease()
{
  Q_Q(Music);
  q->startApplication(T_USBDiskVideo);
}

//----------------------------------

Music::Music(QObject *parent):
 Activity(parent),
 d_ptr(new MusicPrivate(this))
{

}

void Music::onCreate(QWidget *parent)
{
    Q_D(Music);
    //centralWidget = new QWidget(parent);
    d->initializeBasicWidget(parent);

    //setContentView(centralWidget);
}
void Music::onStart()
{

}
void Music::onResume()
{

}
void Music::onPause()
{

}
void Music::onStop()
{

}
void Music::onDestroy()
{

}

bool Music::onBackPressed()
{

return false;
}

void Music::onLanguageChanged()
{

}

void Music::onReceiveBroadcast(AppType appType,OMessage &msg)
{

}

void Music::onReceiveCmd(AppType appType,OMessage &msg)
{

}


