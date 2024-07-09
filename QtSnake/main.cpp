#include "mainWindow.h"
#include <QApplication>
#pragma execution_character_set("utf-8")

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowIcon(QIcon(":/image/image/snake.png"));
    w.setWindowTitle(QObject::tr("贪吃蛇 ver1.4.3"));
    w.show();

    return a.exec();
}
