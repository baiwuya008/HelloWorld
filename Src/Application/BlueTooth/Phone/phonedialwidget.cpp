#include "phonedialwidget.h"
#include <QDebug>
#include <QPixmap>

PhoneDialWidgetPrivate::PhoneDialWidgetPrivate(PhoneDialWidget *parent)
    : q_ptr(parent)
{
    m_PhoneStatus = PhoneDialWidget::B_Normal ;
    p_Timer = new QTimer;
    connect(this->p_Timer,SIGNAL(timeout()),this,SLOT(updatePhoneTime()));

    initializeBasicWidget(parent);
    initializeBlutoothManager();//初始化蓝牙信号 回调
}

void PhoneDialWidgetPrivate::initializeBasicWidget(QWidget *parent)
{
        //Q_Q(PhoneDialWidget);
        QFont font("Microsoft YaHei");
        font.setPointSize(18);
        //font.setBold(true);

        QFont ft("Microsoft YaHei");
        ft.setPointSize(22);

        //设置字体颜色
        QPalette pa;
        pa.setColor(QPalette::WindowText,Qt::white);

           mBmpkeyboardWidget = new BmpWidget(parent);
           mBmpkeyboardWidget->setGeometry(0,0,406,316);

           mBmpDialDiaplayWidget = new BmpWidget(mBmpkeyboardWidget);
           mBmpDialDiaplayWidget->setBackgroundBmpPath(":/res/blu/phonenum_edit.png");
           mBmpDialDiaplayWidget->setGeometry(15,15,391,54);
           mDialNumber = new QLabel(mBmpDialDiaplayWidget);
           mDialNumber->setFont(ft);
           mDialNumber->setAlignment(Qt::AlignCenter);
           mDialNumber->setPalette(pa);
           mDialNumber->setGeometry(0,0,391,54);
           btn_1 = new BmpButton(mBmpkeyboardWidget);
           btn_1->setNormalBmpPath(":/res/blu/one_normal.png");
           btn_1->setPressBmpPath(":/res/blu/one_press.png");
           btn_1->setGeometry(15,84,92,52);
           connect(btn_1,SIGNAL(released()),this,SLOT(onclick01()));

           btn_2 = new BmpButton(parent);
           btn_2->setNormalBmpPath(":/res/blu/two_normal.png");
           btn_2->setPressBmpPath(":/res/blu/two_press.png");
           btn_2->setGeometry(115,84,92,52);
           connect(btn_2,SIGNAL(released()),this,SLOT(onclick02()));

           btn_3 = new BmpButton(mBmpkeyboardWidget);
           btn_3->setNormalBmpPath(":/res/blu/three_normal.png");
           btn_3->setPressBmpPath(":/res/blu/three_press.png");
           btn_3->setGeometry(215,84,92,52);
           connect(btn_3,SIGNAL(released()),this,SLOT(onclick03()));

           btn_clear = new BmpButton(mBmpkeyboardWidget);
           btn_clear->setNormalBmpPath(":/res/blu/clear_normal.png");
           btn_clear->setPressBmpPath(":/res/blu/clear_press.png");
           btn_clear->setGeometry(315,84,92,52);
           connect(btn_clear,SIGNAL(released()),this,SLOT(onclickclear()));

           btn_4 = new BmpButton(mBmpkeyboardWidget);
           btn_4->setNormalBmpPath(":/res/blu/four_normal.png");
           btn_4->setPressBmpPath(":/res/blu/four_press.png");
           btn_4->setGeometry(15,144,92,52);
           connect(btn_4,SIGNAL(released()),this,SLOT(onclick04()));

           btn_5 = new BmpButton(mBmpkeyboardWidget);
           btn_5->setNormalBmpPath(":/res/blu/five_normal.png");
           btn_5->setPressBmpPath(":/res/blu/five_press.png");
           btn_5->setGeometry(115,144,92,52);
           connect(btn_5,SIGNAL(released()),this,SLOT(onclick05()));

           btn_6 = new BmpButton(mBmpkeyboardWidget);
           btn_6->setNormalBmpPath(":/res/blu/six_normal.png");
           btn_6->setPressBmpPath(":/res/blu/six_press.png");
           btn_6->setGeometry(215,144,92,52);
           connect(btn_6,SIGNAL(released()),this,SLOT(onclick06()));

           btn_0 = new BmpButton(mBmpkeyboardWidget);
           btn_0->setNormalBmpPath(":/res/blu/zero_normal.png");
           btn_0->setPressBmpPath(":/res/blu/zero_press.png");
           btn_0->setGeometry(315,144,92,52);
           connect(btn_0,SIGNAL(released()),this,SLOT(onclick00()));

           btn_7 = new BmpButton(mBmpkeyboardWidget);
           btn_7->setNormalBmpPath(":/res/blu/eleven_normal.png");
           btn_7->setPressBmpPath(":/res/blu/eleven_press.png");
           btn_7->setGeometry(15,204,92,52);
           connect(btn_7,SIGNAL(released()),this,SLOT(onclick07()));

           btn_8 = new BmpButton(mBmpkeyboardWidget);
           btn_8->setNormalBmpPath(":/res/blu/eight_normal.png");
           btn_8->setPressBmpPath(":/res/blu/eight_press.png");
           btn_8->setGeometry(115,204,92,52);
           connect(btn_8,SIGNAL(released()),this,SLOT(onclick08()));

           btn_9 = new BmpButton(mBmpkeyboardWidget);
           btn_9->setNormalBmpPath(":/res/blu/nine_normal.png");
           btn_9->setPressBmpPath(":/res/blu/nine_press.png");
           btn_9->setGeometry(215,204,92,52);
           connect(btn_9,SIGNAL(released()),this,SLOT(onclick09()));

           btn_backspace = new BmpButton(mBmpkeyboardWidget);
           btn_backspace->setNormalBmpPath(":/res/blu/backspace_normal.png");
           btn_backspace->setPressBmpPath(":/res/blu/backspace_press.png");
           btn_backspace->setGeometry(315,204,92,52);
           connect(btn_backspace,SIGNAL(released()),this,SLOT(onclickbackspace()));

           btn_star = new BmpButton(mBmpkeyboardWidget);
           btn_star->setNormalBmpPath(":/res/blu/star_normal.png");
           btn_star->setPressBmpPath(":/res/blu/star_press.png");
           btn_star->setGeometry(15,264,192,52);
           connect(btn_star,SIGNAL(released()),this,SLOT(onclickstar()));

           btn_well = new BmpButton(mBmpkeyboardWidget);
           btn_well->setNormalBmpPath(":/res/blu/well_normal.png");
           btn_well->setPressBmpPath(":/res/blu/well_press.png");
           btn_well->setGeometry(215,264,192,52);
           connect(btn_well,SIGNAL(released()),this,SLOT(onclickwell()));

           mBmpToolbarWidget = new BmpWidget(parent);
           mBmpToolbarWidget->setBackgroundBmpPath(":/res/blu/toolbar_bg.png");
           mBmpToolbarWidget->setGeometry(0,326,800,60);
           btn_dial = new BmpButton(mBmpToolbarWidget);
           btn_dial->setNormalBmpPath(":/res/blu/phone_dial.png");
           btn_dial->setPressBmpPath(":/res/blu/phone_dial_press.png");
           btn_dial->setGeometry(0,0,267,60);
           connect(btn_dial,SIGNAL(released()),this,SLOT(onBtPhoneDial()));
           btn_Swapcalls = new BmpButton(mBmpToolbarWidget);
           btn_Swapcalls->setText(tr("切换通话"));
           btn_Swapcalls->setFont(font);
           btn_Swapcalls->setNormalBmpPath(":/res/blu/toolbar_swap.png");
           btn_Swapcalls->setPressBmpPath(":/res/blu/toolbar_press_bg.png");
           btn_Swapcalls->setGeometry(267,0,267,60);
           btn_hungup = new BmpButton(mBmpToolbarWidget);
           btn_hungup->setNormalBmpPath(":/res/blu/phone_hungup.png");
           btn_hungup->setPressBmpPath(":/res/blu/phone_hungup_press.png");
           btn_hungup->setGeometry(534,0,267,60);
           connect(btn_hungup,SIGNAL(released()),this,SLOT(onBtPhoneHungup()));

           //通话中显示界面
           mBmpCallingWidget = new BmpWidget(parent);
           mBmpCallingWidget->setBackgroundBmpPath(":/res/blu/phone_dial_msg_bg.png");
           mBmpCallingWidget->setGeometry(423,15,360,296);
           mBmpCallingWidget->setVisible(false);
           mCallingTitle = new QLabel(mBmpCallingWidget);
           mCallingTitle->setText(tr("通话中 ..."));
           mCallingTitle->setAlignment(Qt::AlignCenter);
           mCallingTitle->setFont(font);
           mCallingTitle->setPalette(pa);
           mCallingTitle->setGeometry(115,0,131,52);
           mCallingTitleWidget = new BmpWidget(mBmpCallingWidget);
           mCallingTitleWidget->setBackgroundBmpPath(":/res/blu/dialing_msg_bg.png");
           mCallingTitleWidget->setGeometry(115,52,131,2);

           mCallingPhoneNameIcon = new BmpWidget(mBmpCallingWidget);
           mCallingPhoneNameIcon->setBackgroundBmpPath(":/res/blu/dial_name_icon.png");
           mCallingPhoneNameIcon->setGeometry(24,113,22,25);
           mCallingPhoneName = new QLabel(mBmpCallingWidget);
           mCallingPhoneName->setText(tr("张三"));
           mCallingPhoneName->setFont(font);
           mCallingPhoneName->setPalette(pa);
           mCallingPhoneName->setGeometry(75,110,260,30);

           mCallingPhoneNumberIcon = new BmpWidget(mBmpCallingWidget);
           mCallingPhoneNumberIcon->setBackgroundBmpPath(":/res/blu/dial_number_icon.png");
           mCallingPhoneNumberIcon->setGeometry(21,160,28,28);
           mCallingPhoneNumber = new QLabel(mBmpCallingWidget);
           mCallingPhoneNumber->setFont(font);
           mCallingPhoneNumber->setText(tr("15023456789"));
           mCallingPhoneNumber->setPalette(pa);
           mCallingPhoneNumber->setGeometry(75,160,260,30);

           mCallingTimeIcon = new BmpWidget(mBmpCallingWidget);
           mCallingTimeIcon->setBackgroundBmpPath(":/res/blu/dial_time_icon.png");
           mCallingTimeIcon->setGeometry(20,210,29,29);
           mCallingTime = new QLabel(mBmpCallingWidget);
           mCallingTime->setText(tr("12:12:12"));
           mCallingTime->setFont(font);
           mCallingTime->setPalette(pa);
           mCallingTime->setGeometry(75,210,260,30);

           mDialingWidget = new BmpWidget(parent);
           mDialingWidget->setBackgroundBmpPath(":/res/blu/phone_dial_msg_bg.png");
           mDialingWidget->setGeometry(423,15,360,296);
           mDialingWidget->setVisible(false);
           mDialingPhoneNumber = new QLabel(mDialingWidget);
           //mDialingPhoneNumber->setText(tr("15098765432"));
           mDialingPhoneNumber->setFont(ft);
           mDialingPhoneNumber->setPalette(pa);
           mDialingPhoneNumber->setAlignment(Qt::AlignCenter);
           mDialingPhoneNumber->setGeometry(0,85,360,35);
           mDialingPhoneText = new QLabel(mDialingWidget);
           mDialingPhoneText->setText(tr("拨号中 ..."));
           mDialingPhoneText->setFont(font);
           mDialingPhoneText->setPalette(pa);
           mDialingPhoneText->setAlignment(Qt::AlignCenter);
           mDialingPhoneText->setGeometry(0,150,360,35);

           mNormalWidget = new BmpWidget(parent);
           mNormalWidget->setBackgroundBmpPath(":/res/blu/phone_dial_msg_bg.png");
           mNormalWidget->setGeometry(423,15,360,296);
		
}

