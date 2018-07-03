#include "image.h"


ImagePrivate::ImagePrivate(Image *parent)
    : QObject(),q_ptr(parent)
{
}

void ImagePrivate::initializeBasicWidget(QWidget *parent)
{
    Q_Q(Image);
    MediaUtils::setWidgetBackground(parent, ":/img/Common/img_wap_bg.png");
    initializeToolsWidget(parent);
    initializeFullView(parent);
    initializeFlowView(parent);
    initializeBottomView(parent);
    connectAllSlots();

    showView(false);
    setCenterTab(0, 0);
    //test
    g_Multimedia->setPlayStatus(MediaUtils::IMAGE, true);
}

void ImagePrivate::initializeToolsWidget(QWidget *parent) {
    QList<QString> list;
    list.append("照片");
    mMediaToolsWidget = new MediaToolsWidget(parent, list);
    connect(mMediaToolsWidget, SIGNAL(onItemClick(int)), this, SLOT(setCurrentPageView(int)));
}

void ImagePrivate::setCurrentPageView(int tabIndex) {
}

void ImagePrivate::setPlayItem(int deviceType, QString filePath)
{
    g_Multimedia->setPlayPath(MediaUtils::IMAGE, deviceType, filePath);
}

void ImagePrivate::backScanFiles(int deviceType, int queryMode, QString dirPath, QStringList &pathList)
{
    this->mCurrentDeviceType = deviceType;
    mFlowAdapter->setInfoList(pathList);
}

void ImagePrivate::initializeFlowView(QWidget *parent)
{
    Q_Q(Image);
    mFlowView = new FlowView(parent);
    mFlowView->setFixedSize(800, 324);
    mFlowView->setGeometry(0, 50, 0, 0);
    mFlowView->setParent(parent);
    mFlowAdapter = new FlowAdapter(parent);
    mFlowView->setAdapter(mFlowAdapter);
}

void ImagePrivate::initializeFullView(QWidget *parent)
{
    mFullWidget = new QWidget(parent);
    mFullWidget->setFixedSize(800, 385);
    mFullWidget->setGeometry(0, 50, 0, 0);
    mFullWidget->setParent(parent);
    mFullLayout = new QHBoxLayout();
    mFullLayout->setContentsMargins(0, 0, 0, 0);
    mFullWidget->setLayout(mFullLayout);

    mFullPicture = new QLabel(parent);
    mFullLayout->addWidget(mFullPicture, 0, Qt::AlignCenter);
}

void ImagePrivate::setCenterTab(int position, int size)
{
    if (size > 0) {
        if (isShowFull && mFlowAdapter != NULL) {
            mFullPicture->setPixmap(MediaUtils::getPixmap(mFlowAdapter->getPath(position)));
        }
        mTabLabel->setText(QString::number(position+1)+"/"+QString::number(size));
        setPlayItem(mCurrentDeviceType, mFlowAdapter->getPath(position));
    }else {
        mTabLabel->setText("0/0");
    }
}

void ImagePrivate::onItemClick(int position, QString path) {
    mFullPicture->setPixmap(MediaUtils::getPixmap(path));
    if (!isShowFull) {
        showView(true);
    }
    mFlowAdapter->setCenterPosition(position);
}


QList<QString> ImagePrivate::initTestList()
{
    QList<QString> list;
    list.append(":/picture_test/music_1.jpeg");
    list.append(":/picture_test/music_2.jpeg");
    list.append(":/picture_test/music_3.jpeg");
    list.append(":/picture_test/music_4.jpeg");
    list.append(":/picture_test/music_5.jpeg");
    list.append(":/picture_test/music_6.jpeg");
    list.append(":/picture_test/music_7.jpeg");
    list.append(":/picture_test/music_8.jpeg");
    return list;
}

void ImagePrivate::initializeBottomView(QWidget *parent)
{
    mBottomWidget = new QWidget(parent);
    mBottomWidget->setFixedSize(QSize(800, 45));
    mBottomWidget->setGeometry(0, 376, 0, 0);

    mBottomLayout = new QHBoxLayout();
    mBottomWidget->setLayout(mBottomLayout);
    mBottomLayout->setContentsMargins(0, 0, 0, 0);

    prevBtn = new BmpButton(mBottomWidget);
    prevBtn->setFixedSize(QSize(46, 45));
    prevBtn->setNormalBmpPath(":/img/setting/img_sound_seat_left_a.png");
    prevBtn->setPressBmpPath(":/img/setting/img_sound_seat_left_b.png");
    prevBtn->setGeometry(180, 0, 0, 0);


    nextBtn = new BmpButton(mBottomWidget);
    nextBtn->setFixedSize(QSize(46, 45));
    nextBtn->setNormalBmpPath(":/img/setting/img_sound_seat_right_a.png");
    nextBtn->setPressBmpPath(":/img/setting/img_sound_seat_right_b.png");
    nextBtn->setGeometry(575, 0, 0, 0);



    mTabLabel = new QLabel();
    MediaUtils::setLabText(mTabLabel, 20);
    mTabLabel->setText("3/10");
    mBottomLayout->addWidget(mTabLabel, 0, Qt::AlignCenter);
}

void ImagePrivate::connectAllSlots()
{
    connect(mFlowView, SIGNAL(itemClick(int,QString)), this, SLOT(onItemClick(int,QString)));
    connect(mFlowView, SIGNAL(switchCenterView(int,int)), this, SLOT(setCenterTab(int,int)));

    connect(prevBtn, SIGNAL(released()), this, SLOT(onPrev()));
    connect(nextBtn, SIGNAL(released()), this, SLOT(onNext()));

    connect(g_Multimedia, SIGNAL(onScanImageFiles(int,int,QString,QStringList&)), this, SLOT(backScanFiles(int,int,QString,QStringList&)));
}

void ImagePrivate::showView(bool isFull)
{
    if (isFull) {
        isShowFull = true;
        mFlowView->setVisible(false);
        mFullPicture->setVisible(true);
    }else {
        isShowFull = false;
        mFlowView->setVisible(true);
        mFullPicture->setVisible(false);
    }
}

bool ImagePrivate::isBackPressed()
{
    if (isShowFull) {
        showView(false);
        return true;
    }
    return false;
}

void ImagePrivate::onPrev() {
    mFlowView->showPrevious();
}
void ImagePrivate::onNext() {
    mFlowView->showNext();
}

void ImagePrivate::onBtnTestRelease()
{
    Q_Q(Image);
    q->startApplication(T_Home);
}

//----------------------------------

Image::Image(QObject *parent):
    Activity(parent),
    d_ptr(new ImagePrivate(this))
{

}

void Image::onCreate(QWidget *parent)
{
    Q_D(Image);
    d->initializeBasicWidget(parent);
}
void Image::onStart()
{

}
void Image::onResume()
{

}
void Image::onPause()
{

}
void Image::onStop()
{

}
void Image::onDestroy()
{

}

bool Image::onBackPressed()
{
    Q_D(Image);
    return d->isBackPressed();
}

void Image::onLanguageChanged()
{

}

void Image::onReceiveBroadcast(AppType appType,OMessage &msg)
{

}

void Image::onReceiveCmd(AppType appType,OMessage &msg)
{

}




