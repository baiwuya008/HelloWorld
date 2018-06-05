#ifndef AVIN_H
#define AVIN_H

#include "Src/Framework/Base/Core/activity.h"


class AvinPrivate;
class Avin : public Activity
{
    Q_OBJECT
    Q_DISABLE_COPY(Avin)

public:

    Avin(QObject *parent = 0);

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
    Q_DECLARE_PRIVATE(Avin)
    AvinPrivate* const d_ptr;

};

class AvinPrivate :public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(AvinPrivate)
public:
    explicit AvinPrivate(Avin* parent);
    ~AvinPrivate(){delete q_ptr;}
    void initializeBasicWidget(QWidget *parent);

private:
    Q_DECLARE_PUBLIC(Avin)
    Avin* const q_ptr;

    //----------
    BmpWidget *mBackground;
    BmpButton *mBtnTest;
    //----------
private slots:
    void onBtnTestRelease();

};

#endif // AVIN_H
