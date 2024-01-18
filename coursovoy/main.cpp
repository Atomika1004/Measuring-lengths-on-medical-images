#include "mainwindow.h"

#include <QApplication>
#include <QLabel>
#include <QWidget>
#include <QPainter>
#include <QPoint>
#include <QMouseEvent>
#include <QFileDialog>
#include <QMouseEvent>
#include <QLine>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Программа для измерения расстояния между объектами");
    w.show();
    return a.exec();
}
