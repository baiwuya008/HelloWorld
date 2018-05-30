#ifndef SYSTEMUI_H
#define SYSTEMUI_H

#include "Src/Framework/Base/Core/activity.h"
#include "configuration.h"

#include <QLabel>
#include <QTime>
#include <QDebug>
#include <QString>

class SystemuiPrivate;
class Systemui : public Activity
{
    Q_OBJECT
    Q_DISABLE_COPY(Systemui)

public:

    Systemui(QObject *parent = 0);

    void onCreate(QWidget *parent=0);
    void onStart();
    void onResume();
    void onDestroy();
    void onLanguageChanged();
    void onReceiveBroadcast(AppType appType,OMessage &msg);
    void onReceiveCmd(AppType appType,OMessage &msg);

private:
    Q_DECLARE_PRIVATE(Systemui)
    SystemuiPrivate* const d_ptr;

};

class SystemuiPrivate :public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(SystemuiPrivate)
public:
    explicit SystemuiPrivate(Systemui* parent);
    ~SystemuiPrivate(){delete q_ptr;}
    void initializeBasicWidget(QWidget *parent);

private:
    Q_DECLARE_PUBLIC(Systemui)
    Systemui* const q_ptr;

    //----------
    BmpWidget *mBackground;
#if (STATEBAR_WITH_BACK == 1)
    BmpButton *mBtnBack;
#endif
#if (STATEBAR_WITH_HOME == 1)
    BmpButton *mBtnHome;
#endif

    //----------
private slots:
    void onBtnBackRelease();
    void onBtnHomeRelease();

};

#endif // SYSTEMUI_H
