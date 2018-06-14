#ifndef PHONELISTWIDGETITEM_H
#define PHONELISTWIDGETITEM_H

#include <QObject>
#include <QWidget>
#include <QResizeEvent>
#include "Src/Framework/Base/Core/activity.h"

class phoneListwidgetItemPrivate;
class phoneListwidgetItem : public QWidget
{
    Q_OBJECT
public:
    explicit phoneListwidgetItem(QWidget *parent = nullptr);
    ~phoneListwidgetItem();

    //设置Item数据
    void setItemInfo(QString iconPath, QString dialRecord);
    void refreshItemBgImage(bool isFocus);//刷新背景图片

protected:
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

signals:
    deleteBtnOnclick();//删除键被点击

public slots:
    deleteBtnOnclickSlots();//删除键被点击槽函数

private:
    Q_DECLARE_PRIVATE(phoneListwidgetItem)
    phoneListwidgetItemPrivate* const d_ptr;
};

#endif // PHONELISTWIDGETITEM_H
