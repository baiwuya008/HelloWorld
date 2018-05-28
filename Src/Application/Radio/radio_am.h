#ifndef RADIO_AM_H
#define RADIO_AM_H

#include "Src/Framework/Base/Core/activity.h"


class RadioAmPrivate;
class RadioAm : public Activity
{
    Q_OBJECT
    Q_DISABLE_COPY(RadioAm)

public:

    RadioAm(QObject *parent = 0);

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
    Q_DECLARE_PRIVATE(RadioAm)
    RadioAmPrivate* const d_ptr;

};

class RadioAmPrivate :public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(RadioAmPrivate)
public:
    explicit RadioAmPrivate(RadioAm* parent);
    ~RadioAmPrivate(){delete q_ptr;}
    void initializeBasicWidget(QWidget *parent);

private:
    Q_DECLARE_PUBLIC(RadioAm)
    RadioAm* const q_ptr;

    //----------
    BmpWidget *mBackground;
    BmpButton *mBtnTest;
    //----------
private slots:
    void onBtnTestRelease();

};

#endif // RADIO_AM_H
