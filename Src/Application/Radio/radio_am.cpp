#include "radio_am.h"

RadioAmPrivate::RadioAmPrivate(RadioAm *parent)
    : QObject(),q_ptr(parent)
{
     mTab = AM;
}

void RadioAmPrivate::initializeBasicWidget(QWidget *parent)
{
  Q_Q(RadioAm);

    mTabBar = new BmpWidget(parent);
    mTabBar->setBackgroundBmpPath(QString(":/res/drawable/app_statebar.png"));
    mTabBar->setFixedSize(QSize(800, 50));

    mStateBarTab_AM= new BmpButton(mTabBar);
    mStateBarTab_AM->setNormalBmpPath(QString(":/res/drawable/app_statebar_btn.png"));
    mStateBarTab_AM->setPressBmpPath(QString(":/res/drawable/app_statebar_btn_pressed.png"));
    mStateBarTab_AM->setCheckBmpPath(QString(":/res/drawable/app_statebar_btn_pressed.png"));
    mStateBarTab_AM->setGeometry(0,0,140,50);
    mStateBarTab_AM->setText(QString("AM"));
    mStateBarTab_AM->setFontPointSize(18);

    mStateBarTab_Preset= new BmpButton(mTabBar);
    mStateBarTab_Preset->setNormalBmpPath(QString(":/res/drawable/app_statebar_btn.png"));
    mStateBarTab_Preset->setPressBmpPath(QString(":/res/drawable/app_statebar_btn_pressed.png"));
    mStateBarTab_Preset->setCheckBmpPath(QString(":/res/drawable/app_statebar_btn_pressed.png"));
    mStateBarTab_Preset->setGeometry(140,0,140,50);
    mStateBarTab_Preset->setText(QString("预置电台"));
    mStateBarTab_Preset->setFontPointSize(18);

    mStateBarTab_List= new BmpButton(mTabBar);
    mStateBarTab_List->setNormalBmpPath(QString(":/res/drawable/app_statebar_btn.png"));
    mStateBarTab_List->setPressBmpPath(QString(":/res/drawable/app_statebar_btn_pressed.png"));
    mStateBarTab_List->setCheckBmpPath(QString(":/res/drawable/app_statebar_btn_pressed.png"));
    mStateBarTab_List->setGeometry(280,0,140,50);
    mStateBarTab_List->setText(QString("列表"));
    mStateBarTab_List->setFontPointSize(18);


    mFmFragmentContain = new QWidget(parent);
    mFmFragmentContain->setGeometry(0,95,800,325);
    mFragmentViewLayout = new QStackedLayout();
    mFmFragmentContain->setLayout(mFragmentViewLayout);

    mFmFragmentView = new QWidget(parent);
    mFmFragmentView->setFixedSize(QSize(800, 325));
    const int freq_y= 40;
    const int freq_text_w= 140;
    const int freq_scalebar_y= 160;
    mFmFragment_FreqBg = new BmpWidget(mFmFragmentView);
    mFmFragment_FreqBg->setBackgroundBmpPath(QString(":/res/drawable/radio_freq_bg.png"));
    mFmFragment_FreqBg->setGeometry((800-124)/2,freq_y,124,50);
    mFmFragment_FreqText = new TextWidget(mFmFragmentView);
    mFmFragment_FreqText->setLanguageType(TextWidget::T_NoTranslate);
    mFmFragment_FreqText->setText(QString("780"));
    mFmFragment_FreqText->setFontPointSize(40);
    mFmFragment_FreqText->setGeometry((800-freq_text_w)/2,freq_y,freq_text_w,50);
    mFmFragment_ScaleBarBg = new BmpWidget(mFmFragmentView);
    mFmFragment_ScaleBarBg->setBackgroundBmpPath(QString(":/res/drawable/radio_scale_bar_bg.png"));
    mFmFragment_ScaleBarBg->setGeometry((800-641)/2,freq_scalebar_y,641,65);
    mFmFragment_ScalePointer = new BmpWidget(mFmFragmentView);
    mFmFragment_ScalePointer->setBackgroundBmpPath(QString(":/res/drawable/radio_scale_pointer.png"));
    mFmFragment_ScalePointer->setGeometry((800-3)/2,freq_scalebar_y-10,3,50);
    mFragmentViewLayout->addWidget(mFmFragmentView);

    mPresetFragmentView = new QWidget(parent);
    mPresetFragmentView->setFixedSize(QSize(800, 325));
    mFragmentViewLayout->addWidget(mPresetFragmentView);

    mListFragmentView = new QWidget(parent);
    mListFragmentView->setFixedSize(QSize(800, 325));
    mFragmentViewLayout->addWidget(mListFragmentView);
    mFragmentViewLayout->setCurrentIndex(mTab);

    mBottomBar = new QWidget(parent);
    mBottomBar->setGeometry(0,375,800,60);
    mBottomBarLayout = new QStackedLayout();
    mBottomBar->setLayout(mBottomBarLayout);

    mBottom_Am = new BmpWidget(mBottomBar);
    mBottom_Am->setBackgroundBmpPath(QString(":/res/drawable/app_bottombar_4btns_bg.png"));
    mBottom_Am->setFixedSize(QSize(800, 60));
    mBottom_Am_Prev= new BmpButton(mBottom_Am);
    mBottom_Am_Prev->setNormalBmpPath(QString(":/res/drawable/bottom_bar_prev.png"));
    mBottom_Am_Prev->setPressBmpPath(QString(":/res/drawable/bottom_bar_prev_pressed.png"));
    mBottom_Am_Prev->setGeometry(0,0,200,60);
    mBottom_Am_Seek_Prev= new BmpButton(mBottom_Am);
    mBottom_Am_Seek_Prev->setNormalBmpPath(QString(":/res/drawable/bottom_bar_seek_prev.png"));
    mBottom_Am_Seek_Prev->setPressBmpPath(QString(":/res/drawable/bottom_bar_seek_prev_pressed.png"));
    mBottom_Am_Seek_Prev->setGeometry(200,0,200,60);
    mBottom_Am_Seek_Next= new BmpButton(mBottom_Am);
    mBottom_Am_Seek_Next->setNormalBmpPath(QString(":/res/drawable/bottom_bar_seek_next.png"));
    mBottom_Am_Seek_Next->setPressBmpPath(QString(":/res/drawable/bottom_bar_seek_next_pressed.png"));
    mBottom_Am_Seek_Next->setGeometry(400,0,200,60);
    mBottom_Am_Next= new BmpButton(mBottom_Am);
    mBottom_Am_Next->setNormalBmpPath(QString(":/res/drawable/bottom_bar_next.png"));
    mBottom_Am_Next->setPressBmpPath(QString(":/res/drawable/bottom_bar_next_pressed.png"));
    mBottom_Am_Next->setGeometry(600,0,200,60);
    mBottomBarLayout->addWidget(mBottom_Am);

    mBottom_Preset = new BmpWidget(mBottomBar);
    mBottom_Preset->setBackgroundBmpPath(QString(":/res/drawable/app_bottombar_3btns_bg.png"));
    mBottom_Preset->setFixedSize(QSize(800, 60));
    mBottom_Preset_PageUp= new BmpButton(mBottom_Preset);
    mBottom_Preset_PageUp->setNormalBmpPath(QString(":/res/drawable/bottom_bar_page_up.png"));
    mBottom_Preset_PageUp->setPressBmpPath(QString(":/res/drawable/bottom_bar_page_up_pressed.png"));
    mBottom_Preset_PageUp->setGeometry(0,0,267,60);
    mBottom_Preset_AutoSearch= new BmpButton(mBottom_Preset);
    mBottom_Preset_AutoSearch->setNormalBmpPath(QString(":/res/drawable/bottom_bar_btn_normal.png"));
    mBottom_Preset_AutoSearch->setPressBmpPath(QString(":/res/drawable/bottom_bar_btn_pressed.png"));
    mBottom_Preset_AutoSearch->setGeometry(267,0,267,60);
    mBottom_Preset_AutoSearch->setText(QString("自动选台"));
    mBottom_Preset_AutoSearch->setFontPointSize(18);
    mBottom_Preset_PageDown= new BmpButton(mBottom_Preset);
    mBottom_Preset_PageDown->setNormalBmpPath(QString(":/res/drawable/bottom_bar_page_down.png"));
    mBottom_Preset_PageDown->setPressBmpPath(QString(":/res/drawable/bottom_bar_page_down_pressed.png"));
    mBottom_Preset_PageDown->setGeometry(533,0,267,60);
    mBottomBarLayout->addWidget(mBottom_Preset);

    mBottom_List = new BmpWidget(mBottomBar);
    mBottom_List->setBackgroundBmpPath(QString(":/res/drawable/app_bottombar_3btns_bg.png"));
    mBottom_List->setFixedSize(QSize(800, 60));
    mBottomBarLayout->addWidget(mBottom_List);
    mBottom_List_PageUp= new BmpButton(mBottom_List);
    mBottom_List_PageUp->setNormalBmpPath(QString(":/res/drawable/bottom_bar_page_up.png"));
    mBottom_List_PageUp->setPressBmpPath(QString(":/res/drawable/bottom_bar_page_up_pressed.png"));
    mBottom_List_PageUp->setGeometry(0,0,267,60);
    mBottom_List_Search= new BmpButton(mBottom_List);
    mBottom_List_Search->setNormalBmpPath(QString(":/res/drawable/bottom_bar_btn_normal.png"));
    mBottom_List_Search->setPressBmpPath(QString(":/res/drawable/bottom_bar_btn_pressed.png"));
    mBottom_List_Search->setGeometry(267,0,267,60);
    mBottom_List_Search->setText(QString("搜索"));
    mBottom_List_Search->setFontPointSize(18);
    mBottom_List_PageDown= new BmpButton(mBottom_List);
    mBottom_List_PageDown->setNormalBmpPath(QString(":/res/drawable/bottom_bar_page_down.png"));
    mBottom_List_PageDown->setPressBmpPath(QString(":/res/drawable/bottom_bar_page_down_pressed.png"));
    mBottom_List_PageDown->setGeometry(533,0,267,60);
    mBottomBarLayout->setCurrentIndex(mTab);

    tabSwitch(mTab);

    connect(mStateBarTab_AM,SIGNAL(released()),this,SLOT(onBtnTabAm()));
    connect(mStateBarTab_Preset,SIGNAL(released()),this,SLOT(onBtnTabPreset()));
    connect(mStateBarTab_List,SIGNAL(released()),this,SLOT(onBtnTabList()));

}

