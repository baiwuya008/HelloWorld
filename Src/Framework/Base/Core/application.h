#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <QWidget>
#include <QStack>
#include <QMap>

#include "context.h"
#include "apptype.h"
#include "message.h"
#include "configuration.h"


#if (APP_WITH_SIMULATION == 1)
#include "simulation.h"
#endif

#if defined(oklApp)
#undef oklApp
#endif
#define oklApp (static_cast<Application *>(QCoreApplication::instance()))



class ApplicationPrivate;
class Application : public QApplication
{
    Q_OBJECT
    Q_DISABLE_COPY(Application)
public:
    explicit Application(int &argc, char **argv);

    bool setWindowWidget(QWidget *windowWidget);
    bool setWindowWallPaper(const QString &path);
    bool callBackPressed();
    bool callLanguageChanged();

    bool startApplication(AppType type,char **argv= 0);
    //bool startView(AppType type,char **argv= 0);
    bool sendBroadcast(AppType type,OMessage &msg);
    bool onReceiveBroadcast(AppType type,OMessage &msg);
    bool sendCmdTo(AppType type,OMessage &msg);
    bool onReceiveCmd(AppType type,OMessage &msg);

#if (APP_WITH_SIMULATION == 1)
    bool setSimulation(Simulation *simu);
#endif

private:
    bool onCreate(AppType type);
    bool onStart(AppType type);
    bool onResume(AppType type);
    bool onPause(AppType type);
    bool onStop(AppType type);
    bool onDestroy(AppType type);
    bool onBackPressed(AppType type);
    bool onLanguageChanged(AppType type);

    Q_DECLARE_PRIVATE(Application)
    ApplicationPrivate * const d_ptr;

};

class ApplicationPrivate :public QObject{
    Q_OBJECT
    Q_DISABLE_COPY(ApplicationPrivate)
public:
    explicit ApplicationPrivate(Application *parent);
    ~ApplicationPrivate(){delete q_ptr;}

private:
    //data
    QMap <AppType,Context*> mAppMaps;
    Context * mStateBar;
    QStack <AppType> mAppStack;
    AppType mCurApp;

#if (APP_WITH_SIMULATION == 1)
    QWidget *mSimulationWindowWidget;
    Simulation *mSimulation;
#endif
    QWidget *mWindowWidget;
    QWidget *mWindowWallPaper;

    QWidget *mTopBarWidget;
    QWidget *mContentViewWidget;

    Q_DECLARE_PUBLIC(Application)
    Application * const q_ptr;

private slots:

};

#endif // APPLICATION_H
