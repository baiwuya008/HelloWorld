#include "mainwindow.h"
#include "configuration.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
// mBackground = new BmpWidget(this); //设置背景图片
// mBackground->setBackgroundBmpPath(QString(":/Res/drawable/test/logo01.png"));
// mBackground->setFixedSize(QSize(800, 480));

    //此次使用微软雅黑字体
    QFont myfont = font();
    myfont.setFamily("Microsoft YaHei");
    setFont(myfont);

#if (APP_WITH_SIMULATION == 1)
    setFixedSize(1088,498); //固定窗口大小
    move(300,240); //设置窗口起始顶点位置
#else
    setFixedSize(800,480); //固定窗口大小
    move(0,0); //设置窗口起始顶点位置
#endif

 //setStyleSheet("MainWindow{background-image:url(:/Res/drawable/test/logo01.png);}"); //设置背景图片
 #if(APP_WITH_SIMULATION == 0)
    setWindowFlags(Qt::FramelessWindowHint); //去掉应用框架外框
 #endif
 //setWindowFlags(Qt::FramelessWindowHint); //去掉应用框架外框
}

MainWindow::~MainWindow()
{

}
