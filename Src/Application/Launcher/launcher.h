#ifndef LAUNCHER_H
#define LAUNCHER_H
#include "Src/Framework/Base/Core/activity.h"

class LauncherPrivate;

class Launcher : public Activity
{
    Q_OBJECT
    Q_DISABLE_COPY(Launcher)

public:
    Launcher(QObject *parent = 0);

    void onCreate(QWidget *parent=0);
    void onStart();
    void onResume();
    void onPause();
    void onStop();
    void onDestroy();
    bool onBackPressed();
    void onLanguageChanged();
    void onReceiveBroadcast(AppType appType,OMessage &msg);
    void onReceiveCmd(AppType appType,OMessage &msg);

private:
    Q_DECLARE_PRIVATE(Launcher)
    LauncherPrivate* const d_ptr;


};

class LauncherPrivate :public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(LauncherPrivate)

public:
    explicit LauncherPrivate(Launcher* parent);
    ~LauncherPrivate(){delete q_ptr;}
    void initializeBasicWidget(QWidget *parent);

private:
    Q_DECLARE_PUBLIC(Launcher)
    Launcher* const q_ptr;

    //----------
    BmpWidget *mBackground;

    BmpButton *mBtnFm;
    BmpButton *mBtnAm;
    BmpButton *mBtnMusic;
    BmpButton *mBtnVideo;
    BmpButton *mBtnElink;
    BmpButton *mBtnBlueTooth;
    BmpButton *mBtnImage;
    BmpButton *mBtnSettings;
    BmpButton *mBtnAvin; //Aux
    //----------
private slots:
    void onBtnFmRelease();
    void onBtnAmRelease();
    void onBtnMusicRelease();
    void onBtnVideoRelease();
    void onBtnElinkRelease();
    void onBtnBlueToothRelease();
    void onBtnImagetRelease();
    void onBtnSettingsRelease();
    void onBtnAvinRelease();


};


#endif // LAUNCHER_H
