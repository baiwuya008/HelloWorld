#include "radio_am.h"
#include "radio_unit.h"
#include "radio_process.h"
#include "radio_data.h"

#include <QDebug>

#define FREQ_MAX  1602
#define FREQ_MIN  531
#define FREQ_STEP  9
#define SLIDER_BAR_MAX ((FREQ_MAX-FREQ_MIN)/FREQ_STEP)
#define LISTVIEW_SLIDER_THRESHOLD  5

RadioAmPrivate::RadioAmPrivate(RadioAm *parent)
    : QObject(),q_ptr(parent)
{
     mTab = AM;
     mTabBar =NULL;
     mStateBarTab_AM =NULL;
     mStateBarTab_Preset =NULL;
     mStateBarTab_List =NULL;

     mFragmentViewLayout =NULL;
     mAmFragmentContain =NULL;
     mAmFragmentView =NULL;
     mPresetFragmentView =NULL;
     mListFragmentView =NULL;

     mAmFragment_FreqBg =NULL;
     mAmFragment_FreqText =NULL;
     mAmFreqBarSlider = NULL;

     mBottomBarLayout =NULL;
     mBottomBar =NULL;
     mBottom_Am =NULL;
     mBottom_Preset =NULL;
     mBottom_List =NULL;

     mBottom_Am_Prev =NULL;
     mBottom_Am_Seek_Prev =NULL;
     mBottom_Am_Seek_Next =NULL;
     mBottom_Am_Next =NULL;

     mBottom_Preset_Seek_Prev =NULL;
     mBottom_Preset_AutoSearch =NULL;
     mBottom_Preset_Seek_Next =NULL;

     mBottom_List_Seek_Prev =NULL;
     mBottom_List_Search =NULL;
     mBottom_List_Seek_Next =NULL;

     mRadioPresetFragmentListView =NULL;
     mRadioPresetFragmentListViewScrollBar =NULL;
     mRadioPresetDelegate =NULL;
     mRadioPresetStandardItemModel =NULL;

     mRadioListFragmentListView =NULL;
     mRadioListFragmentListViewScrollBar =NULL;
     mRadioListDelegate =NULL;
     mRadioListStandardItemModel =NULL;

     mProcess = RadioProcess::instance();

}

