#ifndef PHONEOPTIONWIDGETITEM_H
#define PHONEOPTIONWIDGETITEM_H

#include <QObject>
#include <QWidget>
#include <QResizeEvent>
#include "Src/Framework/Base/Core/activity.h"
#include <QMouseEvent>
#include <QString>
#include <QDebug>

class PhoneOptionWidgetItemPrivate;
class PhoneOptionWidgetItem : public QWidget
{
    Q_OBJECT
public:
    explicit PhoneOptionWidgetItem(QWidget *parent = 0);
    ~PhoneOptionWidgetItem();

    //设置Item数据
    void setItemInfo(QString phoneName, bool status);
    void refreshItemBgImage(bool isFocus);//刷新背景图片
    void refreshItemVisible(bool isVisible);//设置组件是否可见，实现删除效果
    void setWidgetIndex(int index);
    int getWidgetIndex();

protected:
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);

signals:
    void deleteBtnOnclick();//删除键被点击
    void operationBtnOnClick();//连接/断开 蓝牙键被点击
    void widgetOnClick(int index);//widget 被点击

public slots:
    void deleteBtnOnclickSlots();//删除键被点击槽函数
    void operationBtnOnClickSlots();//删除键被点击槽函数

private:
    Q_DECLARE_PRIVATE(PhoneOptionWidgetItem)
    PhoneOptionWidgetItemPrivate* const d_ptr;

    int currentIndex = -1;//表示当前的item位置
};

#endif // PHONEOPTIONWIDGETITEM_H
