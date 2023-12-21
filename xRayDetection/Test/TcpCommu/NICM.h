
#pragma once
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QList>

/* 
    name:  network interface card manager
    desc:  scanning the whole nic in the computer, Filter out invalid network cards
*/
class NICM
{
public:
    struct InterfaceInfo
    {
        QHostAddress ip;
        QHostAddress netMask;
    };
    
public:
    NICM() = default;
    ~NICM() = default;

    static QList<InterfaceInfo> GetNicInfo();
};