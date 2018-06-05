#ifndef RADIO_H
#define RADIO_H

#include "Src/Framework/Base/Core/activity.h"


class RadioPrivate;
class Radio : public Activity
{
    Q_OBJECT
    Q_DISABLE_COPY(Radio)

public:

    Radio(QObject *parent = 0);

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
    Q_DECLARE_PRIVATE(Radio)
    RadioPrivate* const d_ptr;

};

class RadioPrivate :public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(RadioPrivate)
public:
    explicit RadioPrivate(Radio* parent);
    ~RadioPrivate(){delete q_ptr;}
    void initializeBasicWidget(QWidget *parent);

private:
    Q_DECLARE_PUBLIC(Radio)
    Radio* const q_ptr;

    //----------
    BmpWidget *mBackground;
    BmpButton *mBtnTest;
    //----------
private slots:
    void onBtnTestRelease();

};

#endif // RADIO_H
