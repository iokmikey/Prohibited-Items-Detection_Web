#include "SocketServer.h"
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SocketServer server;
    server.listen(QHostAddress::AnyIPv4, 8888);

    return a.exec();
}