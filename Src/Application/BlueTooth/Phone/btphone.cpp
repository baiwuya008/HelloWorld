#include "btphone.h"
#include <QDebug>

BtphonePrivate::BtphonePrivate(Btphone *parent)
    : q_ptr(parent)
{

}

void BtphonePrivate::initializeBasicWidget(QWidget *parent)
{
		
    mStackedWidget = new QStackedWidget(parent);
    mStackedWidget->setFixedSize(QSize(800, 435));
    mStackedWidget->setGeometry(0, 0, 0, 0);\

    mPhoneDevicesWidget = new PhoneDevicesWidget(parent);
    mBtPhoneWidget = new BtPhoneWidget(parent);

    mStackedWidget->insertWidget(0, mPhoneDevicesWidget);
    mStackedWidget->insertWidget(1, mBtPhoneWidget);

    mStackedWidget->setCurrentIndex(0);
    connect(mPhoneDevicesWidget,SIGNAL(onPhoneItemClick()),this,SLOT(switchWidget()));
}

void BtphonePrivate::onBtnTestRelease()
{
  Q_Q(Btphone);
    q->startApplication(T_USBDiskMusic);
}

//切换页面
void BtphonePrivate::switchWidget()
{
    mStackedWidget->setCurrentIndex(1);
}

//----------------------------------

Btphone::Btphone(QObject *parent):
 Activity(parent),
 d_ptr(new BtphonePrivate(this))
{

}

void Btphone::onCreate(QWidget *parent)
{
    Q_D(Btphone);
    d->initializeBasicWidget(parent);
}
void Btphone::onStart()
{

}
void Btphone::onResume()
{

}
void Btphone::onPause()
{

}
void Btphone::onStop()
{

}
void Btphone::onDestroy()
{

}

bool Btphone::onBackPressed()
{

return false;
}

void Btphone::onLanguageChanged()
{

}

void Btphone::onReceiveBroadcast(AppType appType,OMessage &msg)
{

}

void Btphone::onReceiveCmd(AppType appType,OMessage &msg)
{

}




