#ifndef ACTIVITY_H
#define ACTIVITY_H
#include "context.h"
#include<QWidget>
#include "Src/CommonUserWidget/BmpWidget.h"
#include "Src/CommonUserWidget/BmpButton.h"
#include "Src/CommonUserWidget/CustomItemDelegate.h"
#include "Src/CommonUserWidget/CustomScrollBar.h"
#include "Src/CommonUserWidget/MessageBox.h"
#include "Src/CommonUserWidget/Slider.h"
#include "Src/CommonUserWidget/TextWidget.h"
#include "Src/CommonUserWidget/UserInterfaceUtility.h"


enum  ActivitySta{
    Sta_None = -1,
    Sta_Create = 1,
    Sta_Start,
    Sta_Resume,
    Sta_Pause,
    Sta_Stop,
    Sta_Destroy,
};

class Application;
class ActivityPrivate;
class Activity : public Context
{
    Q_OBJECT
    Q_DISABLE_COPY(Activity)
public:
    Activity(QObject *parent = 0);


    // must be overlay define
    virtual void onCreate(QWidget *parent = 0)=0;
    virtual void onStart(){}
    virtual void onResume(){}
    virtual void onPause(){}
    virtual void onStop(){}
    virtual void onDestroy(){}
    virtual bool onBackPressed(){return false;}
    virtual void onLanguageChanged()=0;
    virtual void onReceiveBroadcast(AppType appType,OMessage &msg){}
    virtual void onReceiveCmd(AppType appType,OMessage &msg){}
    //*************************
//    void setContentView(QWidget *pContentView);
//    QWidget *centralWidget;

private:
    ActivitySta getState();
    void doCreate(QWidget *parent = 0);
    void doStart();
    void doResume();
    void doPause();
    void doStop();
    void doDestroy();
    //*************************
    friend class Application;
    Q_DECLARE_PRIVATE(Activity)
    ActivityPrivate * const d_ptr;

};

class ActivityPrivate :public QObject{
    Q_OBJECT
    Q_DISABLE_COPY(ActivityPrivate)
public:
    explicit ActivityPrivate(Activity *parent);
    ~ActivityPrivate(){delete q_ptr;}

private:
    //data
    QWidget *mpContentView;
    ActivitySta mState;

    Q_DECLARE_PUBLIC(Activity)
    Activity * const q_ptr;

private slots:

};

#endif // ACTIVITY_H
