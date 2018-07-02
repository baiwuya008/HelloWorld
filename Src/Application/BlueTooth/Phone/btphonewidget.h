#ifndef BTPHONEWIDGET_H
#define BTPHONEWIDGET_H

#include <QWidget>
#include "phonerecordwidget.h"
#include "phonedialwidget.h"
#include "Src/Framework/Base/Core/activity.h"

class BtPhoneWidgetPrivate;
class BtPhoneWidget : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(BtPhoneWidget)
public:
    explicit BtPhoneWidget(QWidget *parent = 0);
    ~BtPhoneWidget();

private:
    Q_DECLARE_PRIVATE(BtPhoneWidget)
    BtPhoneWidgetPrivate* const d_ptr;

public slots:
};

class BtPhoneWidgetPrivate :public QObject{
    Q_OBJECT
    Q_DISABLE_COPY(BtPhoneWidgetPrivate)

public:
    explicit BtPhoneWidgetPrivate(BtPhoneWidget *parent);
    ~BtPhoneWidgetPrivate();

    void initializeBasicWidget(QWidget *parent);
    void initToolbarText(BmpButton *btn);

private:
    Q_DECLARE_PUBLIC(BtPhoneWidget)
    BtPhoneWidget* const q_ptr;

    //tab分页标题
    BmpWidget *mPhoneTitle;
    BmpButton *mBmpDialTab;
    BmpButton *mBmpRecordTab;
    BmpButton *mBmpOptionsTab;

    //widget 主布局
    PhoneDialWidget *mBmpDialWidget;
    PhoneRecordWidget *mBmpRecordWidget;
    BmpWidget *mBmpOptionsWidget;

private slots:

    void switchPage(int index);
    void onBtnDialTabClick();
    void onBtnRecordTabClick();
    void onBtnOptionsTabClick();
};

#endif // BTPHONEWIDGET_H
