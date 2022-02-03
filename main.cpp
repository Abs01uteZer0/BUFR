#include "mainwindow.h"
#include <QApplication>
#include <clocale>
int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"rus");
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("BUFR decoder");
    w.show();
    return a.exec();
}
