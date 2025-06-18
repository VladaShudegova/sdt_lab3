#include "mainwindow.h"
#include "IOC/iocconteiner.h"

#include <QApplication>
#include <QMessageBox>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    try{
    IOCContainer container;

    std::cout << "Registering ChartCreatorsFactory..." << std::endl;
    container.registerInstance<IChartCreatorsFactory, ChartCreatorsFactory>();


    std::cout << "Registering DataReaderFactory..." << std::endl;
    container.registerInstance<IDataReaderFactory, DataReaderFactory>();


    std::cout << "Registering MainWindow..." << std::endl;
    container.registerInstance<MainWindow, MainWindow, IDataReaderFactory, IChartCreatorsFactory>();

    std::cout << "\nAll registrations complete. Now retrieving MainWindow...\n" << std::endl;

    std::shared_ptr<MainWindow> w = container.getObject<MainWindow>();
    w->show();
    return a.exec();
    }
    catch(const std::exception& e){
        QMessageBox::critical(nullptr, "Startup Error", e.what());
    }
}
