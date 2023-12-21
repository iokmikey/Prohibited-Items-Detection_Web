#include "UITest.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UITest w;
    w.show();
    return a.exec();
}