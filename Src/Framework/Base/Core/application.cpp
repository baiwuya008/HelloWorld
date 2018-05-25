#include "application.h"
#include "activity.h"
#include "service.h"
#include "Src/Application/AllApplication.h"

Application::Application(int &argc, char **argv) :
    QApplication(argc, argv)
{

}

Application::~Application()
{

}

bool Application::setWindowWidget(QWidget *windowWidget)
{
  mWindowWidget = windowWidget;
  return true;
}


bool Application::startApplication(AppType type,char **argv)
{
    if(type > T_None && type < T_ServiceSectionStart)
    {
        //for activity
        if(mAppMaps.isEmpty() || !mAppMaps.contains(type))
        {
            //first create here!!
            //*********onCreate
           onCreate(type);
        }
        mCurApp = type;

        if(type == T_Home){
            if(!mAppStack.isEmpty()){
                mAppStack.clear();
            }
           mAppStack.push(type);
        }else{
            //for check three times to clear up the same type already open
            if(mAppStack.contains(type)){
               mAppStack.remove(mAppStack.indexOf(type));
            }
            if(mAppStack.contains(type)){
               mAppStack.remove(mAppStack.indexOf(type));
            }
            if(mAppStack.contains(type)){
               mAppStack.remove(mAppStack.indexOf(type));
            }

            mAppStack.push(type);
        }

        //*********onStart
        onStart(type);

        //*********onResume
        onResume(type);

        //the others onPause() and onStop()
        for (int var = 0; var < mAppMaps.size(); ++var) {
            AppType otherType = mAppMaps.keys().takeAt(var);
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
        if(mAppMaps.isEmpty() || !mAppMaps.contains(type))
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
 if(mCurApp<T_Home && mCurApp < T_ServiceSectionStart){
     return onBackPressed(mCurApp);
 }
 return false;
}

bool Application::callLanguageChanged()
{
    for (int var = 0; var < mAppMaps.size(); ++var) {
        AppType appType = mAppMaps.keys().takeAt(var);
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
    //*********here instance the app by the apptype
    switch (type) {
    case T_Home:
        //for launcher
        mAppMaps.insert(type,new Launcher());
        break;
    case T_Radio:
        mAppMaps.insert(type,new Radio());
        break;
    case T_Setting:
        mAppMaps.insert(type,new Settings());
        break;
    case T_AVIN:
        mAppMaps.insert(type,new Avin());
        break;
    case T_Bluetooth:
        mAppMaps.insert(type,new Btphone());
        break;
    case T_BluetoothMusic:
        mAppMaps.insert(type,new Btmusic());
        break;
    case T_Ipod:
        mAppMaps.insert(type,new Ipod());
        break;
    case T_USBDiskMusic:
        mAppMaps.insert(type,new Music());
        break;
    case T_USBDiskImage:
        mAppMaps.insert(type,new Image());
        break;
    case T_USBDiskVideo:
        mAppMaps.insert(type,new Video());
        break;
    default:
        break;
    }
    //end of*****here instance the app by the apptype


    if(type>T_None && type< T_ServiceSectionStart){
        (static_cast<Activity *>(mAppMaps.find(type).value()))->onCreate(mWindowWidget);
        (static_cast<Activity *>(mAppMaps.find(type).value()))->doCreate(mWindowWidget);
    }else if(type> T_ServiceSectionStart && T_All){

    }

   return true;
}
//---------------- end of section need add more mode for different app -------------------//


bool Application::onReceiveBroadcast(AppType type,OMessage &msg)
{
    if(type == T_All){
        for (int var = 0; var < mAppMaps.size(); ++var) {
            AppType appType = mAppMaps.keys().takeAt(var);
            onReceiveBroadcast(appType,msg);
        }
    }else{
        if(type>T_None && type< T_ServiceSectionStart){
            (static_cast<Activity *>(mAppMaps.find(type).value()))->onReceiveBroadcast(type,msg);
        }else if(type> T_ServiceSectionStart && T_All){

        }
    }

    return true;
}

bool Application::onReceiveCmd(AppType type,OMessage &msg)
{
    if(type == T_All){
        for (int var = 0; var < mAppMaps.size(); ++var) {
            AppType appType = mAppMaps.keys().takeAt(var);
            onReceiveCmd(appType,msg);
        }
    }else{
        if(type>T_None && type< T_ServiceSectionStart){
            (static_cast<Activity *>(mAppMaps.find(type).value()))->onReceiveCmd(type,msg);
        }else if(type> T_ServiceSectionStart && T_All){

        }
    }
   return true;
}



bool Application::onStart(AppType type)
{
    if(type>T_None && type< T_ServiceSectionStart){
        (static_cast<Activity *>(mAppMaps.find(type).value()))->onStart();
        (static_cast<Activity *>(mAppMaps.find(type).value()))->doStart();
    }else if(type> T_ServiceSectionStart && T_All){

    }
   return true;
}

bool Application::onResume(AppType type)
{
   if(type>T_None && type< T_ServiceSectionStart){
        (static_cast<Activity *>(mAppMaps.find(type).value()))->onResume();
        (static_cast<Activity *>(mAppMaps.find(type).value()))->doResume();
   }else if(type> T_ServiceSectionStart && T_All){

   }

   return true;
}

bool Application::onPause(AppType type)
{
    if(type>T_None && type< T_ServiceSectionStart){
        if((static_cast<Activity *>(mAppMaps.find(type).value()))->getState() == Sta_Resume){
            (static_cast<Activity *>(mAppMaps.find(type).value()))->onPause();
            (static_cast<Activity *>(mAppMaps.find(type).value()))->doPause();
        }
    }else if(type> T_ServiceSectionStart && T_All){

    }
   return true;
}

bool Application::onStop(AppType type)
{
    if(type>T_None && type< T_ServiceSectionStart){
        if((static_cast<Activity *>(mAppMaps.find(type).value()))->getState() == Sta_Start||
           (static_cast<Activity *>(mAppMaps.find(type).value()))->getState() == Sta_Resume ){
            (static_cast<Activity *>(mAppMaps.find(type).value()))->onStop();
            (static_cast<Activity *>(mAppMaps.find(type).value()))->doStop();
        }
    }else if(type> T_ServiceSectionStart && T_All){

    }

   return true;
}

bool Application::onDestroy(AppType type)
{
    if(type>T_None && type< T_ServiceSectionStart){
        if((static_cast<Activity *>(mAppMaps.find(type).value()))->getState() != Sta_Destroy){
            (static_cast<Activity *>(mAppMaps.find(type).value()))->onDestroy();
            (static_cast<Activity *>(mAppMaps.find(type).value()))->doDestroy();
        }
    }else if(type> T_ServiceSectionStart && T_All){

    }

   return true;
}


bool Application::onBackPressed(AppType type)
{
    bool ret = false;
   if(type>T_None && type< T_ServiceSectionStart){
       if((static_cast<Activity *>(mAppMaps.find(type).value()))->getState() == Sta_Resume){
           ret= (static_cast<Activity *>(mAppMaps.find(type).value()))->onBackPressed();
           if(!ret)
           {
               if(!mAppStack.isEmpty()){
                   mAppStack.pop();
                   if(mAppStack.isEmpty()){
                       startApplication(T_Home);
                   }else{
                       startApplication(mAppStack.pop());
                   }
               }
           }
        }
   }else if(type> T_ServiceSectionStart && T_All){

   }

   return ret;
}

bool Application::onLanguageChanged(AppType type)
{
    if(type>T_None && type< T_ServiceSectionStart){
         (static_cast<Activity *>(mAppMaps.find(type).value()))->onLanguageChanged();
    }else if(type> T_ServiceSectionStart && T_All){

    }
   return true;
}




