#ifndef SETTINGS_H
#define SETTINGS_H
#include "Src/Framework/Base/Core/activity.h"

#include <QMouseEvent>
#include <QLabel>

class SettingsPrivate;
class Settings : public Activity
{

    Q_OBJECT
    Q_DISABLE_COPY(Settings)

public:

    Settings(QObject *parent = 0);

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
    Q_DECLARE_PRIVATE(Settings)
    SettingsPrivate* const d_ptr;

};

class SettingsPrivate :public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(SettingsPrivate)
public:
    explicit SettingsPrivate(Settings* parent);
    ~SettingsPrivate(){delete q_ptr;}
    void initializeBasicWidget(QWidget *parent);


private:
    void selectTab(int index);

protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent*e);

private:
    Q_DECLARE_PUBLIC(Settings)
    Settings* const q_ptr;

    //----------
    BmpWidget *mBackTitle;
    BmpWidget *mBackground;
    BmpButton *mBtnTest;
    //----------`

    BmpButton *mBmpSoundTab;
    BmpButton *mBmpBrightnessTab;
    BmpButton *mBmpSystemTab;

    BmpWidget *mBmpSound;
    BmpWidget *mBmpBrightness;
    BmpWidget *mBmpSystem;

    BmpButton *mBmpCentre;
    BmpWidget *mSoundControlGroup;
    BmpButton *mTopControl;
    BmpButton *mBottomControl;
    BmpButton *mLeftControl;
    BmpButton *mRightControl;
    BmpButton *mSeatPoint;

    bool isClickTouch;

    QLabel * mSoundSLabel;

    BmpButton* mKeySoundSwitch;
    bool isKeySound = true;

    BmpButton * mLowSoundLeft;
    BmpButton * mLowSoundRight;
    BmpButton * mLowSoundPoint;
    BmpWidget * mLowSoundBg;
    QLabel * mLabelLowSound;

    BmpButton * mCenSoundLeft;
    BmpButton * mCenSoundRight;
    BmpButton * mCenSoundPoint;
    BmpWidget * mCenSoundBg;
    QLabel * mLabelCenSound;

    BmpButton * mHeightSoundLeft;
    BmpButton * mHeightSoundRight;
    BmpButton * mHeightSoundPoint;
    BmpWidget * mHeightSoundBg;
    QLabel * mLabelHeightSound;

private slots:
    void onBtnTestRelease();

    void onBtnSoundTabClick();
    void onBtnBrightnessTabClick();
    void onBtnSystemTabClick();

    void onBtnCentreClick();

    void onBtnSoundTopClick();
    void onBtnSoundBottomClick();
    void onBtnSoundLeftClick();
    void onBtnSoundRightClick();

    void onBtnKeySoundtClick();

};

#endif // SETTINGS_H