//connect 蓝牙信号
void PhoneDialWidgetPrivate::initializeBlutoothManager()
{
    //拨打电话回调
    connect(gBluetoothManager,SIGNAL(callOnCallSucceed(QString)),this,SLOT(onCallSucceed(QString)));
    //挂断电话
    connect(gBluetoothManager,SIGNAL(callOnHangUp()),this,SLOT(onHangUp()));
    //来电
    connect(gBluetoothManager,SIGNAL(callOnIncoming(QString)),this,SLOT(onIncoming(QString)));
    //来电接听
    connect(gBluetoothManager,SIGNAL(callOnTalking()),this,SLOT(callOnTalking()));
}

//不同电话状态显示不同的界面
void PhoneDialWidgetPrivate::showDialDiaplay(const PhoneDialWidget::PhoneStatus &status)
{
    if (status != m_PhoneStatus) {
        m_PhoneStatus = status;
        switch (status) {
        case PhoneDialWidget::B_Normal:
        case PhoneDialWidget::B_Hangup:
            mDialingWidget->setVisible(false);
            mBmpCallingWidget->setVisible(false);
            mNormalWidget->setVisible(true);
            break;
        case PhoneDialWidget::B_Dialing:
            mDialingWidget->setVisible(true);
            mBmpCallingWidget->setVisible(false);
            mNormalWidget->setVisible(false);
            break;
        case PhoneDialWidget::B_Calling:
            mDialingWidget->setVisible(false);
            mBmpCallingWidget->setVisible(true);
            mNormalWidget->setVisible(false);
            break;
        }
    }
}

