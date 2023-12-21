#pragma once
#include <QtNetwork/QTcpServer>


class SocketServer: public QTcpServer
{
    Q_OBJECT
public:
    explicit SocketServer(QObject *parent = nullptr);
    ~SocketServer();
protected:
    void incomingConnection(qintptr socket) override;


private slots:
    void readClient();

    void clientDisconnected();
};