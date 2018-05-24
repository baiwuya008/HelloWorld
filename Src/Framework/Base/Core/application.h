#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <QWidget>
#include <QStack>
#include <QMap>

#include "context.h"
#include "apptype.h"
#include "message.h"

#if defined(oklApp)
#undef oklApp
#endif
#define oklApp (static_cast<Application *>(QCoreApplication::instance()))




class Application : public QApplication
{
    Q_OBJECT
    Q_DISABLE_COPY(Application)
public:
    explicit Application(int &argc, char **argv);
    virtual ~Application();
    bool setWindowWidget(QWidget *windowWidget);
    bool callBackPressed();
    bool callLanguageChanged();

    bool startApplication(AppType type,char **argv= 0);
    //bool startView(AppType type,char **argv= 0);
    bool sendBroadcast(AppType type,OMessage &msg);
    bool onReceiveBroadcast(AppType type,OMessage &msg);
    bool sendCmdTo(AppType type,OMessage &msg);
    bool onReceiveCmd(AppType type,OMessage &msg);

private:
    bool onCreate(AppType type);
    bool onStart(AppType type);
    bool onResume(AppType type);
    bool onPause(AppType type);
    bool onStop(AppType type);
    bool onDestroy(AppType type);
    bool onBackPressed(AppType type);
    bool onLanguageChanged(AppType type);

    //data
    QMap <AppType,Context*> mAppMaps;
    QWidget *mWindowWidget;
    QStack <AppType> mAppStack;
    AppType mCurApp;

signals:

public slots:

};

#endif // APPLICATION_H
