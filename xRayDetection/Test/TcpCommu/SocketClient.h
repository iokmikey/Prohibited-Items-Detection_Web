#pragma once
#include <QtNetwork/QTcpSocket>


class SocketClient: public QTcpSocket
{
public:
    SocketClient();
    ~SocketClient();
};