
#include "Communications/AssetHandler.h"
#include "MainContext.h"


namespace Communications
{

    AssetHandler::AssetHandler(Resources::ImageManager& imageMgr):
        m_imageMgr(imageMgr)
    {
        imageRoot = std::filesystem::current_path().string();
    }

    bool AssetHandler::handle()
    {
        const mg_request_info* info =  mg_get_request_info(conn_);
        std::string requestUri = std::string(info->request_uri);

        std::string name = GetAssetName(requestUri);
        log("Image Name:%s\n", name.c_str());
        if(IsValidImage(name))
            return handleImage(name);
        
        
        return false;
    }

    

    bool AssetHandler::handleImage(const std::string& name)
    {
        std::string imagePath =  m_imageMgr.Get(name);
        if(imagePath.empty())
            return false;

        sendFile(conn_, imagePath);
        
        return true;
    }

    bool AssetHandler::IsValidImage(const std::string& name) 
    {
        auto pos = name.find_last_of('.');
        if(pos == std::string::npos)
            return false;

        return exts.count(name.substr(pos + 1)) != 0;
    }

    std::string AssetHandler::GetAssetName(const std::string& uri)
    {
        std::string name;
        auto pos = uri.find_last_of('/');
        if(pos != std::string::npos)
            name = uri.substr(pos + 1);

        return name;
    }
}