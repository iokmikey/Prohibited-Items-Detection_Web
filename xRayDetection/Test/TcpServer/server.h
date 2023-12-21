#pragma once 


#include <QtNetwork>
#include <QObject>

class HttpServer : public QObject {
    Q_OBJECT
    
public:
    explicit HttpServer(QObject *parent = nullptr);

private slots:
    inline void handleConnection() {
        while (server.hasPendingConnections()) {
            QTcpSocket *socket = server.nextPendingConnection();
            connect(socket, &QTcpSocket::readyRead, this, &HttpServer::readRequest);
        }
    }

    void readRequest();

private:
    QTcpServer server;
};
