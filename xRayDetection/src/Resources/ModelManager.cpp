#include "Resources/ModelManager.h"

#include "Common/Filesystem.h"

#include "Common/Logger.hpp"

namespace Resources
{
    bool ModelManager::Initialize(const std::string &modelPath, const std::string &extension)
    {
        log("Init Model:%s, Extension:%s\n", modelPath.c_str(), extension.c_str());
        if(!Common::IFilesystem::IsExist(modelPath)) 
            return false;
        
        log("Init Model Manager!\n");
        std::vector<std::string> models =  Common::IFilesystem::GetFilesBySuffix(modelPath, extension);    
        for(const auto& model : models) {
            InsertPath(model);
        }

        return true;
    }


}