void RadioAmPrivate::initializeBasicWidget(QWidget *parent)
{
  Q_Q(RadioAm);

    //***** add top bar ********
    mTabBar = new BmpWidget(parent);
    mTabBar->setBackgroundBmpPath(QString(":/res/drawable/app_statebar.png"));
    mTabBar->setFixedSize(QSize(800, 50));
    //init topbar Am tab
    mStateBarTab_AM= new BmpButton(mTabBar);
    mStateBarTab_AM->setNormalBmpPath(QString(":/res/drawable/app_statebar_btn.png"));
    mStateBarTab_AM->setPressBmpPath(QString(":/res/drawable/app_statebar_btn_pressed.png"));
    mStateBarTab_AM->setCheckBmpPath(QString(":/res/drawable/app_statebar_btn_pressed.png"));
    mStateBarTab_AM->setGeometry(0,0,140,50);
    mStateBarTab_AM->setText(QString("AM"));
    mStateBarTab_AM->setFontPointSize(14);
    //init topbar Preset tab
    mStateBarTab_Preset= new BmpButton(mTabBar);
    mStateBarTab_Preset->setNormalBmpPath(QString(":/res/drawable/app_statebar_btn.png"));
    mStateBarTab_Preset->setPressBmpPath(QString(":/res/drawable/app_statebar_btn_pressed.png"));
    mStateBarTab_Preset->setCheckBmpPath(QString(":/res/drawable/app_statebar_btn_pressed.png"));
    mStateBarTab_Preset->setGeometry(140,0,140,50);
    mStateBarTab_Preset->setText(QString("预置电台"));
    mStateBarTab_Preset->setFontPointSize(14);
    //init topbar List tab
    mStateBarTab_List= new BmpButton(mTabBar);
    mStateBarTab_List->setNormalBmpPath(QString(":/res/drawable/app_statebar_btn.png"));
    mStateBarTab_List->setPressBmpPath(QString(":/res/drawable/app_statebar_btn_pressed.png"));
    mStateBarTab_List->setCheckBmpPath(QString(":/res/drawable/app_statebar_btn_pressed.png"));
    mStateBarTab_List->setGeometry(280,0,140,50);
    mStateBarTab_List->setText(QString("列表"));
    mStateBarTab_List->setFontPointSize(14);

    //*****add middle part fragment container ******
    mAmFragmentContain = new QWidget(parent);
    mAmFragmentContain->setGeometry(0,50,800,325);
    mFragmentViewLayout = new QStackedLayout();
    mAmFragmentContain->setLayout(mFragmentViewLayout);

    //init Am fragment
    mAmFragmentView = new QWidget(parent);
    mAmFragmentView->setFixedSize(QSize(800, 325));
    mFragmentViewLayout->addWidget(mAmFragmentView);
    //init Preset fragment
    mPresetFragmentView = new QWidget(parent);
    mPresetFragmentView->setFixedSize(QSize(800, 325));
    mFragmentViewLayout->addWidget(mPresetFragmentView);
    //init List fragment
    mListFragmentView = new QWidget(parent);
    mListFragmentView->setFixedSize(QSize(800, 325));
    mFragmentViewLayout->addWidget(mListFragmentView);

    //******add buttom bar**********
    mBottomBar = new QWidget(parent);
    mBottomBar->setGeometry(0,375,800,60);
    mBottomBarLayout = new QStackedLayout();
    mBottomBar->setLayout(mBottomBarLayout);
    //init buttom bar am
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

    //init buttom bar preset
    mBottom_Preset = new BmpWidget(mBottomBar);
    mBottom_Preset->setBackgroundBmpPath(QString(":/res/drawable/app_bottombar_3btns_bg.png"));
    mBottom_Preset->setFixedSize(QSize(800, 60));
    mBottom_Preset_Seek_Prev= new BmpButton(mBottom_Preset);
    mBottom_Preset_Seek_Prev->setNormalBmpPath(QString(":/res/drawable/bottom_bar_page_up.png"));
    mBottom_Preset_Seek_Prev->setPressBmpPath(QString(":/res/drawable/bottom_bar_page_up_pressed.png"));
    mBottom_Preset_Seek_Prev->setGeometry(0,0,267,60);
    mBottom_Preset_AutoSearch= new BmpButton(mBottom_Preset);
    mBottom_Preset_AutoSearch->setNormalBmpPath(QString(":/res/drawable/bottom_bar_btn_normal.png"));
    mBottom_Preset_AutoSearch->setPressBmpPath(QString(":/res/drawable/bottom_bar_btn_pressed.png"));
    mBottom_Preset_AutoSearch->setGeometry(267,0,267,60);
    mBottom_Preset_AutoSearch->setText(QString("自动选台"));
    mBottom_Preset_AutoSearch->setFontPointSize(18);
    mBottom_Preset_Seek_Next= new BmpButton(mBottom_Preset);
    mBottom_Preset_Seek_Next->setNormalBmpPath(QString(":/res/drawable/bottom_bar_page_down.png"));
    mBottom_Preset_Seek_Next->setPressBmpPath(QString(":/res/drawable/bottom_bar_page_down_pressed.png"));
    mBottom_Preset_Seek_Next->setGeometry(533,0,267,60);
    mBottomBarLayout->addWidget(mBottom_Preset);

    //init buttom bar list
    mBottom_List = new BmpWidget(mBottomBar);
    mBottom_List->setBackgroundBmpPath(QString(":/res/drawable/app_bottombar_3btns_bg.png"));
    mBottom_List->setFixedSize(QSize(800, 60));
    mBottomBarLayout->addWidget(mBottom_List);
    mBottom_List_Seek_Prev= new BmpButton(mBottom_List);
    mBottom_List_Seek_Prev->setNormalBmpPath(QString(":/res/drawable/bottom_bar_page_up.png"));
    mBottom_List_Seek_Prev->setPressBmpPath(QString(":/res/drawable/bottom_bar_page_up_pressed.png"));
    mBottom_List_Seek_Prev->setGeometry(0,0,267,60);
    mBottom_List_Search= new BmpButton(mBottom_List);
    mBottom_List_Search->setNormalBmpPath(QString(":/res/drawable/bottom_bar_btn_normal.png"));
    mBottom_List_Search->setPressBmpPath(QString(":/res/drawable/bottom_bar_btn_pressed.png"));
    mBottom_List_Search->setGeometry(267,0,267,60);
    mBottom_List_Search->setText(QString("搜索"));
    mBottom_List_Search->setFontPointSize(18);
    mBottom_List_Seek_Next= new BmpButton(mBottom_List);
    mBottom_List_Seek_Next->setNormalBmpPath(QString(":/res/drawable/bottom_bar_page_down.png"));
    mBottom_List_Seek_Next->setPressBmpPath(QString(":/res/drawable/bottom_bar_page_down_pressed.png"));
    mBottom_List_Seek_Next->setGeometry(533,0,267,60);
    mBottomBarLayout->setCurrentIndex(mTab);

    tabSwitch(mTab);

    connect(mStateBarTab_AM,SIGNAL(released()),this,SLOT(onBtnTabAm()));
    connect(mStateBarTab_Preset,SIGNAL(released()),this,SLOT(onBtnTabPreset()));
    connect(mStateBarTab_List,SIGNAL(released()),this,SLOT(onBtnTabList()));
    mProcess->linkRadioAm(this);

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
    mTab = mytab;
    switch (mytab) {
    case AM:
        mStateBarTab_AM->setStatus(BmpButton::B_Check);
        mStateBarTab_Preset->setStatus(BmpButton::B_Normal);
        mStateBarTab_List->setStatus(BmpButton::B_Normal);
        initRadioAmFragment();
        break;
    case PRESET:
        mStateBarTab_AM->setStatus(BmpButton::B_Normal);
        mStateBarTab_Preset->setStatus(BmpButton::B_Check);
        mStateBarTab_List->setStatus(BmpButton::B_Normal);
        initRadioPresetFragment();
        //-------
        doReFreshCurFreq(gRadioData->getData().getCurAmFreq(),true,false);
        break;
    case LIST:
        mStateBarTab_AM->setStatus(BmpButton::B_Normal);
        mStateBarTab_Preset->setStatus(BmpButton::B_Normal);
        mStateBarTab_List->setStatus(BmpButton::B_Check);
        initRadioListFragment();
        //-------
        doReFreshCurFreq(gRadioData->getData().getCurAmFreq(),false,true);
        break;
    default:
        break;
    }
    mFragmentViewLayout->setCurrentIndex(mytab);
    mBottomBarLayout->setCurrentIndex(mytab);
}

