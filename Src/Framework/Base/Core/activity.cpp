#include "activity.h"

Activity::Activity(QObject *parent):
    Context(parent)
{
    mpContentView=NULL;
    mState=Sta_None;
}


void Activity::doCreate(QWidget *parent)
{
   mState = Sta_Create;
}

void Activity::doStart()
{
    if(mpContentView == NULL){
        //throw exception here!!

    }
    mState = Sta_Start;
}

void Activity::doResume()
{
  if(mpContentView != NULL&& mpContentView->isHidden()){
      mpContentView->setVisible(true);
  }
  mState = Sta_Resume;
}

void Activity::doPause()
{
    if(mpContentView != NULL && !mpContentView->isHidden()){
        mpContentView->setVisible(false);
    }
    mState = Sta_Pause;
}

void Activity::doStop()
{
    if(mpContentView != NULL && !mpContentView->isHidden()){
        mpContentView->setVisible(false);
    }
    mState = Sta_Stop;
}

void Activity::doDestroy()
{
//delete mpContentView;
    mState = Sta_Destroy;
}

void Activity::setContentView(QWidget *pContentView)
{
    mpContentView = pContentView;
    mpContentView->setFixedSize(QSize(800, 480));

}
