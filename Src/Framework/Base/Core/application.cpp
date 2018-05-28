#include "application.h"
#include "activity.h"
#include "service.h"
#include "Src/Application/AllApplication.h"

ApplicationPrivate::ApplicationPrivate(Application *parent):
    QObject(),q_ptr(parent)
{

}

//------------------------

Application::Application(int &argc, char **argv) :
    QApplication(argc, argv),
    d_ptr(new ApplicationPrivate(this))
{

}


#if (APP_WITH_SIMULATION == 1)
bool Application::setSimulation(Simulation *simu)
{
    Q_D(Application);
    d->mSimulation = simu;
}
#endif

bool Application::setWindowWidget(QWidget *windowWidget)
{
 Q_D(Application);
 #if (APP_WITH_SIMULATION == 1)
    d->mSimulationWindowWidget = windowWidget;

    d->mSimulation->onCreate(d->mSimulationWindowWidget);


    d->mWindowWidget = new QWidget(d->mSimulationWindowWidget);
    d->mWindowWidget->setFixedSize(800,480); //固定窗口大小
    d->mWindowWidget->setGeometry(146,10,800,480);
    d->mWindowWidget->setVisible(true);

    d->mTopBarWidget = new QWidget(d->mWindowWidget);
    d->mTopBarWidget->setFixedSize(800,45); //固定窗口大小
    d->mTopBarWidget->setGeometry(0,0,800,45);
    d->mTopBarWidget->setVisible(true);

    d->mContentViewWidget = new QWidget(d->mWindowWidget);
    d->mContentViewWidget->setFixedSize(800,435); //固定窗口大小
    d->mContentViewWidget->setGeometry(0,45,800,435);
    d->mContentViewWidget->setVisible(true);

 #else
    d->mWindowWidget = windowWidget;//new QWidget(windowWidget);
    //d->mWindowWidget->setFixedSize(800,480); //固定窗口大小

    d->mTopBarWidget = new QWidget(d->mWindowWidget);
    d->mTopBarWidget->setFixedSize(800,45); //固定窗口大小
    d->mTopBarWidget->setGeometry(0,0,800,45);
    d->mTopBarWidget->setVisible(true);

    d->mContentViewWidget = new QWidget(d->mWindowWidget);
    d->mContentViewWidget->setFixedSize(800,435); //固定窗口大小
    d->mContentViewWidget->setGeometry(0,45,800,435);
    d->mContentViewWidget->setVisible(true);
 #endif

  return true;
}


bool Application::startApplication(AppType type,char **argv)
{
    Q_D(Application);
    if(type == T_SystemUi)
    {
      //for state bar
        //if(d->mStateBar == NULL)
        //{
           onCreate(type);
        //}
        //*********onStart
        onStart(type);
        //*********onResume
        onResume(type);

    }
    else if(type >= T_Home && type < T_ServiceSectionStart)
    {
        //for activity
        if(d->mAppMaps.isEmpty() || !d->mAppMaps.contains(type))
        {
            //first create here!!
            //*********onCreate
           onCreate(type);
        }
        d->mCurApp = type;

        if(type == T_Home){
            if(!d->mAppStack.isEmpty()){
                d->mAppStack.clear();
            }
           d->mAppStack.push(type);
        }else{
            //for check three times to clear up the same type already open
            if(d->mAppStack.contains(type)){
               d->mAppStack.remove(d->mAppStack.indexOf(type));
            }
            if(d->mAppStack.contains(type)){
               d->mAppStack.remove(d->mAppStack.indexOf(type));
            }
            if(d->mAppStack.contains(type)){
               d->mAppStack.remove(d->mAppStack.indexOf(type));
            }

            d->mAppStack.push(type);
        }

        //*********onStart
        onStart(type);

        //*********onResume
        onResume(type);

        //the others onPause() and onStop()
        for (int var = 0; var < d->mAppMaps.size(); ++var) {
            AppType otherType = d->mAppMaps.keys().takeAt(var);
            if(otherType != type ){
                //*********onPause()
                onPause(otherType);
                //*********onStop()
                onStop(otherType);
            }
        }

    }else if(type > T_ServiceSectionStart && type < T_All)
    {
        //for service
        if(d->mAppMaps.isEmpty() || !d->mAppMaps.contains(type))
        {
            //create first
            //*********onCreate
           onCreate(type);
        }

    }
   return true;
}

