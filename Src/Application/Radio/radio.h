#ifndef RADIO_H
#define RADIO_H

#include "Src/Framework/Base/Core/activity.h"
#include<QStackedLayout>

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
    BmpWidget *mTabBar;
    BmpButton *mStateBarTab_FM;
    TextWidget *mTabFmTextView;
    BmpButton *mStateBarTab_Preset;
    TextWidget *mTabPresetTextView;
    BmpButton *mStateBarTab_List;
    TextWidget *mTabListTextView;

    QStackedLayout *mFragmentViewLayout;
    QWidget *mFmFragmentView;
    QWidget *mPresetFragmentView;
    QWidget *mListFragmentView;

    QStackedLayout *mBottomBarLayout;
    BmpWidget *mBottomBar;
    QWidget *mBottom_Fm;
    QWidget *mBottom_Preset;
    QWidget *mBottom_List;

    //----------
private slots:
    void onBtnTestRelease();

};

#endif // RADIO_H