void RadioAmPrivate::initRadioAmFragment()
{
    const int freq_y= 85;
    const int freq_text_w= 200;
    const int freq_scalebar_y= 205;
    const int cur_freq = gRadioData->getData().getCurAmFreq();

    if(mAmFragment_FreqBg == NULL)
    {
        int slider_val = (cur_freq-FREQ_MIN)*SLIDER_BAR_MAX/(FREQ_MAX-FREQ_MIN);

        mAmFragment_FreqBg = new BmpWidget(mAmFragmentView);
        mAmFragment_FreqBg->setBackgroundBmpPath(QString(":/res/drawable/radio_freq_bg.png"));
        mAmFragment_FreqBg->setGeometry((800-124)/2,freq_y,124,50);
        mAmFragment_FreqText = new TextWidget(mAmFragmentView);
        mAmFragment_FreqText->setLanguageType(TextWidget::T_NoTranslate);
        mAmFragment_FreqText->setText(QString("%1").arg(cur_freq));
        mAmFragment_FreqText->setFontPointSize(28);
        mAmFragment_FreqText->setGeometry((800-freq_text_w)/2,freq_y,freq_text_w,50);

        mAmFreqBarSlider = new Slider(mAmFragmentView);
        mAmFreqBarSlider->setMaximum(SLIDER_BAR_MAX);
        mAmFreqBarSlider->setMinimum(0);
        mAmFreqBarSlider->setValue(slider_val);
        mAmFreqBarSlider->setGeometry((800-641)/2,freq_scalebar_y,641,65);
        mAmFreqBarSlider->setStyleSheet(
                    "QSlider{"
                    //"border-color: #bcbcbc;"
                    "border-image:  url(:/res/drawable/radio_scale_bar_bg.png);"
                    "}"
                    "QSlider::groove:horizontal {"
                         "border: 0px solid #999999;" //#999999
                         "height: 50px;"
                         "margin: 0px, 35px, 0px, 0px;" //top,down,left,right
                         "padding: 0px, 0px, 0px, 0px;" //top,down,left,right
                     "}"
                     //设置中间的那个滑动的块
                    "QSlider::handle:horizontal {"
                         "border: 0px ;"
                         "border-image:  url(:/res/drawable/radio_scale_pointer.png);"
                         "height: 50px;"
                         "width: 3px;"
                         "margin: 0px 0px 0px 0px;"
                         "padding: 0px, 0px, 0px, 0px;"
                    "}"
                    //还没有滑过的地方
                    "QSlider::add-page:horizontal{"
                    "background: transparent;"
                    //"background: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 #bcbcbc, stop:0.25 #bcbcbc, stop:0.5 #bcbcbc, stop:1 #bcbcbc);"

                    "}"
                    //已经划过的从地方
                    "QSlider::sub-page:horizontal{"
                    "background: transparent;"
                    //"background: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 #439cf3, stop:0.25 #439cf3, stop:0.5 #439cf3, stop:1 #439cf3);"
                    "}"
        );

        connect(mAmFreqBarSlider,SIGNAL(sliderPressed(int)),this,SLOT(doSliderPressed(int)));
        connect(mAmFreqBarSlider,SIGNAL(sliderMoved(int)),this,SLOT(doSliderMoved(int)));
        connect(mAmFreqBarSlider,SIGNAL(sliderReleased(int)),this,SLOT(doSliderReleased(int)));

        connect(mBottom_Am_Prev,SIGNAL(released()),this,SLOT(onBtnBottomAmPrev()));
        connect(mBottom_Am_Seek_Prev,SIGNAL(released()),this,SLOT(onBtnBottomAmSeekPrev()));
        connect(mBottom_Am_Seek_Next,SIGNAL(released()),this,SLOT(onBtnBottomAmSeekNext()));
        connect(mBottom_Am_Next,SIGNAL(released()),this,SLOT(onBtnBottomAmNext()));

        connect(mBottom_Preset_Seek_Prev,SIGNAL(released()),this,SLOT(onBtnBottomPresetSeekPrev()));
        connect(mBottom_Preset_AutoSearch,SIGNAL(released()),this,SLOT(onBtnBottomPresetAutoSearch()));
        connect(mBottom_Preset_Seek_Next,SIGNAL(released()),this,SLOT(onBtnBottomPresetSeekNext()));

        connect(mBottom_List_Seek_Prev,SIGNAL(released()),this,SLOT(onBtnBottomListSeekPrev()));
        connect(mBottom_List_Search,SIGNAL(released()),this,SLOT(onBtnBottomListSearch()));
        connect(mBottom_List_Seek_Next,SIGNAL(released()),this,SLOT(onBtnBottomListSeekNext()));

    }

}
void RadioAmPrivate::initRadioPresetFragment()
{
    const int preset_x= 20;
    const int preset_xw= 720;
    const int preset_y= 10;
    const int preset_yw= 300;
    if (NULL == mRadioPresetFragmentListView) {
            //mRadioPresetFragmentListView = new CustomListView(mPresetFragmentView);
        mRadioPresetFragmentListView = new RadioListView(mPresetFragmentView);
            mRadioPresetFragmentListView->setGeometry(preset_x,preset_y,preset_xw,preset_yw);
            mRadioPresetFragmentListView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
            //for test
            //QPalette palette = mRadioPresetFragmentListView->palette();
            //palette.setBrush(QPalette::Base, QBrush(Qt::red));
            //mRadioPresetFragmentListView->setPalette(palette);
            //********


            if (NULL == mRadioPresetStandardItemModel) {
                    mRadioPresetStandardItemModel = new QStandardItemModel(mRadioPresetFragmentListView);
                }

            if (NULL == mRadioPresetDelegate) {
                    mRadioPresetDelegate = new RadioAmPresetFreqDelegate(this,mRadioPresetFragmentListView);
                }

            if (NULL == mRadioPresetFragmentListViewScrollBar) {
                    mRadioPresetFragmentListViewScrollBar = new CustomScrollBar(mRadioPresetFragmentListView);
                    mRadioPresetFragmentListViewScrollBar->setStyleSheet(
                    "QScrollBar:vertical{"
                    "width: " + QString::number(8) + "px;"
                    "border-top-right-radius: " + QString::number(4) + "px;"
                    "border-bottom-right-radius: " + QString::number(4) + "px;"
                    "border-top-left-radius: " + QString::number(4) + "px;"
                    "border-bottom-left-radius: " + QString::number(4) + "px;"
                    "background: rgba(56, 56, 56, 255);"//transparent
                    "margin: 20px, 0px, 0px, 0px;"
                    "padding: 0px, 0px, 0px, 0px;"
                    "}"
                    "QScrollBar::handle:vertical{"
                    "border-top-right-radius: " + QString::number(4) + "px;"
                    "border-bottom-right-radius: " + QString::number(4) + "px;"
                    "border-top-left-radius: " + QString::number(4) + "px;"
                    "border-bottom-left-radius: " + QString::number(4) + "px;"
                    "min-height: " + QString::number(40) + "px;"
                    "background: rgba(41, 151, 252, 255);"//rgba(0, 162, 255, 191)
                    "}"
                    "QScrollBar::add-line:vertical{"
                    "height: 0px;"
                    "width: 0px;"
                    "}"
                    "QScrollBar::sub-line:vertical{"
                    "height: 0px;"
                    "width: 0px;"
                    "}"
                    "QScrollBar::add-page:vertical{"
                    "margin-left: " + QString::number(2) + "px;"
                    "margin-right: " + QString::number(2) + "px;"
                    "background: transparent;"//rgba(42, 42, 42, 191)
                    "}"
                    "QScrollBar::sub-page:vertical{"
                    "margin-left: " + QString::number(2) + "px;"
                    "margin-right: " + QString::number(2) + "px;"
                    "background: transparent;"//rgba(42, 42, 42, 191)
                    "}"
                     );
            }


            mRadioPresetFragmentListView->setItemDelegate(mRadioPresetDelegate);
            mRadioPresetFragmentListView->setVerticalScrollBar(mRadioPresetFragmentListViewScrollBar);
            mRadioPresetFragmentListView->setModel(mRadioPresetStandardItemModel);
            initRadioPresetData();

        }

}
void RadioAmPrivate::initRadioPresetData()
{

    if(mRadioPresetStandardItemModel != NULL)
    {
        QList<int> am_freq = gRadioData->getData().getAmPresetFreqs();
        unsigned int i;
        for(i=0;i<am_freq.size();i++)
        {
            QStandardItem* listItem = new QStandardItem();
            PresetVariant itemVariant;
            itemVariant.mFrequency = am_freq.at(i);
            listItem->setSizeHint(QSize(695 , 50));
            listItem->setData(qVariantFromValue(itemVariant), Qt::UserRole);
            QStandardItem* root = mRadioPresetStandardItemModel->invisibleRootItem();
            mRadioPresetStandardItemModel->setItem(root->rowCount(), 0, listItem);
        }

        //add current freq in the last item
        {
            int cur_freq = gRadioData->getData().getCurAmFreq();
            QStandardItem* listItem = new QStandardItem();
            PresetVariant itemVariant;
            itemVariant.mFrequency = cur_freq;
            itemVariant.m_ActiveIcon = PresetVariant::SaveIcon;
            listItem->setSizeHint(QSize(695 , 50));
            listItem->setData(qVariantFromValue(itemVariant), Qt::UserRole);
            QStandardItem* root = mRadioPresetStandardItemModel->invisibleRootItem();
            mRadioPresetStandardItemModel->setItem(root->rowCount(), 0, listItem);
        }
        //----------------------------------------

    }
}
void RadioAmPrivate::initRadioListFragment()
{
    const int list_x= 20;
    const int list_xw= 720;
    const int list_y= 10;
    const int list_yw= 300;
    if (NULL == mRadioListFragmentListView) {
            //mRadioListFragmentListView = new CustomListView(mListFragmentView);
            mRadioListFragmentListView = new RadioListView(mListFragmentView);
            mRadioListFragmentListView->setGeometry(list_x,list_y,list_xw,list_yw);
            mRadioListFragmentListView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

            if (NULL == mRadioListStandardItemModel) {
                    mRadioListStandardItemModel = new QStandardItemModel(mRadioListFragmentListView);
                }

            if (NULL == mRadioListDelegate) {
                    mRadioListDelegate = new RadioAmListFreqDelegate(this,mRadioListFragmentListView);
                }

            if (NULL == mRadioListFragmentListViewScrollBar) {
                    mRadioListFragmentListViewScrollBar = new CustomScrollBar(mRadioListFragmentListView);
                    mRadioListFragmentListViewScrollBar->setStyleSheet(
                    "QScrollBar:vertical{"
                    "width: " + QString::number(8) + "px;"
                    "border-top-right-radius: " + QString::number(4) + "px;"
                    "border-bottom-right-radius: " + QString::number(4) + "px;"
                    "border-top-left-radius: " + QString::number(4) + "px;"
                    "border-bottom-left-radius: " + QString::number(4) + "px;"
                    "background: rgba(56, 56, 56, 255);"//transparent
                    "margin: 20px, 0px, 0px, 0px;"
                    "padding: 0px, 0px, 0px, 0px;"
                    "}"
                    "QScrollBar::handle:vertical{"
                    "border-top-right-radius: " + QString::number(4) + "px;"
                    "border-bottom-right-radius: " + QString::number(4) + "px;"
                    "border-top-left-radius: " + QString::number(4) + "px;"
                    "border-bottom-left-radius: " + QString::number(4) + "px;"
                    "min-height: " + QString::number(40) + "px;"
                    "background: rgba(41, 151, 252, 255);"//rgba(0, 162, 255, 191)
                    "}"
                    "QScrollBar::add-line:vertical{"
                    "height: 0px;"
                    "width: 0px;"
                    "}"
                    "QScrollBar::sub-line:vertical{"
                    "height: 0px;"
                    "width: 0px;"
                    "}"
                    "QScrollBar::add-page:vertical{"
                    "margin-left: " + QString::number(2) + "px;"
                    "margin-right: " + QString::number(2) + "px;"
                    "background: transparent;"//rgba(42, 42, 42, 191)
                    "}"
                    "QScrollBar::sub-page:vertical{"
                    "margin-left: " + QString::number(2) + "px;"
                    "margin-right: " + QString::number(2) + "px;"
                    "background: transparent;"//rgba(42, 42, 42, 191)
                    "}"
                     );
            }

            mRadioListFragmentListView->setItemDelegate(mRadioListDelegate);
            mRadioListFragmentListView->setVerticalScrollBar(mRadioListFragmentListViewScrollBar);
            mRadioListFragmentListView->setModel(mRadioListStandardItemModel);
            initRadioListData();

        }

}

