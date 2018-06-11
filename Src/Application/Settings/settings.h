#ifndef SETTINGS_H
#define SETTINGS_H
#include "Src/Framework/Base/Core/activity.h"
#include "configuration.h"

#include <QMouseEvent>
#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>
#include <QModelIndex>
#include <QDialog>
#include <QMenu>
#include <QSettings>
#include <QCoreApplication>
#include "wheelview.h"
#include <QDate>

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
    void initLanguageDialog();
    void initTimeSetDialog();
    void initResetBtDialog();
    void initSystemList(QString language);

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

    BmpWidget *mBmpDisplayImg;

    BmpButton * mDisplayLeft;
    BmpButton * mDisplayRight;
    BmpButton * mDisplayPoint;
    BmpWidget * mDisplayBg;
    QLabel * mLabelmDisplay;

    QListWidget* mListWidget;

    bool isEventSeatPoint;
    bool isEventSoundLow;
    bool isEventSoundCentre;
    bool isEventSoundHeight;

    QSlider* mLowSoundSlider;
    QSlider* mCenSoundSlider;
    QSlider* mHeightSoundSlider;
    QSlider* mDisplaySlider;

    QStringList mListSystem;

    QDialog* mLanguageDialog;
    QStringList listLanguage;

    QDialog* mTimeSetDialog;
    QDialog* mReSetBtDialog;

    //当前语言
    QString currentLanguage;

    QSettings settings;

    const int LINE_MIN = 5;
    const int LINE_MAX = 95;

    //当前时间格式
    int formats;

    WheelView * mWheelView;
    //当前日期
    QDate date;

    BmpButton* mBmpSetSyTime;

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

    void onSeatPointDown();
    void onSeatPointUp();

    void onLowSoundValuesChange(int);
    void onCenSoundValuesChange(int);
    void onHeightSoundValuesChange(int);

    void onBrightnessValuesChange(int);

    void onSystemListLanguagePressed(QModelIndex);
    void onLanguageSelectPressed(QModelIndex);

    //------------
    void onBmpSoundWidgetMove(QMouseEvent*e);

    void onBmpTimeSetPressed();

    void onResetDialogOkPressed();
    void onResetDialogNoPressed();
};

#endif // SETTINGS_H
