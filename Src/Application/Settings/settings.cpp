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

    connect(mBmpSound,SIGNAL(mouseMove(QMouseEvent*)),this,SLOT(onBmpSoundWidgetMove(QMouseEvent*)));
    //connect(mBmpSound,SIGNAL(mousePress(QMouseEvent*)),this,SLOT(onBmpSoundWidgetPress(QMouseEvent*)));
    //connect(mBmpSound,SIGNAL(mouseRelease(QMouseEvent*)),this,SLOT(onBmpSoundWidgetRelease(QMouseEvent*)));

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

    connect(mSeatPoint,SIGNAL(OnPressed()),this,SLOT(onSeatPointDown()));
    connect(mSeatPoint,SIGNAL(released()),this,SLOT(onSeatPointUp()));

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
    //mLowSoundBg= new BmpWidget(mBmpSound);
    //mLowSoundBg->setBackgroundBmpPath(":/img/setting/img_sound_progress_bg.png");
    //mLowSoundBg->setGeometry(440,110,280,30);

    //低 点
    //mLowSoundPoint= new BmpButton(mBmpSound);
    //mLowSoundPoint->setNormalBmpPath(":/img/setting/img_sound_progress_point.png");
    //mLowSoundPoint->setPressBmpPath(":/img/setting/img_sound_progress_point.png");
    //mLowSoundPoint->setGeometry(460,110,30,30);

    mLowSoundSlider = new QSlider(mBmpSound);
    mLowSoundSlider->setGeometry(450,110,260,30);
    mLowSoundSlider->setOrientation(Qt::Horizontal);

    connect(mLowSoundSlider,SIGNAL(valueChanged(int)),this,SLOT(onLowSoundValuesChange(int)));

    mLowSoundSlider->setStyleSheet(
                "QSlider::handle:horizontal { "
                "background-image:url(:/img/setting/img_sound_progress_point.png);"
                "}"
                );

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
    //mCenSoundBg= new BmpWidget(mBmpSound);
    //mCenSoundBg->setBackgroundBmpPath(":/img/setting/img_sound_progress_bg.png");
    //mCenSoundBg->setGeometry(440,210,260,30);

    //中 点
    //mCenSoundPoint= new BmpButton(mBmpSound);
    //mCenSoundPoint->setNormalBmpPath(":/img/setting/img_sound_progress_point.png");
    //mCenSoundPoint->setPressBmpPath(":/img/setting/img_sound_progress_point.png");
    //mCenSoundPoint->setGeometry(550,210,30,30);

    mCenSoundSlider = new QSlider(mBmpSound);
    mCenSoundSlider->setGeometry(450,210,260,30);
    mCenSoundSlider->setOrientation(Qt::Horizontal);

    connect(mCenSoundSlider,SIGNAL(valueChanged(int)),this,SLOT(onCenSoundValuesChange(int)));

    mCenSoundSlider->setStyleSheet(
                "QSlider::handle:horizontal { "
                "background-image:url(:/img/setting/img_sound_progress_point.png);"
                "}"
                );

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
    //mHeightSoundBg= new BmpWidget(mBmpSound);
    //mHeightSoundBg->setBackgroundBmpPath(":/img/setting/img_sound_progress_bg.png");
    //mHeightSoundBg->setGeometry(440,310,280,30);

    //高 点
    //mHeightSoundPoint= new BmpButton(mBmpSound);
    //mHeightSoundPoint->setNormalBmpPath(":/img/setting/img_sound_progress_point.png");
    //mHeightSoundPoint->setPressBmpPath(":/img/setting/img_sound_progress_point.png");
    //mHeightSoundPoint->setGeometry(600,310,30,30);

    mHeightSoundSlider = new QSlider(mBmpSound);
    mHeightSoundSlider->setGeometry(450,310,260,30);
    mHeightSoundSlider->setOrientation(Qt::Horizontal);

    connect(mHeightSoundSlider,SIGNAL(valueChanged(int)),this,SLOT(onHeightSoundValuesChange(int)));

    mHeightSoundSlider->setStyleSheet(
                "QSlider::handle:horizontal { "
                "background-image:url(:/img/setting/img_sound_progress_point.png);"
                "}"
                );

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
    //mDisplayBg= new BmpWidget(mBmpBrightness);
    //mDisplayBg->setBackgroundBmpPath(":/img/setting/img_sound_progress_bg.png");
    //mDisplayBg->setGeometry(260,300,280,30);

    //亮度 点
    //mDisplayPoint= new BmpButton(mBmpBrightness);
    //mDisplayPoint->setNormalBmpPath(":/img/setting/img_sound_progress_point.png");
    //mDisplayPoint->setPressBmpPath(":/img/setting/img_sound_progress_point.png");
    //mDisplayPoint->setGeometry(500,300,30,30);

    //面 点 以面的坐标
    mDisplaySlider = new QSlider(mBmpBrightness);
    mDisplaySlider->setGeometry(275,300,280,30);
    mDisplaySlider->setOrientation(Qt::Horizontal);

    connect(mDisplaySlider,SIGNAL(valueChanged(int)),this,SLOT(onBrightnessValuesChange(int)));

    mDisplaySlider->setStyleSheet(
                "QSlider::handle:horizontal { "
                "background-image:url(:/img/setting/img_sound_progress_point.png);"
                "}"
                );
    //亮度 字
    mLabelmDisplay = new QLabel(mBmpBrightness);
    mLabelmDisplay->setFont(font);
    mLabelmDisplay->setPalette(pa);
    mLabelmDisplay->setText(tr("亮度"));
    mLabelmDisplay->setGeometry(380,320,50,50);

    //---------------------------------------------------------

    //系统
    mBmpSystem = new BmpWidget(parent);
    mBmpSystem->setBackgroundBmpPath(":/img/Common/img_wap_bg.png");
    mBmpSystem->setGeometry(0,50,800,435);

    mListWidget = new QListWidget(mBmpSystem);
    mListWidget->setStyleSheet("background-color:transparent");
    mListWidget->setGeometry(0,50,800,480);
    //去除白边框
    mListWidget->setFrameShape(QListWidget::NoFrame);
    //设置无焦点
    mListWidget->setFocusPolicy(Qt::NoFocus);
    //按下事件
    connect(mListWidget,SIGNAL(pressed(QModelIndex)),this,SLOT(onSystemListLanguagePressed(QModelIndex)));


    QStringList mList;
    mList << "Change Language ENGLISH";
    mList << "SW Version (MI)";
    mList << "BT Version";
    mList << "Time Format 12 Hours";
    mList << "Time Setting";
    mList << "Reset Bluetooth settings";

    for (int i = 0; i < mList.size(); ++i) {
        QListWidgetItem*item=new QListWidgetItem;
        //分割线
        QListWidgetItem*itemLine=new QListWidgetItem;
        itemLine->setBackground(QBrush(QPixmap(":/img/setting/img_setting_list_line.png")));
        itemLine->setSizeHint(QSize(20, 1.5));
        //居中
        item->setTextAlignment(Qt::AlignCenter);
        //对齐

        //行高
        item->setSizeHint(QSize(60, 40));
        //去除选中效果
        item->setFlags(item->flags() & ~Qt::ItemIsSelectable);
        item->setFont(font);
        item->setTextColor(Qt::white);
        item->setText(mList.at(i));
        mListWidget->addItem(item);
        mListWidget->addItem(itemLine);
    }

    //init
    this->initLanguageDialog();
    //def widget
    selectTab(0);
}

