#include "launcher.h"

LauncherPrivate::LauncherPrivate(Launcher *parent)
    :QObject(),q_ptr(parent)

{
    mBackground = NULL;
}

void LauncherPrivate::initializeBasicWidget(QWidget *parent)
{
    Q_Q(Launcher);

    const int icon_first = 88;
    const int icon_step = 175;
    const int first_line_y = 80;
    const int second_line_y = 254;
    const int icon_size = 100;

    const int title_text_x =28;
    const int title_text_y =70;

    mBackTitle = new BmpWidget(parent);
    mBackTitle->setBackgroundBmpPath(QString(":/img/setting/img_btn_tab_bg.png"));
    mBackTitle->setFixedSize(QSize(800, 50));

    QFont font("Microsoft YaHei");
    font.setPointSize(18);

    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);

    mBmpMultimedia = new BmpButton(parent);
    mBmpMultimedia->setText(tr("多媒体"));
    mBmpMultimedia->setNormalBmpPath(":/img/setting/img_btn_tab_a.png");
    mBmpMultimedia->setPressBmpPath(":/img/setting/img_btn_tab_b.png");
    mBmpMultimedia->setGeometry(0,0,126,50);
    mBmpMultimedia->setVisible(true);
    mBmpMultimedia->setFont(font);

    //mBackground = new BmpWidget(parent);
    //mBackground->setBackgroundBmpPath(QString(":/img/Common/img_wap_bg.png"));
    //mBackground->setFixedSize(QSize(800, 435));

    //---------------------------------------------------------
    mHomePagerOne = new BmpWidget(parent);
    mHomePagerOne->setBackgroundBmpPath(":/img/Common/img_wap_bg.png");
    mHomePagerOne->setGeometry(0,50,800,480);

    mBtnFm = new BmpButton(parent);
    mBtnFm->setNormalBmpPath(QString(":/img/Launcher/img_launcher_fm_a.png"));
    mBtnFm->setPressBmpPath(QString(":/img/Launcher/img_launcher_fm_b.png"));
    mBtnFm->setGeometry(icon_first,first_line_y,icon_size,icon_size);
    q->connect(mBtnFm,SIGNAL(released()),this,SLOT(onBtnFmRelease()));

    mLabelFm = new QLabel(parent);
    mLabelFm->setFont(font);
    mLabelFm->setPalette(pa);
    mLabelFm->setGeometry(icon_first + title_text_x,first_line_y + title_text_y,icon_size,icon_size);
    mLabelFm->setText(tr("FM"));

    mBtnAm = new BmpButton(parent);
    mBtnAm->setNormalBmpPath(QString(":/img/Launcher/img_launcher_am_a.png"));
    mBtnAm->setPressBmpPath(QString(":/img/Launcher/img_launcher_am_b.png"));
    mBtnAm->setGeometry(icon_first+icon_step,first_line_y,icon_size,icon_size);
    q->connect(mBtnAm,SIGNAL(released()),this,SLOT(onBtnAmRelease()));

    mLabelAm = new QLabel(parent);
    mLabelAm->setFont(font);
    mLabelAm->setPalette(pa);
    mLabelAm->setGeometry(icon_first+icon_step+title_text_x,first_line_y+title_text_y,icon_size,icon_size);
    mLabelAm->setText(tr("AM"));

    mBtnMusic = new BmpButton(parent);
    mBtnMusic->setNormalBmpPath(QString(":/img/Launcher/img_launcher_music_a.png"));
    mBtnMusic->setPressBmpPath(QString(":/img/Launcher/img_launcher_music_b.png"));
    mBtnMusic->setGeometry(icon_first+icon_step*2,first_line_y,icon_size,icon_size);
    q->connect(mBtnMusic,SIGNAL(released()),this,SLOT(onBtnMusicRelease()));

    mLabelMusic = new QLabel(parent);
    mLabelMusic->setFont(font);
    mLabelMusic->setPalette(pa);
    mLabelMusic->setGeometry(icon_first+icon_step*2+title_text_x,first_line_y+title_text_y,icon_size,icon_size);
    mLabelMusic->setText(tr("音乐"));

    mBtnVideo = new BmpButton(parent);
    mBtnVideo->setNormalBmpPath(QString(":/img/Launcher/img_launcher_video_a.png"));
    mBtnVideo->setPressBmpPath(QString(":/img/Launcher/img_launcher_video_b.png"));
    mBtnVideo->setGeometry(icon_first+icon_step*3,first_line_y,icon_size,icon_size);
    q->connect(mBtnVideo,SIGNAL(released()),this,SLOT(onBtnVideoRelease()));

    mLabelVideo = new QLabel(parent);
    mLabelVideo->setFont(font);
    mLabelVideo->setPalette(pa);
    mLabelVideo->setGeometry(icon_first+icon_step*3+title_text_x,first_line_y+title_text_y,icon_size,icon_size);
    mLabelVideo->setText(tr("视频"));

    mBtnElink = new BmpButton(parent);
    mBtnElink->setNormalBmpPath(QString(":/img/Launcher/img_launcher_elink_a.png"));
    mBtnElink->setPressBmpPath(QString(":/img/Launcher/img_launcher_elink_b.png"));
    mBtnElink->setGeometry(icon_first,second_line_y,icon_size,icon_size);
    q->connect(mBtnElink,SIGNAL(released()),this,SLOT(onBtnElinkRelease()));

    mLabelElink = new QLabel(parent);
    mLabelElink->setFont(font);
    mLabelElink->setPalette(pa);
    mLabelElink->setGeometry(icon_first+title_text_x-10,second_line_y+title_text_y,icon_size,icon_size);
    mLabelElink->setText(tr("E-Link"));

    mBtnBlueTooth = new BmpButton(parent);
    mBtnBlueTooth->setNormalBmpPath(QString(":/img/Launcher/img_launcher_bt_music_a.png"));
    mBtnBlueTooth->setPressBmpPath(QString(":/img/Launcher/img_launcher_bt_music_b.png"));
    mBtnBlueTooth->setGeometry(icon_first+icon_step,second_line_y,icon_size,icon_size);
    q->connect(mBtnBlueTooth,SIGNAL(released()),this,SLOT(onBtnBlueToothRelease()));

    mLabelBlueTooth = new QLabel(parent);
    mLabelBlueTooth->setFont(font);
    mLabelBlueTooth->setPalette(pa);
    mLabelBlueTooth->setGeometry(icon_first+icon_step+title_text_x,second_line_y+title_text_y,icon_size,icon_size);
    mLabelBlueTooth->setText(tr("蓝牙"));

    mBtnImage = new BmpButton(parent);
    mBtnImage->setNormalBmpPath(QString(":/img/Launcher/img_launcher_img_a.png"));
    mBtnImage->setPressBmpPath(QString(":/img/Launcher/img_launcher_img_b.png"));
    mBtnImage->setGeometry(icon_first+icon_step*2,second_line_y,icon_size,icon_size);
    q->connect(mBtnImage,SIGNAL(released()),this,SLOT(onBtnImagetRelease()));

    mLabelImage = new QLabel(parent);
    mLabelImage->setFont(font);
    mLabelImage->setPalette(pa);
    mLabelImage->setGeometry(icon_first+icon_step*2+title_text_x,second_line_y+title_text_y,icon_size,icon_size);
    mLabelImage->setText(tr("图片"));

    mBtnSettings = new BmpButton(parent);
    mBtnSettings->setNormalBmpPath(QString(":/img/Launcher/img_launcher_setting_a.png"));
    mBtnSettings->setPressBmpPath(QString(":/img/Launcher/img_launcher_setting_b.png"));
    mBtnSettings->setGeometry(icon_first+icon_step*3,second_line_y,icon_size,icon_size);
    q->connect(mBtnSettings,SIGNAL(released()),this,SLOT(onBtnSettingsRelease()));

    mLabelSetting = new QLabel(parent);
    mLabelSetting->setFont(font);
    mLabelSetting->setPalette(pa);
    mLabelSetting->setGeometry(icon_first+icon_step*3+title_text_x,second_line_y+title_text_y,icon_size,icon_size);
    mLabelSetting->setText(tr("设置"));

    //   mBtnAvin = new BmpButton(parent);
    //   mBtnAvin->setNormalBmpPath(QString(":/Res/drawable/test/btn_n.png"));
    //   mBtnAvin->setPressBmpPath(QString(":/Res/drawable/test/btn_p.png"));
    //   mBtnAvin->setGeometry(600,425,90,90);
    //   q->connect(mBtnAvin,SIGNAL(released()),this,SLOT(onBtnAvinRelease()));



}


