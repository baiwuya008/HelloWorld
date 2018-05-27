#include "service.h"

ServicePrivate::ServicePrivate(Service *parent):
    QObject(),q_ptr(parent)
{

}


Service::Service(QObject *parent):
    Context(parent),
    d_ptr(new ServicePrivate(this))
{
}

void Service::onCreate()
{

}

void Service::onDestroy()
{

}

void Service::onLanguageChanged()
{

}
