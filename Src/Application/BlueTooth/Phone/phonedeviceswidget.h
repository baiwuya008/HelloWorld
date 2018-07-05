#ifndef PHONEDEVICESWIDGET_H
#define PHONEDEVICESWIDGET_H

#include <QWidget>
#include "Src/Framework/Base/Core/activity.h"
#include "Src/Framework/Manager/BluetoothManagerGoc.h"
#include <QString>
#include <QLabel>
#include "phoneoptionswidget.h"

class PhoneDevicesWidgetPrivate;
class PhoneDevicesWidget : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(PhoneDevicesWidget)

public:
    explicit PhoneDevicesWidget(QWidget *parent = 0);
    ~PhoneDevicesWidget();

private:
    Q_DECLARE_PRIVATE(PhoneDevicesWidget)
    PhoneDevicesWidgetPrivate* const d_ptr;

};

class PhoneDevicesWidgetPrivate :public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(PhoneDevicesWidgetPrivate)

public:
    explicit PhoneDevicesWidgetPrivate(PhoneDevicesWidget* parent);
    ~PhoneDevicesWidgetPrivate(){delete q_ptr;}
    void initializeBasicWidget(QWidget *parent);
    void setWidgetBackground(QWidget *parent);
    void initToolbarText(BmpButton *bt);
    void initBluetoothData();//初始化蓝牙数据
    void initBluetoothConnect();//设置蓝牙信号connect，

    void switchPage(int index);

private:
    Q_DECLARE_PUBLIC(PhoneDevicesWidget)
    PhoneDevicesWidget* const q_ptr;

    //tab分页标题
    BmpWidget *mPhoneTitle;
    BmpButton *mBmpPhoneListTab;
    BmpButton *mBmpPhoneOptionTab;

    PhoneOptionsWidget *mPhoneOptionsWidget;//选项布局

    BmpWidget *mBmpBtInfoWidget;
    QLabel *deviceName;
    QLabel *deviceID;



private slots:

    void onBtnBtInfoTabClick();//切换tab
    void onBtnOptionTabClick();//切换tab

    void onLocalName(QString name);
    void onLocalAddress(QString addr);

};

#endif // PHONEDEVICESWIDGET_H
