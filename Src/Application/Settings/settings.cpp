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
    mBackground->setBackgroundBmpPath(QString(":/img/setting/img_btn_tab_bg.png"));
    mBackground->setFixedSize(QSize(800, 50));

    //    mBtnTest= new BmpButton(parent);
    //    mBtnTest->setNormalBmpPath(QString(":/Res/drawable/test/btn_n.png"));
    //    mBtnTest->setPressBmpPath(QString(":/Res/drawable/test/btn_p.png"));
    //    mBtnTest->setGeometry(600,300,195,50);

    //   q->connect(mBtnTest,SIGNAL(released()),this,SLOT(onBtnTestRelease()));

    //Setting TAB
    mBmpSoundTab = new BmpButton(parent);
    mBmpSoundTab->setText(tr("声音"));
    mBmpSoundTab->setGeometry(0,0,126,50);
    mBmpSoundTab->setVisible(true);
    mBmpBrightnessTab= new BmpButton(parent);
    mBmpBrightnessTab->setText(tr("亮度设置"));
    mBmpBrightnessTab->setVisible(true);
    mBmpBrightnessTab->setGeometry(126,0,126,50);
    mBmpSystemTab= new BmpButton(parent);
    mBmpSystemTab->setText(tr("系统"));
    mBmpSystemTab->setGeometry(252,0,126,50);
    mBmpSystemTab->setVisible(true);

    connect(mBmpSoundTab,SIGNAL(released()),this,SLOT(onBtnSoundTabClick()));
    connect(mBmpBrightnessTab,SIGNAL(released()),this,SLOT(onBtnBrightnessTabClick()));
    connect(mBmpSystemTab,SIGNAL(released()),this,SLOT(onBtnSystemTabClick()));

    mBmpSound = new BmpWidget(parent);
    mBmpSound->setGeometry(0,50,800,435);

    mBmpCentre = new BmpButton(parent);
    mBmpCentre->setText(tr("居中"));
    mBmpCentre->setGeometry(15,80,100,50);
    mBmpCentre->setNormalBmpPath(":/img/setting/img_btn_centre_a.png");
    mBmpCentre->setPressBmpPath(":/img/setting/img_btn_centre_b.png");
    connect(mBmpCentre,SIGNAL(released()),this,SLOT(onBtnCentreClick()));

    mSoundControlGroup = new BmpWidget(parent);
    mSoundControlGroup->setBackgroundBmpPath(":/img/setting/img_sound_seat_bg.png");
    mSoundControlGroup->setGeometry(80,130,250,250);

    mTopControl = new BmpButton(parent);
    mTopControl->setNormalBmpPath(":/img/setting/img_sound_seat_top_b.png");
    mTopControl->setPressBmpPath(":/img/setting/img_sound_seat_top_a.png");
    mTopControl->setGeometry(188,90,30,30);

    mBottomControl = new BmpButton(parent);
    mBottomControl->setNormalBmpPath(":/img/setting/img_sound_seat_bottom_b.png");
    mBottomControl->setPressBmpPath(":/img/setting/img_sound_seat_bottom_a.png");
    mBottomControl->setGeometry(188,380,30,30);

    mLeftControl = new BmpButton(parent);
    mLeftControl->setNormalBmpPath(":/img/setting/img_sound_seat_left_b.png");
    mLeftControl->setPressBmpPath(":/img/setting/img_sound_seat_left_a.png");
    mLeftControl->setGeometry(5,230,30,30);

    mRightControl = new BmpButton(parent);
    mRightControl->setNormalBmpPath(":/img/setting/img_sound_seat_right_b.png");
    mRightControl->setPressBmpPath(":/img/setting/img_sound_seat_right_a.png");
    mRightControl->setGeometry(370,230,30,30);

    mSeatPoint = new BmpButton(parent);
    mSeatPoint->setNormalBmpPath(":/img/setting/img_sound_seat_point_a.png");
    mSeatPoint->setPressBmpPath(":/img/setting/img_sound_seat_point_b.png");
    mSeatPoint->setGeometry(180,220,50,50);

    mBmpBrightness = new BmpWidget(parent);
    mBmpBrightness->setGeometry(0,50,800,435);

    mBmpSystem = new BmpWidget(parent);
    mBmpSystem->setGeometry(0,50,800,435);

    //def widget
    selectTab(0);

    mBmpSystem->setBackgroundBmpPath(QString(":/Res/drawable/test/settings.png"));
}

void SettingsPrivate::selectTab(int index)
{
    if(index == 0){
        mBmpSound->show();
        mBmpBrightness->hide();
        mBmpSystem->hide();

        mBmpSoundTab->setNormalBmpPath(":/img/setting/img_btn_tab_b.png");
        mBmpBrightnessTab->setNormalBmpPath(":/img/setting/img_btn_tab_a.png");
        mBmpSystemTab->setNormalBmpPath(":/img/setting/img_btn_tab_a.png");

    }else if(index == 1){
        mBmpSound->hide();
        mBmpBrightness->show();
        mBmpSystem->hide();

        mBmpSoundTab->setNormalBmpPath(":/img/setting/img_btn_tab_a.png");
        mBmpBrightnessTab->setNormalBmpPath(":/img/setting/img_btn_tab_b.png");
        mBmpSystemTab->setNormalBmpPath(":/img/setting/img_btn_tab_a.png");

    }else if(index == 2){
        mBmpSound->hide();
        mBmpBrightness->hide();
        mBmpSystem->show();

        mBmpSoundTab->setNormalBmpPath(":/img/setting/img_btn_tab_a.png");
        mBmpBrightnessTab->setNormalBmpPath(":/img/setting/img_btn_tab_a.png");
        mBmpSystemTab->setNormalBmpPath(":/img/setting/img_btn_tab_b.png");
    }
}

void SettingsPrivate::onBtnTestRelease()
{
    Q_Q(Settings);
    q->startApplication(T_Bluetooth);
}

void SettingsPrivate::onBtnSoundTabClick()
{
    selectTab(0);
}

void SettingsPrivate::onBtnBrightnessTabClick()
{
    selectTab(1);
}

void SettingsPrivate::onBtnSystemTabClick()
{
    selectTab(2);
}

void SettingsPrivate::onBtnCentreClick()
{
    this->mSeatPoint->move(180,220);
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



