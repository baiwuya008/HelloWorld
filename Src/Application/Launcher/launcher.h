#ifndef LAUNCHER_H
#define LAUNCHER_H
#include "Src/Framework/Base/Core/activity.h"
#include "Src/Application/MultiMedia/Tools/mediatoolswidget.h"
#include "viewpagerwidget.h"
#include <QList>
#include <QLabel>

class LauncherPrivate;

class Launcher : public Activity
{
    Q_OBJECT
    Q_DISABLE_COPY(Launcher)

public:
    Launcher(QObject *parent = 0);

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
    Q_DECLARE_PRIVATE(Launcher)
    LauncherPrivate* const d_ptr;


};

class LauncherPrivate :public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(LauncherPrivate)
public:
    explicit LauncherPrivate(Launcher* parent);
    ~LauncherPrivate(){delete q_ptr;}
    void initializeBasicWidget(QWidget *parent);
private slots:
    void setCurrentPageView(int tabIndex);
    void onItemClick(int index);

private:
    Q_DECLARE_PUBLIC(Launcher)
    Launcher* const q_ptr;

    void setWidgetBackground(QWidget *widget, QString path);
    void initializeToolsWidget(QWidget *parent);
    void initializeViewPager(QWidget *parent);
    void initializeViewPagerPoint(QWidget *parent, int number);
    void setCurrentViewPager(int index);

    inline QPixmap getPixmap(QString path) {
        QImage image;
        image.load(path);
        return QPixmap::fromImage(image);
    }


    MediaToolsWidget *mMediaToolsWidget = NULL;
    ViewPagerWidget *mViewPaperWidget = NULL;
    QList<QLabel*> mPointList;
    QPixmap *mNormalPointPixmap = NULL;
    QPixmap *mPressPointPixmap = NULL;

    const int POINT_SPACE_WIDTH = 38;
    const int POINT_WIDTH = 12;
    const int POINT_HEIGHT = 12;

};


#endif // LAUNCHER_H
