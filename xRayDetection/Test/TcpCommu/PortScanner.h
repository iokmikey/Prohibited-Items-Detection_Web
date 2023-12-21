#pragma once

#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QList>

class PortScanner: public QTcpSocket
{
    Q_OBJECT
public:
    PortScanner(QObject *parent = nullptr);
    ~PortScanner() = default;

public:
    QList<QHostAddress> scan(const QHostAddress& ip, quint16 port, const QHostAddress& mask);

private:
    void connectToPort(const QHostAddress& ip, quint16 port);

    void onSocketConnected();

    void onSocketError(QAbstractSocket::SocketError err);

private:
    QList<QHostAddress> openedPortAddr;
};