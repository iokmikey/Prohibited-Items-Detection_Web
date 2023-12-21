#include "SocketServer.h"
#include <QtNetwork/QTcpSocket>

SocketServer::SocketServer(QObject *parent)
    : QTcpServer{parent}
{

}


SocketServer::~SocketServer()
{

}

void SocketServer::incomingConnection(qintptr socket)
{
    QTcpSocket *client = new QTcpSocket(this);

    // 将新连接的套接字描述符传递给QTcpSocket
    if (!client->setSocketDescriptor(socket)) {
        qDebug() << "Error setting socket descriptor:" << client->errorString();
        return;
    }

    qDebug() << "New connection from:" << client->peerAddress().toString();
    
    // 连接信号槽以处理客户端发送的数据
    connect(client, &QTcpSocket::readyRead, this, &SocketServer::readClient);
    connect(client, &QTcpSocket::disconnected, this, &SocketServer::clientDisconnected);
}


void SocketServer::readClient()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (!clientSocket)
        return;

    // 从客户端套接字读取数据
    QByteArray data = clientSocket->readAll();
    
    qDebug() << "Received data:" << data;
    
    // 在这里可以对数据进行处理，然后向客户端发送响应
    // clientSocket->write(responseData);
}

void SocketServer::clientDisconnected()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (!clientSocket)
        return;

    qDebug() << "Client disconnected:" << clientSocket->peerAddress().toString();
    clientSocket->deleteLater();
}
