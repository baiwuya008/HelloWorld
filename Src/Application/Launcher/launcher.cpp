#include "launcher.h"


LauncherPrivate::LauncherPrivate(Launcher *parent)
    :QObject(),q_ptr(parent)

{
}

void LauncherPrivate::initializeToolsWidget(QWidget *parent)
{
    QList<QString> list;
    list.append(tr("多媒体"));
    mMediaToolsWidget = new MediaToolsWidget(parent, list);
    connect(mMediaToolsWidget, SIGNAL(onItemClick(int)), this, SLOT(setCurrentPageView(int)));
}

void LauncherPrivate::initializeBasicWidget(QWidget *parent)
{
    parent->setFixedSize(QSize(800, 435));
    MediaUtils::setWidgetBackground(parent, ":/img/Common/img_wap_bg.png");
    initializeToolsWidget(parent);

    initializeViewPager(parent);

    setCurrentViewPager(0);
}

void LauncherPrivate::initializeViewPager(QWidget *parent)
{
    mViewPaperWidget = new ViewPagerWidget(parent);
    mViewPaperWidget->setFixedSize(800, 384);
    mViewPaperWidget->setGeometry(0, 50, 0, 0);
    connect(mViewPaperWidget, SIGNAL(itemClick(int)), this, SLOT(onItemClick(int)));
    connect(mViewPaperWidget, SIGNAL(changeViewPager(int)), this, SLOT(setCurrentViewPager(int)));

    initializeViewPagerPoint(parent, 2);
}

void LauncherPrivate::initializeViewPagerPoint(QWidget *parent, int number)
{
    QLabel *icon = NULL;
    mPointList.clear();
    int left = 800/2 - (POINT_WIDTH*number+(number-1)*POINT_SPACE_WIDTH)/2;
    int top = 414;
    for (int i = 0; i < number; i++) {
        icon = new QLabel(parent);
        icon->setFixedSize(POINT_WIDTH, POINT_HEIGHT);
        icon->setGeometry(left, top, 0, 0);

        left += POINT_WIDTH + POINT_SPACE_WIDTH;

        mPointList.append(icon);
    }

    mPressPointPixmap = new QPixmap(":/img/Launcher/img_launcher_point_a.png");
    mNormalPointPixmap = new QPixmap(":/img/Launcher/img_launcher_point_b.png");
}

void LauncherPrivate::setCurrentViewPager(int index) {
    int count = mPointList.size();
    for (int i = 0; i < count; i++) {
        if (i == index) {
            mPointList.at(i)->setPixmap(*mPressPointPixmap);
        }else {
            mPointList.at(i)->setPixmap(*mNormalPointPixmap);
        }
    }
}

void LauncherPrivate::onItemClick(int index) {
    Q_Q(Launcher);
    switch (index) {
    case 0:
        q->startApplication(T_Radio);
        break;
    case 1:
        q->startApplication(T_RadioAm);
        break;
    case 2:
         q->startApplication(T_USBDiskMusic);
        break;
    case 3:
         q->startApplication(T_USBDiskVideo);
        break;
    case 4:
//         q->startApplication(T_Link);
        break;
    case 5:
         q->startApplication(T_Bluetooth);
        break;
    case 6:
         q->startApplication(T_USBDiskImage);
        break;
    case 7:
         q->startApplication(T_Setting);
        break;
    }
}


void LauncherPrivate::setCurrentPageView(int tabIndex)
{

}

Launcher::Launcher(QObject *parent):
    Activity(parent),
    d_ptr(new LauncherPrivate(this))
{
}

void Launcher::onCreate(QWidget *parent)
{
    Q_D(Launcher);
    d->initializeBasicWidget(parent);
}
void Launcher::onStart()
{

}
void Launcher::onResume()
{

}
void Launcher::onPause()
{

}
void Launcher::onStop()
{

}
void Launcher::onDestroy()
{

}

bool Launcher::onBackPressed()
{

    return false;
}

void Launcher::onLanguageChanged()
{

}

void Launcher::onReceiveBroadcast(AppType appType,OMessage &msg)
{

}

void Launcher::onReceiveCmd(AppType appType,OMessage &msg)
{

}

