#ifndef IMAGE_H
#define IMAGE_H

#include "Src/Framework/Base/Core/activity.h"
#include <QHBoxLayout>
#include <QPushButton>
#include "Src/CommonUserWidget/flowview.h"
#include "Src/CommonUserWidget/flowadapter.h"
#include "Src/Application/MultiMedia/Tools/mediatoolswidget.h"
#include "Src/Application/MultiMedia/multimedia.h"
#include <QList>
#include <QLabel>
#include <QHBoxLayout>


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

private slots:
    void setCurrentPageView(int tabIndex);
    void onPrev();
    void onNext();
    void onItemClick(int position, QString path);
    void setCenterTab(int position, int size);

    void setPlayItem(int deviceType, QString filePath);
    void scanImageFiles(int deviceType, int queryMode, QString dirPath, QStringList& pathList);

private:
    Q_DECLARE_PUBLIC(Image)
    Image* const q_ptr;

    void initializeToolsWidget(QWidget *parent);
    void initializeFlowView(QWidget *parent);
    void initializeFullView(QWidget *parent);
    void initializeBottomView(QWidget *parent);
    void connectAllSlots();
    void showView(bool isFull);
    bool isBackPressed();

    QList<QString> initTestList();
    int mCurrentDeviceType = -1;
    bool isShowFull = false;

    QWidget *mBottomWidget = NULL;
    QHBoxLayout *mBottomLayout = NULL;
    BmpButton *prevBtn = NULL;
    BmpButton *nextBtn = NULL;

    MediaToolsWidget *mMediaToolsWidget = NULL;
    FlowView *mFlowView = NULL;
    FlowAdapter *mFlowAdapter = NULL;
    QLabel *mTabLabel = NULL;

    QWidget *mFullWidget = NULL;
    QHBoxLayout *mFullLayout = NULL;
    QLabel *mFullPicture = NULL;

private slots:
    void onBtnTestRelease();


};

#endif // IMAGE_H
