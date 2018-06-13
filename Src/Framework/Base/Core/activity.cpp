#include "activity.h"

ActivityPrivate::ActivityPrivate(Activity *parent):
    QObject(),q_ptr(parent)
{
    mpContentView=NULL;
    mState=Sta_None;
}

Activity::Activity(QObject *parent):
    Context(parent),
    d_ptr(new ActivityPrivate(this))
{

}


void Activity::doCreate(QWidget *parent)
{
   Q_D(Activity);
   d->mpContentView = parent;
   d->mState = Sta_Create;
}

void Activity::doStart()
{
    Q_D(Activity);
    if(d->mpContentView == NULL){
        //throw exception here!!

    }
    d->mState = Sta_Start;
}

void Activity::doResume()
{
  Q_D(Activity);
  if(d->mpContentView != NULL&& d->mpContentView->isHidden()){
      d->mpContentView->setVisible(true);
  }
  d->mState = Sta_Resume;
}

void Activity::doPause()
{
    Q_D(Activity);
    if(d->mpContentView != NULL && !d->mpContentView->isHidden()){
        d->mpContentView->setVisible(false);
    }
    d->mState = Sta_Pause;
}

void Activity::doStop()
{
    Q_D(Activity);
    if(d->mpContentView != NULL && !d->mpContentView->isHidden()){
        d->mpContentView->setVisible(false);
    }
    d->mState = Sta_Stop;
}

void Activity::doDestroy()
{
    Q_D(Activity);
//delete mpContentView;
    d->mState = Sta_Destroy;
}

ActivitySta Activity::getState()
{
    Q_D(Activity);
    return d->mState;
}

//void Activity::setContentView(QWidget *pContentView)
//{
//    //Q_D(Activity)
//    //d->mpContentView = pContentView;
//    //d->mpContentView->setFixedSize(QSize(800, 480));

//}
