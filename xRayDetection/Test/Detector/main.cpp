#include "YoloSession.h"
#include <memory>
#include <iostream>

int main(int argc, char* argv[])
{
    std::shared_ptr<Ortw::Detection::ISession> session = std::make_shared<Ortw::Detection::YoloSession>();
    session->initialize("/home/wxxz/workspace/weights/nxray.onnx");
    
    std::cout << session->GetModel() << std::endl;
    
    return 0;
}