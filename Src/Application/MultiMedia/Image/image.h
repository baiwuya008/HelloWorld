#ifndef IMAGE_H
#define IMAGE_H

#include "Src/Framework/Base/Core/activity.h"
#include <QHBoxLayout>
#include <QPushButton>
#include "Src/CommonUserWidget\flowview.h"
#include "Src/CommonUserWidget\flowadapter.h"
#include "Src/Application/MultiMedia/Tools/mediatoolswidget.h"
#include <QList>
#include <QLabel>


class ImagePrivate;
class Image : public Activity
{
    Q_OBJECT
    Q_DISABLE_COPY(Image)
public:

    Image(QObject *parent = 0);

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

private slots:
    void prevPicture();
    void nextPicture();


private:
    Q_DECLARE_PRIVATE(Image)
    ImagePrivate* const d_ptr;

};

class ImagePrivate :public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ImagePrivate)
public:
    explicit ImagePrivate(Image* parent);
    ~ImagePrivate(){delete q_ptr;}
    void initializeBasicWidget(QWidget *parent);
    void setWidgetBackground(QWidget *widget, QString path);

private slots:
    void onPrevPicture();
    void onNextPicture();
    void onItemClick(int position, QString path);
    void onSwitchCenter(int position);
    void setCurrentPageView(int tabIndex);

private:
    Q_DECLARE_PUBLIC(Image)
    Image* const q_ptr;

    void initializeToolsWidget(QWidget *parent);
    void initializeFlowView(QWidget *parent);
    void initListData();
    void initializeBottomView(QWidget *parent);
    void initLabText(QLabel *text, int size);
    void setCurrentTab();

    MediaToolsWidget *mMediaToolsWidget = NULL;
    FlowView *mFlowView = NULL;
    FlowAdapter *mFlowAdapter = NULL;
    QList<QString> mList;
    QLabel *mTabLabel = NULL;


    //----------
    BmpWidget *mBackground;
    BmpButton *mBtnTest;
    //----------
private slots:
    void onBtnTestRelease();


};

#endif // IMAGE_H