void RadioAmPrivate::initRadioListData(){

    if(mRadioListStandardItemModel != NULL)
    {
        QList<int> am_freq = gRadioData->getData().getAmListFreqs();
        unsigned int i;
        for(i=0;i<am_freq.size();i++)
        {
            QStandardItem* listItem = new QStandardItem();
            ListVariant itemVariant;
            itemVariant.mFrequency = am_freq.at(i);
            listItem->setSizeHint(QSize(695 , 50));
            listItem->setData(qVariantFromValue(itemVariant), Qt::UserRole);
            QStandardItem* root = mRadioListStandardItemModel->invisibleRootItem();
            mRadioListStandardItemModel->setItem(root->rowCount(), 0, listItem);
        }

    }

}

void RadioAmPrivate::doReFreshCurFreq(const int &curFreq,bool updatePreset,bool updateList){
    //qDebug()<<"doReFreshCurFreq curFreq:"<<curFreq<<endl;
    if(mAmFragment_FreqText != NULL){
      mAmFragment_FreqText->setText(QString("%1").arg(curFreq));
    }
    if(mAmFreqBarSlider != NULL){
       int slider_val = (curFreq-FREQ_MIN)*SLIDER_BAR_MAX/(FREQ_MAX-FREQ_MIN);
       mAmFreqBarSlider->setValue(slider_val);
    }

    if(updatePreset){
       QList<int> presetFreqs =gRadioData->getData().getAmPresetFreqs();
       int curfreq_in_preset_idx = -1;
       for (int i = 0; i < presetFreqs.size(); ++i) {
           //qDebug()<<"doReFreshCurFreq presetFreqs["<<i<<"]="<<presetFreqs.at(i)<<endl;
           if(curFreq == presetFreqs.at(i)){
               curfreq_in_preset_idx = i;
               break;
           }
       }

       if(mRadioPresetDelegate != NULL&&mRadioPresetStandardItemModel !=NULL){
           //update or new item in the list tails
           QStandardItem* listItem = new QStandardItem();
           PresetVariant itemVariant;
           itemVariant.mFrequency = curFreq;
           itemVariant.m_ActiveIcon = PresetVariant::SaveIcon;
           listItem->setSizeHint(QSize(695 , 50));
           listItem->setData(qVariantFromValue(itemVariant), Qt::UserRole);
           mRadioPresetStandardItemModel->setItem(presetFreqs.size(), 0, listItem);
       }

       //qDebug()<<"doReFreshCurFreq curfreq_in_preset_idx:"<<curfreq_in_preset_idx<<endl;
       if(curfreq_in_preset_idx != -1){
           if(mRadioPresetDelegate != NULL &&mRadioPresetStandardItemModel !=NULL){
               mRadioPresetDelegate->m_CurIndex =  mRadioPresetStandardItemModel->index(curfreq_in_preset_idx,0);
               //delete the tails sava item here
               ////mRadioPresetStandardItemModel->removeRow(presetFreqs.size());
               if(mRadioPresetFragmentListView != NULL){
                   mRadioPresetFragmentListView->scrollTo(mRadioPresetDelegate->m_CurIndex);
               }

           }
       }else{
           if(mRadioPresetDelegate != NULL &&mRadioPresetStandardItemModel !=NULL){
               mRadioPresetDelegate->m_CurIndex =  QModelIndex(); //use a new instance to clean the orig one
//               if(mRadioPresetFragmentListView != NULL){
//                   mRadioPresetFragmentListView->scrollToBottom();
//               }
           }
       }
    }
    if(updateList){
        QList<int> listFreqs =gRadioData->getData().getAmListFreqs();
        int curfreq_in_list_idx = -1;
        for (int i = 0; i < listFreqs.size(); ++i) {
            if(curFreq == listFreqs.at(i)){
                curfreq_in_list_idx = i;
                break;
            }
        }
        if(curfreq_in_list_idx != -1){
            if(mRadioListDelegate != NULL &&mRadioListStandardItemModel !=NULL){
                mRadioListDelegate->m_CurIndex =  mRadioListStandardItemModel->index(curfreq_in_list_idx,0);
            }
        }else{
            if(mRadioListDelegate != NULL){
               mRadioListDelegate->m_CurIndex =  QModelIndex(); //use a new instance to clean the orig one
            }
        }
    }

}
void RadioAmPrivate::doReFreshPresetFreqs(const QList<int> &presetFreqs){
    if(mRadioPresetStandardItemModel !=NULL){
        unsigned int i;
        mRadioPresetStandardItemModel->clear();
        for(i=0;i<presetFreqs.size();i++)
        {
            QStandardItem* listItem = new QStandardItem();
            PresetVariant itemVariant;
            itemVariant.mFrequency = presetFreqs.at(i);
            listItem->setSizeHint(QSize(695 , 50));
            listItem->setData(qVariantFromValue(itemVariant), Qt::UserRole);
            QStandardItem* root = mRadioPresetStandardItemModel->invisibleRootItem();
            mRadioPresetStandardItemModel->setItem(root->rowCount(), 0, listItem);
        }

        //add current freq in the last item if not in the list here!!
        //if in the qlist then set the item hight light
        int cur_freq = gRadioData->getData().getCurAmFreq();
        QStandardItem* listItem = new QStandardItem();
        PresetVariant itemVariant;
        itemVariant.mFrequency = cur_freq;
        itemVariant.m_ActiveIcon = PresetVariant::SaveIcon;
        listItem->setSizeHint(QSize(695 , 50));
        listItem->setData(qVariantFromValue(itemVariant), Qt::UserRole);
        QStandardItem* root = mRadioPresetStandardItemModel->invisibleRootItem();
        mRadioPresetStandardItemModel->setItem(root->rowCount(), 0, listItem);

        if(presetFreqs.contains(cur_freq))
        {
            int curfreq_in_preset_idx = -1;
            for (int i = 0; i < presetFreqs.size(); ++i) {
                if(cur_freq == presetFreqs.at(i)){
                    curfreq_in_preset_idx = i;
                    break;
                }
            }

            if(curfreq_in_preset_idx != -1){
                if(mRadioPresetDelegate != NULL &&mRadioPresetStandardItemModel !=NULL){
                    mRadioPresetDelegate->m_CurIndex =  mRadioPresetStandardItemModel->index(curfreq_in_preset_idx,0);
                    if(curfreq_in_preset_idx == presetFreqs.size()-1){
                        mRadioPresetFragmentListView->scrollToBottom();
                    }
                }
            }
        }
        //----------------------------------------
    }
}
void RadioAmPrivate::doReFreshListFreqs(const QList<int> &listFreqs){
    if(mRadioListStandardItemModel !=NULL){
        unsigned int i;
        mRadioListStandardItemModel->clear();
        for(i=0;i<listFreqs.size();i++)
        {
            QStandardItem* listItem = new QStandardItem();
            ListVariant itemVariant;
            itemVariant.mFrequency = listFreqs.at(i);
            listItem->setSizeHint(QSize(695 , 50));
            listItem->setData(qVariantFromValue(itemVariant), Qt::UserRole);
            QStandardItem* root = mRadioListStandardItemModel->invisibleRootItem();
            mRadioListStandardItemModel->setItem(root->rowCount(), 0, listItem);
        }
    }
}

