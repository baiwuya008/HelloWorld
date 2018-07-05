#include "phoneoptionwidgetitem.h"


#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPalette>
#include <QDebug>
#include "customwidget.h"

class PhoneOptionWidgetItemPrivate {
public:
    explicit PhoneOptionWidgetItemPrivate(PhoneOptionWidgetItem *parent);
    ~PhoneOptionWidgetItemPrivate();
private:
    Q_DECLARE_PUBLIC(PhoneOptionWidgetItem)
    PhoneOptionWidgetItem* const q_ptr;

    void initializeBasicWidget(QWidget *parent);
    void refreshItemView(QString phoneName, bool status);
    void setWidgetBackground(bool isFocus);//设置背景图片
    void setWidgetVisible(bool isVisible);//设置组件是否可见，实现删除效果
    void initTextColor(QLabel *text);
    void initBtnColor(BmpButton *btn);

    inline QPixmap getPixmap(QString path) {
        QImage image;
        image.load(path);
        return QPixmap::fromImage(image);
    }

    inline QPixmap getPixmap(QString path, int width, int height) {
        QImage image;
        image.load(path);
        QImage reulst = image.scaled(QSize(width, height)
                                     , Qt::KeepAspectRatio,Qt::SmoothTransformation);
        return QPixmap::fromImage(reulst);
    }

    QLabel *mPhoneName = NULL;//蓝牙名称
    BmpButton *operationBtn= NULL;//连接、断开蓝牙
    BmpButton *deleteBtn= NULL;//删除
    QLabel *connectStatus = NULL;//连接状态
    QLabel *connectStatusIcon= NULL;//显示图标
    QLabel *line = NULL;//分割线
    CustomWidget *backgroundWidget;//背景颜色图片

    bool isVisibleItem = false ;//item是否显示

};

PhoneOptionWidgetItem::PhoneOptionWidgetItem(QWidget *parent)
    : QWidget(parent)
    , d_ptr(new PhoneOptionWidgetItemPrivate(this))
{

}

PhoneOptionWidgetItemPrivate::PhoneOptionWidgetItemPrivate(PhoneOptionWidgetItem *parent)
    : q_ptr(parent)
{
    initializeBasicWidget(parent);
}

void PhoneOptionWidgetItemPrivate::initializeBasicWidget(QWidget *parent) {

    //设置字号
    QFont ft("Microsoft YaHei");
    ft.setPointSize(12);

    backgroundWidget = new CustomWidget(parent);
    backgroundWidget->setGeometry(74,0,600,46);
    backgroundWidget->setEnabled(true);

    mPhoneName = new QLabel(backgroundWidget);
    mPhoneName->setFont(ft);
    initTextColor(mPhoneName);
    mPhoneName->setGeometry(75,9,200,28);

    connectStatus = new QLabel(backgroundWidget);
    connectStatus->setFont(ft);
    initTextColor(connectStatus);
    connectStatus->setAlignment(Qt::AlignCenter);
    connectStatus->setGeometry(480,9,60,28);

    connectStatusIcon = new QLabel(backgroundWidget);
    connectStatusIcon->setPixmap(getPixmap(":/res/blu/phonestatus_icon.png"));
    connectStatusIcon->setGeometry(545, 14, 19, 19);

    operationBtn = new BmpButton(backgroundWidget);
    operationBtn->setNormalBmpPath(":/res/blu/opration_bt_normal.png");
    operationBtn->setPressBmpPath(":/res/blu/opration_bt_normal.png");
    operationBtn->setVisible(false);
    operationBtn->setFont(ft);
    initBtnColor(operationBtn);
    operationBtn->setText("连接");
    operationBtn->setGeometry(416,0,74,44);

    deleteBtn = new BmpButton(backgroundWidget);
    deleteBtn->setNormalBmpPath(":/res/blu/delete_phonedevices_normal.png");
    deleteBtn->setPressBmpPath(":/res/blu/delete_phonedevices_onclick.png");
    deleteBtn->setVisible(false);
    deleteBtn->setFont(ft);
    initBtnColor(deleteBtn);
    deleteBtn->setText("删除");
    deleteBtn->setGeometry(490,0,74,44);

    line = new QLabel(backgroundWidget);
    line->setPixmap(getPixmap(":/res/blu/phone_itemlin.png"));
    line->setGeometry(5, 44, 639, 2);

    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(operationBtn, SIGNAL(released()), parent, SLOT(operationBtnOnClickSlots()), type);
    QObject::connect(deleteBtn, SIGNAL(released()), parent, SLOT(deleteBtnOnclickSlots()), type);

    setWidgetBackground(false);
}