PhoneDialWidget::PhoneDialWidget(QWidget *parent):
 QWidget(parent),d_ptr(new PhoneDialWidgetPrivate(this))
{
    Q_D(PhoneDialWidget);
    d->setWidgetBackground(this);
}

PhoneDialWidgetPrivate::~PhoneDialWidgetPrivate(){

}

PhoneDialWidget::~PhoneDialWidget() {

}

void PhoneDialWidgetPrivate::onclick01()
{
    currentPhonenumber += "1";
    setCurrentPhoneNumber(currentPhonenumber);
}

void PhoneDialWidgetPrivate::onclick02()
{
    currentPhonenumber += "2";
    setCurrentPhoneNumber(currentPhonenumber);
}

void PhoneDialWidgetPrivate::onclick03()
{
    currentPhonenumber += "3";
    setCurrentPhoneNumber(currentPhonenumber);
}

void PhoneDialWidgetPrivate::onclick04()
{
    currentPhonenumber += "4";
    setCurrentPhoneNumber(currentPhonenumber);
}

void PhoneDialWidgetPrivate::onclick05()
{
    currentPhonenumber += "5";
    setCurrentPhoneNumber(currentPhonenumber);
}

void PhoneDialWidgetPrivate::onclick06()
{
    currentPhonenumber += "6";
    setCurrentPhoneNumber(currentPhonenumber);
}

