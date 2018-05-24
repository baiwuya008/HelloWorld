#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
// mBackground = new BmpWidget(this); //设置背景图片
// mBackground->setBackgroundBmpPath(QString(":/Res/drawable/test/logo01.png"));
// mBackground->setFixedSize(QSize(800, 480));


 setFixedSize(800,480); //固定窗口大小

 move(600,240); //设置窗口起始顶点位置
 //setStyleSheet("MainWindow{background-image:url(:/Res/drawable/test/logo01.png);}"); //设置背景图片
 //setWindowFlags(Qt::FramelessWindowHint); //去掉应用框架外框
}

MainWindow::~MainWindow()
{

}
