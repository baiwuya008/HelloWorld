#ifndef SERVICE_H
#define SERVICE_H
#include "context.h"

class Application;
class Service : public Context
{
    Q_OBJECT
    //Q_DISABLE_COPY(Service)

public:
    Service(QObject *parent = 0);

    virtual void onCreate()=0;
    virtual void onDestroy();
    virtual void onLanguageChanged();

private:
    void doCreate(QWidget *parent = 0);
    void doDestroy();
    //*************************
    friend class Application;
};

#endif // SERVICE_H
