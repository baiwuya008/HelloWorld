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

    //声音
    mBmpSound = new BmpWidget(parent);
    mBmpSound->setBackgroundBmpPath(":/img/Common/img_wap_bg.png");
    mBmpSound->setGeometry(0,50,800,435);

    //居中按钮
    mBmpCentre = new BmpButton(parent);
    mBmpCentre->setText(tr("居中"));
    mBmpCentre->setGeometry(15,80,100,50);
    mBmpCentre->setFont(font);
    mBmpCentre->setNormalBmpPath(":/img/setting/img_btn_centre_a.png");
    mBmpCentre->setPressBmpPath(":/img/setting/img_btn_centre_b.png");
    connect(mBmpCentre,SIGNAL(released()),this,SLOT(onBtnCentreClick()));

    //座椅调节
    mSoundControlGroup = new BmpWidget(parent);
    mSoundControlGroup->setBackgroundBmpPath(":/img/setting/img_sound_seat_bg.png");
    mSoundControlGroup->setGeometry(80,130,250,250);

    mTopControl = new BmpButton(parent);
    mTopControl->setNormalBmpPath(":/img/setting/img_sound_seat_top_a.png");
    mTopControl->setPressBmpPath(":/img/setting/img_sound_seat_top_b.png");
    mTopControl->setGeometry(188,90,30,30);
    connect(mTopControl,SIGNAL(released()),this,SLOT(onBtnSoundTopClick()));

    mBottomControl = new BmpButton(parent);
    mBottomControl->setNormalBmpPath(":/img/setting/img_sound_seat_bottom_a.png");
    mBottomControl->setPressBmpPath(":/img/setting/img_sound_seat_bottom_b.png");
    mBottomControl->setGeometry(188,380,30,30);
    connect(mBottomControl,SIGNAL(released()),this,SLOT(onBtnSoundBottomClick()));

    mLeftControl = new BmpButton(parent);
    mLeftControl->setNormalBmpPath(":/img/setting/img_sound_seat_left_a.png");
    mLeftControl->setPressBmpPath(":/img/setting/img_sound_seat_left_b.png");
    mLeftControl->setGeometry(5,230,30,30);
    connect(mLeftControl,SIGNAL(released()),this,SLOT(onBtnSoundLeftClick()));

    mRightControl = new BmpButton(parent);
    mRightControl->setNormalBmpPath(":/img/setting/img_sound_seat_right_a.png");
    mRightControl->setPressBmpPath(":/img/setting/img_sound_seat_right_b.png");
    mRightControl->setGeometry(370,230,30,30);
    connect(mRightControl,SIGNAL(released()),this,SLOT(onBtnSoundRightClick()));

    mSeatPoint = new BmpButton(parent);
    mSeatPoint->setNormalBmpPath(":/img/setting/img_sound_seat_point_a.png");
    mSeatPoint->setPressBmpPath(":/img/setting/img_sound_seat_point_b.png");
    mSeatPoint->setGeometry(180,220,50,50);

    //声音调节
    mSoundSLabel = new QLabel(parent);
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);
    mSoundSLabel->setPalette(pa);
    mSoundSLabel->setVisible(true);
    mSoundSLabel->setFont(font);
    mSoundSLabel->setText(tr("按键音:打开"));
    mSoundSLabel->setGeometry(400,80,180,80);

    //开关
    mKeySoundSwitch = new BmpButton(parent);
    mKeySoundSwitch->setNormalBmpPath(":/img/setting/img_key_sound_on.png");
    mKeySoundSwitch->setGeometry(520,80,80,80);
    connect(mKeySoundSwitch,SIGNAL(released()),this,SLOT(onBtnKeySoundtClick()));

    //获取系统按键音的开关 lgl

    //声音调节
    //低 左
    mLowSoundLeft = new BmpButton(parent);
    mLowSoundLeft->setNormalBmpPath(":/img/setting/img_sound_left_a.png");
    mLowSoundLeft->setPressBmpPath(":/img/setting/img_sound_left_b.png");
    mLowSoundLeft->setGeometry(420,160,30,30);

    //低 右
    mLowSoundRight = new BmpButton(parent);
    mLowSoundRight->setNormalBmpPath(":/img/setting/img_sound_right_a.png");
    mLowSoundRight->setPressBmpPath(":/img/setting/img_sound_right_b.png");
    mLowSoundRight->setGeometry(710,160,30,30);

    //低 面
    mLowSoundBg= new BmpWidget(parent);
    mLowSoundBg->setBackgroundBmpPath(":/img/setting/img_sound_progress_bg.png");
    mLowSoundBg->setGeometry(440,160,280,30);

    //低 点
    mLowSoundPoint= new BmpButton(parent);
    mLowSoundPoint->setNormalBmpPath(":/img/setting/img_sound_progress_point.png");
    mLowSoundPoint->setPressBmpPath(":/img/setting/img_sound_progress_point.png");
    mLowSoundPoint->setGeometry(460,160,30,30);

    //低 字
    mLabelLowSound = new QLabel(parent);
    mLabelLowSound->setFont(font);
    mLabelLowSound->setPalette(pa);
    mLabelLowSound->setText(tr("低音"));
    mLabelLowSound->setGeometry(460,180,50,50);

    //中 左
    mCenSoundLeft= new BmpButton(parent);
    mCenSoundLeft->setNormalBmpPath(":/img/setting/img_sound_left_a.png");
    mCenSoundLeft->setPressBmpPath(":/img/setting/img_sound_left_b.png");
    mCenSoundLeft->setGeometry(420,260,30,30);

    //中 右
    mCenSoundRight= new BmpButton(parent);
    mCenSoundRight->setNormalBmpPath(":/img/setting/img_sound_right_a.png");
    mCenSoundRight->setPressBmpPath(":/img/setting/img_sound_right_b.png");
    mCenSoundRight->setGeometry(710,260,30,30);

    //中 面
    mCenSoundBg= new BmpWidget(parent);
    mCenSoundBg->setBackgroundBmpPath(":/img/setting/img_sound_progress_bg.png");
    mCenSoundBg->setGeometry(440,260,280,30);

    //中 点
    mCenSoundPoint= new BmpButton(parent);
    mCenSoundPoint->setNormalBmpPath(":/img/setting/img_sound_progress_point.png");
    mCenSoundPoint->setPressBmpPath(":/img/setting/img_sound_progress_point.png");
    mCenSoundPoint->setGeometry(550,260,30,30);

    //中 字
    mLabelCenSound = new QLabel(parent);
    mLabelCenSound->setFont(font);
    mLabelCenSound->setPalette(pa);
    mLabelCenSound->setText(tr("中音"));
    mLabelCenSound->setGeometry(460,280,50,50);

    //高 左
    mHeightSoundLeft= new BmpButton(parent);
    mHeightSoundLeft->setNormalBmpPath(":/img/setting/img_sound_left_a.png");
    mHeightSoundLeft->setPressBmpPath(":/img/setting/img_sound_left_b.png");
    mHeightSoundLeft->setGeometry(420,360,30,30);

    //高 右
    mHeightSoundRight= new BmpButton(parent);
    mHeightSoundRight->setNormalBmpPath(":/img/setting/img_sound_right_a.png");
    mHeightSoundRight->setPressBmpPath(":/img/setting/img_sound_right_b.png");
    mHeightSoundRight->setGeometry(710,360,30,30);

    //高 面
    mHeightSoundBg= new BmpWidget(parent);
    mHeightSoundBg->setBackgroundBmpPath(":/img/setting/img_sound_progress_bg.png");
    mHeightSoundBg->setGeometry(440,360,280,30);

    //高 点
    mHeightSoundPoint= new BmpButton(parent);
    mHeightSoundPoint->setNormalBmpPath(":/img/setting/img_sound_progress_point.png");
    mHeightSoundPoint->setPressBmpPath(":/img/setting/img_sound_progress_point.png");
    mHeightSoundPoint->setGeometry(600,360,30,30);

    //高 字
    mLabelHeightSound = new QLabel(parent);
    mLabelHeightSound->setFont(font);
    mLabelHeightSound->setPalette(pa);
    mLabelHeightSound->setText(tr("高音"));
    mLabelHeightSound->setGeometry(460,380,50,50);

    //亮度
    mBmpBrightness = new BmpWidget(parent);
    mBmpBrightness->setGeometry(0,50,800,435);

    //系统
    mBmpSystem = new BmpWidget(parent);
    mBmpSystem->setGeometry(0,50,800,435);

    //def widget
    selectTab(0);

    mBmpBrightness->setBackgroundBmpPath(QString(":/Res/drawable/test/settings.png"));
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
    this->mSeatPoint->move(180,220);
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



