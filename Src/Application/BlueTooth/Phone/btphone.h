#ifndef BTPHONE_H
#define BTPHONE_H

#include "Src/Framework/Base/Core/activity.h"


class BtphonePrivate;
class Btphone : public Activity
{
    Q_OBJECT
    Q_DISABLE_COPY(Btphone)

public:

    Btphone(QObject *parent = 0);

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
    Q_DECLARE_PRIVATE(Btphone)
    BtphonePrivate* const d_ptr;

};

class BtphonePrivate :public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(BtphonePrivate)
public:
    explicit BtphonePrivate(Btphone* parent);
    ~BtphonePrivate(){delete q_ptr;}
    void initializeBasicWidget(QWidget *parent);

private:
    Q_DECLARE_PUBLIC(Btphone)
    Btphone* const q_ptr;

    //----------
    BmpWidget *mBackground;
    BmpButton *mBtnTest;
    //----------
private slots:
    void onBtnTestRelease();

};

#endif // BTPHONE_H
