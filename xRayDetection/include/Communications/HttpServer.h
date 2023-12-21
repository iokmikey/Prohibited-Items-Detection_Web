#pragma once
#include "External/Civet/CivetServer.h"
#include "External/Civet/Civetweb.h"

#include "Resources/ImageManager.h"


#include <map>
#include <string>

namespace Communications
{

    

    class HttpServer
    {
    public:
        HttpServer() ;
        ~HttpServer();

        /// @brief 停止并销毁http服务
        void stop();

        /// @brief 创建并启动http服务
        /// @return 返回是否启动成功
        bool start(const std::string& rootDoc, ushort listenPort, Resources::ImageManager& imageMgr);

        inline std::string getDocumentRoot() { return rootDoc_; };
        //inline std::string getServerPort() { return listenPort_; };


        bool SetProperty(const std::string& rootDoc, ushort listenPort);
    private:
        CivetServer* srv_ = nullptr;
        CivetHandler *uiHandler_ = nullptr;
        CivetHandler *assetHandler_ = nullptr;

        std::string rootDoc_;
        std::string listenPort_;
    };

}