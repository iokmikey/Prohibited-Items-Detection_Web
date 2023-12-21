#include "PortScanner.h"
#include "NICM.h"

int main(int argc, char* argv[])
{
    PortScanner scanner;
    //NICM nicMgr;

    auto nicInfo = NICM::GetNicInfo();
    for(const auto& info : nicInfo)
    {
        qDebug() << "ip:"<< info.ip.toString() << " mask:" << info.netMask.toString();
    }

    return 0;
}