void LauncherPrivate::onBtnFmRelease()
{
    Q_Q(Launcher);
    q->startApplication(T_Radio);
}

void LauncherPrivate::onBtnAmRelease()
{
    Q_Q(Launcher);
    q->startApplication(T_RadioAm);
}

void LauncherPrivate::onBtnMusicRelease()
{
    Q_Q(Launcher);
    q->startApplication(T_USBDiskMusic);
}

void LauncherPrivate::onBtnVideoRelease()
{
    Q_Q(Launcher);
    q->startApplication(T_USBDiskVideo);
}

void LauncherPrivate::onBtnElinkRelease()
{
    //Q_Q(Launcher);
    //q->startApplication(T_Link);
}

void LauncherPrivate::onBtnBlueToothRelease()
{
    Q_Q(Launcher);
    q->startApplication(T_Bluetooth);
}

void LauncherPrivate::onBtnImagetRelease()
{
    Q_Q(Launcher);
    q->startApplication(T_USBDiskImage);
}

void LauncherPrivate::onBtnSettingsRelease()
{
    Q_Q(Launcher);
    q->startApplication(T_Setting);
}

void LauncherPrivate::onBtnAvinRelease()
{
    Q_Q(Launcher);
    q->startApplication(T_AVIN);
}

//----------------------------------



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