void RadioAmPrivate::onBtnBottomAmPrev()
{
  mProcess->requestAmPrevChannel();
}
void RadioAmPrivate::onBtnBottomAmSeekPrev()
{
  mProcess->requestAmSeekPrev();
}
void RadioAmPrivate::onBtnBottomAmSeekNext()
{
  mProcess->requestAmSeekNext();
}
void RadioAmPrivate::onBtnBottomAmNext()
{
  mProcess->requestAmNextChannel();
}

void RadioAmPrivate::onBtnBottomPresetSeekPrev()
{
  //mProcess->requestAmSeekPrev();
  //here change to page up function
  mRadioPresetFragmentListView->pageUpOrDown(true);
}
void RadioAmPrivate::onBtnBottomPresetAutoSearch()
{

}
void RadioAmPrivate::onBtnBottomPresetSeekNext()
{
  //mProcess->requestAmSeekNext();
  //here change to page down function
  mRadioPresetFragmentListView->pageUpOrDown(false);
}

void RadioAmPrivate::onBtnBottomListSeekPrev()
{
  //mProcess->requestAmSeekPrev();
  //here change to page up function
  mRadioListFragmentListView->pageUpOrDown(true);

}
void RadioAmPrivate::onBtnBottomListSearch()
{

}
void RadioAmPrivate::onBtnBottomListSeekNext()
{
  //mProcess->requestAmSeekNext();
  //here change to page down function
  mRadioListFragmentListView->pageUpOrDown(false);
}


