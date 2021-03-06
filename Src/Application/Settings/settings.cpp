#include "settings.h"

#define LINE_MIN 5
#define LINE_MAX 95

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

    QString Linestyle = "QSlider::groove:horizontal"
                        "{"
                        "   border-image:url(:/img/setting/img_sound_progress_bg.png);"
                        "}"
                        "QSlider::handle:horizontal"
                        "{"
                        "   border-image:url(:/img/setting/img_sound_progress_point.png);"
                        "   margin: -1px -5px -5px -5px;"
                        "}";

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
    mSoundSLabel->setGeometry(400,30,180,80);

    //开关
    mKeySoundSwitch = new BmpButton(mBmpSound);
    mKeySoundSwitch->setNormalBmpPath(":/img/setting/img_key_sound_on.png");
    mKeySoundSwitch->setGeometry(520,30,80,80);
    connect(mKeySoundSwitch,SIGNAL(released()),this,SLOT(onBtnKeySoundtClick()));

    //获取系统按键音的开关 lgl
    isKeySound = settings.value("keySound").toBool();
    if(isKeySound){
        mSoundSLabel->setText(tr("按键音:打开"));
        mKeySoundSwitch->setNormalBmpPath(":/img/setting/img_key_sound_on.png");
        mKeySoundSwitch->setPressBmpPath(":/img/setting/img_key_sound_on.png");
        mKeySoundSwitch->setCheckBmpPath(":/img/setting/img_key_sound_on.png");
    }else{
        mSoundSLabel->setText(tr("按键音:关闭"));
        mKeySoundSwitch->setNormalBmpPath(":/img/setting/img_key_sound_off.png");
        mKeySoundSwitch->setPressBmpPath(":/img/setting/img_key_sound_off.png");
        mKeySoundSwitch->setCheckBmpPath(":/img/setting/img_key_sound_off.png");
    }


    //声音调节
    //低 左
    mLowSoundLeft = new BmpButton(mBmpSound);
    mLowSoundLeft->setNormalBmpPath(":/img/setting/img_sound_left_a.png");
    mLowSoundLeft->setPressBmpPath(":/img/setting/img_sound_left_b.png");
    mLowSoundLeft->setGeometry(420,110,30,30);
    connect(mLowSoundLeft,SIGNAL(released()),this,SLOT(onLowSoundNumberLeft()));

    //低 右
    mLowSoundRight = new BmpButton(mBmpSound);
    mLowSoundRight->setNormalBmpPath(":/img/setting/img_sound_right_a.png");
    mLowSoundRight->setPressBmpPath(":/img/setting/img_sound_right_b.png");
    mLowSoundRight->setGeometry(710,110,30,30);
    connect(mLowSoundRight,SIGNAL(released()),this,SLOT(onLowSoundNumberRight()));

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
    mLowSoundSlider->setValue(LINE_MIN);
    mLowSoundSlider->setStyleSheet(Linestyle);

    connect(mLowSoundSlider,SIGNAL(valueChanged(int)),this,SLOT(onLowSoundValuesChange(int)));

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
    connect(mCenSoundLeft,SIGNAL(released()),this,SLOT(onCenSoundNumberLeft()));

    //中 右
    mCenSoundRight= new BmpButton(mBmpSound);
    mCenSoundRight->setNormalBmpPath(":/img/setting/img_sound_right_a.png");
    mCenSoundRight->setPressBmpPath(":/img/setting/img_sound_right_b.png");
    mCenSoundRight->setGeometry(710,210,30,30);
    connect(mCenSoundRight,SIGNAL(released()),this,SLOT(onCenSoundNumberRight()));

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
    mCenSoundSlider->setValue(LINE_MIN);
    mCenSoundSlider->setStyleSheet(Linestyle);

    connect(mCenSoundSlider,SIGNAL(valueChanged(int)),this,SLOT(onCenSoundValuesChange(int)));

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
    connect(mHeightSoundLeft,SIGNAL(released()),this,SLOT(onHeightSoundNumberLeft()));

    //高 右
    mHeightSoundRight= new BmpButton(mBmpSound);
    mHeightSoundRight->setNormalBmpPath(":/img/setting/img_sound_right_a.png");
    mHeightSoundRight->setPressBmpPath(":/img/setting/img_sound_right_b.png");
    mHeightSoundRight->setGeometry(710,310,30,30);
    connect(mHeightSoundRight,SIGNAL(released()),this,SLOT(onHeightSoundNumberRight()));

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
    mHeightSoundSlider->setValue(LINE_MIN);
    mHeightSoundSlider->setStyleSheet(Linestyle);

    connect(mHeightSoundSlider,SIGNAL(valueChanged(int)),this,SLOT(onHeightSoundValuesChange(int)));

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
    connect(mDisplayLeft,SIGNAL(released()),this,SLOT(onDisplayNumberLeft()));

    //亮度 右
    mDisplayRight= new BmpButton(mBmpBrightness);
    mDisplayRight->setNormalBmpPath(":/img/setting/img_sound_right_a.png");
    mDisplayRight->setPressBmpPath(":/img/setting/img_sound_right_b.png");
    mDisplayRight->setGeometry(566,300,30,30);
    connect(mDisplayRight,SIGNAL(released()),this,SLOT(onDisplayNumberRight()));

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
    mDisplaySlider->setValue(LINE_MIN);
    mDisplaySlider->setStyleSheet(Linestyle);

    connect(mDisplaySlider,SIGNAL(valueChanged(int)),this,SLOT(onBrightnessValuesChange(int)));

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

    this->initSystemList("ENGLIST");

    this->initLanguageDialog();
    this->initTimeSetDialog();
    this->initResetBtDialog();
    //def widget
    selectTab(0);
}

