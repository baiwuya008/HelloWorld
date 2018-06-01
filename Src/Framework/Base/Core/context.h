#ifndef CONTEXT_H
#define CONTEXT_H

#include <QObject>
#include "apptype.h"
#include "message.h"


#if defined(ConnectType)
#undef ConnectType
#endif
#define ConnectType (static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection))

class ContextPrivate;
class Context : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(Context)

public:
    explicit Context(QObject *parent = 0);

    bool startApplication(AppType type,char **argv= 0);
    bool setWindowWallPaper(const QString &path);

    void callBack();

    void sendBroadcast(AppType type,OMessage &msg);

    void sendCmdTo(AppType type,OMessage &msg);

    AppType getAppType();

private:
    Q_DECLARE_PRIVATE(Context)
    ContextPrivate * const d_ptr;

};

class ContextPrivate :public QObject{
    Q_OBJECT
    Q_DISABLE_COPY(ContextPrivate)
public:
    explicit ContextPrivate(Context *parent);
    ~ContextPrivate(){delete q_ptr;}

private:
    //data
    AppType mApptype;

    Q_DECLARE_PUBLIC(Context)
    Context * const q_ptr;

private slots:

};

#endif // CONTEXT_H