void RadioAmPrivate::doSliderPressed(const int value){
    int freq = (FREQ_MAX-FREQ_MIN)*value/SLIDER_BAR_MAX+FREQ_MIN;
    if(mAmFragment_FreqText != NULL){
      mAmFragment_FreqText->setText(QString("%1").arg(freq));
    }
    mProcess->setAmCurFreq(freq,true,true);
}
void RadioAmPrivate::doSliderMoved(const int value){
    int freq = (FREQ_MAX-FREQ_MIN)*value/SLIDER_BAR_MAX+FREQ_MIN;
    if(mAmFragment_FreqText != NULL){
      mAmFragment_FreqText->setText(QString("%1").arg(freq));
    }
    mProcess->setAmCurFreq(freq,true,true);
}
void RadioAmPrivate::doSliderReleased(const int value){
    int freq = (FREQ_MAX-FREQ_MIN)*value/SLIDER_BAR_MAX+FREQ_MIN;
    if(mAmFragment_FreqText != NULL){
      mAmFragment_FreqText->setText(QString("%1").arg(freq));
    }
    mProcess->setAmCurFreq(freq,true,true);
}

//-----------------------

RadioAmPresetFreqDelegate::RadioAmPresetFreqDelegate(RadioAmPrivate *radioPri,QObject* parent)
    : mRadioPri(radioPri),CustomItemDelegate(parent),mFunIconRect(500,10,24,29)
{
  m_Interval_Line.reset(new QPixmap(QString(":/res/drawable/list_item_space_line.png")));
  m_SaveIconNormal.reset(new QPixmap(QString(":/res/drawable/edit_save.png")));
  m_SaveIconPressed.reset(new QPixmap(QString(":/res/drawable/edit_save_pressed.png")));
  m_RemoveIconNormal.reset(new QPixmap(QString(":/res/drawable/edit_remove.png")));
  m_RemoveIconPressed.reset(new QPixmap(QString(":/res/drawable/edit_remove_pressed.png")));
}

RadioAmPresetFreqDelegate::~RadioAmPresetFreqDelegate()
{
  delete mRadioPri;
}