void SettingsPrivate::selectTab(int index)
{
    if(mLanguageDialog->isEnabled()){
        mLanguageDialog->hide();
    }
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

//init dialog
void SettingsPrivate::initLanguageDialog()
{
    QFont font("Microsoft YaHei");
    font.setPointSize(16);
    QPalette pl;
    pl.setColor(QPalette::WindowText,Qt::blue);
    const int DIALOG_W = 120;
    const int DIALOG_H = 240;
    mLanguageDialog = new QDialog(mBmpSystem);
    mLanguageDialog->resize(350,80);
    mLanguageDialog->setFixedSize(DIALOG_W,DIALOG_H);
    mLanguageDialog->setGeometry(350,100,DIALOG_W,DIALOG_H);
    mLanguageDialog->setWindowFlags(Qt::FramelessWindowHint);

    QListWidget * mLanguageListWidget = new QListWidget(mLanguageDialog);
    mLanguageListWidget->resize(DIALOG_W,DIALOG_H);

    connect(mLanguageListWidget,SIGNAL(pressed(QModelIndex)),this,SLOT(onLanguageSelectPressed(QModelIndex)));

    QStringList list;
    list << "英语";
    list << "汉语";
    list << "葡萄牙语";
    list << "西班牙语";
    list << "俄语";
    list << "法语";
    list << "阿拉伯语";
    list << "简体中文";
    list << "泰语";

    for (int i = 0; i < list.size(); ++i) {
        QListWidgetItem*item = new QListWidgetItem();
        item->setText(list.at(i));
        //居中
        //item->setTextAlignment(Qt::AlignCenter);
        item->setFont(font);
        item->setTextColor(Qt::black);

        //分割线
        QListWidgetItem*itemLine=new QListWidgetItem;
        itemLine->setBackground(QBrush(QPixmap(":/img/setting/img_setting_list_line.png")));
        itemLine->setSizeHint(QSize(20, 1.5));

        mLanguageListWidget->addItem(item);
        mLanguageListWidget->addItem(itemLine);
    }
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

void SettingsPrivate::onSeatPointDown()
{
    qDebug() << "onSeatPointDown";
    isEventSeatPoint = true;
}

void SettingsPrivate::onSeatPointUp()
{
    qDebug() << "onSeatPointUp";
    isEventSeatPoint = false;
}

void SettingsPrivate::onLowSoundValuesChange(int values)
{
    qDebug()<< "Low" << values;
}

void SettingsPrivate::onCenSoundValuesChange(int values)
{
    qDebug()<< "Cen" << values;
}

void SettingsPrivate::onHeightSoundValuesChange(int values)
{
    qDebug()<< "Height" << values;
}

void SettingsPrivate::onBrightnessValuesChange(int values)
{
    qDebug()<< "Brightness" << values;
}

void SettingsPrivate::onSystemListLanguagePressed(QModelIndex  index)
{
    qDebug() << index.row();
    switch(index.row()){
    case 0:
        mLanguageDialog->show();
        break;
    }
}

void SettingsPrivate::onLanguageSelectPressed(QModelIndex index)
{
    qDebug() << index.row();
}

//------------------------------------------------------------
void SettingsPrivate::onBmpSoundWidgetMove(QMouseEvent *e)
{
    qDebug() << e->x() << ":" << e->y();
    if(isEventSeatPoint){
        //左上：65 85 左下：65 255 右上：285 85 右下 285 255
        if(e->x() >= 65 && e->x() <= 285 && e->y() >= 85 && e->y() <= 255){
            mSeatPoint->move(e->x(),e->y());
        }
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



