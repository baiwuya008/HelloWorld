#include "btphonewidget.h"

BtPhoneWidget::BtPhoneWidget(QWidget *parent)
    : QWidget(parent),d_ptr(new BtPhoneWidgetPrivate(this))
{

}

BtPhoneWidget::~BtPhoneWidget()
{

}

BtPhoneWidgetPrivate::BtPhoneWidgetPrivate(BtPhoneWidget *parent)
: q_ptr(parent)
{
     initializeBasicWidget(parent);
}

BtPhoneWidgetPrivate::~BtPhoneWidgetPrivate()
{
    delete q_ptr;
}

void BtPhoneWidgetPrivate::initializeBasicWidget(QWidget *parent)
{

      //三个选项卡
      mBmpDialTab = new BmpButton(parent);
      mBmpDialTab->setText(tr("拨打电话"));
      mBmpDialTab->setGeometry(0,0,136,50);
      mBmpDialTab->setVisible(true);
      initToolbarText(mBmpDialTab);
      mBmpRecordTab= new BmpButton(parent);
      mBmpRecordTab->setText(tr("通话记录"));
      mBmpRecordTab->setVisible(true);
      initToolbarText(mBmpRecordTab);
      mBmpRecordTab->setGeometry(136,0,136,50);
      mBmpOptionsTab= new BmpButton(parent);
      mBmpOptionsTab->setText(tr("选项"));
      initToolbarText(mBmpOptionsTab);
      mBmpOptionsTab->setGeometry(272,0,136,50);
      mBmpOptionsTab->setVisible(true);

      connect(mBmpDialTab,SIGNAL(released()),this,SLOT(onBtnDialTabClick()));
      connect(mBmpRecordTab,SIGNAL(released()),this,SLOT(onBtnRecordTabClick()));
      connect(mBmpOptionsTab,SIGNAL(released()),this,SLOT(onBtnOptionsTabClick()));

      //拨号界面
      mBmpDialWidget = new PhoneDialWidget(parent);
      mBmpDialWidget->setGeometry(0,50,800,480);

      //通话记录tab界面
      mBmpRecordWidget = new PhoneRecordWidget(parent);
      mBmpRecordWidget->setGeometry(0,50,800,480);

      //选项tab界面
      mBmpOptionsWidget = new BmpWidget(parent);
      mBmpOptionsWidget->setBackgroundBmpPath(":/img/Common/img_wap_bg.png");
      mBmpOptionsWidget->setGeometry(0,50,800,480);

      //默认页面第一页
      switchPage(0);
}

void BtPhoneWidgetPrivate::initToolbarText(BmpButton *btn)
{
    //设置字号
    QFont ft("Microsoft YaHei");;
    ft.setPointSize(18);
    btn->setFont(ft);
    //设置颜色
    btn->setStyleSheet("color:white;");
}

//切换页面
void BtPhoneWidgetPrivate::switchPage(int index)
{
    if(index == 0){
        mBmpDialWidget->setVisible(true);
        mBmpRecordWidget->setVisible(false);
        mBmpOptionsWidget->setVisible(false);
        mBmpDialTab->setNormalBmpPath(":/res/blu/img_btn_tab_b.png");
        mBmpRecordTab->setNormalBmpPath(":/res/blu/img_btn_tab_a.png");
        mBmpOptionsTab->setNormalBmpPath(":/res/blu/img_btn_tab_a.png");

    }else if(index == 1){
        mBmpDialWidget->setVisible(false);
        mBmpRecordWidget->setVisible(true);
        mBmpOptionsWidget->setVisible(false);
        mBmpDialTab->setNormalBmpPath(":/res/blu/img_btn_tab_a.png");
        mBmpRecordTab->setNormalBmpPath(":/res/blu/img_btn_tab_b.png");
        mBmpOptionsTab->setNormalBmpPath(":/res/blu/img_btn_tab_a.png");

    }else if(index == 2){
        mBmpDialWidget->setVisible(false);
        mBmpRecordWidget->setVisible(false);
        mBmpOptionsWidget->setVisible(true);
        mBmpDialTab->setNormalBmpPath(":/res/blu/img_btn_tab_a.png");
        mBmpRecordTab->setNormalBmpPath(":/res/blu/img_btn_tab_a.png");
        mBmpOptionsTab->setNormalBmpPath(":/res/blu/img_btn_tab_b.png");
    }
}

//打电话
void BtPhoneWidgetPrivate::onBtnDialTabClick()
{
    switchPage(0);
}

//电话记录
void BtPhoneWidgetPrivate::onBtnRecordTabClick()
{
    switchPage(1);
}
//选项
void BtPhoneWidgetPrivate::onBtnOptionsTabClick()
{
    switchPage(2);
}