void RadioAmPresetFreqDelegate::paint(QPainter* painter,
                                    const QStyleOptionViewItem &option,
                                    const QModelIndex &index) const {

    if(m_CurIndex == index){
        painter->setPen(Qt::green);
    }else{
        painter->setPen(Qt::white);
    }

    if(m_PressIndex == index){
        painter->setPen(Qt::green);
    }
    QFont myfont;
    myfont.setPointSize(13);
    painter->setFont(myfont);

    PresetVariant variant = qVariantFromValue(index.data(Qt::UserRole)).value<PresetVariant>();//qvariant_cast<PresetVariant>(index.data(Qt::UserRole));//qVariantValue<PresetVariant>(index.data(Qt::UserRole));
    QRect textRect(150 + option.rect.x(),
                               10 + option.rect.y(),
                               693,
                               40);

    QString freqShow = QString("PO%1   AM ").arg(index.row()+1)+tr("电台")+QString(" %2 KHz").arg(variant.mFrequency);
    painter->drawText(textRect, Qt::AlignLeft, freqShow);

    QRect spaceLineRect(30 + option.rect.x(),
                               47 + option.rect.y(),
                               693,
                               2);

    painter->drawPixmap(spaceLineRect.x(), spaceLineRect.y(), *m_Interval_Line);

    QRect RightIconRect(mFunIconRect.x() + option.rect.x(),
                               mFunIconRect.y() + option.rect.y(),
                               mFunIconRect.width(),
                               mFunIconRect.height());

    switch (variant.m_ActiveIcon) {
    case PresetVariant::SaveIcon:
         {
           switch (variant.m_SaveIconSta) {
          case PresetVariant::B_Normal:
            painter->drawPixmap(RightIconRect, *m_SaveIconNormal);
            break;
          case PresetVariant::B_Press:
            painter->drawPixmap(RightIconRect, *m_SaveIconPressed);
            break;
          default:
            break;
           }
         }
        break;
    case PresetVariant::RemoveIcon:
        {
         switch (variant.m_RemoveIconSta) {
         case PresetVariant::B_Normal:
              painter->drawPixmap(RightIconRect, *m_RemoveIconNormal);
              break;
         case PresetVariant::B_Press:
              painter->drawPixmap(RightIconRect, *m_RemoveIconPressed);
              break;
         default:
              break;
          }
        }
        break;
    default:
        break;
    }
}

void RadioAmPresetFreqDelegate::mousePressEvent(QMouseEvent* event,
                                         QAbstractItemModel *model,
                                         const QStyleOptionViewItem &option,
                                         const QModelIndex &index)
{
   m_StartMovePoint = event->pos();
   PresetVariant variant = qVariantFromValue(index.data(Qt::UserRole)).value<PresetVariant>();
   QRect ItemFuncIconRect(mFunIconRect.x() + option.rect.x(),
                              mFunIconRect.y() + option.rect.y(),
                              mFunIconRect.width(),
                              mFunIconRect.height());
   if(ItemFuncIconRect.contains(event->pos())){
       switch (variant.m_ActiveIcon) {
       case PresetVariant::SaveIcon:
           variant.m_SaveIconSta = PresetVariant::B_Press;
           variant.m_RemoveIconSta = PresetVariant::B_Normal;
           break;
       case PresetVariant::RemoveIcon:
           variant.m_RemoveIconSta = PresetVariant::B_Press;
           variant.m_SaveIconSta = PresetVariant::B_Normal;
           break;
        default:
           break;
       }
       model->setData(index, qVariantFromValue(variant), Qt::UserRole);
       m_PressIndex = QModelIndex(); //clean the press modelindex here
   }
}

void RadioAmPresetFreqDelegate::mouseMoveEvent(QMouseEvent* event,
                                        QAbstractItemModel *model,
                                        const QStyleOptionViewItem &option,
                                        const QModelIndex &index)
{
    PresetVariant variant = qVariantFromValue(index.data(Qt::UserRole)).value<PresetVariant>();
    QRect ItemFuncIconRect(mFunIconRect.x() + option.rect.x(),
                               mFunIconRect.y() + option.rect.y(),
                               mFunIconRect.width(),
                               mFunIconRect.height());
    if(!ItemFuncIconRect.contains(event->pos())){
        variant.m_SaveIconSta = PresetVariant::B_Normal;
        variant.m_RemoveIconSta = PresetVariant::B_Normal;
        model->setData(index, qVariantFromValue(variant), Qt::UserRole);
    }
    int deltaEnd = event->pos().y() - m_StartMovePoint.y();
    if(qAbs(deltaEnd)>LISTVIEW_SLIDER_THRESHOLD){
        m_PressIndex = QModelIndex(); //clean the press modelindex here
    }
}

void RadioAmPresetFreqDelegate::mouseReleaseEvent(QMouseEvent* event,
                                           QAbstractItemModel *model,
                                           const QStyleOptionViewItem &option,
                                           const QModelIndex &index)
{
    PresetVariant variant = qVariantFromValue(index.data(Qt::UserRole)).value<PresetVariant>();

    variant.m_SaveIconSta = PresetVariant::B_Normal;
    variant.m_RemoveIconSta = PresetVariant::B_Normal;
    model->setData(index, qVariantFromValue(variant), Qt::UserRole);

    QRect ItemFuncIconRect(mFunIconRect.x() + option.rect.x(),
                               mFunIconRect.y() + option.rect.y(),
                               mFunIconRect.width(),
                               mFunIconRect.height());
    QList<int> presetFreqs =gRadioData->getData().getAmPresetFreqs();

    if(ItemFuncIconRect.contains(event->pos())&&ItemFuncIconRect.contains(m_StartMovePoint)){
        switch (variant.m_ActiveIcon) {
        case PresetVariant::SaveIcon:
             //TODO: add the item
            if(!presetFreqs.contains(variant.mFrequency)){
                presetFreqs.append(variant.mFrequency);
                mRadioPri->mProcess->setAmPresetFreqs(presetFreqs);
            }
            break;
        case PresetVariant::RemoveIcon:
             //TODO: delete the item
             presetFreqs.removeOne(variant.mFrequency);
             mRadioPri->mProcess->setAmPresetFreqs(presetFreqs);
            break;
         default:
            break;
       }
    }
}

