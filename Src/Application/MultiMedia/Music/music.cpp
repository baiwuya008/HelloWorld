#include "music.h"


MusicPrivate::MusicPrivate(Music *parent)
    : QObject(),q_ptr(parent)
{
    mBackground = NULL;
    mBtnTest = NULL;
}

void MusicPrivate::initializeBasicWidget(QWidget *parent)
{
    Q_Q(Music);

    //    mBackground = new BmpWidget(parent); //设置背景图片
    //    mBackground->setBackgroundBmpPath(QString(":/Res/drawable/test/music.png"));
    //    mBackground->setFixedSize(QSize(800, 435));

    //    mBtnTest= new BmpButton(parent);
    //    mBtnTest->setNormalBmpPath(QString(":/Res/drawable/test/btn_n.png"));
    //    mBtnTest->setPressBmpPath(QString(":/Res/drawable/test/btn_p.png"));
    //    mBtnTest->setGeometry(600,300,195,50);

    //   q->connect(mBtnTest,SIGNAL(released()),this,SLOT(onBtnTestRelease()));


    initializeToolsWidget(parent);


    mStackedWidget = new QStackedWidget(parent);
    mStackedWidget->setFixedSize(QSize(800, 435));
    mStackedWidget->setGeometry(0, 50, 0, 0);

    initializePlayView(parent);
    initializeListView(parent);

    setCurrentPageView(0);

}


void MusicPrivate::initializeToolsWidget(QWidget *parent) {
    Q_Q(Music);

    QWidget *toolsWidget = new QWidget(parent);
    QHBoxLayout *toolsLayout = new QHBoxLayout;
    toolsWidget->setFixedSize(QSize(800, 50));
    toolsWidget->setLayout(toolsLayout);
    setWidgetBackground(toolsWidget, ":/Res/drawable/multimedia/main_second_line.png");


    QPushButton *musicBtn = new QPushButton;
    musicBtn->setFixedSize(QSize(100, 40));
    musicBtn->setText("音乐");
    musicBtn->setObjectName("music_play");
    toolsLayout->addWidget(musicBtn, 0, Qt::AlignVCenter);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(musicBtn, SIGNAL(clicked(bool)), q, SLOT(onClick()), type);
    btnList.append(musicBtn);

    QPushButton *listBtn = new QPushButton;
    listBtn->setObjectName("music_list");
    listBtn->setFixedSize(QSize(100, 40));
    listBtn->setText("列表");
    toolsLayout->addWidget(listBtn, 0, Qt::AlignVCenter);
    QObject::connect(listBtn, SIGNAL(clicked(bool)), q, SLOT(onClick()), type);
    btnList.append(listBtn);
}

void MusicPrivate::onClick(QString objectName) {
    if (!objectName.compare("music_play")) {
        mStackedWidget->setCurrentIndex(0);
        setCurrentPageView(0);
    }else if (!objectName.compare("music_list")) {
        mStackedWidget->setCurrentIndex(1);
        setCurrentPageView(1);
    }
}

void Music::onClick() {
    QPushButton* btn= qobject_cast<QPushButton*>(sender());
    qDebug() << "onClick---objectName = "+btn->objectName();
    Q_D(Music);
    d->onClick(btn->objectName());
}

void MusicPrivate::setCurrentPageView(int tabIndex) {
    for (int i = 0; i < btnList.size(); i++) {
        if (tabIndex == i) {
            btnList.at(i)->setStyleSheet("color: red");
        }else {
            btnList.at(i)->setStyleSheet("color: black");
        }
    }

}



void MusicPrivate::initializePlayView(QWidget *parent) {
    mMusicPlayWidget = new MusicPlayWidget(parent);
    mStackedWidget->insertWidget(0, mMusicPlayWidget);
}



void MusicPrivate::initializeListView(QWidget *parent) {
    mMusicListWidget = new MusicListWidget(parent);
    mStackedWidget->insertWidget(1, mMusicListWidget);

    Q_Q(Music);
    Qt::ConnectionType type = static_cast<Qt::ConnectionType>(Qt::UniqueConnection | Qt::AutoConnection);
    QObject::connect(mMusicListWidget, SIGNAL(selectItem(QString,int)), q, SLOT(onSelectItem(QString,int)), type);
}

void Music::onSelectItem(QString filePath, int index) {
    qDebug() << "onSelectItem filePath = " << filePath
             << "; index = " << index;
}

void MusicPrivate::setWidgetBackground(QWidget *widget, QString path) {
    //设置背景图片
    widget->setAutoFillBackground(true); // 这句要加上, 否则可能显示不出背景图.
    QPalette palette = widget->palette();
    palette.setBrush(QPalette::Window,
                     QBrush(QPixmap(path).scaled(widget->size(),
                                                 Qt::IgnoreAspectRatio,
                                                 Qt::SmoothTransformation)));
    widget->setPalette(palette);
}

void MusicPrivate::onBtnTestRelease()
{
    Q_Q(Music);
    q->startApplication(T_USBDiskVideo);
}

//----------------------------------

Music::Music(QObject *parent):
    Activity(parent),
    d_ptr(new MusicPrivate(this))
{
    //    setFixedSize(QSize(800, 435));
}

void Music::onCreate(QWidget *parent)
{
    Q_D(Music);
    //centralWidget = new QWidget(parent);
    d->initializeBasicWidget(parent);

    //setContentView(centralWidget);
}
void Music::onStart()
{

}
void Music::onResume()
{

}
void Music::onPause()
{

}
void Music::onStop()
{

}
void Music::onDestroy()
{

}

bool Music::onBackPressed()
{

    return false;
}

void Music::onLanguageChanged()
{

}

void Music::onReceiveBroadcast(AppType appType,OMessage &msg)
{

}

void Music::onReceiveCmd(AppType appType,OMessage &msg)
{

}


