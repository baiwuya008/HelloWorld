#ifndef SETTINGS_H
#define SETTINGS_H
#include "Src/Framework/Base/Core/activity.h"

class SettingsPrivate;
class Settings : public Activity
{

    Q_OBJECT
    Q_DISABLE_COPY(Settings)

public:

    Settings(QObject *parent = 0);

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
    Q_DECLARE_PRIVATE(Settings)
    SettingsPrivate* const d_ptr;

};

class SettingsPrivate :public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(SettingsPrivate)
public:
    explicit SettingsPrivate(Settings* parent);
    ~SettingsPrivate(){delete q_ptr;}
    void initializeBasicWidget(QWidget *parent);

private:
    Q_DECLARE_PUBLIC(Settings)
    Settings* const q_ptr;

    //----------
    BmpWidget *mBackground;
    BmpButton *mBtnTest;
    //----------
private slots:
    void onBtnTestRelease();

};

#endif // SETTINGS_H
