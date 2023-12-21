#include "Resources/ResourceManager.h"
#include "Common/Logger.hpp"


namespace Resources
{


    ImageManager& ResourceManager::GetImageManager()
    {
        return m_imageMgr;
    }

    ModelManager& ResourceManager::GetModelManager()
    {
        return m_modelMgr;
    }

     bool ResourceManager::Initialize(const INIReader& config)
     {

        std::string modelPath = config.GetString("Detection", "ModelPath", "");
        std::string modelExt = config.GetString("Detection", "ModelExtension", "onnx");
        if(modelPath.empty() || modelExt.empty()) {
            err("Invalid ModelPath:[%s] or Extension:[%s]\n", modelPath.c_str(), modelExt.c_str());
            return false;
        }

        log("Config ModelDir:%s, ModelExt:%s\n", modelPath.c_str(), modelExt.c_str());

        std::string imagePath = config.GetString("Images", "MonitorPath", "");
        std::string imageExt = config.GetString("Images", "ImageExtension", "jpg");
        if(imagePath.empty() || imageExt.empty()) {
            err("Invalid ImagePath:[%s] or Extension:[%s]\n", imagePath.c_str(), imageExt.c_str());
            return false;
        }

        return  InitModelManager(modelPath, modelExt) && InitImageManager(imagePath, imageExt);
     }  
    
    bool ResourceManager::InitModelManager(const std::string& modelPath, const std::string& extension)
    {
        return m_modelMgr.Initialize(modelPath, extension);
    }

    bool ResourceManager::InitImageManager(const std::string& imagePath, const std::string& extension)
    {
        return m_imageMgr.Initialize(imagePath, extension);
    }
}