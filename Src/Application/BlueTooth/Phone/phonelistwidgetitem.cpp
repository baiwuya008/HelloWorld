#include "phonelistwidgetitem.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPalette>
#include <QDebug>
#include "customwidget.h"

class phoneListwidgetItemPrivate {
public:
    explicit phoneListwidgetItemPrivate(phoneListwidgetItem *parent);
    ~phoneListwidgetItemPrivate();
private:
    Q_DECLARE_PUBLIC(phoneListwidgetItem)
    phoneListwidgetItem* const q_ptr;
    void initializeBasicWidget(QWidget *parent);
    void initLabText(QLabel *text);
    void refreshItemView(QString iconPath, QString dialRecord);
    void refreshItemTextColor(bool isFocus);
    void setWidgetBackground(bool isFocus);


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

    int mWidth = 0;
    int mHeight = 0;
    //标识当前Item在ListWidget的下标
    int itemPosition = 0;

    //QVBoxLayout *mainLayout = NULL;
    //QHBoxLayout *infoLayout = NULL;
    QLabel *icon = NULL;
    QLabel *name = NULL;
    BmpButton *deleteBtn= NULL;
    QLabel *line = NULL;
    CustomWidget *backgroundWidget;//背景颜色图片

};

phoneListwidgetItem::phoneListwidgetItem(QWidget *parent)
    : QWidget(parent)
    , d_ptr(new phoneListwidgetItemPrivate(this))
{

}

phoneListwidgetItemPrivate::phoneListwidgetItemPrivate(phoneListwidgetItem *parent)
    : q_ptr(parent)
{
    initializeBasicWidget(parent);
}

void phoneListwidgetItem::setItemInfo(QString iconPath, QString dialRecord) {
    Q_D(phoneListwidgetItem);
    d->refreshItemView(iconPath, dialRecord);
}

void phoneListwidgetItemPrivate::refreshItemView(QString iconPath, QString dialRecord) {
    icon->setPixmap(getPixmap(iconPath));
    name->setText(dialRecord);
    refreshItemTextColor(false);
}

void phoneListwidgetItem::refreshItemBgImage(bool isFocus)
{
    Q_D(phoneListwidgetItem);
    d->setWidgetBackground(isFocus);
    d->refreshItemTextColor(isFocus);
}

void phoneListwidgetItemPrivate::refreshItemTextColor(bool isFocus)
{
    if (isFocus) {
           name->setStyleSheet("color:#87CEFA;");
       }else {
           name->setStyleSheet("color:white;");
       }
}

void phoneListwidgetItemPrivate::initializeBasicWidget(QWidget *parent) {
    backgroundWidget = new CustomWidget(parent);
    backgroundWidget->setGeometry(75,0,600,45);
    setWidgetBackground(false);

    icon = new QLabel(backgroundWidget);
    icon->setGeometry(71,13,18,18);
    name = new QLabel(backgroundWidget);
    initLabText(name);
    name->setGeometry(115,8,200,28);
    deleteBtn = new BmpButton(backgroundWidget);
    deleteBtn->setNormalBmpPath(":/res/blu/delete_normal.png");
    deleteBtn->setPressBmpPath(":/res/blu/delete_press.png");
    deleteBtn->setGeometry(455,8,23,29);

    line = new QLabel(backgroundWidget);
    line->setPixmap(getPixmap(":/res/blu/phone_itemlin.png"));
    line->setGeometry(5, 43, 639, 2);

    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(deleteBtn, SIGNAL(released()), parent, SLOT(deleteBtnOnclickSlots()), type);

}

void phoneListwidgetItemPrivate::setWidgetBackground(bool isFocus) {
    //设置背景图片
   if(isFocus){
       backgroundWidget->setBackgroundBmpPath(":/res/blu/phone_item_bg.png");
   }else{
       backgroundWidget->setBackgroundBmpPath(":/res/blu/phone_item_bg_normal.png");
   }
}

void phoneListwidgetItemPrivate::initLabText(QLabel *text) {
    //设置字号
    QFont ft("Microsoft YaHei");
    ft.setPointSize(16);
    text->setFont(ft);
    //设置颜色
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);
    text->setPalette(pa);
}


void phoneListwidgetItem::resizeEvent(QResizeEvent *event) {
    Q_D(phoneListwidgetItem);
    d->mWidth = event->size().width();
    d->mHeight = event->size().height();
}

//删除按钮被点击
phoneListwidgetItem::deleteBtnOnclickSlots()
{
   qDebug() << "deleteBtnOnclickSlots" << endl;
   emit deleteBtnOnclick();
}

phoneListwidgetItem::~phoneListwidgetItem() {

}

phoneListwidgetItemPrivate::~phoneListwidgetItemPrivate() {

}
