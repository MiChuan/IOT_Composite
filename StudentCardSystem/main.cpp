#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    DB_Init();//数据库初始化
    w.show();

    return a.exec();
}