bool RadioAmPresetFreqDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    switch (event->type()) {
    case QEvent::MouseButtonPress: {
        QMouseEvent* mouseEvent = reinterpret_cast<QMouseEvent*>(event);
        if (NULL != mouseEvent) {
            mousePressEvent(mouseEvent, model, option, index);
        }
        break;
    }
   case QEvent::MouseMove: {
        QMouseEvent* mouseEvent = reinterpret_cast<QMouseEvent*>(event);
        if (NULL != mouseEvent) {
            mouseMoveEvent(mouseEvent, model, option, index);
        }
        break;
    }
    case QEvent::MouseButtonRelease: {
        QMouseEvent* mouseEvent = reinterpret_cast<QMouseEvent*>(event);
        if (NULL != mouseEvent) {
            mouseReleaseEvent(mouseEvent, model, option, index);
        }
        break;
    }
    default: {
        break;
    }
    }
    return true;
    ////return QItemDelegate::editorEvent(event, model, option, index);
 }


void RadioAmPresetFreqDelegate::onPressIndexChanged(const QModelIndex &index)
{
    PresetVariant variant = qVariantFromValue(index.data(Qt::UserRole)).value<PresetVariant>();
    PresetVariant last_variant = qVariantFromValue(m_PressIndex.data(Qt::UserRole)).value<PresetVariant>();
    if(variant.mFrequency==0 && last_variant.mFrequency >0){
        if(mRadioPri->mRadioPresetFragmentListView != NULL){
            mRadioPri->mRadioPresetFragmentListView->setCurrentIndex(m_PressIndex);
        }
    }

    m_PressIndex = index;
  //qDebug()<<"RadioAmPresetFreqDelegate::onPressIndexChanged mFrequency="<<variant.mFrequency<<endl;
}

void RadioAmPresetFreqDelegate::onCurrentIndexChange(const QModelIndex &index)
{
    m_CurIndex = index;
    PresetVariant variant = qVariantFromValue(index.data(Qt::UserRole)).value<PresetVariant>();
    mRadioPri->mProcess->setAmCurFreq(variant.mFrequency,true,true,true);
}

//---------------------------
RadioAmListFreqDelegate::RadioAmListFreqDelegate(RadioAmPrivate *radioPri,QObject* parent)
    :mRadioPri(radioPri), CustomItemDelegate(parent)
{
   m_Interval_Line.reset(new QPixmap(QString(":/res/drawable/list_item_space_line.png")));
}

RadioAmListFreqDelegate::~RadioAmListFreqDelegate()
{
  delete mRadioPri;
}

void RadioAmListFreqDelegate::paint(QPainter* painter,
                               const QStyleOptionViewItem &option,
                               const QModelIndex &index) const
{

    if(m_CurIndex == index){
        painter->setPen(Qt::green);
    }else{
        painter->setPen(Qt::white);
    }

    if(m_PressIndex == index){
        painter->setPen(Qt::green);
    }
    QFont myfont;
    myfont.setPointSize(13);
    painter->setFont(myfont);

    ListVariant variant = qVariantFromValue(index.data(Qt::UserRole)).value<ListVariant>();
    QRect textRect(150 + option.rect.x(),
                               10 + option.rect.y(),
                               693,
                               40);

    QString freqShow = QString("PO%1   AM ").arg(index.row()+1)+tr("电台")+QString(" %2 KHz").arg(variant.mFrequency);
    painter->drawText(textRect, Qt::AlignLeft, freqShow);

    QRect spaceLineRect(30 + option.rect.x(),
                               47 + option.rect.y(),
                               693,
                               2);

    painter->drawPixmap(spaceLineRect.x(), spaceLineRect.y(), *m_Interval_Line);
}
void RadioAmListFreqDelegate::mousePressEvent(QMouseEvent* event,
                                         QAbstractItemModel *model,
                                         const QStyleOptionViewItem &option,
                                         const QModelIndex &index)
{
   m_StartMovePoint = event->pos();
}

void RadioAmListFreqDelegate::mouseMoveEvent(QMouseEvent* event,
                                        QAbstractItemModel *model,
                                        const QStyleOptionViewItem &option,
                                        const QModelIndex &index)
{
    int deltaEnd = event->pos().y() - m_StartMovePoint.y();
    if(qAbs(deltaEnd)>LISTVIEW_SLIDER_THRESHOLD){
        m_PressIndex = QModelIndex(); //clean the press modelindex here
    }
}

void RadioAmListFreqDelegate::mouseReleaseEvent(QMouseEvent* event,
                                           QAbstractItemModel *model,
                                           const QStyleOptionViewItem &option,
                                           const QModelIndex &index)
{

}
void RadioAmListFreqDelegate::onPressIndexChanged(const QModelIndex &index)
{
    ListVariant variant = qVariantFromValue(index.data(Qt::UserRole)).value<ListVariant>();
    ListVariant last_variant = qVariantFromValue(m_PressIndex.data(Qt::UserRole)).value<ListVariant>();
    if(variant.mFrequency==0 && last_variant.mFrequency >0){
        if(mRadioPri->mRadioListFragmentListView != NULL){
            mRadioPri->mRadioListFragmentListView->setCurrentIndex(m_PressIndex);
        }
    }

    m_PressIndex = index;
  //qDebug()<<"RadioAmListFreqDelegate::onPressIndexChanged mFrequency="<<variant.mFrequency<<endl;
}

void RadioAmListFreqDelegate::onCurrentIndexChange(const QModelIndex &index)
{
    m_CurIndex = index;
    ListVariant variant = qVariantFromValue(index.data(Qt::UserRole)).value<ListVariant>();
    mRadioPri->mProcess->setAmCurFreq(variant.mFrequency,true,true,false);
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
qDebug()<<"RadioAm::onStart()"<<endl;

}
void RadioAm::onResume()
{
  qDebug()<<"RadioAm::onResume()"<<endl;
}
void RadioAm::onPause()
{
  qDebug()<<"RadioAm::onPause()"<<endl;
  Q_D(RadioAm);
  if(d->mTab != RadioAmPrivate::AM)
  {
   d->tabSwitch(RadioAmPrivate::AM);
  }
}
void RadioAm::onStop()
{
  qDebug()<<"RadioAm::onStop()"<<endl;
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
