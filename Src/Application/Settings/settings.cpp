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
    //设置标题背景图片
    mBackTitle = new BmpWidget(parent);
    mBackTitle->setBackgroundBmpPath(QString(":/img/setting/img_btn_tab_bg.png"));
    mBackTitle->setFixedSize(QSize(800, 50));
    //设置背景图片
    //mBackground = new BmpWidget(parent);
    //mBackground->setBackgroundBmpPath(QString(":/img/Common/img_wap_bg.png"));
    //mBackground->setFixedSize(QSize(800, 450));
    //mBackground->set

    //    mBtnTest= new BmpButton(parent);
    //    mBtnTest->setNormalBmpPath(QString(":/Res/drawable/test/btn_n.png"));
    //    mBtnTest->setPressBmpPath(QString(":/Res/drawable/test/btn_p.png"));
    //    mBtnTest->setGeometry(600,300,195,50);

    //   q->connect(mBtnTest,SIGNAL(released()),this,SLOT(onBtnTestRelease()));

    //QStackedLayout* mStackedLayout = new QStackedLayout(parent);

    QFont font("Microsoft YaHei");
    font.setPointSize(18);
    //font.setBold(true);
    //三个选项卡
    mBmpSoundTab = new BmpButton(parent);
    mBmpSoundTab->setText(tr("声音"));
    mBmpSoundTab->setGeometry(0,0,126,50);
    mBmpSoundTab->setVisible(true);
    mBmpSoundTab->setFont(font);
    mBmpBrightnessTab= new BmpButton(parent);
    mBmpBrightnessTab->setText(tr("亮度设置"));
    mBmpBrightnessTab->setVisible(true);
    mBmpBrightnessTab->setGeometry(126,0,126,50);
    mBmpBrightnessTab->setFont(font);
    mBmpSystemTab= new BmpButton(parent);
    mBmpSystemTab->setText(tr("系统"));
    mBmpSystemTab->setGeometry(252,0,126,50);
    mBmpSystemTab->setVisible(true);
    mBmpSystemTab->setFont(font);

    connect(mBmpSoundTab,SIGNAL(released()),this,SLOT(onBtnSoundTabClick()));
    connect(mBmpBrightnessTab,SIGNAL(released()),this,SLOT(onBtnBrightnessTabClick()));
    connect(mBmpSystemTab,SIGNAL(released()),this,SLOT(onBtnSystemTabClick()));

    //---------------------------------------------------------

    //声音
    mBmpSound = new BmpWidget(parent);
    mBmpSound->setBackgroundBmpPath(":/img/Common/img_wap_bg.png");
    mBmpSound->setGeometry(0,50,800,480);

    //居中按钮
    mBmpCentre = new BmpButton(mBmpSound);
    mBmpCentre->setText(tr("居中"));
    mBmpCentre->setGeometry(15,30,100,50);
    mBmpCentre->setFont(font);
    mBmpCentre->setNormalBmpPath(":/img/setting/img_btn_centre_a.png");
    mBmpCentre->setPressBmpPath(":/img/setting/img_btn_centre_b.png");
    connect(mBmpCentre,SIGNAL(released()),this,SLOT(onBtnCentreClick()));

    //座椅调节
    mSoundControlGroup = new BmpWidget(mBmpSound);
    mSoundControlGroup->setBackgroundBmpPath(":/img/setting/img_sound_seat_bg.png");
    mSoundControlGroup->setGeometry(80,80,250,250);

    mTopControl = new BmpButton(mBmpSound);
    mTopControl->setNormalBmpPath(":/img/setting/img_sound_seat_top_a.png");
    mTopControl->setPressBmpPath(":/img/setting/img_sound_seat_top_b.png");
    mTopControl->setGeometry(190,40,30,30);
    connect(mTopControl,SIGNAL(released()),this,SLOT(onBtnSoundTopClick()));

    mBottomControl = new BmpButton(mBmpSound);
    mBottomControl->setNormalBmpPath(":/img/setting/img_sound_seat_bottom_a.png");
    mBottomControl->setPressBmpPath(":/img/setting/img_sound_seat_bottom_b.png");
    mBottomControl->setGeometry(190,330,30,30);
    connect(mBottomControl,SIGNAL(released()),this,SLOT(onBtnSoundBottomClick()));

    mLeftControl = new BmpButton(mBmpSound);
    mLeftControl->setNormalBmpPath(":/img/setting/img_sound_seat_left_a.png");
    mLeftControl->setPressBmpPath(":/img/setting/img_sound_seat_left_b.png");
    mLeftControl->setGeometry(5,180,30,30);
    connect(mLeftControl,SIGNAL(released()),this,SLOT(onBtnSoundLeftClick()));

    mRightControl = new BmpButton(mBmpSound);
    mRightControl->setNormalBmpPath(":/img/setting/img_sound_seat_right_a.png");
    mRightControl->setPressBmpPath(":/img/setting/img_sound_seat_right_b.png");
    mRightControl->setGeometry(370,180,30,30);
    connect(mRightControl,SIGNAL(released()),this,SLOT(onBtnSoundRightClick()));

    mSeatPoint = new BmpButton(mBmpSound);
    mSeatPoint->setNormalBmpPath(":/img/setting/img_sound_seat_point_a.png");
    mSeatPoint->setPressBmpPath(":/img/setting/img_sound_seat_point_b.png");
    mSeatPoint->setGeometry(180,170,50,50);

    //声音调节
    mSoundSLabel = new QLabel(mBmpSound);
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);
    mSoundSLabel->setPalette(pa);
    mSoundSLabel->setVisible(true);
    mSoundSLabel->setFont(font);
    mSoundSLabel->setText(tr("按键音:打开"));
    mSoundSLabel->setGeometry(400,30,180,80);

    //开关
    mKeySoundSwitch = new BmpButton(mBmpSound);
    mKeySoundSwitch->setNormalBmpPath(":/img/setting/img_key_sound_on.png");
    mKeySoundSwitch->setGeometry(520,30,80,80);
    connect(mKeySoundSwitch,SIGNAL(released()),this,SLOT(onBtnKeySoundtClick()));

    //获取系统按键音的开关 lgl

    //声音调节
    //低 左
    mLowSoundLeft = new BmpButton(mBmpSound);
    mLowSoundLeft->setNormalBmpPath(":/img/setting/img_sound_left_a.png");
    mLowSoundLeft->setPressBmpPath(":/img/setting/img_sound_left_b.png");
    mLowSoundLeft->setGeometry(420,110,30,30);

    //低 右
    mLowSoundRight = new BmpButton(mBmpSound);
    mLowSoundRight->setNormalBmpPath(":/img/setting/img_sound_right_a.png");
    mLowSoundRight->setPressBmpPath(":/img/setting/img_sound_right_b.png");
    mLowSoundRight->setGeometry(710,110,30,30);

    //低 面
    mLowSoundBg= new BmpWidget(mBmpSound);
    mLowSoundBg->setBackgroundBmpPath(":/img/setting/img_sound_progress_bg.png");
    mLowSoundBg->setGeometry(440,110,280,30);

    //低 点
    mLowSoundPoint= new BmpButton(mBmpSound);
    mLowSoundPoint->setNormalBmpPath(":/img/setting/img_sound_progress_point.png");
    mLowSoundPoint->setPressBmpPath(":/img/setting/img_sound_progress_point.png");
    mLowSoundPoint->setGeometry(460,110,30,30);

    //低 字
    mLabelLowSound = new QLabel(mBmpSound);
    mLabelLowSound->setFont(font);
    mLabelLowSound->setPalette(pa);
    mLabelLowSound->setText(tr("低音"));
    mLabelLowSound->setGeometry(460,130,50,50);

    //中 左
    mCenSoundLeft= new BmpButton(mBmpSound);
    mCenSoundLeft->setNormalBmpPath(":/img/setting/img_sound_left_a.png");
    mCenSoundLeft->setPressBmpPath(":/img/setting/img_sound_left_b.png");
    mCenSoundLeft->setGeometry(420,210,30,30);

    //中 右
    mCenSoundRight= new BmpButton(mBmpSound);
    mCenSoundRight->setNormalBmpPath(":/img/setting/img_sound_right_a.png");
    mCenSoundRight->setPressBmpPath(":/img/setting/img_sound_right_b.png");
    mCenSoundRight->setGeometry(710,210,30,30);

    //中 面
    mCenSoundBg= new BmpWidget(mBmpSound);
    mCenSoundBg->setBackgroundBmpPath(":/img/setting/img_sound_progress_bg.png");
    mCenSoundBg->setGeometry(440,210,280,30);

    //中 点
    mCenSoundPoint= new BmpButton(mBmpSound);
    mCenSoundPoint->setNormalBmpPath(":/img/setting/img_sound_progress_point.png");
    mCenSoundPoint->setPressBmpPath(":/img/setting/img_sound_progress_point.png");
    mCenSoundPoint->setGeometry(550,210,30,30);

    //中 字
    mLabelCenSound = new QLabel(mBmpSound);
    mLabelCenSound->setFont(font);
    mLabelCenSound->setPalette(pa);
    mLabelCenSound->setText(tr("中音"));
    mLabelCenSound->setGeometry(460,230,50,50);

    //高 左
    mHeightSoundLeft= new BmpButton(mBmpSound);
    mHeightSoundLeft->setNormalBmpPath(":/img/setting/img_sound_left_a.png");
    mHeightSoundLeft->setPressBmpPath(":/img/setting/img_sound_left_b.png");
    mHeightSoundLeft->setGeometry(420,310,30,30);

    //高 右
    mHeightSoundRight= new BmpButton(mBmpSound);
    mHeightSoundRight->setNormalBmpPath(":/img/setting/img_sound_right_a.png");
    mHeightSoundRight->setPressBmpPath(":/img/setting/img_sound_right_b.png");
    mHeightSoundRight->setGeometry(710,310,30,30);

    //高 面
    mHeightSoundBg= new BmpWidget(mBmpSound);
    mHeightSoundBg->setBackgroundBmpPath(":/img/setting/img_sound_progress_bg.png");
    mHeightSoundBg->setGeometry(440,310,280,30);

    //高 点
    mHeightSoundPoint= new BmpButton(mBmpSound);
    mHeightSoundPoint->setNormalBmpPath(":/img/setting/img_sound_progress_point.png");
    mHeightSoundPoint->setPressBmpPath(":/img/setting/img_sound_progress_point.png");
    mHeightSoundPoint->setGeometry(600,310,30,30);

    //高 字
    mLabelHeightSound = new QLabel(mBmpSound);
    mLabelHeightSound->setFont(font);
    mLabelHeightSound->setPalette(pa);
    mLabelHeightSound->setText(tr("高音"));
    mLabelHeightSound->setGeometry(460,330,50,50);

    //---------------------------------------------------------

    //亮度
    mBmpBrightness = new BmpWidget(parent);
    mBmpBrightness->setBackgroundBmpPath(":/img/Common/img_wap_bg.png");
    mBmpBrightness->setGeometry(0,50,800,480);

    BmpWidget * mBmpDisplayImg = new BmpWidget(mBmpBrightness);
    mBmpDisplayImg->setBackgroundBmpPath(":/img/setting/img_display_bg.png");
    mBmpDisplayImg->setGeometry(170,10,460,260);

    //亮度 左
    mDisplayLeft= new BmpButton(mBmpBrightness);
    mDisplayLeft->setNormalBmpPath(":/img/setting/img_sound_left_a.png");
    mDisplayLeft->setPressBmpPath(":/img/setting/img_sound_left_b.png");
    mDisplayLeft->setGeometry(233,300,30,30);

    //亮度 右
    mDisplayRight= new BmpButton(mBmpBrightness);
    mDisplayRight->setNormalBmpPath(":/img/setting/img_sound_right_a.png");
    mDisplayRight->setPressBmpPath(":/img/setting/img_sound_right_b.png");
    mDisplayRight->setGeometry(566,300,30,30);

    //亮度 面
    mDisplayBg= new BmpWidget(mBmpBrightness);
    mDisplayBg->setBackgroundBmpPath(":/img/setting/img_sound_progress_bg.png");
    mDisplayBg->setGeometry(260,300,280,30);

    //亮度 点
    mDisplayPoint= new BmpButton(mBmpBrightness);
    mDisplayPoint->setNormalBmpPath(":/img/setting/img_sound_progress_point.png");
    mDisplayPoint->setPressBmpPath(":/img/setting/img_sound_progress_point.png");
    mDisplayPoint->setGeometry(500,300,30,30);

    //亮度 字
    mLabelmDisplay = new QLabel(mBmpBrightness);
    mLabelmDisplay->setFont(font);
    mLabelmDisplay->setPalette(pa);
    mLabelmDisplay->setText(tr("亮度"));
    mLabelmDisplay->setGeometry(400,320,50,50);

    //---------------------------------------------------------

    //系统
    mBmpSystem = new BmpWidget(parent);
    mBmpSystem->setBackgroundBmpPath(":/img/Common/img_wap_bg.png");
    mBmpSystem->setGeometry(0,50,800,435);

    //def widget
    selectTab(0);
}

