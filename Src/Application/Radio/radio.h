#ifndef RADIO_H
#define RADIO_H

#include "Src/Framework/Base/Core/activity.h"
#include <QStackedLayout>
#include <QList>
#include <QPoint>
#include <QStandardItemModel>
#include <QMouseEvent>
#include <QRect>
#include <QScopedPointer>
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QModelIndex>
#include <QAbstractItemModel>
#include <QPixmap>


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

//----------
class RadioPresetFreqDelegate : public CustomItemDelegate
{
    Q_OBJECT
    Q_DISABLE_COPY(RadioPresetFreqDelegate)
public:
    explicit RadioPresetFreqDelegate(RadioPrivate *radioPri,QObject* parent = NULL);
    ~RadioPresetFreqDelegate();

protected:

    void paint(QPainter* painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const;
private:
    void mousePressEvent(QMouseEvent* event,
                                 QAbstractItemModel *model,
                                 const QStyleOptionViewItem &option,
                                 const QModelIndex &index);
    void mouseMoveEvent(QMouseEvent* event,
                                QAbstractItemModel *model,
                                const QStyleOptionViewItem &option,
                                const QModelIndex &index);
    void mouseReleaseEvent(QMouseEvent* event,
                                   QAbstractItemModel *model,
                                   const QStyleOptionViewItem &option,
                                   const QModelIndex &index);

    bool editorEvent(QEvent* event,
                     QAbstractItemModel *model,
                     const QStyleOptionViewItem &option,
                     const QModelIndex &index);

protected slots:
    void onCurrentIndexChange(const QModelIndex &index);
    void onPressIndexChanged(const QModelIndex &index);
private:
    const RadioPrivate *mRadioPri;
    QModelIndex m_PressIndex;
    QModelIndex m_CurIndex;
    QPoint m_StartMovePoint;
    QScopedPointer<QPixmap> m_Interval_Line;
    QScopedPointer<QPixmap> m_SaveIconNormal;
    QScopedPointer<QPixmap> m_SaveIconPressed;
    QScopedPointer<QPixmap> m_RemoveIconNormal;
    QScopedPointer<QPixmap> m_RemoveIconPressed;
    const QRect mFunIconRect;
    friend class RadioPrivate;

};

//----------
class RadioListFreqDelegate : public CustomItemDelegate
{
    Q_OBJECT
    Q_DISABLE_COPY(RadioListFreqDelegate)
public:
    explicit RadioListFreqDelegate(RadioPrivate *radioPri,QObject* parent = NULL);
    ~RadioListFreqDelegate();
protected:
    void paint(QPainter* painter,
               const QStyleOptionViewItem &option,
               const QModelIndex &index) const;
private:
    void mousePressEvent(QMouseEvent* event,
                                 QAbstractItemModel *model,
                                 const QStyleOptionViewItem &option,
                                 const QModelIndex &index);
    void mouseMoveEvent(QMouseEvent* event,
                                QAbstractItemModel *model,
                                const QStyleOptionViewItem &option,
                                const QModelIndex &index);
    void mouseReleaseEvent(QMouseEvent* event,
                                   QAbstractItemModel *model,
                                   const QStyleOptionViewItem &option,
                                   const QModelIndex &index);


protected slots:
    void onCurrentIndexChange(const QModelIndex &index);
    void onPressIndexChanged(const QModelIndex &index);
private:
    const RadioPrivate *mRadioPri;
    QModelIndex m_PressIndex;
    QModelIndex m_CurIndex;
    QPoint m_StartMovePoint;
    QScopedPointer<QPixmap> m_Interval_Line;
    friend class RadioPrivate;

};


//----------
class RadioProcess;
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

    friend class RadioPresetFreqDelegate;
    friend class RadioListFreqDelegate;

    RadioProcess *mProcess;
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
    Slider    *mFmFreqBarSlider;

    QStackedLayout *mBottomBarLayout;
    QWidget *mBottomBar;
    BmpWidget *mBottom_Fm;
    BmpWidget *mBottom_Preset;
    BmpWidget *mBottom_List;

    BmpButton *mBottom_Fm_Prev;
    BmpButton *mBottom_Fm_Seek_Prev;
    BmpButton *mBottom_Fm_Seek_Next;
    BmpButton *mBottom_Fm_Next;

    BmpButton *mBottom_Preset_Seek_Prev;
    BmpButton *mBottom_Preset_AutoSearch;
    BmpButton *mBottom_Preset_Seek_Next;

    BmpButton *mBottom_List_Seek_Prev;
    BmpButton *mBottom_List_Search;
    BmpButton *mBottom_List_Seek_Next;

    CustomListView *mRadioPresetFragmentListView;
    CustomScrollBar *mRadioPresetFragmentListViewScrollBar;
    RadioPresetFreqDelegate *mRadioPresetDelegate;
    QStandardItemModel *mRadioPresetStandardItemModel;

    CustomListView *mRadioListFragmentListView;
    CustomScrollBar *mRadioListFragmentListViewScrollBar;
    RadioListFreqDelegate *mRadioListDelegate;
    QStandardItemModel *mRadioListStandardItemModel;

    Tab mTab;

    void tabSwitch(const Tab mytab);
    void initRadioFmFragment();
    void initRadioPresetFragment();
    void initRadioPresetData();
    void initRadioListFragment();
    void initRadioListData();

public slots:
    //----------
    void doReFreshCurFreq(const double &curFreq,bool updatePreset=false,bool updateList=false);
    void doReFreshPresetFreqs(const QList<double> &presetFreqs);
    void doReFreshListFreqs(const QList<double> &listFreqs);
    //----------
private slots:
    void onBtnTabFm();
    void onBtnTabPreset();
    void onBtnTabList();

    void onBtnBottomFmPrev();
    void onBtnBottomFmSeekPrev();
    void onBtnBottomFmSeekNext();
    void onBtnBottomFmNext();

    void onBtnBottomPresetSeekPrev();
    void onBtnBottomPresetAutoSearch();
    void onBtnBottomPresetSeekNext();

    void onBtnBottomListSeekPrev();
    void onBtnBottomListSearch();
    void onBtnBottomListSeekNext();

    void doSliderPressed(const int value);
    void doSliderMoved(const int value);
    void doSliderReleased(const int value);

};

#endif // RADIO_H
