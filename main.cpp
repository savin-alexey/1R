#include <QtWidgets>
#include "mainwindow.h"





int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Программа");
    MainWindow window;

    window.resize(1300, 640);
    window.setWindowState(Qt::WindowMaximized);
    window.show();

    return app.exec();
}
