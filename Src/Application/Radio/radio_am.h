#ifndef RADIO_AM_H
#define RADIO_AM_H

#include "Src/Framework/Base/Core/activity.h"
#include<QStackedLayout>

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
    enum Tab{
        AM =0,
        PRESET,
        LIST,
    };
private:
    Q_DECLARE_PUBLIC(RadioAm)
    RadioAm* const q_ptr;

    //----------
    //----------
    BmpWidget *mTabBar;
    BmpButton *mStateBarTab_AM;
    BmpButton *mStateBarTab_Preset;
    BmpButton *mStateBarTab_List;

    QStackedLayout *mFragmentViewLayout;
    QWidget *mFmFragmentContain;
    QWidget *mFmFragmentView;
    QWidget *mPresetFragmentView;
    QWidget *mListFragmentView;

    BmpWidget *mFmFragment_FreqBg;
    TextWidget *mFmFragment_FreqText;
    BmpWidget *mFmFragment_ScaleBarBg;
    BmpWidget *mFmFragment_ScalePointer;

    QStackedLayout *mBottomBarLayout;
    QWidget *mBottomBar;
    BmpWidget *mBottom_Am;
    BmpWidget *mBottom_Preset;
    BmpWidget *mBottom_List;

    BmpButton *mBottom_Am_Prev;
    BmpButton *mBottom_Am_Seek_Prev;
    BmpButton *mBottom_Am_Seek_Next;
    BmpButton *mBottom_Am_Next;

    BmpButton *mBottom_Preset_PageUp;
    BmpButton *mBottom_Preset_AutoSearch;
    BmpButton *mBottom_Preset_PageDown;

    BmpButton *mBottom_List_PageUp;
    BmpButton *mBottom_List_Search;
    BmpButton *mBottom_List_PageDown;

    Tab mTab;

    void tabSwitch(const Tab mytab);
    //----------
private slots:
    void onBtnTabAm();
    void onBtnTabPreset();
    void onBtnTabList();

};

#endif // RADIO_AM_H
