#include "mainwindow.h"
#include "IOC/iocconteiner.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    IOCContainer container;

    MainWindow w(container);
    w.show();
    return a.exec();
}
