#pragma once

#include <string>

#include "PathContainer.h"


namespace Resources
{
    /// @brief 只用于管理指定文件夹的所有模型路径
    class ModelManager: public PathContainer
    {
    public:
        ModelManager() = default;
        ~ModelManager() = default;

        bool Initialize(const std::string& modelPath, const std::string& extension);
    };
}