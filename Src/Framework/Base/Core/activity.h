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
class Activity : public Context
{
    Q_OBJECT
    Q_DISABLE_COPY(Activity)
public:
    Activity(QObject *parent = 0);


    // must be overlay define
    virtual void onCreate(QWidget *parent = 0)=0;
    virtual void onStart()=0;
    virtual void onResume()=0;
    virtual void onPause()=0;
    virtual void onStop()=0;
    virtual void onDestroy()=0;
    virtual bool onBackPressed(){return false;}
    virtual void onLanguageChanged()=0;
    virtual void onReceiveBroadcast(AppType appType,OMessage &msg)=0;
    virtual void onReceiveCmd(AppType appType,OMessage &msg)=0;
    //*************************

    void setContentView(QWidget *pContentView);
    QWidget *centralWidget;

private:
    QWidget *mpContentView;
    ActivitySta mState;

    ActivitySta getState(){return mState;}
    void doCreate(QWidget *parent = 0);
    void doStart();
    void doResume();
    void doPause();
    void doStop();
    void doDestroy();
    //*************************
    friend class Application;


};

#endif // ACTIVITY_H
