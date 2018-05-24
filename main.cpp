#include "mainwindow.h"
#include <QApplication>
#include "Src/Framework/Base/Core/application.h"

int main(int argc, char *argv[])
{
    Application app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();

    app.setWindowWidget(&mainWindow);
    app.startApplication(T_Home);
    //app.startApplication(T_Radio);

    return app.exec();
}
