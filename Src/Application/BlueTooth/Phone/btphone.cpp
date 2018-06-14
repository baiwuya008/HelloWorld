#include "btphone.h"
#include <QDebug>
#include <QPixmap>

BtphonePrivate::BtphonePrivate(Btphone *parent)
    : q_ptr(parent)
{
    mBackground = NULL;
    mBtnTest = NULL;
}

void BtphonePrivate::initializeBasicWidget(QWidget *parent)
{
  Q_Q(Btphone);
    //设置标题背景图片
        mPhoneTitle = new BmpWidget(parent);
        mPhoneTitle->setBackgroundBmpPath(QString(":/res/blu/img_btn_tab_bg.png"));
        mPhoneTitle->setFixedSize(QSize(800, 50));
		
		    //mBackground = new BmpWidget(parent); //设置背景图片
    //mBackground->setBackgroundBmpPath(QString(":/Res/drawable/test/bt_phone.png"));
    //mBackground->setFixedSize(QSize(800, 435));

//    mBtnTest= new BmpButton(parent);
//    mBtnTest->setNormalBmpPath(QString(":/Res/drawable/test/btn_n.png"));
//    mBtnTest->setPressBmpPath(QString(":/Res/drawable/test/btn_p.png"));
//    mBtnTest->setGeometry(600,300,195,50);

//   q->connect(mBtnTest,SIGNAL(released()),this,SLOT(onBtnTestRelease()));

        QFont font("Microsoft YaHei");
        font.setPointSize(18);
        //font.setBold(true);

        QFont ft("Microsoft YaHei");
        ft.setPointSize(22);

        //设置字体颜色
        QPalette pa;
        pa.setColor(QPalette::WindowText,Qt::white);
           //三个选项卡
           mBmpDialTab = new BmpButton(parent);
           mBmpDialTab->setText(tr("拨打电话"));
           mBmpDialTab->setGeometry(0,0,136,50);
           mBmpDialTab->setVisible(true);
           mBmpDialTab->setFont(font);
           mBmpRecordTab= new BmpButton(parent);
           mBmpRecordTab->setText(tr("通话记录"));
           mBmpRecordTab->setVisible(true);
           mBmpRecordTab->setGeometry(136,0,136,50);
           mBmpRecordTab->setFont(font);
           mBmpOptionsTab= new BmpButton(parent);
           mBmpOptionsTab->setText(tr("选项"));
           mBmpOptionsTab->setGeometry(272,0,136,50);
           mBmpOptionsTab->setVisible(true);
           mBmpOptionsTab->setFont(font);

           connect(mBmpDialTab,SIGNAL(released()),this,SLOT(onBtnDialTabClick()));
           connect(mBmpRecordTab,SIGNAL(released()),this,SLOT(onBtnRecordTabClick()));
           connect(mBmpOptionsTab,SIGNAL(released()),this,SLOT(onBtnOptionsTabClick()));

           //拨号界面
           mBmpDialWidget = new PhoneDialWidget(parent);
           mBmpDialWidget->setGeometry(0,50,800,480);

           //通话记录tab界面
           //mBmpRecordWidget = new BmpWidget(parent);
           mBmpRecordWidget = new PhoneRecordWidget(parent);
           mBmpRecordWidget->setGeometry(0,50,800,480);

           //选项tab界面
           mBmpOptionsWidget = new BmpWidget(parent);
           mBmpOptionsWidget->setBackgroundBmpPath(":/img/Common/img_wap_bg.png");
           mBmpOptionsWidget->setGeometry(0,50,800,480);

           //默认页面第一页
           switchPage(0);

}

void BtphonePrivate::onBtnTestRelease()
{
  Q_Q(Btphone);
  q->startApplication(T_USBDiskMusic);
}

//----------------------------------

Btphone::Btphone(QObject *parent):
 Activity(parent),
 d_ptr(new BtphonePrivate(this))
{

}

void Btphone::onCreate(QWidget *parent)
{
    Q_D(Btphone);
    d->initializeBasicWidget(parent);
}
void Btphone::onStart()
{

}
void Btphone::onResume()
{

}
void Btphone::onPause()
{

}
void Btphone::onStop()
{

}
void Btphone::onDestroy()
{

}

bool Btphone::onBackPressed()
{

return false;
}

void Btphone::onLanguageChanged()
{

}

void Btphone::onReceiveBroadcast(AppType appType,OMessage &msg)
{

}

void Btphone::onReceiveCmd(AppType appType,OMessage &msg)
{

}

//切换页面
void BtphonePrivate::switchPage(int index)
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
void BtphonePrivate::onBtnDialTabClick()
{
    switchPage(0);
}

//电话记录
void BtphonePrivate::onBtnRecordTabClick()
{
    switchPage(1);
}
//选项
void BtphonePrivate::onBtnOptionsTabClick()
{
    switchPage(2);
}



