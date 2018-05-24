#ifndef AUX_H
#define AUX_H

#include "Src/Framework/Base/Core/activity.h"


class AuxPrivate;
class Aux : public Activity
{
    Q_OBJECT
    Q_DISABLE_COPY(Aux)

public:

    Aux(QObject *parent = 0);

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
    Q_DECLARE_PRIVATE(Aux)
    AuxPrivate* const d_ptr;

};

class AuxPrivate :public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(AuxPrivate)
public:
    explicit AuxPrivate(Aux* parent);
    ~AuxPrivate(){delete q_ptr;}
    void initializeBasicWidget(QWidget *parent);

private:
    Q_DECLARE_PUBLIC(Aux)
    Aux* const q_ptr;

    //----------
    BmpWidget *mBackground;
    BmpButton *mBtnTest;
    //----------
private slots:
    void onBtnTestRelease();

};

#endif // AUX_H
