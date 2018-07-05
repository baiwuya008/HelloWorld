#include "phonedeviceswidget.h"
#include <QDebug>
#include <QPixmap>
#include <QPalette>
#include <QSize>
#include <QFont>


PhoneDevicesWidgetPrivate::PhoneDevicesWidgetPrivate(PhoneDevicesWidget *parent)
    : q_ptr(parent)
{
    initializeBasicWidget(parent);
    //setWidgetBackground(parent);
    //initBluetoothConnect();
    //initBluetoothData();
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

        mBmpPhoneOptionTab = new BmpButton(parent);
        mBmpPhoneOptionTab->setText(tr("选项"));
        mBmpPhoneOptionTab->setGeometry(136,0,136,50);
        mBmpPhoneOptionTab->setVisible(true);
        initToolbarText(mBmpPhoneOptionTab);

        mBmpBtInfoWidget = new BmpWidget(parent);
        mBmpBtInfoWidget->setGeometry(0,50,800,360);

        deviceName = new QLabel(mBmpBtInfoWidget);
        deviceName->setGeometry(0,80,800,100);
        deviceName->setText("设备名: MIGHY-5ECA");
        deviceName->setAlignment(Qt::AlignCenter);
        deviceName->setPalette(pa);
        deviceName->setFont(ft);

        deviceID = new QLabel(mBmpBtInfoWidget);
        deviceID->setGeometry(0,130,800,100);
        deviceID->setText("设备ID: 00:14:OA:04:5E:CA");
        deviceID->setAlignment(Qt::AlignCenter);
        deviceID->setPalette(pa);
        deviceID->setFont(ft);

        mPhoneOptionsWidget = new PhoneOptionsWidget(parent);
        mPhoneOptionsWidget->setGeometry(0,50,800,360);

        connect(mBmpPhoneListTab,SIGNAL(released()),this,SLOT(onBtnBtInfoTabClick()));
        connect(mBmpPhoneOptionTab,SIGNAL(released()),this,SLOT(onBtnOptionTabClick()));

        switchPage(0);

}

PhoneDevicesWidget::PhoneDevicesWidget(QWidget *parent):
 QWidget(parent),
 d_ptr(new PhoneDevicesWidgetPrivate(this))
{
    //setFixedSize(QSize(800, 386));
}

//切换页面
void PhoneDevicesWidgetPrivate::switchPage(int index)
{
    if(index == 0){
        mBmpBtInfoWidget->setVisible(true);
        mPhoneOptionsWidget->setVisible(false);
        mBmpPhoneListTab->setNormalBmpPath(":/res/blu/img_btn_tab_b.png");
        mBmpPhoneOptionTab->setNormalBmpPath(":/res/blu/img_btn_tab_a.png");

    }else if(index == 1){
        mBmpBtInfoWidget->setVisible(false);
        mPhoneOptionsWidget->setVisible(true);
        mBmpPhoneListTab->setNormalBmpPath(":/res/blu/img_btn_tab_a.png");
        mBmpPhoneOptionTab->setNormalBmpPath(":/res/blu/img_btn_tab_b.png");

    }
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

void PhoneDevicesWidgetPrivate::initBluetoothData()
{
    //获取蓝牙名称和蓝牙地址
    gBluetoothManager->getLocalName();
    gBluetoothManager->getLocalAddress();
}

void PhoneDevicesWidgetPrivate::initBluetoothConnect()
{
    //获取本地蓝牙名称
    connect(gBluetoothManager,SIGNAL(callOnCurrentName(QString)),this,SLOT(onLocalName(QString)));
    //获取本地蓝牙地址
    //这里有两个回调，需要测试取其一
    //connect(gBluetoothManager,SIGNAL(callOnCurrentAddr(QString)),this,SLOT(onLocalAddress(QString)));
    connect(gBluetoothManager,SIGNAL(callOnLocalAddress(QString)),this,SLOT(onLocalAddress(QString)));
}

void PhoneDevicesWidgetPrivate::onBtnBtInfoTabClick()
{
    switchPage(0);
}

void PhoneDevicesWidgetPrivate::onBtnOptionTabClick()
{
    switchPage(1);
}

void PhoneDevicesWidgetPrivate::onLocalName(QString name)
{
    QString displayName = tr("设备名") + ": " + name ;
    deviceName->setText(displayName);
}

void PhoneDevicesWidgetPrivate::onLocalAddress(QString addr)
{
    QString displayAddr = tr("设备ID")+ ": " + addr ;
    deviceName->setText(displayAddr);
}

PhoneDevicesWidget::~PhoneDevicesWidget()
{

}
