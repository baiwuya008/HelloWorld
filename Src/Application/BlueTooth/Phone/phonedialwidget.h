#ifndef PHONEDIALWIDGET_H
#define PHONEDIALWIDGET_H

#include <QWidget>
#include "Src/Framework/Base/Core/activity.h"
#include "Src/Framework/Manager/BluetoothManagerGoc.h"
#include <QTimer>
#include <QTime>
#include <QString>

class PhoneDialWidgetPrivate;
class PhoneDialWidget : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(PhoneDialWidget)
public:
    explicit PhoneDialWidget(QWidget *parent = 0);
    ~PhoneDialWidget();

    //电话状态
    enum PhoneStatus {
        B_Normal = 0,
        B_Dialing = 1,
        B_Calling = 2,
        B_Hangup = 3,
        B_Incoming = 4,
    };

signals:


private:
    Q_DECLARE_PRIVATE(PhoneDialWidget)
    PhoneDialWidgetPrivate* const d_ptr;

};

class PhoneDialWidgetPrivate :public QObject{
    Q_OBJECT
    Q_DISABLE_COPY(PhoneDialWidgetPrivate)

public:
    explicit PhoneDialWidgetPrivate(PhoneDialWidget *parent);
    ~PhoneDialWidgetPrivate();
	
	void initializeBasicWidget(QWidget *parent);
    //当前电话状态
    PhoneDialWidget::PhoneStatus m_PhoneStatus;
    //输入的电话号码，显示在编辑框中
    QString currentPhonenumber;
	
	//显示拨打电话的界面
    void showDialDiaplay(const PhoneDialWidget::PhoneStatus &status);
    void setCurrentPhoneNumber(QString phoneNumber);
    void setWidgetBackground(PhoneDialWidget *parent);

    //初始化蓝牙信号 回调
    void initializeBlutoothManager();

private:
    Q_DECLARE_PUBLIC(PhoneDialWidget)
    PhoneDialWidget* const q_ptr;
	
    //拨号界面组件
    BmpWidget *mBmpkeyboardWidget;
    BmpWidget *mBmpDialDiaplayWidget;
    QLabel *mDialNumber;//显示拨打的号码
    BmpButton *btn_1;
    BmpButton *btn_2;
    BmpButton *btn_3;
    BmpButton *btn_4;
    BmpButton *btn_5;
    BmpButton *btn_6;
    BmpButton *btn_7;
    BmpButton *btn_8;
    BmpButton *btn_9;
    BmpButton *btn_0;
    BmpButton *btn_clear;
    BmpButton *btn_star;
    BmpButton *btn_well;
    BmpButton *btn_backspace;

    BmpWidget *mBmpToolbarWidget;
    BmpButton *btn_dial;
    BmpButton *btn_hungup;
    BmpButton *btn_Swapcalls;


    //通话中的界面
    BmpWidget *mBmpCallingWidget;
    BmpWidget *mCallingTitleWidget;
    QLabel *mCallingTitle;
    BmpWidget *mCallingPhoneNameIcon;
    QLabel *mCallingPhoneName;
    BmpWidget *mCallingPhoneNumberIcon;
    QLabel *mCallingPhoneNumber;
    BmpWidget *mCallingTimeIcon;
    QLabel *mCallingTime;

    //拨号中的界面
    BmpWidget *mDialingWidget;
    QLabel *mDialingPhoneNumber;
    QLabel *mDialingPhoneText;

    //未通话和挂断界面
    BmpWidget *mNormalWidget;

    QTimer *p_Timer;//计时器
    QString showStrTime;//显示通话时间
	
private slots:
	
    void onclick01();
    void onclick02();
    void onclick03();
    void onclick04();
    void onclick05();
    void onclick06();
    void onclick07();
    void onclick08();
    void onclick09();
    void onclick00();
    void onclickstar();
    void onclickclear();
    void onclickwell();
    void onclickbackspace();

    void onBtPhoneDial();//拨号
    void onBtPhoneHungup();//挂断

    //通话时间 计时器
    void updatePhoneTime();

    //拨打电话的信号槽
    void onCallSucceed(QString number);
    void onHangUp();//挂断
    void onIncoming(QString number);//来电
    void onTalking();//来电接听的回调

};

#endif // PHONEDIALWIDGET_H
