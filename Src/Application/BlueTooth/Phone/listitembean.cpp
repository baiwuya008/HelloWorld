#include "listitembean.h"

listitemBean::listitemBean(QObject *parent)
    : QObject(parent)
    , d_ptr(new listitemBeanPrivate(this))
{
}


listitemBean::~listitemBean()
{
}


listitemBeanPrivate::listitemBeanPrivate(listitemBean* parent)
    : q_ptr(parent)
{

}

listitemBeanPrivate::~listitemBeanPrivate()
{
}

void listitemBean::settype(int type)
{
    d_ptr->type = type;
}

void listitemBean::setPhoneName(QString phoneName)
{
    d_ptr->phoneName = phoneName;
}

void listitemBean::setPhoneNumber(QString phoneNumber)
{
    d_ptr->phoneNumber = phoneNumber;
}

int listitemBean::getType()
{
    d_ptr->type;
}

QString listitemBean::getPhoneName()
{
    d_ptr->phoneName;
}

QString listitemBean::getPhoneNumber()
{
    d_ptr->phoneName;
}
