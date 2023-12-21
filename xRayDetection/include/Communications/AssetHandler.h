#pragma once

#include "Communications/Handler.h"

#include <unordered_set>

#include <string>

#include "Common/Filesystem.h"

#include "Resources/ImageManager.h"


namespace Communications
{
    class AssetHandler: public Handler
    {
    public:
        AssetHandler(Resources::ImageManager& imageMgr);
        
        /// @brief 实现处理资源请求的实际部分
        /// @return 返回是否成功
        bool handle() override;

        
        /// @brief 处理获取图像的请求
        /// @param conn 
        /// @param name 图像名称
        /// @return 返回处理是否成功
        bool handleImage(const std::string& name);

    private:
        /// @brief 判断是否是符合条件的图像
        /// @param name 图像名称
        /// @return 返回true 如果符合
        bool IsValidImage(const std::string& name);
        


        /// @brief 根据uri获取这个被请求资源的名称
        /// @param uri 
        /// @return 返回这个名称
        std::string GetAssetName(const std::string& uri);
        
        
    private:
        std::string imageRoot;

        /// @brief 存储符合要求的所有后缀类型， 比如jpg jpeg png 
        std::unordered_set<std::string> exts = {"jpg", "jpeg", "png"};

        Resources::ImageManager& m_imageMgr;
    };
}
