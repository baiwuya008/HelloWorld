#ifndef IPOD_H
#define IPOD_H

#include "Src/Framework/Base/Core/activity.h"


class IpodPrivate;
class Ipod : public Activity
{
    Q_OBJECT
    Q_DISABLE_COPY(Ipod)

public:

    Ipod(QObject *parent = 0);

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
    Q_DECLARE_PRIVATE(Ipod)
    IpodPrivate* const d_ptr;

};

class IpodPrivate :public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(IpodPrivate)
public:
    explicit IpodPrivate(Ipod* parent);
    ~IpodPrivate(){delete q_ptr;}
    void initializeBasicWidget(QWidget *parent);

private:
    Q_DECLARE_PUBLIC(Ipod)
    Ipod* const q_ptr;

    //----------
    BmpWidget *mBackground;
    BmpButton *mBtnTest;
    //----------
private slots:
    void onBtnTestRelease();

};

#endif // IPOD_H
