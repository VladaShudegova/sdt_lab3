#include "mainwindow.h"
#include "IOC/iocconteiner.h"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    try{
    IOCContainer container;

    MainWindow w(container);
    w.show();
    return a.exec();
    }
    catch(const std::exception& e){
        QMessageBox::critical(nullptr, "Startup Error", e.what());
    }
}
