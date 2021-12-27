#include "mainwindow.h"
#include "student.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

    //std::cout<<"Hello world";
}