bool Application::callBackPressed()
{
 Q_D(Application);
 if(d->mCurApp>T_Home && d->mCurApp < T_ServiceSectionStart){
     return onBackPressed(d->mCurApp);
 }
 return false;
}

bool Application::callLanguageChanged()
{
 Q_D(Application);
    for (int var = 0; var < d->mAppMaps.size(); ++var) {
        AppType appType = d->mAppMaps.keys().takeAt(var);
        onLanguageChanged(appType);
    }
 return true;
}


//bool Application::startView(AppType type,char **argv)
//{
// return true;
//}

bool Application::sendBroadcast(AppType type,OMessage &msg)
{
 onReceiveBroadcast(type,msg);
 return true;
}

bool Application::sendCmdTo(AppType type,OMessage &msg)
{
   onReceiveCmd(type,msg);
   return true;
}


//-------------------- the next section need add more mode for different app -------------------//
bool Application::onCreate(AppType type)
{
  Q_D(Application);
    //*********here instance the app by the apptype
    switch (type) {
    case T_Home:
        //for launcher
        d->mAppMaps.insert(type,new Launcher());
        break;
    case T_Radio:
        d->mAppMaps.insert(type,new Radio());
        break;
    case T_RadioAm:
        d->mAppMaps.insert(type,new RadioAm());
        break;
    case T_Setting:
        d->mAppMaps.insert(type,new Settings());
        break;
    case T_AVIN:
        d->mAppMaps.insert(type,new Avin());
        break;
    case T_Bluetooth:
        d->mAppMaps.insert(type,new Btphone());
        break;
    case T_BluetoothMusic:
        d->mAppMaps.insert(type,new Btmusic());
        break;
    case T_Ipod:
        d->mAppMaps.insert(type,new Ipod());
        break;
    case T_USBDiskMusic:
        d->mAppMaps.insert(type,new Music());
        break;
    case T_USBDiskImage:
        d->mAppMaps.insert(type,new Image());
        break;
    case T_USBDiskVideo:
        d->mAppMaps.insert(type,new Video());
        break;
    case T_SystemUi:
        d->mStateBar= new Systemui();
        break;
    default:
        break;
    }
    //end of*****here instance the app by the apptype

    if(type == T_SystemUi)
    {
        (static_cast<Activity *>(d->mStateBar))->onCreate(d->mTopBarWidget);
        (static_cast<Activity *>(d->mStateBar))->doCreate(d->mTopBarWidget);
    }
    else if(type>=T_Home && type< T_ServiceSectionStart){
        QWidget *contextView = new QWidget(d->mContentViewWidget);
        (static_cast<Activity *>(d->mAppMaps.find(type).value()))->onCreate(contextView);
        (static_cast<Activity *>(d->mAppMaps.find(type).value()))->doCreate(contextView);
        //set size here
        contextView->setFixedSize(800,435);
        //contextView->setGeometry(0,45,800,435);
    }else if(type> T_ServiceSectionStart && type<T_All){

    }

   return true;
}
//---------------- end of section need add more mode for different app -------------------//


bool Application::onReceiveBroadcast(AppType type,OMessage &msg)
{
   Q_D(Application);
    if(type == T_All){
        for (int var = 0; var < d->mAppMaps.size(); ++var) {
            AppType appType = d->mAppMaps.keys().takeAt(var);
            onReceiveBroadcast(appType,msg);
        }
    }else{
        if(type == T_SystemUi)
        {
            (static_cast<Activity *>(d->mStateBar))->onReceiveBroadcast(type,msg);
        }
        else if(type>=T_Home && type< T_ServiceSectionStart){
            (static_cast<Activity *>(d->mAppMaps.find(type).value()))->onReceiveBroadcast(type,msg);
        }else if(type> T_ServiceSectionStart && type<T_All){

        }
    }

    return true;
}

bool Application::onReceiveCmd(AppType type,OMessage &msg)
{
    Q_D(Application);
    if(type == T_All){
        for (int var = 0; var < d->mAppMaps.size(); ++var) {
            AppType appType = d->mAppMaps.keys().takeAt(var);
            onReceiveCmd(appType,msg);
        }
    }else{
        if(type == T_SystemUi)
        {
            (static_cast<Activity *>(d->mStateBar))->onReceiveCmd(type,msg);
        }
        else if(type>=T_Home && type< T_ServiceSectionStart){
            (static_cast<Activity *>(d->mAppMaps.find(type).value()))->onReceiveCmd(type,msg);
        }else if(type> T_ServiceSectionStart && type<T_All){

        }
    }
   return true;
}



