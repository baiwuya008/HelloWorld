#include "radio.h"

RadioPrivate::RadioPrivate(Radio *parent)
    : QObject(),q_ptr(parent)
{
    mBackground = NULL;
    mBtnTest = NULL;
}

void RadioPrivate::initializeBasicWidget(QWidget *parent)
{
  Q_Q(Radio);

//    mBackground = new BmpWidget(parent); //设置背景图片
//    mBackground->setBackgroundBmpPath(QString(":/Res/drawable/test/radio_fm.png"));
//    mBackground->setFixedSize(QSize(800, 435));

//    mBtnTest= new BmpButton(parent);
//    mBtnTest->setNormalBmpPath(QString(":/Res/drawable/test/btn_n.png"));
//    mBtnTest->setPressBmpPath(QString(":/Res/drawable/test/btn_p.png"));
//    mBtnTest->setGeometry(600,300,195,50);

//   q->connect(mBtnTest,SIGNAL(released()),this,SLOT(onBtnTestRelease()));

    mTabBar = new BmpWidget(parent);
    mTabBar->setBackgroundBmpPath(QString(":/res/drawable/app_statebar.png"));
    mTabBar->setFixedSize(QSize(800, 50));

    mStateBarTab_FM= new BmpButton(mTabBar);
    mStateBarTab_FM->setNormalBmpPath(QString(":/res/drawable/app_statebar_btn.png"));
    mStateBarTab_FM->setPressBmpPath(QString(":/res/drawable/app_statebar_btn_pressed.png"));
    mStateBarTab_FM->setGeometry(0,0,140,50);
    mTabFmTextView=new TextWidget(mStateBarTab_FM);
    mTabFmTextView->setLanguageType(TextWidget::Type::T_NoTranslate);
    mTabFmTextView->setText(QString("FM"));
    mTabFmTextView->setFontPointSize(14);
    mTabFmTextView->setStyleSheet("TextWidget{font-color:red}");
    mTabFmTextView->move((mStateBarTab_FM->width()-mTabFmTextView->width())/2,(mStateBarTab_FM->height()-mTabFmTextView->height())/2);

    mStateBarTab_Preset= new BmpButton(mTabBar);
    mStateBarTab_Preset->setNormalBmpPath(QString(":/res/drawable/app_statebar_btn.png"));
    mStateBarTab_Preset->setPressBmpPath(QString(":/res/drawable/app_statebar_btn_pressed.png"));
    mStateBarTab_Preset->setGeometry(140,0,140,50);
    mTabPresetTextView=new TextWidget(mStateBarTab_Preset);
    mTabPresetTextView->setText(QObject::tr("预置电台"));
    mTabPresetTextView->setFontPointSize(14);
    mTabFmTextView->setStyleSheet("TextWidget{font-color:white}");
    mTabPresetTextView->move((mStateBarTab_Preset->width()-mTabPresetTextView->width())/2,(mStateBarTab_Preset->height()-mTabPresetTextView->height())/2);

    mStateBarTab_List= new BmpButton(mTabBar);
    mStateBarTab_List->setNormalBmpPath(QString(":/res/drawable/app_statebar_btn.png"));
    mStateBarTab_List->setPressBmpPath(QString(":/res/drawable/app_statebar_btn_pressed.png"));
    mStateBarTab_List->setGeometry(280,0,140,50);
    mTabListTextView=new TextWidget(mStateBarTab_List);
    mTabPresetTextView->setText(QObject::tr("列表"));
    mTabPresetTextView->setFontPointSize(14);
    mTabFmTextView->setStyleSheet("TextWidget{font-color:blue}");
    mTabPresetTextView->move((mStateBarTab_List->width()-mTabPresetTextView->width())/2,(mStateBarTab_List->height()-mTabPresetTextView->height())/2);



    mFragmentViewLayout = new QStackedLayout();


    QStackedLayout *mFragmentViewLayout;
    QWidget *mFmFragmentView;
    QWidget *mPresetFragmentView;
    QWidget *mListFragmentView;

    QStackedLayout *mBottomBarLayout;
    BmpWidget *mBottomBar;
    QWidget *mBottom_Fm;
    QWidget *mBottom_Preset;
    QWidget *mBottom_List;




}

void RadioPrivate::onBtnTestRelease()
{
  Q_Q(Radio);
  q->startApplication(T_Setting);
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

}
void Radio::onResume()
{

}
void Radio::onPause()
{

}
void Radio::onStop()
{

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


