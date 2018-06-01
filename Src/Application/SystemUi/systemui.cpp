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
    mBackground->setGeometry(0,0,800,45);
    mBackground->setVisible(true);

    //init System Time
    mSyTime = new BmpButton(parent);
    QFont font("Microsoft YaHei");
    font.setPixelSize(20);
    mSyTime->setFont(font);
    mSyTime->setGeometry(690,5,110,45);
    mSyTime->setVisible(true);

    //def time
    this->getSyTime();

    QTimer *syTimer = new QTimer(this);
    connect( syTimer,SIGNAL(timeout()), this, SLOT(getSyTime()) );

    //start system time timer
    syTimer->start(1000);

#if (STATEBAR_WITH_BACK == 1 && STATEBAR_WITH_HOME == 1)
    mBtnHome= new BmpButton(parent);
    mBtnHome->setNormalBmpPath(QString(":/img/SystemUI/img_home_a.png"));
    mBtnHome->setPressBmpPath(QString(":/img/SystemUI/img_home_b.png"));
    mBtnHome->setGeometry(10,5,40,32);
    mBtnHome->setVisible(true);
    q->connect(mBtnHome,SIGNAL(released()),this,SLOT(onBtnHomeRelease()));

    mBtnBack= new BmpButton(parent);
    mBtnBack->setNormalBmpPath(QString(":/img/SystemUI/img_back_a.png"));
    mBtnBack->setPressBmpPath(QString(":/img/SystemUI/img_back_b.png"));
    mBtnBack->setGeometry(80,5,32,32);
    mBtnBack->setVisible(true);
    q->connect(mBtnBack,SIGNAL(released()),this,SLOT(onBtnBackRelease()));

#else
#if (STATEBAR_WITH_BACK == 1)
    mBtnBack= new BmpButton(parent);
    mBtnBack->setNormalBmpPath(QString(":/img/SystemUI/img_back_a.png"));
    mBtnBack->setPressBmpPath(QString(":/img/SystemUI/img_back_b.png"));
    mBtnBack->setGeometry(10,5,32,32);
    mBtnBack->setVisible(true);
    q->connect(mBtnBack,SIGNAL(released()),this,SLOT(onBtnBackRelease()));
#endif
#if (STATEBAR_WITH_HOME == 1)
    mBtnHome= new BmpButton(parent);
    mBtnHome->setNormalBmpPath(QString(":/img/SystemUI/img_home_a.png"));
    mBtnHome->setPressBmpPath(QString(":/img/SystemUI/img_home_b.png"));
    mBtnHome->setGeometry(10,5,40,32);
    mBtnHome->setVisible(true);
    q->connect(mBtnHome,SIGNAL(released()),this,SLOT(onBtnHomeRelease()));
#endif
#endif

}

void SystemuiPrivate::getSyTime()
{
    currentTime = QTime::currentTime();
    mLo = QLocale::English;
    time = mLo.toString(currentTime,"hh:mm AP");
    mSyTime->setText(time);
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


