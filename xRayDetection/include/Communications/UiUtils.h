#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "Detection/YoloDefine.h"
#include "Communications/Structure.hpp"

namespace Communications
{
    // Todo: 
    
    class UiUtils
    {
    public:
        UiUtils() = default;
        ~UiUtils() = default;

    public:
        /// @brief 创建这个初始化返回的json模板，并且填充这个模型列表参数到json中
        /// @param modelNamesList 存在的模型列表
        /// @return 返回生成好的字符串类型的json数据
        static std::string CreateInitRes(const std::vector<std::string>& modelNamesList);

        /// @brief 创建切换模型返回json的模板，并且将数据添加到json中
        /// @param statistics 统计的数据<类别, 被检测到的历史数量>
        /// @return 返回生成好的字符串类型的json数据
        static std::string CreateSwitchModelRes(const std::unordered_map<std::string, int> statistics);
        
        /// @brief 创建切换模型返回json的模板，并且将数据添加到json中，并且将所有统计数据设置为0
        /// @param labels 所有类别的标签
        /// @return 返回生成好的字符串类型的json数据
        static std::string CreateSwitchModelRes(const std::vector<std::string> labels);

        
        /// @brief 创建查询结果的返回json的模板
        /// @param results 查询结果
        /// @return 返回json的字符串形式
        static std::string CreateQueryResultRes(const DetectResults& results);

    private:
        
    };
}