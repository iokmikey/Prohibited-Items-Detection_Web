#pragma once
#include "Resources/PathContainer.h"



namespace Resources
{   
    /// @brief 管理图像的存储
    class ImageManager: public PathContainer
    {
    public:
        ImageManager() = default;
        ~ImageManager() = default;


        bool Initialize(const std::string& imagePath, const std::string& extension);

        const std::string& GetOutputPath() const;
        
    private:
        std::string m_outputPath;

    };
} // namespace Resources
