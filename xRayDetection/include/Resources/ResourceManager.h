#pragma once

#include "Resources/ModelManager.h"
#include "Resources/ImageManager.h"

#include "Common/INI/INIReader.h"
#include <map>

namespace Resources
{

    enum class ResourcesType
    {
        RES_MODEL,
        RES_PICTURE
    };

    class ResourceManager
    {
    public:
        ResourceManager() = default;
        ~ResourceManager() = default;


        /// @brief 获取图像
        /// @return 
        ImageManager& GetImageManager();

        /// @brief 获取模型
        /// @return 
        ModelManager& GetModelManager();


        /// @brief 使用配置文件初始化资源管理器
        /// @param config 已读取的配置文件
        /// @return 返回是否初始化成功
        bool Initialize(const INIReader& config);


    private:
        bool InitModelManager(const std::string& modelPath, const std::string& extension);

        bool InitImageManager(const std::string& imagePath, const std::string& extension);

    private:
        ImageManager m_imageMgr;
        ModelManager m_modelMgr;
    };

}