#include "PortScanner.h"


PortScanner::PortScanner(QObject* parent)   
    :QTcpSocket(parent)
{

}

QList<QHostAddress> PortScanner::scan(const QHostAddress& ip, quint16 port, const QHostAddress& mask)
{
    quint32 ipValue = ip.toIPv4Address();
    quint32 maskValue = mask.toIPv4Address();

    quint32 netAddr = ipValue & maskValue;
    quint32 boradcastAddr = netAddr | ~maskValue;

    for(quint32 idx = netAddr + 1; idx < boradcastAddr; ++idx)
    {
        QHostAddress ip_scan(idx);
        connectToPort(ip_scan, port);
    }

    return openedPortAddr;
}

void PortScanner::connectToPort(const QHostAddress& ip, quint16 port)
{
    QTcpSocket* socket = new QTcpSocket(this);

    connect(socket, SIGNAL(connected()), this, SLOT(onSocketConnected()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSocketError(QAbstractSocket::SocketError)));

    socket->connectToHost(ip, port);
}

void PortScanner::onSocketConnected()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());

    socket->peerAddress();
    QHostAddress ip = socket->peerAddress();
     
    openedPortAddr.append(ip);

    socket->deleteLater();
}

void PortScanner::onSocketError(QAbstractSocket::SocketError err)
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());

    QHostAddress ip = socket->peerAddress();
    quint16 port = socket->peerPort();

    qDebug() << "connectError:" << err << " Host[" << ip << ":"<<port << "]\n";

    socket->deleteLater();
}