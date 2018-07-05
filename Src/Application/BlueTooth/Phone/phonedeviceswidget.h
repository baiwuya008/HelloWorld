#ifndef PHONEDEVICESWIDGET_H
#define PHONEDEVICESWIDGET_H

#include <QWidget>
#include "Src/Framework/Base/Core/activity.h"
#include <QString>
#include <QLabel>

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

signals:
    void onPhoneItemClick();

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


private:
    Q_DECLARE_PUBLIC(PhoneDevicesWidget)
    PhoneDevicesWidget* const q_ptr;

    //tab分页标题
    BmpWidget *mPhoneTitle;
    BmpButton *mBmpPhoneListTab;

    BmpWidget *mBmpListWidget;
    QLabel *deviceName;
    QLabel *deviceID;

    BmpWidget *mBmpListToolBarWidget;
    BmpButton *mBtPhone01;
    BmpButton *mBtPhone02;
    BmpButton *mBtPhone03;
    BmpButton *mBtPhone04;
    BmpButton *mBtPhone05;

private slots:
    void onBtnPhoneItemClick();

};

#endif // PHONEDEVICESWIDGET_H
