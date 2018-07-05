#ifndef PHONEOPTIONSWIDGET_H
#define PHONEOPTIONSWIDGET_H

#include <QWidget>
#include "Src/Framework/Base/Core/activity.h"
#include <QString>
#include <QDialog>
#include "Src/Framework/Manager/BluetoothManagerGoc.h"
#include <QLabel>
#include "phoneoptionwidgetitem.h"
#include <QList>

class PhoneOptionsWidgetPrivate;
class PhoneOptionsWidget : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(PhoneOptionsWidget)
public:
    explicit PhoneOptionsWidget(QWidget *parent = 0);
    ~PhoneOptionsWidget();
signals:

public slots:


private:
    Q_DECLARE_PRIVATE(PhoneOptionsWidget)
    PhoneOptionsWidgetPrivate* const d_ptr;

};


class PhoneOptionsWidgetPrivate :public QObject{
    Q_OBJECT
    Q_DISABLE_COPY(PhoneOptionsWidgetPrivate)

public:
    explicit PhoneOptionsWidgetPrivate(PhoneOptionsWidget *parent);
    ~PhoneOptionsWidgetPrivate();

private:
    Q_DECLARE_PUBLIC(PhoneOptionsWidget)
    PhoneOptionsWidget* const q_ptr;

    void initializeBasicWidget(QWidget *parent);
    void setWidgetBackground(PhoneOptionsWidget *parent);
    void initBtConnectStatus();//初始化蓝牙连接状态
    void initDeletePhoneDialog();//初始化删除对话框
    void initWidgetItemData();//初始化item数据

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

    //系统背景
    BmpWidget *mBmpSystem;

    QLabel *btSwitchLabel;//蓝牙开关label
    BmpButton *btSwitchBtn;//蓝牙开关btn
    QLabel *line01;//分割线

    QLabel *pairTitleName;//配对设备标题
    QLabel *line02;//分割线

    QList<PhoneOptionWidgetItem*> mListPhonePairItem;//电话item 的list

    //删除dialog
    QDialog *mDeleteDialog;

    int onClickWidgetIndex = -1;//哪一个widget被点击 -1 表示没有widget被选中
    QList<QString> mPhonePairListData;//蓝牙配对数据

private slots:

    void deleteBtnOnclick();//删除按键事件
    void operationBtnOnclick();//连接、断开蓝牙事件

    void widgetOnClick(int index);//item被点击

    void onDeleteDialogOkPressed();
    void onDeleteDialogNoPressed();//dialog按钮的点击事件

};


#endif // PHONEOPTIONSWIDGET_H
