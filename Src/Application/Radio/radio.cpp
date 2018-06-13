#include "radio.h"
#include "radio_unit.h"
#include "radio_process.h"
#include "radio_data.h"

#include <QDebug>


#define FREQ_MAX  108.0
#define FREQ_MIN  87.5
#define FREQ_STEP  0.1
#define SLIDER_BAR_MAX  ((FREQ_MAX-FREQ_MIN)/FREQ_STEP)


RadioPrivate::RadioPrivate(Radio *parent)
    : QObject(),q_ptr(parent)
{
   mTab = FM;
   mTabBar =NULL;
   mStateBarTab_FM =NULL;
   mStateBarTab_Preset =NULL;
   mStateBarTab_List =NULL;

   mFragmentViewLayout =NULL;
   mFmFragmentContain =NULL;
   mFmFragmentView =NULL;
   mPresetFragmentView =NULL;
   mListFragmentView =NULL;

   mFmFragment_FreqBg =NULL;
   mFmFragment_FreqText =NULL;
   mFmFreqBarSlider = NULL;

   mBottomBarLayout =NULL;
   mBottomBar =NULL;
   mBottom_Fm =NULL;
   mBottom_Preset =NULL;
   mBottom_List =NULL;

   mBottom_Fm_Prev =NULL;
   mBottom_Fm_Seek_Prev =NULL;
   mBottom_Fm_Seek_Next =NULL;
   mBottom_Fm_Next =NULL;

   mBottom_Preset_PageUp =NULL;
   mBottom_Preset_AutoSearch =NULL;
   mBottom_Preset_PageDown =NULL;

   mBottom_List_PageUp =NULL;
   mBottom_List_Search =NULL;
   mBottom_List_PageDown =NULL;

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

void RadioPrivate::initializeBasicWidget(QWidget *parent)
{

  //Q_Q(Radio);

    //***** add top bar ********
    mTabBar = new BmpWidget(parent);
    mTabBar->setBackgroundBmpPath(QString(":/res/drawable/app_statebar.png"));
    mTabBar->setFixedSize(QSize(800, 50));
    //init topbar Fm tab
    mStateBarTab_FM= new BmpButton(mTabBar);
    mStateBarTab_FM->setNormalBmpPath(QString(":/res/drawable/app_statebar_btn.png"));
    mStateBarTab_FM->setPressBmpPath(QString(":/res/drawable/app_statebar_btn_pressed.png"));
    mStateBarTab_FM->setCheckBmpPath(QString(":/res/drawable/app_statebar_btn_pressed.png"));
    mStateBarTab_FM->setGeometry(0,0,140,50);
    mStateBarTab_FM->setText(QString("FM"));
    mStateBarTab_FM->setFontPointSize(14);
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
    mFmFragmentContain = new QWidget(parent);
    mFmFragmentContain->setGeometry(0,50,800,325);
    mFragmentViewLayout = new QStackedLayout();
    mFmFragmentContain->setLayout(mFragmentViewLayout);

    //init Fm fragment
    mFmFragmentView = new QWidget(parent);
    mFmFragmentView->setFixedSize(QSize(800, 325));
    mFragmentViewLayout->addWidget(mFmFragmentView);
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
    //init buttom bar fm
    mBottom_Fm = new BmpWidget(mBottomBar);
    mBottom_Fm->setBackgroundBmpPath(QString(":/res/drawable/app_bottombar_4btns_bg.png"));
    mBottom_Fm->setFixedSize(QSize(800, 60));
    mBottom_Fm_Prev= new BmpButton(mBottom_Fm);
    mBottom_Fm_Prev->setNormalBmpPath(QString(":/res/drawable/bottom_bar_prev.png"));
    mBottom_Fm_Prev->setPressBmpPath(QString(":/res/drawable/bottom_bar_prev_pressed.png"));
    mBottom_Fm_Prev->setGeometry(0,0,200,60);
    mBottom_Fm_Seek_Prev= new BmpButton(mBottom_Fm);
    mBottom_Fm_Seek_Prev->setNormalBmpPath(QString(":/res/drawable/bottom_bar_seek_prev.png"));
    mBottom_Fm_Seek_Prev->setPressBmpPath(QString(":/res/drawable/bottom_bar_seek_prev_pressed.png"));
    mBottom_Fm_Seek_Prev->setGeometry(200,0,200,60);
    mBottom_Fm_Seek_Next= new BmpButton(mBottom_Fm);
    mBottom_Fm_Seek_Next->setNormalBmpPath(QString(":/res/drawable/bottom_bar_seek_next.png"));
    mBottom_Fm_Seek_Next->setPressBmpPath(QString(":/res/drawable/bottom_bar_seek_next_pressed.png"));
    mBottom_Fm_Seek_Next->setGeometry(400,0,200,60);
    mBottom_Fm_Next= new BmpButton(mBottom_Fm);
    mBottom_Fm_Next->setNormalBmpPath(QString(":/res/drawable/bottom_bar_next.png"));
    mBottom_Fm_Next->setPressBmpPath(QString(":/res/drawable/bottom_bar_next_pressed.png"));
    mBottom_Fm_Next->setGeometry(600,0,200,60);
    mBottomBarLayout->addWidget(mBottom_Fm);


    //init buttom bar preset
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
    mBottom_Preset_AutoSearch->setFontPointSize(16);
    mBottom_Preset_PageDown= new BmpButton(mBottom_Preset);
    mBottom_Preset_PageDown->setNormalBmpPath(QString(":/res/drawable/bottom_bar_page_down.png"));
    mBottom_Preset_PageDown->setPressBmpPath(QString(":/res/drawable/bottom_bar_page_down_pressed.png"));
    mBottom_Preset_PageDown->setGeometry(533,0,267,60);
    mBottomBarLayout->addWidget(mBottom_Preset);

    //init buttom bar list
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
    mBottom_List_Search->setFontPointSize(16);
    mBottom_List_PageDown= new BmpButton(mBottom_List);
    mBottom_List_PageDown->setNormalBmpPath(QString(":/res/drawable/bottom_bar_page_down.png"));
    mBottom_List_PageDown->setPressBmpPath(QString(":/res/drawable/bottom_bar_page_down_pressed.png"));
    mBottom_List_PageDown->setGeometry(533,0,267,60);
    mBottomBarLayout->setCurrentIndex(mTab);

    tabSwitch(mTab);

    connect(mStateBarTab_FM,SIGNAL(released()),this,SLOT(onBtnTabFm()));
    connect(mStateBarTab_Preset,SIGNAL(released()),this,SLOT(onBtnTabPreset()));
    connect(mStateBarTab_List,SIGNAL(released()),this,SLOT(onBtnTabList()));

    connect(mBottom_Fm_Prev,SIGNAL(released()),this,SLOT(onBtnBottomFmPrev()));
    connect(mBottom_Fm_Seek_Prev,SIGNAL(released()),this,SLOT(onBtnBottomFmSeekPrev()));
    connect(mBottom_Fm_Seek_Next,SIGNAL(released()),this,SLOT(onBtnBottomFmSeekNext()));
    connect(mBottom_Fm_Next,SIGNAL(released()),this,SLOT(onBtnBottomFmNext()));

    connect(mBottom_Preset_PageUp,SIGNAL(released()),this,SLOT(onBtnBottomPresetPageUp()));
    connect(mBottom_Preset_AutoSearch,SIGNAL(released()),this,SLOT(onBtnBottomPresetAutoSearch()));
    connect(mBottom_Preset_PageDown,SIGNAL(released()),this,SLOT(onBtnBottomPresetPageDown()));

    connect(mBottom_List_PageUp,SIGNAL(released()),this,SLOT(onBtnBottomListPageUp()));
    connect(mBottom_List_Search,SIGNAL(released()),this,SLOT(onBtnBottomListSearch()));
    connect(mBottom_List_PageDown,SIGNAL(released()),this,SLOT(onBtnBottomListPageDown()));

    mProcess->linkRadio(this);
}


void RadioPrivate::onBtnTabFm()
{
    if(mTab != FM){
       mTab = FM;
    }
    tabSwitch(mTab);
}
void RadioPrivate::onBtnTabPreset()
{
    if(mTab != PRESET){
       mTab = PRESET;
    }
    tabSwitch(mTab);
}
void RadioPrivate::onBtnTabList()
{
    if(mTab != LIST){
       mTab = LIST;
    }
    tabSwitch(mTab);
}

void RadioPrivate::tabSwitch(const Tab mytab)
{
    mTab = mytab;
    switch (mytab) {
    case FM:
        mStateBarTab_FM->setStatus(BmpButton::B_Check);
        mStateBarTab_Preset->setStatus(BmpButton::B_Normal);
        mStateBarTab_List->setStatus(BmpButton::B_Normal);
        initRadioFmFragment();
        break;
    case PRESET:
        mStateBarTab_FM->setStatus(BmpButton::B_Normal);
        mStateBarTab_Preset->setStatus(BmpButton::B_Check);
        mStateBarTab_List->setStatus(BmpButton::B_Normal);
        initRadioPresetFragment();
        //-------
        doReFreshCurFreq(gRadioData->getData().getCurFmFreq(),true,false);
        break;
    case LIST:
        mStateBarTab_FM->setStatus(BmpButton::B_Normal);
        mStateBarTab_Preset->setStatus(BmpButton::B_Normal);
        mStateBarTab_List->setStatus(BmpButton::B_Check);
        initRadioListFragment();
        //-------
        doReFreshCurFreq(gRadioData->getData().getCurFmFreq(),false,true);
        break;
    default:
        break;
    }
    mFragmentViewLayout->setCurrentIndex(mytab);
    mBottomBarLayout->setCurrentIndex(mytab);
}

void RadioPrivate::initRadioFmFragment()
{
    const int freq_y= 85;
    const int freq_text_w= 140;
    const int freq_scalebar_y= 205;
    const double cur_freq = gRadioData->getData().getCurFmFreq();

    if(mFmFragment_FreqBg==NULL)
    {
        int slider_val = (cur_freq-FREQ_MIN)*SLIDER_BAR_MAX/(FREQ_MAX-FREQ_MIN);

        mFmFragment_FreqBg = new BmpWidget(mFmFragmentView);
        mFmFragment_FreqBg->setBackgroundBmpPath(QString(":/res/drawable/radio_freq_bg.png"));
        mFmFragment_FreqBg->setGeometry((800-124)/2,freq_y,124,50);
        mFmFragment_FreqText = new TextWidget(mFmFragmentView);
        mFmFragment_FreqText->setLanguageType(TextWidget::T_NoTranslate);
        mFmFragment_FreqText->setText(QString("%1").arg(cur_freq,1,'f',1));
        mFmFragment_FreqText->setFontPointSize(28);
        mFmFragment_FreqText->setGeometry((800-freq_text_w)/2,freq_y,freq_text_w,50);

        mFmFreqBarSlider = new Slider(mFmFragmentView);
        mFmFreqBarSlider->setMaximum(SLIDER_BAR_MAX);
        mFmFreqBarSlider->setMinimum(0);
        mFmFreqBarSlider->setValue(slider_val);
        mFmFreqBarSlider->setGeometry((800-641)/2,freq_scalebar_y,641,65);
        mFmFreqBarSlider->setStyleSheet(
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

        connect(mFmFreqBarSlider,SIGNAL(sliderPressed(int)),this,SLOT(doSliderPressed(int)));
        connect(mFmFreqBarSlider,SIGNAL(sliderMoved(int)),this,SLOT(doSliderMoved(int)));
        connect(mFmFreqBarSlider,SIGNAL(sliderReleased(int)),this,SLOT(doSliderReleased(int)));

    }

}
void RadioPrivate::initRadioPresetFragment()
{
    const int preset_x= 20;
    const int preset_xw= 720;
    const int preset_y= 10;
    const int preset_yw= 300;
    if (NULL == mRadioPresetFragmentListView) {
            mRadioPresetFragmentListView = new CustomListView(mPresetFragmentView);
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
                    mRadioPresetDelegate = new RadioPresetFreqDelegate(this,mRadioPresetFragmentListView);
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
void RadioPrivate::initRadioPresetData()
{

    if(mRadioPresetStandardItemModel != NULL)
    {
        QList<double> fm_freq = gRadioData->getData().getFmPresetFreqs();
        unsigned int i;
        for(i=0;i<fm_freq.size();i++)
        {
            QStandardItem* listItem = new QStandardItem();
            PresetVariant itemVariant;
            itemVariant.mFrequency = fm_freq.at(i);
            listItem->setSizeHint(QSize(695 , 50));
            listItem->setData(qVariantFromValue(itemVariant), Qt::UserRole);
            QStandardItem* root = mRadioPresetStandardItemModel->invisibleRootItem();
            mRadioPresetStandardItemModel->setItem(root->rowCount(), 0, listItem);
        }

    }
}
void RadioPrivate::initRadioListFragment()
{
    const int list_x= 20;
    const int list_xw= 720;
    const int list_y= 10;
    const int list_yw= 300;
    if (NULL == mRadioListFragmentListView) {
            mRadioListFragmentListView = new CustomListView(mListFragmentView);
            mRadioListFragmentListView->setGeometry(list_x,list_y,list_xw,list_yw);
            mRadioListFragmentListView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

            if (NULL == mRadioListStandardItemModel) {
                    mRadioListStandardItemModel = new QStandardItemModel(mRadioListFragmentListView);
                }

            if (NULL == mRadioListDelegate) {
                    mRadioListDelegate = new RadioListFreqDelegate(this,mRadioListFragmentListView);
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

void RadioPrivate::initRadioListData(){

    if(mRadioListStandardItemModel != NULL)
    {
        QList<double> fm_freq = gRadioData->getData().getFmListFreqs();
        unsigned int i;
        for(i=0;i<fm_freq.size();i++)
        {
            QStandardItem* listItem = new QStandardItem();
            ListVariant itemVariant;
            itemVariant.mFrequency = fm_freq.at(i);
            listItem->setSizeHint(QSize(695 , 50));
            listItem->setData(qVariantFromValue(itemVariant), Qt::UserRole);
            QStandardItem* root = mRadioListStandardItemModel->invisibleRootItem();
            mRadioListStandardItemModel->setItem(root->rowCount(), 0, listItem);
        }

    }

}

void RadioPrivate::doReFreshCurFreq(const double &curFreq,bool updatePreset,bool updateList){
    //qDebug()<<"doReFreshCurFreq curFreq:"<<curFreq<<endl;

    if(mFmFragment_FreqText != NULL){
      mFmFragment_FreqText->setText(QString("%1").arg(curFreq,1,'f',1));
    }
    if(mFmFreqBarSlider != NULL){
       int slider_val = (curFreq-FREQ_MIN)*SLIDER_BAR_MAX/(FREQ_MAX-FREQ_MIN);
       mFmFreqBarSlider->setValue(slider_val);
    }

    if(updatePreset){
       QList<double> presetFreqs =gRadioData->getData().getFmPresetFreqs();
       int curfreq_in_preset_idx = -1;
       for (int i = 0; i < presetFreqs.size(); ++i) {
           //qDebug()<<"doReFreshCurFreq presetFreqs["<<i<<"]="<<presetFreqs.at(i)<<endl;
           if(curFreq == presetFreqs.at(i)){
               curfreq_in_preset_idx = i;
               break;
           }else if((float)curFreq == (float)presetFreqs.at(i)){
               curfreq_in_preset_idx = i;
               break;
           }
       }
       //qDebug()<<"doReFreshCurFreq curfreq_in_preset_idx:"<<curfreq_in_preset_idx<<endl;
       if(curfreq_in_preset_idx != -1){
           if(mRadioPresetDelegate != NULL &&mRadioPresetStandardItemModel !=NULL){
               mRadioPresetDelegate->m_CurIndex =  mRadioPresetStandardItemModel->index(curfreq_in_preset_idx,0);
           }
       }else{
           if(mRadioPresetDelegate != NULL){
               mRadioPresetDelegate->m_CurIndex =  QModelIndex(); //use a new instance to clean the orig one
           }

       }
    }
    if(updateList){
        QList<double> listFreqs =gRadioData->getData().getFmListFreqs();
        int curfreq_in_list_idx = -1;
        for (int i = 0; i < listFreqs.size(); ++i) {
            if(curFreq == listFreqs.at(i)){
                curfreq_in_list_idx = i;
                break;
            }else if((float)curFreq == (float)listFreqs.at(i)){
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
void RadioPrivate::doReFreshPresetFreqs(const QList<double> &presetFreqs){
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
    }
}
void RadioPrivate::doReFreshListFreqs(const QList<double> &listFreqs){
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

void RadioPrivate::onBtnBottomFmPrev()
{
 mProcess->requestFmPrevChannel();
}
void RadioPrivate::onBtnBottomFmSeekPrev()
{
 mProcess->requestFmSeekPrev();
}
void RadioPrivate::onBtnBottomFmSeekNext()
{
 mProcess->requestFmSeekNext();
}
void RadioPrivate::onBtnBottomFmNext()
{
 mProcess->requestFmNextChannel();
}

void RadioPrivate::onBtnBottomPresetPageUp()
{

}
void RadioPrivate::onBtnBottomPresetAutoSearch()
{

}
void RadioPrivate::onBtnBottomPresetPageDown()
{

}

void RadioPrivate::onBtnBottomListPageUp()
{

}
void RadioPrivate::onBtnBottomListSearch()
{

}
void RadioPrivate::onBtnBottomListPageDown()
{

}



void RadioPrivate::doSliderPressed(const int value){
   double freq = (FREQ_MAX-FREQ_MIN)*value/SLIDER_BAR_MAX+FREQ_MIN;
   if(mFmFragment_FreqText != NULL){
     mFmFragment_FreqText->setText(QString("%1").arg(freq,1,'f',1));
   }
   mProcess->setFmCurFreq(freq,true,true);
}
void RadioPrivate::doSliderMoved(const int value){
    double freq = (FREQ_MAX-FREQ_MIN)*value/SLIDER_BAR_MAX+FREQ_MIN;
    if(mFmFragment_FreqText != NULL){
       mFmFragment_FreqText->setText(QString("%1").arg(freq,1,'f',1));
    }
    mProcess->setFmCurFreq(freq,true,true);
}
void RadioPrivate::doSliderReleased(const int value){
    double freq = (FREQ_MAX-FREQ_MIN)*value/SLIDER_BAR_MAX+FREQ_MIN;
    if(mFmFragment_FreqText != NULL){
       mFmFragment_FreqText->setText(QString("%1").arg(freq,1,'f',1));
    }
    mProcess->setFmCurFreq(freq,true,true);
}

//---------------------------
RadioPresetFreqDelegate::RadioPresetFreqDelegate(RadioPrivate *radioPri,QObject* parent)
    : mRadioPri(radioPri),CustomItemDelegate(parent),mFunIconRect(500,10,24,29)
{
  m_Interval_Line.reset(new QPixmap(QString(":/res/drawable/list_item_space_line.png")));
  m_SaveIconNormal.reset(new QPixmap(QString(":/res/drawable/edit_save.png")));
  m_SaveIconPressed.reset(new QPixmap(QString(":/res/drawable/edit_save_pressed.png")));
  m_RemoveIconNormal.reset(new QPixmap(QString(":/res/drawable/edit_remove.png")));
  m_RemoveIconPressed.reset(new QPixmap(QString(":/res/drawable/edit_remove_pressed.png")));
}

RadioPresetFreqDelegate::~RadioPresetFreqDelegate()
{
  delete mRadioPri;

}

void RadioPresetFreqDelegate::paint(QPainter* painter,
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

    QString freqShow = QString("PO%1   FM ").arg(index.row()+1)+tr("电台")+QString(" %2 MHz").arg(variant.mFrequency,1,'f',1);
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

void RadioPresetFreqDelegate::mousePressEvent(QMouseEvent* event,
                                         QAbstractItemModel *model,
                                         const QStyleOptionViewItem &option,
                                         const QModelIndex &index)
{
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
   }
}

void RadioPresetFreqDelegate::mouseMoveEvent(QMouseEvent* event,
                                        QAbstractItemModel *model,
                                        const QStyleOptionViewItem &option,
                                        const QModelIndex &index)
{

}

void RadioPresetFreqDelegate::mouseReleaseEvent(QMouseEvent* event,
                                           QAbstractItemModel *model,
                                           const QStyleOptionViewItem &option,
                                           const QModelIndex &index)
{
    PresetVariant variant = qVariantFromValue(index.data(Qt::UserRole)).value<PresetVariant>();
    QRect ItemFuncIconRect(mFunIconRect.x() + option.rect.x(),
                               mFunIconRect.y() + option.rect.y(),
                               mFunIconRect.width(),
                               mFunIconRect.height());
    if(ItemFuncIconRect.contains(event->pos())){
        switch (variant.m_ActiveIcon) {
        case PresetVariant::SaveIcon:
            variant.m_SaveIconSta = PresetVariant::B_Normal;
            variant.m_RemoveIconSta = PresetVariant::B_Normal;
            //ToDo something

            break;
        case PresetVariant::RemoveIcon:
            variant.m_RemoveIconSta = PresetVariant::B_Normal;
            variant.m_SaveIconSta = PresetVariant::B_Normal;
            //ToDo something

            break;
         default:
            break;
        }
        model->setData(index, qVariantFromValue(variant), Qt::UserRole);
    }
}

void RadioPresetFreqDelegate::onPressIndexChanged(const QModelIndex &index)
{
  m_PressIndex = index;
  PresetVariant variant = qVariantFromValue(index.data(Qt::UserRole)).value<PresetVariant>();
  if(variant.mFrequency>0){
      if(mRadioPri->mRadioPresetFragmentListView != NULL){
          mRadioPri->mRadioPresetFragmentListView->setCurrentIndex(index);
      }
  }
  //qDebug()<<"RadioPresetFreqDelegate::onPressIndexChanged mFrequency="<<variant.mFrequency<<endl;
}

void RadioPresetFreqDelegate::onCurrentIndexChange(const QModelIndex &index)
{
    m_CurIndex = index;
    PresetVariant variant = qVariantFromValue(index.data(Qt::UserRole)).value<PresetVariant>();
    mRadioPri->mProcess->setFmCurFreq(variant.mFrequency,true,false,true);
}

//---------------------------
RadioListFreqDelegate::RadioListFreqDelegate(RadioPrivate *radioPri,QObject* parent)
    :mRadioPri(radioPri),CustomItemDelegate(parent)
{
   m_Interval_Line.reset(new QPixmap(QString(":/res/drawable/list_item_space_line.png")));
}

RadioListFreqDelegate::~RadioListFreqDelegate()
{
  delete mRadioPri;
}

void RadioListFreqDelegate::paint(QPainter* painter,
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

    QString freqShow = QString("PO%1   FM ").arg(index.row()+1)+tr("电台")+QString(" %2 MHz").arg(variant.mFrequency,1,'f',1);
    painter->drawText(textRect, Qt::AlignLeft, freqShow);

    QRect spaceLineRect(30 + option.rect.x(),
                               47 + option.rect.y(),
                               693,
                               2);

    painter->drawPixmap(spaceLineRect.x(), spaceLineRect.y(), *m_Interval_Line);

}

void RadioListFreqDelegate::onPressIndexChanged(const QModelIndex &index)
{
  m_PressIndex = index;
  ListVariant variant = qVariantFromValue(index.data(Qt::UserRole)).value<ListVariant>();
  if(variant.mFrequency>0){
      if(mRadioPri->mRadioListFragmentListView != NULL){
          mRadioPri->mRadioListFragmentListView->setCurrentIndex(index);
      }
  }
  //qDebug()<<"RadioListFreqDelegate::onPressIndexChanged mFrequency="<<variant.mFrequency<<endl;
}

void RadioListFreqDelegate::onCurrentIndexChange(const QModelIndex &index)
{
    m_CurIndex = index;
    ListVariant variant = qVariantFromValue(index.data(Qt::UserRole)).value<ListVariant>();
    mRadioPri->mProcess->setFmCurFreq(variant.mFrequency,true,true,false);
}

//----------------------------------

Radio::Radio(QObject *parent):
    Activity(parent),
    d_ptr(new RadioPrivate(this))
{

}

void Radio::onCreate(QWidget *parent)
{
    Q_D(Radio);
    d->initializeBasicWidget(parent);
}
void Radio::onStart()
{
qDebug()<<"Radio::onStart()"<<endl;

}
void Radio::onResume()
{
qDebug()<<"Radio::onResume()"<<endl;
}
void Radio::onPause()
{
  qDebug()<<"Radio::onPause()"<<endl;
  Q_D(Radio);
  if(d->mTab != RadioPrivate::FM)
  {
   d->tabSwitch(RadioPrivate::FM);
  }
}
void Radio::onStop()
{
  qDebug()<<"Radio::onStop()"<<endl;
}
void Radio::onDestroy()
{

}

bool Radio::onBackPressed()
{

    return false;
}

void Radio::onLanguageChanged()
{

}

void Radio::onReceiveBroadcast(AppType appType,OMessage &msg)
{

}

void Radio::onReceiveCmd(AppType appType,OMessage &msg)
{

}
