#include "Communications/HttpServer.h"

#include <iostream>

#include "Communications/SieHandler.h"
#include "Communications/UiHandler.h"
#include "Communications/AssetHandler.h"

#include "Common/Logger.hpp"

namespace Communications
{

    HttpServer::HttpServer()
    {
        mg_init_library(0);
    }

    HttpServer::~HttpServer()
    {
        stop();
    }

    void HttpServer::stop()
    {
        mg_exit_library();
            
        if(srv_)
            delete srv_;
    }

    bool HttpServer::start(const std::string& rootDoc, ushort listenPort, Resources::ImageManager& imageMgr)
    {
        if (!SetProperty(rootDoc, listenPort))
            return false;

        std::vector<std::string> option = {
            "document_root", rootDoc_,
            "listening_ports", listenPort_
        };

        if(srv_ == nullptr)
        {
            srv_ = new CivetServer(option);
            uiHandler_ = new UiHandler();
            assetHandler_ = new AssetHandler(imageMgr);

            srv_->addHandler("/QueryData", uiHandler_);
            srv_->addHandler("/QueryAsset", assetHandler_);


            log("Service started: http://localhost:%s\n", listenPort_.c_str()); 
            log("RootDocument:%s\n", rootDoc_.c_str());
            return true;
        }
        
        return false;
    }

    bool HttpServer::SetProperty(const std::string& rootDoc, ushort listenPort)
    {
        try
        {
            rootDoc_ = rootDoc;
            listenPort_ = std::to_string(listenPort);
        }
        catch(const std::exception& e)
        {
            err("Failed To Convert Listening Port: %s", e.what());
            return false;
        }

        return true;   
    }

} // namespace Communications

