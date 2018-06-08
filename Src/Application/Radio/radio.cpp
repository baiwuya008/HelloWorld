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

    mBackground = new BmpWidget(parent); //设置背景图片
    mBackground->setBackgroundBmpPath(QString(":/img/Common/img_wap_bg.png"));
    mBackground->setFixedSize(QSize(800, 435));

    //    mBtnTest= new BmpButton(parent);
    //    mBtnTest->setNormalBmpPath(QString(":/Res/drawable/test/btn_n.png"));
    //    mBtnTest->setPressBmpPath(QString(":/Res/drawable/test/btn_p.png"));
    //    mBtnTest->setGeometry(600,300,195,50);

    //   q->connect(mBtnTest,SIGNAL(released()),this,SLOT(onBtnTestRelease()));

    mStackedWidget = new QStackedWidget(parent);
    mStackedWidget->setFixedSize(QSize(800, 435));
    mStackedWidget->setGeometry(0, 50, 0, 0);

    mBmpFM = new BmpWidget(parent);
    mBmpDef= new BmpWidget(parent);
    mBmpFMList= new BmpWidget(parent);

    mStackedWidget->insertWidget(0,mBmpFM);
    mStackedWidget->insertWidget(1,mBmpDef);
    mStackedWidget->insertWidget(2,mBmpFMList);

    //初始化标题
    QList<QString> list;
    list.append(tr("FM"));
    list.append(tr("预设电台"));
    list.append(tr("列表"));
    mMediaToolsWidget = new MediaToolsWidget(parent, list);
    connect(mMediaToolsWidget, SIGNAL(onItemClick(int)), this, SLOT(setCurrentPageView(int)));

    QFont font("Microsoft YaHei");
    font.setPointSize(18);

    //文字
    BmpButton * mLabelFmText = new BmpButton(mBmpFM);
    mLabelFmText->setText(tr("98.5"));
    mLabelFmText->setFont(font);
    mLabelFmText->setGeometry(350,20,100,80);
    mLabelFmText->setNormalBmpPath(":/img/Radio/img_fm_text_bg.png");
    mLabelFmText->setPressBmpPath(":/img/Radio/img_fm_text_bg.png");

    BmpWidget * mKmpWidget = new BmpWidget(mBmpFM);
    mKmpWidget->setGeometry(150,150,500,80);
    mKmpWidget->setBackgroundBmpPath(":/img/Radio/img_fm_k_bg.png");

    //红线
    //BmpButton * mKLine = new BmpButton(mBmpFM);
    //mKLine->setGeometry(400,150,10,80);
    //mKLine->setNormalBmpPath(":/img/Radio/img_fm_k_red_line.png.png");
    //mKLine->setPressBmpPath(":/img/Radio/img_fm_k_red_line.png.png");


    //BmpWidget * mBottomListLayoutBg = new BmpWidget(mBmpFM);
    //mBottomListLayoutBg->setGeometry(0,320,800,60);

    BmpWidget * mBottomListLayout = new BmpWidget(mBmpFM);
    mBottomListLayout->setGeometry(0,325,800,60);
    mBottomListLayout->setBackgroundBmpPath(":/img/Radio/img_k_bg.png");

    //<<
    BmpButton *leftTwo = new BmpButton(mBottomListLayout);
    leftTwo->setFixedSize(QSize(200, 60));
    leftTwo->setNormalBmpPath(":/img/Radio/img_left_two_a.png");
    leftTwo->setPressBmpPath(":/img/Radio/img_left_two_b.png");
    leftTwo->setGeometry(-2, 0, 0, 0);

    //<
    BmpButton * leftOne = new BmpButton(mBottomListLayout);
    leftOne->setFixedSize(QSize(200, 60));
    leftOne->setNormalBmpPath(":/img/Radio/img_left_one_a.png");
    leftOne->setPressBmpPath(":/img/Radio/img_left_one_b.png");
    leftOne->setGeometry(199, 0, 0, 0);

    //>
    BmpButton *rightOne = new BmpButton(mBottomListLayout);
    rightOne->setFixedSize(QSize(200, 60));
    rightOne->setNormalBmpPath(":/img/Radio/img_right_one_a.png");
    rightOne->setPressBmpPath(":/img/Radio/img_right_one_b.png");
    rightOne->setGeometry(399, 0, 0, 0);

    //>>
    BmpButton *rightTwo = new BmpButton(mBottomListLayout);
    rightTwo->setFixedSize(QSize(200, 60));
    rightTwo->setNormalBmpPath(":/img/Radio/img_right_two_a.png");
    rightTwo->setPressBmpPath(":/img/Radio/img_right_two_b.png");
    rightTwo->setGeometry(601, 0, 0, 0);
}

void RadioPrivate::onBtnTestRelease()
{
    Q_Q(Radio);
    q->startApplication(T_Setting);
}

void RadioPrivate::setCurrentPageView(int values)
{
    mStackedWidget->setCurrentIndex(values);
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