bool Application::onStart(AppType type)
{
   Q_D(Application);
     if(type == T_SystemUi)
      {
        (static_cast<Activity *>(d->mStateBar))->onStart();
        (static_cast<Activity *>(d->mStateBar))->doStart();
      }
    else if(type>=T_Home && type< T_ServiceSectionStart){
        (static_cast<Activity *>(d->mAppMaps.find(type).value()))->onStart();
        (static_cast<Activity *>(d->mAppMaps.find(type).value()))->doStart();
    }else if(type> T_ServiceSectionStart && type<T_All){

    }
   return true;
}

bool Application::onResume(AppType type)
{
   Q_D(Application);
    if(type == T_SystemUi)
      {
       (static_cast<Activity *>(d->mStateBar))->onResume();
       (static_cast<Activity *>(d->mStateBar))->doResume();
      }
   else if(type>=T_Home && type< T_ServiceSectionStart){
        (static_cast<Activity *>(d->mAppMaps.find(type).value()))->onResume();
        (static_cast<Activity *>(d->mAppMaps.find(type).value()))->doResume();
   }else if(type> T_ServiceSectionStart && type<T_All){

   }

   return true;
}

bool Application::onPause(AppType type)
{
  Q_D(Application);
   if(type>=T_Home && type< T_ServiceSectionStart){
        if((static_cast<Activity *>(d->mAppMaps.find(type).value()))->getState() == Sta_Resume){
            (static_cast<Activity *>(d->mAppMaps.find(type).value()))->onPause();
            (static_cast<Activity *>(d->mAppMaps.find(type).value()))->doPause();
        }
    }else if(type> T_ServiceSectionStart && type<T_All){

    }
   return true;
}

bool Application::onStop(AppType type)
{
   Q_D(Application);
    if(type>=T_Home && type< T_ServiceSectionStart){
        if((static_cast<Activity *>(d->mAppMaps.find(type).value()))->getState() == Sta_Start||
           (static_cast<Activity *>(d->mAppMaps.find(type).value()))->getState() == Sta_Resume ){
            (static_cast<Activity *>(d->mAppMaps.find(type).value()))->onStop();
            (static_cast<Activity *>(d->mAppMaps.find(type).value()))->doStop();
        }
    }else if(type> T_ServiceSectionStart && type<T_All){

    }

   return true;
}

bool Application::onDestroy(AppType type)
{
   Q_D(Application);
    if(type == T_SystemUi)
       {
        if((static_cast<Activity *>(d->mStateBar))->getState() != Sta_Destroy){
            (static_cast<Activity *>(d->mStateBar))->onDestroy();
            (static_cast<Activity *>(d->mStateBar))->doDestroy();
        }
       }
    else if(type>=T_Home && type< T_ServiceSectionStart){
        if((static_cast<Activity *>(d->mAppMaps.find(type).value()))->getState() != Sta_Destroy){
            (static_cast<Activity *>(d->mAppMaps.find(type).value()))->onDestroy();
            (static_cast<Activity *>(d->mAppMaps.find(type).value()))->doDestroy();
        }
    }else if(type> T_ServiceSectionStart && type<T_All){

    }

   return true;
}


bool Application::onBackPressed(AppType type)
{
   Q_D(Application);
    bool ret = false;
   if(type>=T_Home && type< T_ServiceSectionStart){
       if((static_cast<Activity *>(d->mAppMaps.find(type).value()))->getState() == Sta_Resume){
           ret= (static_cast<Activity *>(d->mAppMaps.find(type).value()))->onBackPressed();
           if(!ret)
           {
               if(!d->mAppStack.isEmpty()){
                   d->mAppStack.pop();
                   if(d->mAppStack.isEmpty()){
                       startApplication(T_Home);
                   }else{
                       startApplication(d->mAppStack.pop());
                   }
               }
           }
        }
   }else if(type> T_ServiceSectionStart && type<T_All){

   }

   return ret;
}

bool Application::onLanguageChanged(AppType type)
{
   Q_D(Application);
    if(type == T_SystemUi)
      {
       (static_cast<Activity *>(d->mStateBar))->onLanguageChanged();
      }
    else if(type>T_None && type< T_ServiceSectionStart){
         (static_cast<Activity *>(d->mAppMaps.find(type).value()))->onLanguageChanged();
    }else if(type> T_ServiceSectionStart && type<T_All){

    }
   return true;
}




