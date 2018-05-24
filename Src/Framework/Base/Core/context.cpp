#include "context.h"
#include "application.h"

Context::Context(QObject *parent) :
    QObject(parent)
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
 oklApp->startApplication(type,argv);
}
