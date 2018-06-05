#include "context.h"
#include "application.h"

ContextPrivate::ContextPrivate(Context *parent):
    QObject(),q_ptr(parent)
{
   mApptype = T_None;
}

Context::Context(QObject *parent) :
    QObject(parent),
    d_ptr(new ContextPrivate(this))
{

}

void Context::sendBroadcast(AppType type,OMessage &msg)
{

}

void Context::sendCmdTo(AppType type,OMessage &msg)
{

}

bool Context::startApplication(AppType type,char **argv)
{
 Q_D(Context);
 d->mApptype = type;
 return oklApp->startApplication(type,argv);
}

void Context::callBack(){
  oklApp->callBackPressed();
}

AppType Context::getAppType(){
  Q_D(Context);
  return d->mApptype;
}
