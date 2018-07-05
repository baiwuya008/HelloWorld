#ifndef BTMUSIC_H
#define BTMUSIC_H

#include "Src/Framework/Base/Core/activity.h"
#include "Src/Application/MultiMedia/BtMusic/btmusicwidget.h"

class BtmusicPrivate;
class Btmusic : public Activity
{
    Q_OBJECT
    Q_DISABLE_COPY(Btmusic)

public:

    Btmusic(QObject *parent = 0);

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
    Q_DECLARE_PRIVATE(Btmusic)
    BtmusicPrivate* const d_ptr;

};


class BtmusicPrivate :public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(BtmusicPrivate)
public:
    explicit BtmusicPrivate(Btmusic* parent);
    ~BtmusicPrivate(){delete q_ptr;}
    void initializeBasicWidget(QWidget *parent);

private:
    Q_DECLARE_PUBLIC(Btmusic)
    Btmusic* const q_ptr;

    BtMusicWidget *mBtMusicWidget = NULL;
private slots:
    void onBtnTestRelease();

};

#endif // BTMUSIC_H