void SettingsPrivate::selectTab(int index)
{
    if(mLanguageDialog->isEnabled()){
        mLanguageDialog->hide();
    }
    if(mReSetBtDialog->isEnabled()){
        mReSetBtDialog->hide();
    }
    if(mTimeSetDialog->isEnabled()){
        mTimeSetDialog->hide();
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
    mLanguageDialog->setStyleSheet("background-color: rgb(0, 85, 255);");
    mLanguageDialog->resize(350,80);
    mLanguageDialog->setFixedSize(DIALOG_W,DIALOG_H);
    mLanguageDialog->setGeometry(350,100,DIALOG_W,DIALOG_H);
    mLanguageDialog->setWindowFlags(Qt::FramelessWindowHint);

    QListWidget * mLanguageListWidget = new QListWidget(mLanguageDialog);

    mLanguageListWidget->verticalScrollBar()->setStyleSheet(
                //进度条背景样式
                "QScrollBar:vertical"
                "{"
                "background:#383838;"
                "width:8px;"
                "margin:0px,0px,0px,0px;"
                "padding-top:0px; padding-bottom:0px;"
                "border-radius:4px;"
                "}"

                //进度条滑动时的背景样式
                "QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical"
                "{"
                "background:#383838;"
                "width:8px;"
                "margin:0px,0px,0px,0px;"
                "padding-top:0px; padding-bottom:0px;"
                "border-radius:4px;"
                "}"

                "QScrollBar::handle:vertical" //滑动条
                "{"
                "background:#2997fc;"
                "width:8px;"
                "min-height:121;"
                "border-radius:4px;"
                "}"

                "QScrollBar::handle:vertical:hover" //滑动条有焦点的时候hover
                "{"
                "background:#2997fc;"
                "width:8px;"
                "min-height:121;"
                "border-radius:4px;"
                "}"

                "QScrollBar::add-line:vertical"
                "{"
                "height:0px;"
                "width:0px;"
                "subcontrol-position:bottom;"//这个是设置下箭头的
                "}"

                "QScrollBar::add-line:vertical:hover"
                "{"
                "height:0px;"
                "width:0px;"
                "subcontrol-position:bottom;"
                "}"

                "QScrollBar::sub-line:vertical"
                "{"
                "height:0px;"
                "width:0px;"
                "subcontrol-position:top;" //顶部的往上图标
                "}"

                "QScrollBar::sub-line:vertical:hover"
                "{"
                "height:0px;"
                "width:0px;"
                "subcontrol-position:top;"
                "}"
                );

    mLanguageListWidget->resize(DIALOG_W,DIALOG_H);

    connect(mLanguageListWidget,SIGNAL(pressed(QModelIndex)),this,SLOT(onLanguageSelectPressed(QModelIndex)));

    listLanguage << "英语";
    listLanguage << "汉语";
    listLanguage << "葡萄牙语";
    listLanguage << "西班牙语";
    listLanguage << "俄语";
    listLanguage << "法语";
    listLanguage << "阿拉伯语";
    listLanguage << "简体中文";
    listLanguage << "泰语";

    for (int i = 0; i < listLanguage.size(); ++i) {
        QListWidgetItem*item = new QListWidgetItem();
        item->setText(listLanguage.at(i));
        //居中
        //item->setTextAlignment(Qt::AlignCenter);
        item->setFont(font);
        item->setTextColor(Qt::white);

        //分割线
        QListWidgetItem*itemLine=new QListWidgetItem;
        itemLine->setBackground(QBrush(QPixmap(":/img/setting/img_setting_list_line.png")));
        itemLine->setSizeHint(QSize(20, 1.5));

        mLanguageListWidget->addItem(item);
        mLanguageListWidget->addItem(itemLine);
    }
}

void SettingsPrivate::initTimeSetDialog()
{
    const int DIALOG_W = 300;
    const int DIALOG_H = 180;
    mTimeSetDialog = new QDialog(mBmpSystem);
    mTimeSetDialog->setGeometry(0,0,800,435);
    mTimeSetDialog->setWindowFlags(Qt::FramelessWindowHint);

    //时间选择器
    mWheelView = new WheelView(mTimeSetDialog);
    mWheelView->setGeometry(250,100,DIALOG_W,DIALOG_H);
    //mWheelView->setStyleSheet("border-image: url(:/img/setting/img_setting_time_setting_bg.png);");
    mWheelView->setFixedSize(DIALOG_W,DIALOG_H);

    //设置按钮
    mBmpSetSyTime = new BmpButton(mTimeSetDialog);
    mBmpSetSyTime->setText(tr("存储"));
    mBmpSetSyTime->setGeometry(650,20,100,50);
    mBmpSetSyTime->setNormalBmpPath(":/img/Common/img_on_button_bg_a.png");
    mBmpSetSyTime->setPressBmpPath(":/img/Common/img_on_button_bg_b.png");
    connect(mBmpSetSyTime,SIGNAL(released()),this,SLOT(onBmpTimeSetPressed()));
}

void SettingsPrivate::initResetBtDialog()
{
    QPalette pl;
    pl.setColor(QPalette::WindowText,Qt::white);
    QFont font("Microsoft YaHei");
    font.setPointSize(16);

    const int DIALOG_W = 300;
    const int DIALOG_H = 180;
    mReSetBtDialog = new QDialog(mBmpSystem);
    mReSetBtDialog->setGeometry(250,100,DIALOG_W,DIALOG_H);
    mReSetBtDialog->setStyleSheet("border-image: url(:/img/Common/img_dialog_bg.png);");
    mReSetBtDialog->setWindowFlags(Qt::FramelessWindowHint);

    //文字
    QLabel * mLabel = new QLabel(mReSetBtDialog);
    mLabel->setText(tr("是否重置？"));
    mLabel->setPalette(pl);
    mLabel->setGeometry(100,30,200,100);
    mLabel->setFont(font);

    //确定
    BmpButton * mBmpDialogOk = new BmpButton(mReSetBtDialog);
    mBmpDialogOk->setNormalBmpPath(":/img/Common/img_dialog_ok_bg_a.png");
    mBmpDialogOk->setPressBmpPath(":/img/Common/img_dialog_ok_bg_b.png");
    mBmpDialogOk->setText(tr("确定"));
    mBmpDialogOk->setFont(font);
    mBmpDialogOk->setGeometry(0,120,150,80);
    mBmpDialogOk->setTextColor(Qt::white);
    connect(mBmpDialogOk,SIGNAL(released()),this,SLOT(onResetDialogOkPressed()));

    //取消
    BmpButton * mBmpDialogNo = new BmpButton(mReSetBtDialog);
    mBmpDialogNo->setNormalBmpPath(":/img/Common/img_dialog_no_bg_a.png");
    mBmpDialogNo->setPressBmpPath(":/img/Common/img_dialog_no_bg_b.png");
    mBmpDialogNo->setText(tr("取消"));
    mBmpDialogNo->setFont(font);
    mBmpDialogNo->setTextColor(Qt::white);
    mBmpDialogNo->setGeometry(152,120,150,80);
    connect(mBmpDialogNo,SIGNAL(released()),this,SLOT(onResetDialogNoPressed()));
}

//init list
void SettingsPrivate::initSystemList(QString language)
{
    currentLanguage = language;
    qDebug() << "language:" <<language;
    QFont font("Microsoft YaHei");
    font.setPointSize(18);

    if(mListSystem.size() > 0){
        mListSystem.clear();
    }

    mListWidget->clear();

    mListSystem << "Change Language " + language;
    mListSystem << "SW Version (MI) V2.59(QT)-V5.224";
    mListSystem << "BT Version BTM-QTc161012av1";

    int format = settings.value("time").toInt();
    qDebug()<<"initSystemList"<<format;
    if(format == 0){
        mListSystem << "Time Format 24 Hours";
    }else if(format == 24){
        mListSystem << "Time Format 24 Hours";
    }else{
        mListSystem << "Time Format 12 Hours";
    }
    mListSystem << "Time Setting";
    mListSystem << "Reset Bluetooth settings";

    for (int i = 0; i < mListSystem.size(); ++i) {
        QListWidgetItem * itemSystemList = new QListWidgetItem;
        //分割线
        QListWidgetItem * itemLine = new QListWidgetItem;
        itemLine->setBackground(QBrush(QPixmap(":/img/setting/img_setting_list_line.png")));
        itemLine->setSizeHint(QSize(20, 1.5));
        //居中
        itemSystemList->setTextAlignment(Qt::AlignCenter);
        //对齐

        //行高
        itemSystemList->setSizeHint(QSize(60, 40));
        //去除选中效果
        itemSystemList->setFlags(itemSystemList->flags() & ~Qt::ItemIsSelectable);
        itemSystemList->setFont(font);
        itemSystemList->setTextColor(Qt::white);
        itemSystemList->setText(mListSystem.at(i));
        mListWidget->addItem(itemSystemList);
        mListWidget->addItem(itemLine);
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
        mSoundSLabel->setText(tr("按键音:打开"));
        mKeySoundSwitch->setNormalBmpPath(":/img/setting/img_key_sound_on.png");
        mKeySoundSwitch->setPressBmpPath(":/img/setting/img_key_sound_on.png");
        mKeySoundSwitch->setCheckBmpPath(":/img/setting/img_key_sound_on.png");
    }else{
        mSoundSLabel->setText(tr("按键音:关闭"));
        mKeySoundSwitch->setNormalBmpPath(":/img/setting/img_key_sound_off.png");
        mKeySoundSwitch->setPressBmpPath(":/img/setting/img_key_sound_off.png");
        mKeySoundSwitch->setCheckBmpPath(":/img/setting/img_key_sound_off.png");
    }
    settings.setValue("keySound",isKeySound);
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
    if(values <= LINE_MIN){
        mLowSoundSlider->setValue(LINE_MIN);
    }else if(values >= LINE_MAX){
        mLowSoundSlider->setValue(LINE_MAX);
    }
}

void SettingsPrivate::onCenSoundValuesChange(int values)
{
    qDebug()<< "Cen" << values;
    if(values <= LINE_MIN){
        mCenSoundSlider->setValue(LINE_MIN);
    }else if(values >= LINE_MAX){
        mCenSoundSlider->setValue(LINE_MAX);
    }
}

void SettingsPrivate::onHeightSoundValuesChange(int values)
{
    qDebug()<< "Height" << values;
    if(values <= LINE_MIN){
        mHeightSoundSlider->setValue(LINE_MIN);
    }else if(values >= LINE_MAX){
        mHeightSoundSlider->setValue(LINE_MAX);
    }
}

void SettingsPrivate::onBrightnessValuesChange(int values)
{
    qDebug()<< "Brightness" << values;
    if(values <= LINE_MIN){
        mDisplaySlider->setValue(LINE_MIN);
    }else if(values >= LINE_MAX){
        mDisplaySlider->setValue(LINE_MAX);
    }
}

void SettingsPrivate::onSystemListLanguagePressed(QModelIndex  index)
{
    qDebug() << index.row();
    switch(index.row() / 2){
    case 0:
        mLanguageDialog->show();
        break;
    case 3:
        formats = settings.value("time").toInt();
        qDebug() << "onSystemListLanguagePressed" << formats;
        if(formats == 24){
            formats = 12;
        }else{
            formats = 24;
        }
        //记录
        settings.setValue("time", formats);
        //更新条目
        initSystemList(currentLanguage);
        //发送
        //Q_Q(Settings);
        //q->sendBroadcast(AppType::Settings,);
        break;
    case 4:
        //每次显示之前获取当前时间
        date = QDate::currentDate();
        mWheelView->setYear(date.year());
        mWheelView->setMonth(date.month());
        qDebug() << date.month();
        mWheelView->setDay(date.day());
        mTimeSetDialog->show();
        break;
    case 5:
        mReSetBtDialog->show();
        break;
    default:
        break;
    }
}

void SettingsPrivate::onLanguageSelectPressed(QModelIndex index)
{
    qDebug() << index.row();
    // 0 2 4 6 8 10 12 14 16
    // 0 1 2 3 4  5  6  7  8
    qDebug() << listLanguage.at(index.row()/2);
    initSystemList(listLanguage.at(index.row()/2));
    mLanguageDialog->hide();
}

//------------------------------------------------------------
void SettingsPrivate::onBmpSoundWidgetMove(QMouseEvent *e)
{
    qDebug() << e->x() << ":" << e->y();
    if(isEventSeatPoint){
        //左上：65 85 左下：65 255 右上：285 85 右下 285 255
        if(e->x() >= 65 && e->x() <= 285 && e->y() >= 85 && e->y() <= 255){
            mSeatPoint->move(e->x(),e->y());

            //判断方向
            if(e->x()>=65 && e->x() <=180 && e->y() >=85 && e->y() <=170){
                qDebug() << "左上";
                return;
            }

            if(e->x()>=180 && e->x() <=285 && e->y() >=85 && e->y() <=170){
                qDebug() << "右上";
                return;
            }

            if(e->x()>=65 && e->x() <=180 && e->y() >=170 && e->y() <=255){
                qDebug() << "左下";
                return;
            }

            if(e->x()>=180 && e->x() <=285 && e->y() >=170 && e->y() <=255){
                qDebug() << "右下";
                return;
            }
        }
    }
}

void SettingsPrivate::onBmpTimeSetPressed()
{
    if(mTimeSetDialog->isEnabled()){
        mTimeSetDialog->hide();
    }
    int year = mWheelView->getYear();
    int month = mWheelView->getMonth();
    int day = mWheelView->getDay();
    qDebug() << year << "-" << month << "-" << day;

    // 用进程调用命令QProcess
    QString strDateTime =  QString::number(year) + "-" + QString::number(month) + "-" + QString::number(day);
    qDebug() << strDateTime;
    // 格式请按照上面格式输入。
    QProcess::execute("data", QStringList() << "-s" << strDateTime);
    // 如果需要写入时钟RTC的话继续调用
    QProcess::execute("hwclock -w");
    // 同步保存
    QProcess::execute("sync");
}

void SettingsPrivate::onResetDialogOkPressed()
{
    if(mReSetBtDialog->isEnabled()){
        mReSetBtDialog->hide();
    }
    qDebug() << "Yes";
    OMessage msg;
    msg.mId = 0x11;
    Q_Q(Settings);
    q->sendBroadcast(T_Bluetooth,msg);
}

void SettingsPrivate::onResetDialogNoPressed()
{
    if(mReSetBtDialog->isEnabled()){
        mReSetBtDialog->hide();
    }
    qDebug() << "No";
}

void SettingsPrivate::onLowSoundNumberLeft()
{
    int values = mLowSoundSlider->value();
    if(values > 5 && values <= 95){
        mLowSoundSlider->setValue(values-FIX_VALUES);
    }
}

void SettingsPrivate::onLowSoundNumberRight()
{
    int values = mLowSoundSlider->value();
    if(values >= 5 && values < 95){
        mLowSoundSlider->setValue(values+FIX_VALUES);
    }
}

void SettingsPrivate::onCenSoundNumberLeft()
{
    int values = mCenSoundSlider->value();
    if(values > 5 && values <= 95){
        mCenSoundSlider->setValue(values-FIX_VALUES);
    }
}

void SettingsPrivate::onCenSoundNumberRight()
{
    int values = mCenSoundSlider->value();
    if(values >= 5 && values < 95){
        mCenSoundSlider->setValue(values+FIX_VALUES);
    }
}

void SettingsPrivate::onHeightSoundNumberLeft()
{
    int values = mHeightSoundSlider->value();
    if(values > 5 && values <= 95){
        mHeightSoundSlider->setValue(values-FIX_VALUES);
    }
}

void SettingsPrivate::onHeightSoundNumberRight()
{
    int values = mHeightSoundSlider->value();
    if(values >= 5 && values < 95){
        mHeightSoundSlider->setValue(values+FIX_VALUES);
    }
}

void SettingsPrivate::onDisplayNumberLeft()
{
    int values = mDisplaySlider->value();
    if(values > 5 && values <= 95){
        mDisplaySlider->setValue(values-FIX_VALUES);
    }
}

void SettingsPrivate::onDisplayNumberRight()
{
    int values = mDisplaySlider->value();
    if(values >= 5 && values < 95){
        mDisplaySlider->setValue(values+FIX_VALUES);
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



