#pragma once
#include <vector>
#include <string>


namespace Detection
{
    struct Model
    {
        Model() = default;
        ~Model() = default;

        /// @brief 模型标签
        std::vector<std::string> labels;

        /// @brief 模型输入维度信息
        std::vector<std::vector<int64_t>> inputShapes;

        /// @brief 模型输出维度信息
        std::vector<std::vector<int64_t>> outputShapes;

        /// @brief 输入维度的名称(一般来说只有一个)
        std::vector<std::string> inputNames;

        /// @brief 这个指针指向上面的每一个inputNames(方便onnxruntime 使用)
        std::vector<const char*> inputNamesPtr;

        /// @brief 输出维度的名称(一个或者多个)
        std::vector<std::string> outputNames;
        
        /// @brief 这个指针指向上面的每一个outputNames(方便onnxruntime 使用)
        std::vector<const char*> outputNamesPtr;
    };

}



