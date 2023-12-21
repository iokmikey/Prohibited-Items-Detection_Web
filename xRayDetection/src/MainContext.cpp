#include "MainContext.h"

#include "Common/INI/INIReader.h"
#include "Common/Filesystem.h"

MainContext* MainContext::m_instance = nullptr;
std::mutex MainContext::m_mtx;


bool MainContext::initialize()
{
    using namespace Common::IFilesystem;

    bool valid = false;
    std::string configPath = ConcatPath(GetCurrentPath(), "Config.ini");

    if(!fs::exists(configPath)) {
        err("Can not find the config path:%s\n", configPath.c_str());
        return false;
    }

    INIReader config(configPath);
    log("Config Path:%s\n", configPath.c_str());

    std::string rootDoc = config.GetString("httpSrv", "RootDocument", "");
    log("root Document:%s\n", rootDoc.c_str());
    if(rootDoc.empty()) {
       err("Invalid root document:%s\n", rootDoc.c_str());
       return false; 
    }

    ushort listenPort = (ushort)config.GetUnsigned("httpSrv", "ListenPort", 7899);

    return CreateResourceManager(config) && CreateService(rootDoc, listenPort);
}


bool MainContext::CreateDetector(const std::string& modelPath)
{
    if(modelPath == m_curSessionId)
        return true;
    
    m_session = std::make_shared<Detection::Yolov5Session>(); // 其实这个也只需要执行一次
    
    bool status = m_session->Initialize(modelPath);
    if(status)
        m_curSessionId = modelPath;
    
    return status;
}


bool MainContext::CreateService(const std::string& rootDoc, ushort listenPort)
{
    m_srv = std::make_shared<Communications::HttpServer>();
    
    auto& imageMgr = m_resMgr->GetImageManager();

    return m_srv->start(rootDoc, listenPort, imageMgr);
}


bool MainContext::CreateResourceManager(const INIReader& config)
{
    m_resMgr = std::make_shared<Resources::ResourceManager>();

    return m_resMgr->Initialize(config);
}