void SettingsPrivate::selectTab(int index)
{
    if(index == 0){
        mBmpSound->setVisible(true);
        mBmpBrightness->setVisible(false);
        mBmpSystem->setVisible(false);

        mBmpSoundTab->setNormalBmpPath(":/img/setting/img_btn_tab_b.png");
        mBmpBrightnessTab->setNormalBmpPath(":/img/setting/img_btn_tab_a.png");
        mBmpSystemTab->setNormalBmpPath(":/img/setting/img_btn_tab_a.png");

    }else if(index == 1){
        mBmpSound->setVisible(false);
        mBmpBrightness->setVisible(true);
        mBmpSystem->setVisible(false);

        mBmpSoundTab->setNormalBmpPath(":/img/setting/img_btn_tab_a.png");
        mBmpBrightnessTab->setNormalBmpPath(":/img/setting/img_btn_tab_b.png");
        mBmpSystemTab->setNormalBmpPath(":/img/setting/img_btn_tab_a.png");

    }else if(index == 2){
        mBmpSound->setVisible(false);
        mBmpBrightness->setVisible(false);
        mBmpSystem->setVisible(true);

        mBmpSoundTab->setNormalBmpPath(":/img/setting/img_btn_tab_a.png");
        mBmpBrightnessTab->setNormalBmpPath(":/img/setting/img_btn_tab_a.png");
        mBmpSystemTab->setNormalBmpPath(":/img/setting/img_btn_tab_b.png");
    }
}

