#include "btmusic.h"

BtmusicPrivate::BtmusicPrivate(Btmusic *parent)
    : QObject(),q_ptr(parent)
{
}

void BtmusicPrivate::initializeBasicWidget(QWidget *parent)
{
    Q_Q(Btmusic);
    mBtMusicWidget = new BtMusicWidget(parent);
    mBtMusicWidget->setFixedSize(800, 435);
}

void BtmusicPrivate::onBtnTestRelease()
{
    Q_Q(Btmusic);
    q->startApplication(T_Setting);
}

//----------------------------------

Btmusic::Btmusic(QObject *parent):
    Activity(parent),
    d_ptr(new BtmusicPrivate(this))
{

}

void Btmusic::onCreate(QWidget *parent)
{
    Q_D(Btmusic);
    d->initializeBasicWidget(parent);
}
void Btmusic::onStart()
{

}
void Btmusic::onResume()
{

}
void Btmusic::onPause()
{

}
void Btmusic::onStop()
{

}
void Btmusic::onDestroy()
{

}

bool Btmusic::onBackPressed()
{

    return false;
}

void Btmusic::onLanguageChanged()
{

}

void Btmusic::onReceiveBroadcast(AppType appType,OMessage &msg)
{

}

void Btmusic::onReceiveCmd(AppType appType,OMessage &msg)
{

}