void RadioAmPrivate::onBtnTabAm()
{
    if(mTab != AM){
       mTab = AM;
    }
    tabSwitch(mTab);
}
void RadioAmPrivate::onBtnTabPreset()
{
    if(mTab != PRESET){
       mTab = PRESET;
    }
    tabSwitch(mTab);
}
void RadioAmPrivate::onBtnTabList()
{
    if(mTab != LIST){
       mTab = LIST;
    }
    tabSwitch(mTab);
}

void RadioAmPrivate::tabSwitch(const Tab mytab)
{
    switch (mytab) {
    case AM:
        mStateBarTab_AM->setStatus(BmpButton::B_Check);
        mStateBarTab_Preset->setStatus(BmpButton::B_Normal);
        mStateBarTab_List->setStatus(BmpButton::B_Normal);
        break;
    case PRESET:
        mStateBarTab_AM->setStatus(BmpButton::B_Normal);
        mStateBarTab_Preset->setStatus(BmpButton::B_Check);
        mStateBarTab_List->setStatus(BmpButton::B_Normal);
        break;
    case LIST:
        mStateBarTab_AM->setStatus(BmpButton::B_Normal);
        mStateBarTab_Preset->setStatus(BmpButton::B_Normal);
        mStateBarTab_List->setStatus(BmpButton::B_Check);
        break;
    default:
        break;
    }
    mFragmentViewLayout->setCurrentIndex(mTab);
    mBottomBarLayout->setCurrentIndex(mTab);
}


//----------------------------------

RadioAm::RadioAm(QObject *parent):
 Activity(parent),
 d_ptr(new RadioAmPrivate(this))
{

}

void RadioAm::onCreate(QWidget *parent)
{
    Q_D(RadioAm);
    d->initializeBasicWidget(parent);
}
void RadioAm::onStart()
{

}
void RadioAm::onResume()
{

}
void RadioAm::onPause()
{

}
void RadioAm::onStop()
{

}
void RadioAm::onDestroy()
{

}

bool RadioAm::onBackPressed()
{

return false;
}

void RadioAm::onLanguageChanged()
{

}

void RadioAm::onReceiveBroadcast(AppType appType,OMessage &msg)
{

}

void RadioAm::onReceiveCmd(AppType appType,OMessage &msg)
{

}


