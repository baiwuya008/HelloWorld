#ifndef BTPHONE_H
#define BTPHONE_H

#include "Src/Framework/Base/Core/activity.h"
#include <QMouseEvent>
#include <QString>
#include "phonerecordwidget.h"
#include "phonedialwidget.h"

class BtphonePrivate;
class Btphone : public Activity
{
    Q_OBJECT
    Q_DISABLE_COPY(Btphone)

public:

    Btphone(QObject *parent = 0);

    void onCreate(QWidget *parent=0);
    void onStart();
    void onResume();
    void onPause();
    void onStop();
    void onDestroy();
    bool onBackPressed();
    void onLanguageChanged();
    void onReceiveBroadcast(AppType appType,OMessage &msg);
    void onReceiveCmd(AppType appType,OMessage &msg);

    //电话状态
    enum PhoneStatus {
        B_Normal = 0,
        B_Dialing = 1,
        B_Calling = 2,
        B_Hangup = 3,
        B_Incoming = 4,
    };

private:
    Q_DECLARE_PRIVATE(Btphone)
    BtphonePrivate* const d_ptr;

};

class BtphonePrivate :public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(BtphonePrivate)
public:
    explicit BtphonePrivate(Btphone* parent);
    ~BtphonePrivate(){delete q_ptr;}
    void initializeBasicWidget(QWidget *parent);
	
protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent*e);

private:
    Q_DECLARE_PUBLIC(Btphone)
    Btphone* const q_ptr;
	
    //tab分页标题
	BmpWidget *mPhoneTitle;
    BmpButton *mBmpDialTab;
    BmpButton *mBmpRecordTab;
    BmpButton *mBmpOptionsTab;

    PhoneDialWidget *mBmpDialWidget;
    //BmpWidget *mBmpRecordWidget;
    PhoneRecordWidget *mBmpRecordWidget;
    BmpWidget *mBmpOptionsWidget;


    //----------
    BmpWidget *mBackground;
    BmpButton *mBtnTest;
    //----------
private slots:
    void onBtnTestRelease();
	
    void switchPage(int index);
	void onBtnDialTabClick();
    void onBtnRecordTabClick();
    void onBtnOptionsTabClick();

};

#endif // BTPHONE_H