//设置item数据
void PhoneOptionWidgetItem::setItemInfo(QString phoneName, bool status) {
    Q_D(PhoneOptionWidgetItem);
    d->refreshItemView(phoneName, status);
}

void PhoneOptionWidgetItemPrivate::refreshItemView(QString phoneName, bool status) {
    mPhoneName->setText(phoneName);
    if(status){
     //已连接状态
        connectStatus->setText(QObject::tr("已连接"));
    }else{
     //未连接状态
        connectStatus->setText(QObject::tr("未连接"));
    }
}

//刷新背景图片
void PhoneOptionWidgetItem::refreshItemBgImage(bool isFocus)
{
    Q_D(PhoneOptionWidgetItem);
    d->setWidgetBackground(isFocus);
}

//设置组件不可见，实现删除效果
void PhoneOptionWidgetItem::refreshItemVisible(bool isVisible)
{
    Q_D(PhoneOptionWidgetItem);
    d->setWidgetVisible(isVisible);
}

void PhoneOptionWidgetItem::setWidgetIndex(int index)
{
    currentIndex = index;
}

int PhoneOptionWidgetItem::getWidgetIndex()
{
    return currentIndex;
}

void PhoneOptionWidgetItem::mousePressEvent(QMouseEvent *)
{
    emit widgetOnClick(currentIndex);

}

void PhoneOptionWidgetItem::mouseReleaseEvent(QMouseEvent *)
{

}

void PhoneOptionWidgetItemPrivate::initTextColor(QLabel *text)
{
     text->setStyleSheet("color:#D3D3D3;");
}

void PhoneOptionWidgetItemPrivate::initBtnColor(BmpButton *btn)
{
     btn->setStyleSheet("color:white;");
}

void PhoneOptionWidgetItemPrivate::setWidgetBackground(bool isFocus) {
    //设置背景图片
   if(isFocus){
       backgroundWidget->setBackgroundBmpPath(":/res/blu/phone_item_bg.png");
       connectStatus->setVisible(false);
       connectStatusIcon->setVisible(false);
       operationBtn->setVisible(true);
       deleteBtn->setVisible(true);
   }else if(isVisibleItem){
       backgroundWidget->setBackgroundBmpPath(":/res/blu/phone_item_bg_normal.png");
       operationBtn->setVisible(false);
       deleteBtn->setVisible(false);
       connectStatus->setVisible(true);
       connectStatusIcon->setVisible(true);
   }
}

void PhoneOptionWidgetItemPrivate::setWidgetVisible(bool isVisible) {
    //设置item是否可见
   isVisibleItem = isVisible;
   if(isVisible){
       backgroundWidget->setBackgroundBmpPath(":/res/blu/phone_item_bg_normal.png");
       mPhoneName->setVisible(true);
       connectStatus->setVisible(true);
       connectStatusIcon->setVisible(true);
       operationBtn->setVisible(false);
       deleteBtn->setVisible(false);
   }else{
       backgroundWidget->setBackgroundBmpPath(":/res/blu/phone_item_bg_normal.png");
       mPhoneName->setVisible(false);
       operationBtn->setVisible(false);
       deleteBtn->setVisible(false);
       connectStatus->setVisible(false);
       connectStatusIcon->setVisible(false);
   }
}




//删除按钮被点击
void PhoneOptionWidgetItem::deleteBtnOnclickSlots()
{
   emit deleteBtnOnclick();
}

//连接/断开 蓝牙键被点击
void PhoneOptionWidgetItem::operationBtnOnClickSlots()
{
    qDebug() << "operationBtnOnClickSlots" << endl;
    emit operationBtnOnClick();
}

PhoneOptionWidgetItem::~PhoneOptionWidgetItem() {

}

PhoneOptionWidgetItemPrivate::~PhoneOptionWidgetItemPrivate() {

}