void PhoneDialWidgetPrivate::onclick07()
{
    currentPhonenumber += "7";
    setCurrentPhoneNumber(currentPhonenumber);
}

void PhoneDialWidgetPrivate::onclick08()
{
    currentPhonenumber += "8";
    setCurrentPhoneNumber(currentPhonenumber);
}

void PhoneDialWidgetPrivate::onclick09()
{
    currentPhonenumber += "9";
    setCurrentPhoneNumber(currentPhonenumber);
}

void PhoneDialWidgetPrivate::onclick00()
{
    currentPhonenumber += "0";
    setCurrentPhoneNumber(currentPhonenumber);
}

void PhoneDialWidgetPrivate::onclickstar()
{
    currentPhonenumber += "*";
    setCurrentPhoneNumber(currentPhonenumber);
}

void PhoneDialWidgetPrivate::onclickclear()
{
    if(currentPhonenumber.length() >0 ){
        currentPhonenumber = "";
        setCurrentPhoneNumber(currentPhonenumber);
    }
}

void PhoneDialWidgetPrivate::onclickwell()
{
    currentPhonenumber += "#";
    setCurrentPhoneNumber(currentPhonenumber);
}

void PhoneDialWidgetPrivate::onclickbackspace()
{
    if(currentPhonenumber.length() > 0){
       currentPhonenumber = currentPhonenumber.mid(0,currentPhonenumber.length()-1);
       setCurrentPhoneNumber(currentPhonenumber);
    }
}

//显示电话号码
void PhoneDialWidgetPrivate::setCurrentPhoneNumber(QString phoneNumber)
{
      mDialNumber->setText(phoneNumber);
}

void PhoneDialWidgetPrivate::setWidgetBackground(PhoneDialWidget *parent){
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

//拨号
void PhoneDialWidgetPrivate::onBtPhoneDial()
{
    if(currentPhonenumber.length() == 0){
        qDebug() << "号码为空" << endl;
        return;
    }
    showDialDiaplay(PhoneDialWidget::B_Dialing);
    btn_dial->setEnabled(false);
    mDialingPhoneNumber->setText(currentPhonenumber);
    currentPhonenumber = "";
    setCurrentPhoneNumber(currentPhonenumber);

    //执行拨打代码
    gBluetoothManager->phoneDail(currentPhonenumber);

}

//挂断
void PhoneDialWidgetPrivate::onBtPhoneHungup()
{
    //挂断电话
    gBluetoothManager->phoneHangUp();

}

//通话计时
void PhoneDialWidgetPrivate::updatePhoneTime()
{
    QTime showTime(0,0,0);
    //在当前时间基础上增加ms毫秒，ms可为负
    showTime = showTime.addSecs(1);
    //设置时间格式
    showStrTime = showTime.toString("hh:mm:ss");
    mCallingTime->setText(showStrTime);
}

//蓝牙回调，信号槽
//拨打电话成功
void PhoneDialWidgetPrivate::onCallSucceed(QString number)
{
    //切换为通话中界面
    //mCallingPhoneName->setText(tr("张三"));
    mCallingPhoneNumber->setText(number);
    mCallingTime->setText(tr("00:00:00"));
    showDialDiaplay(PhoneDialWidget::B_Calling);
    p_Timer->start(1000);//开始计时
}

//挂断电话
void PhoneDialWidgetPrivate::onHangUp()
{
    showDialDiaplay(PhoneDialWidget::B_Hangup);
    btn_dial->setEnabled(true);
    mDialingPhoneNumber->setText("");
    p_Timer->stop();//挂断电话，停止计时
    mCallingTime->setText(tr("00:00:00"));
    //mCallingPhoneName->setText(tr("张三"));
    mCallingPhoneNumber->setText("");
}

//来电
void PhoneDialWidgetPrivate::onIncoming(QString number)
{
    showDialDiaplay(PhoneDialWidget::B_Dialing);
    mDialingPhoneNumber->setText(number);
    mDialingPhoneText->setText("某某某来电");

}

//来电接听
void PhoneDialWidgetPrivate::onTalking()
{

}
