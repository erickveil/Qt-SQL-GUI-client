#include "mainwindow.h"
#include <QApplication>
#include "cstdio"

int main(int argc, char *argv[])
{
    printf("args: %d",argc);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

void initSqliteTable()
{
}
