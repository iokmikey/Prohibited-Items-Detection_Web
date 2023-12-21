#include "Resources/ImageManager.h"

#include <vector>
#include <string>

#include "Common/Filesystem.h"
#include "Common/Logger.hpp"

namespace Resources
{
    bool ImageManager::Initialize(const std::string& imagePath, const std::string& extension)
    {
        if(!Common::IFilesystem::IsExist(imagePath)) {
            err("Invalid imagePath:\n", imagePath.c_str());
            return false;
        }
    
        std::string resultDir = Common::IFilesystem::JoinCurrentPath("results");
        if(!Common::IFilesystem::IsExist(resultDir)) {
            Common::IFilesystem::CreateDir(resultDir);
        }
        m_outputPath = resultDir;
        
        

        /// 目前暂时使用这个中方式读取图像
        std::vector<std::string>imagePaths = Common::IFilesystem::GetFilesBySuffix(imagePath, extension);
        this->InsertPaths(imagePaths);

        return true;
    }    

    const std::string& ImageManager::GetOutputPath() const
    {
        return m_outputPath;
    }
} // namespace Resources

