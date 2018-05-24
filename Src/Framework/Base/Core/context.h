#ifndef CONTEXT_H
#define CONTEXT_H

#include <QObject>
#include "apptype.h"
#include "message.h"


#if defined(ConnectType)
#undef ConnectType
#endif
#define ConnectType (static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection))


class Context : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Context)

public:
    explicit Context(QObject *parent = 0);

    bool startApplication(AppType type,char **argv= 0);

    void sendBroadcast(AppType type,OMessage &msg);

    void sendCmdTo(AppType type,OMessage &msg);

private:
    int mApptype;


signals:

public slots:

};

#endif // CONTEXT_H
