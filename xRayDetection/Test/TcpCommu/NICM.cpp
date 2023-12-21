#include "NICM.h"
#include <QList>

#include <QNetworkInterface>

QList<NICM::InterfaceInfo> NICM::GetNicInfo()
{
    QList<NICM::InterfaceInfo> result;
    QList<QNetworkInterface> netInterfaces = QNetworkInterface::allInterfaces();

    for (const auto& interface : netInterfaces)
    {
        auto flags = interface.flags();
        if(!flags.testFlag(QNetworkInterface::IsUp) || 
            !flags.testFlag(QNetworkInterface::IsRunning) || 
              flags.testFlag(QNetworkInterface::IsLoopBack))
            continue;
        
        for(const auto& entry : interface.addressEntries())
        {
            if(entry.ip().protocol() != QAbstractSocket::IPv4Protocol)
                continue;
            
            QHostAddress ipv4 = entry.ip();
            QHostAddress netMask = entry.netmask();
            
            result.push_back({ipv4, netMask});
        }
    }

    return result;
}