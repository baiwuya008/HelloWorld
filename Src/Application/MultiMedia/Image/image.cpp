#include "image.h"


ImagePrivate::ImagePrivate(Image *parent)
    : QObject(),q_ptr(parent)
{
    mBackground = NULL;
    mBtnTest = NULL;
}

void ImagePrivate::initializeBasicWidget(QWidget *parent)
{
    Q_Q(Image);

    //        mBackground = new BmpWidget(parent); //设置背景图片
    //        mBackground->setBackgroundBmpPath(QString(":/Res/drawable/test/image.png"));
    //        mBackground->setFixedSize(QSize(800, 435));

    //    mBtnTest= new BmpButton(parent);
    //    mBtnTest->setNormalBmpPath(QString(":/Res/drawable/test/btn_n.png"));
    //    mBtnTest->setPressBmpPath(QString(":/Res/drawable/test/btn_p.png"));
    //    mBtnTest->setGeometry(600,300,195,50);

    //   q->connect(mBtnTest,SIGNAL(released()),this,SLOT(onBtnTestRelease()));


    setWidgetBackground(parent, ":/img/Common/img_wap_bg.png");
    initializeToolsWidget(parent);
    initializeBottomView(parent);
    initializeFlowView(parent);

    setCurrentTab();
}


void ImagePrivate::initializeToolsWidget(QWidget *parent) {
    QList<QString> list;
    list.append("照片");
    mMediaToolsWidget = new MediaToolsWidget(parent, list);
    connect(mMediaToolsWidget, SIGNAL(onItemClick(int)), this, SLOT(setCurrentPageView(int)));
}

void ImagePrivate::setCurrentPageView(int tabIndex) {
}


void ImagePrivate::initializeFlowView(QWidget *parent)
{
    Q_Q(Image);
    mFlowView = new FlowView(parent);
    mFlowView->setFixedSize(800, 294);
    mFlowView->setGeometry(0, 50, 0, 0);
    mFlowView->setParent(parent);
    connect(mFlowView, SIGNAL(itemClick(int,QString)), this, SLOT(onItemClick(int,QString)));
    connect(mFlowView, SIGNAL(switchCenterView(int)), this, SLOT(onSwitchCenter(int)));
    mFlowAdapter = new FlowAdapter(parent);
    mFlowView->setAdapter(mFlowAdapter);
    initListData();
    mFlowAdapter->setInfoList(mList);
}

void ImagePrivate::onSwitchCenter(int position) {
    setCurrentTab();
}

void ImagePrivate::onItemClick(int position, QString path) {
    qDebug() << "onItemClick position = " << position
             << "; path = " << path;
}

void ImagePrivate::initListData() {
    mList.append(":/picture_test/music_1.jpeg");
    mList.append(":/picture_test/music_2.jpeg");
    mList.append(":/picture_test/music_3.jpeg");
    mList.append(":/picture_test/music_4.jpeg");
    mList.append(":/picture_test/music_5.jpeg");
    mList.append(":/picture_test/music_6.jpeg");
    mList.append(":/picture_test/music_7.jpeg");
    mList.append(":/picture_test/music_8.jpeg");


    //    mList.append("D:\\QT\\work\\images\\music_1.jpeg");
    //    mList.append("D:\\QT\\work\\images\\music_2.jpeg");
    //    mList.append("D:\\QT\\work\\images\\music_3.jpeg");
    //    mList.append("D:\\QT\\work\\images\\music_4.jpeg");
    //    mList.append("D:\\QT\\work\\images\\music_5.jpeg");
    //    mList.append("D:\\QT\\work\\images\\music_6.jpeg");
    //    mList.append("D:\\QT\\work\\images\\music_7.jpeg");
    //    mList.append("D:\\QT\\work\\images\\music_8.jpeg");
}

void ImagePrivate::initializeBottomView(QWidget *parent)
{
    QWidget *mBottomWidget = new QWidget(parent);
    mBottomWidget->setFixedSize(QSize(800, 45));
    mBottomWidget->setGeometry(0, 346, 0, 0);

    QHBoxLayout *mBottomLayout = new QHBoxLayout;
    mBottomWidget->setLayout(mBottomLayout);
    mBottomLayout->setContentsMargins(0, 0, 0, 0);

    BmpButton *prevBtn = new BmpButton(mBottomWidget);
    prevBtn->setFixedSize(QSize(46, 45));
    prevBtn->setNormalBmpPath(":/img/setting/img_sound_seat_left_a.png");
    prevBtn->setPressBmpPath(":/img/setting/img_sound_seat_left_b.png");
    prevBtn->setGeometry(180, 0, 0, 0);


    BmpButton *nextBtn = new BmpButton(mBottomWidget);
    nextBtn->setFixedSize(QSize(46, 45));
    nextBtn->setNormalBmpPath(":/img/setting/img_sound_seat_right_a.png");
    nextBtn->setPressBmpPath(":/img/setting/img_sound_seat_right_b.png");
    nextBtn->setGeometry(575, 0, 0, 0);



    mTabLabel = new QLabel;
    initLabText(mTabLabel, 20);
    mTabLabel->setText("3/10");
    mBottomLayout->addWidget(mTabLabel, 0, Qt::AlignCenter);


    Q_Q(Image);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(prevBtn, SIGNAL(released()), q, SLOT(prevPicture()), type);
    QObject::connect(nextBtn, SIGNAL(released()), q, SLOT(nextPicture()), type);
}

void Image::prevPicture()
{
    Q_D(Image);
    d->onPrevPicture();
}

void Image::nextPicture()
{
    Q_D(Image);
    d->onNextPicture();
}

void ImagePrivate::onPrevPicture() {
    mFlowView->showPrevious();
}
void ImagePrivate::onNextPicture() {
    mFlowView->showNext();
}


void ImagePrivate::initLabText(QLabel *text, int size)
{
    //设置字号
    QFont ft("Microsoft YaHei");
    ft.setPointSize(size);
    text->setFont(ft);
    //设置颜色
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);
    text->setPalette(pa);
}

void ImagePrivate::setCurrentTab()
{
    if (mFlowAdapter->getTotalLength() > 0) {
        mTabLabel->setText(QString::number(mFlowAdapter->getCenterPosition()+1)
                           +"/"+QString::number(mFlowAdapter->getTotalLength()));
    }else {
        mTabLabel->setText("0/0");
    }
}

void ImagePrivate::setWidgetBackground(QWidget *widget, QString path) {
    //设置背景图片
    widget->setAutoFillBackground(true); // 这句要加上, 否则可能显示不出背景图.
    QPalette palette = widget->palette();
    palette.setBrush(QPalette::Window,
                     QBrush(QPixmap(path).scaled(widget->size(),
                                                 Qt::IgnoreAspectRatio,
                                                 Qt::SmoothTransformation)));
    widget->setPalette(palette);
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

    return false;
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




