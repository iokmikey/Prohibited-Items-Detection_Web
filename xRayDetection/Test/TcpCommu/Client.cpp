#include <QtNetwork>
#include <QTcpSocket>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTcpSocket socket;
    socket.connectToHost("127.0.0.1", 8888); // 连接服务器的IP地址和端口

    if (!socket.waitForConnected()) {
        qDebug() << "Error: " << socket.errorString();
        return 1;
    }

    qDebug() << "Connected to server.";

    // 模拟向服务器发送数据
    QByteArray data = "Hello, server!";
    socket.write(data);
    socket.flush(); // 确保数据被发送

    // 等待服务器的响应
    if (socket.waitForReadyRead()) {
        QByteArray response = socket.readAll();
        qDebug() << "Received response from server:" << response;
    } else {
        qDebug() << "Error receiving response: " << socket.errorString();
    }

    // 断开与服务器的连接
    socket.disconnectFromHost();

    return a.exec();
}