void SettingsPrivate::mouseMoveEvent(QMouseEvent *e)
{
    qDebug() << e->x() << ":" << e->y();
    if(e->button() == Qt::LeftButton){
        this->isClickTouch = true;
    }
}

void SettingsPrivate::mousePressEvent(QMouseEvent *e)
{
    qDebug() << "mousePressEvent";
    if(isClickTouch){
        mSeatPoint->move(e->x(),e->y());
    }
}

void SettingsPrivate::mouseReleaseEvent(QMouseEvent *e)
{
    qDebug() << "mouseReleaseEvent";
    this->isClickTouch = false;
}

void SettingsPrivate::onBtnTestRelease()
{
    Q_Q(Settings);
    q->startApplication(T_Bluetooth);
}
//check 0
void SettingsPrivate::onBtnSoundTabClick()
{
    selectTab(0);
}
//check 1
void SettingsPrivate::onBtnBrightnessTabClick()
{
    selectTab(1);
}
//check 2
void SettingsPrivate::onBtnSystemTabClick()
{
    selectTab(2);
}
//centre
void SettingsPrivate::onBtnCentreClick()
{
    this->mSeatPoint->move(180,170);
}
//top
void SettingsPrivate::onBtnSoundTopClick()
{
    qDebug() << "top";
}
//bottom
void SettingsPrivate::onBtnSoundBottomClick()
{
    qDebug() << "bottom";
}
//left
void SettingsPrivate::onBtnSoundLeftClick()
{
    qDebug() << "left";
}
//right
void SettingsPrivate::onBtnSoundRightClick()
{
    qDebug() << "right";
}
//key sound
void SettingsPrivate::onBtnKeySoundtClick()
{
    isKeySound = !isKeySound;
    if(isKeySound){
        mKeySoundSwitch->setNormalBmpPath(":/img/setting/img_key_sound_on.png");
        mKeySoundSwitch->setPressBmpPath(":/img/setting/img_key_sound_on.png");
        mKeySoundSwitch->setCheckBmpPath(":/img/setting/img_key_sound_on.png");
    }else{
        mKeySoundSwitch->setNormalBmpPath(":/img/setting/img_key_sound_off.png");
        mKeySoundSwitch->setPressBmpPath(":/img/setting/img_key_sound_off.png");
        mKeySoundSwitch->setCheckBmpPath(":/img/setting/img_key_sound_off.png");
    }
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



