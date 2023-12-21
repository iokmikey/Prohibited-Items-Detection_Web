#pragma once

#include "MainContext.h"




class App
{
public:
    App(int &argc, char **argv);
    ~App();
    
    /// @brief 程序入口
    /// @return 
    bool Run();

private:
    MainContext* ctx_ = MainContext::getInstance();
    
};