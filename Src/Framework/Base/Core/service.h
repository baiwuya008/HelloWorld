#ifndef SERVICE_H
#define SERVICE_H
#include "context.h"

class Application;
class ServicePrivate;
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
    Q_DECLARE_PRIVATE(Service)
    ServicePrivate * const d_ptr;

};

class ServicePrivate :public QObject{
    Q_OBJECT
    Q_DISABLE_COPY(ServicePrivate)
public:
    explicit ServicePrivate(Service *parent);
     ~ServicePrivate(){delete q_ptr;}

private:
    //data

    Q_DECLARE_PUBLIC(Service)
    Service * const q_ptr;

private slots:

};

#endif // SERVICE_H
