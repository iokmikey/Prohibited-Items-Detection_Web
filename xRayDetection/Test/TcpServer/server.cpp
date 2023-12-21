#include "server.h"
#include <QJsonDocument>
#include <QJsonObject>

HttpServer::HttpServer(QObject *parent)
        : QObject(parent), server(this)
{

    connect(&server, &QTcpServer::newConnection, this, &HttpServer::handleConnection);

    if (!server.listen(QHostAddress::Any, 7899)) {
        qDebug() << "Server could not start!";
    } else {
        qDebug() << "Server started";
    }
}

void HttpServer::readRequest()
{
        QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
        if (!socket)
            return;

        QByteArray requestData = socket->readAll();
        qDebug() << "recived request!\n";
        // Parse the HTTP request (simple parsing for demonstration p<urposes)
        QString request = QString::fromUtf8(requestData);
        //qDebug() << "request: "<<request << "\n";
        
        QStringList lines = request.split("\r\n");
        if (lines.size() < 2)
            return;
        
        qDebug() << "lines:\n" << lines <<"\n";
        for(auto line: lines){
            qDebug() << "line: " << line <<"\n"; 
        }

        QString firstLine = lines.first();
        QStringList firstLineParts = firstLine.split("< ");
        
    
        QJsonArray jsonLabel;
        jsonLabel.append("knife");
        jsonLabel.append("powerbank");
        jsonLabel.append("gun");

        QJsonObject jsonSta;
        jsonSta.insert("knife", 11);
        jsonSta.insert("powerbank", 21);
        jsonSta.insert("gun", 1);

        QJsonObject jsonArgs; 
        jsonArgs.insert("label", jsonLabel);
        jsonArgs.insert("statistics", jsonSta);

        QJsonObject json;
        json.insert("version", 1.0);
        json.insert("cmd", "ModelLoaded");
        json.insert("args", jsonArgs);
        
        QJsonDocument obj;
        obj.setObject(json);
    
        
        
        QString content = QString::fromUtf8(obj.toJson());
        
        QString res = "HTTP/1.1 200 OK\r\n"
                        "Access-Control-Allow-Origin: *\r\n"
                           "Content-Type: application/json\r\n"
                           "Content-Length: " + QByteArray::number(content.toUtf8().length()) + "\r\n"
                           "\r\n" + 
                            content;

        qDebug() << "echo:" << res;
        socket->write(res.toUtf8());
        socket->disconnectFromHost();
    }