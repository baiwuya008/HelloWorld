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

    enum Tab{
        FM =0,
        PRESET,
        LIST,
    };

private:
    Q_DECLARE_PUBLIC(Radio)
    Radio* const q_ptr;

    //----------
    BmpWidget *mTabBar;
    BmpButton *mStateBarTab_FM;
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
    BmpWidget *mBottom_Fm;
    BmpWidget *mBottom_Preset;
    BmpWidget *mBottom_List;

    BmpButton *mBottom_Fm_Prev;
    BmpButton *mBottom_Fm_Seek_Prev;
    BmpButton *mBottom_Fm_Seek_Next;
    BmpButton *mBottom_Fm_Next;

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
    void onBtnTabFm();
    void onBtnTabPreset();
    void onBtnTabList();

};

#endif // RADIO_H
