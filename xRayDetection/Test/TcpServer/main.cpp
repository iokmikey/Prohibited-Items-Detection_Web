#include "server.h"



int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    HttpServer httpServer;
    return app.exec();
}