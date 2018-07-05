#include "phonedeviceswidget.h"
#include <QDebug>
#include <QPixmap>
#include <QPalette>


PhoneDevicesWidgetPrivate::PhoneDevicesWidgetPrivate(PhoneDevicesWidget *parent)
    : q_ptr(parent)
{
    initializeBasicWidget(parent);
    setWidgetBackground(parent);
}

void PhoneDevicesWidgetPrivate::initializeBasicWidget(QWidget *parent)
{
        //设置标题背景图片
        mPhoneTitle = new BmpWidget(parent);
        mPhoneTitle->setBackgroundBmpPath(QString(":/res/blu/img_btn_tab_bg.png"));
        mPhoneTitle->setFixedSize(QSize(800, 50));

        //设置颜色
        QPalette pa;
        pa.setColor(QPalette::WindowText,Qt::white);

        QFont ft("Microsoft YaHei");;
        ft.setPointSize(18);

        //选项卡
        mBmpPhoneListTab = new BmpButton(parent);
        mBmpPhoneListTab->setText(tr("电话"));
        mBmpPhoneListTab->setGeometry(0,0,136,50);
        mBmpPhoneListTab->setVisible(true);
        initToolbarText(mBmpPhoneListTab);
        mBmpPhoneListTab->setNormalBmpPath(":/res/blu/img_btn_tab_b.png");

        mBmpListWidget = new BmpWidget(parent);
        mBmpListWidget->setGeometry(0,50,800,320);

        deviceName = new QLabel(mBmpListWidget);
        deviceName->setGeometry(0,80,800,100);
        deviceName->setText("设备名：MIGHY-5ECA");
        deviceName->setAlignment(Qt::AlignCenter);
        deviceName->setPalette(pa);
        deviceName->setFont(ft);

        deviceID = new QLabel(mBmpListWidget);
        deviceID->setGeometry(0,130,800,100);
        deviceID->setText("设备ID：00:14:OA:04:5E:CA");
        deviceID->setAlignment(Qt::AlignCenter);
        deviceID->setPalette(pa);
        deviceID->setFont(ft);

        mBmpListToolBarWidget = new BmpWidget(parent);
        mBmpListToolBarWidget->setGeometry(0,376,800,60);
        mBmpListToolBarWidget->setBackgroundBmpPath(":/res/blu/phone_toolbar_bg.png");

        mBtPhone01 = new BmpButton(mBmpListToolBarWidget);
        mBtPhone01->setText(tr("华为 Pro"));
        initToolbarText(mBtPhone01);
        mBtPhone01->setNormalBmpPath(":/res/blu/phone_toolbar_normal.png");
        mBtPhone01->setPressBmpPath(":/res/blu/phone_toolbar_press.png");
        mBtPhone01->setGeometry(0,0,159,60);
        connect(mBtPhone01,SIGNAL(released()),this,SLOT(onBtnPhoneItemClick()));

        mBtPhone02 = new BmpButton(mBmpListToolBarWidget);
        initToolbarText(mBtPhone02);
        mBtPhone02->setEnabled(false);
        mBtPhone02->setNormalBmpPath(":/res/blu/phone_toolbar_normal.png");
        mBtPhone02->setPressBmpPath(":/res/blu/phone_toolbar_press.png");
        mBtPhone02->setGeometry(161,0,159,60);
        connect(mBtPhone02,SIGNAL(released()),this,SLOT(onBtnPhoneItemClick()));

        mBtPhone03 = new BmpButton(mBmpListToolBarWidget);
        initToolbarText(mBtPhone03);
        mBtPhone03->setEnabled(false);
        mBtPhone03->setNormalBmpPath(":/res/blu/phone_toolbar_normal.png");
        mBtPhone03->setPressBmpPath(":/res/blu/phone_toolbar_press.png");
        mBtPhone03->setGeometry(323,0,159,60);
        connect(mBtPhone03,SIGNAL(released()),this,SLOT(onBtnPhoneItemClick()));

        mBtPhone04 = new BmpButton(mBmpListToolBarWidget);
        initToolbarText(mBtPhone04);
        mBtPhone04->setEnabled(false);
        mBtPhone04->setNormalBmpPath(":/res/blu/phone_toolbar_normal.png");
        mBtPhone04->setPressBmpPath(":/res/blu/phone_toolbar_press.png");
        mBtPhone04->setGeometry(484,0,159,60);
        connect(mBtPhone04,SIGNAL(released()),this,SLOT(onBtnPhoneItemClick()));

        mBtPhone05 = new BmpButton(mBmpListToolBarWidget);
        mBtPhone05->setNormalBmpPath(":/res/blu/nextphonepage_normal.png");
        mBtPhone05->setPressBmpPath(":/res/blu/nextphonepage_press.png");
        mBtPhone05->setGeometry(645,0,159,60);
        mBtPhone05->setEnabled(false);
        initToolbarText(mBtPhone05);
        connect(mBtPhone05,SIGNAL(released()),this,SLOT(onBtnPhoneItemClick()));


}

PhoneDevicesWidget::PhoneDevicesWidget(QWidget *parent):
 QWidget(parent),
 d_ptr(new PhoneDevicesWidgetPrivate(this))
{
    //setFixedSize(QSize(800, 386));
}

void PhoneDevicesWidgetPrivate::setWidgetBackground(QWidget *parent){
    //设置背景图片
    parent->setAutoFillBackground(true); // 这句要加上, 否则可能显示不出背景图.
    QPalette palette = parent->palette();
    palette.setBrush(QPalette::Window,
            QBrush(QPixmap(":/img/Common/img_wap_bg.png").scaled(// 缩放背景图.
                parent->size(),
                Qt::IgnoreAspectRatio,
                Qt::SmoothTransformation)));             // 使用平滑的缩放方式
    parent->setPalette(palette);                           // 给widget加上背景图

}

void PhoneDevicesWidgetPrivate::initToolbarText(BmpButton *bt) {
    //设置字号
    QFont ft("Microsoft YaHei");;
    ft.setPointSize(18);
    bt->setFont(ft);
    //设置颜色
    bt->setStyleSheet("color:white;");
}

//item被点击
void PhoneDevicesWidgetPrivate::onBtnPhoneItemClick()
{
    Q_Q(PhoneDevicesWidget);
    emit q->onPhoneItemClick();
}

PhoneDevicesWidget::~PhoneDevicesWidget()
{

}
