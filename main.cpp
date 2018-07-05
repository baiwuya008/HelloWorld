#include "mainwindow.h"
#include <QApplication>
#include "Src/Framework/Base/Core/application.h"
#include "configuration.h"
#include "Src/Framework/Manager/BluetoothManagerGoc.h"
#include "Src/Framework/Manager/RadioManager.h"


#if (APP_WITH_SIMULATION == 1)
  #include "Src/Simulation/simulationda.h"
#endif

#include <QTextCodec>

int main(int argc, char *argv[])
{
    //application encoding
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    QCoreApplication::setOrganizationName(QString("OKL"));
    QCoreApplication::setApplicationName(QString("OKLMAIN"));

    Application app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
#if (APP_WITH_SIMULATION == 1)
    app.setSimulation(new SimulationDa());
#endif
    app.setWindowWidget(&mainWindow);
    app.setWindowWallPaper(QString(":/res/drawable/wallpaper_01.png"));

    app.startApplication(T_SystemUi); //状态栏启动
    app.startApplication(T_Home);//启动媒体主界面
    //app.startApplication(T_Radio);//启动收音机
    //init the service or data manager
    gBluetoothManager;
    gRadioManager;

    return app.exec();
}
