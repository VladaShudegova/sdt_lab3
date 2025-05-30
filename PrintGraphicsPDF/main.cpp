#include "mainwindow.h"

#include <QApplication>
#include <QStyleFactory>

void setDarkTheme(QApplication& app){
    app.setStyle(QStyleFactory::create("Fusion")); // стиль Fusion позволяет настраивать цвета
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(53, 53, 53)); // темно-серый цвет
    palette.setColor(QPalette::WindowText, QColor(200, 200, 200)); // светло-серый цвет текста
    palette.setColor(QPalette::Base, QColor(25, 25, 25)); // темно-серый цвет фона полей ввода
    palette.setColor(QPalette::AlternateBase, QColor(53, 53, 53)); // темно-серый цвет
    palette.setColor(QPalette::ToolTipBase, QColor(200, 200, 200)); // светло-серый цвет
    palette.setColor(QPalette::ToolTipText, QColor(53, 53, 53)); // темно-серый цвет
    palette.setColor(QPalette::Text, QColor(200, 200, 200)); // светло-серый цвет текста
    palette.setColor(QPalette::Button, QColor(53, 53, 53)); // темно-серый цвет
    palette.setColor(QPalette::ButtonText, QColor(200, 200, 200)); // светло-серый цвет текста
    palette.setColor(QPalette::BrightText, QColor(200, 0, 0)); // ярко-красный цвет
    palette.setColor(QPalette::Link, QColor(42, 130, 218)); // синий цвет ссылок
    palette.setColor(QPalette::Highlight, QColor(42, 130, 218)); // синий цвет выделения
    palette.setColor(QPalette::HighlightedText, QColor(0, 0, 0)); // черный цвет текста выделения

    app.setPalette(palette);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    setDarkTheme(a);

    MainWindow w;
    w.show();
    return a.exec();
}



