#pragma once
#include <string>
#include <vector>
#include <algorithm>

namespace Ortw
{
    namespace Share
    {
        /*
            description: 删除字符串左右两端的空格、换行符、水平制表符
            str: 原始字符串
        */
        inline std::string strip(const std::string& str)
        {
            std::string result = str;

            result.erase(std::remove_if(result.begin(), result.end(), [](char ch){
                return std::isblank(ch);
            }), result.end());

            return result;
        }

        /*
            目前仅用于从yolo系列导出到onnx 模型中读取出来的raw string 解析 标签
        */ 
        std::vector<std::string> parseLabel(const std::string& rawData)
        {
            std::vector<std::string> labels;
            std::string data = rawData;
            bool inValue = false;
            size_t start, len;

            for(size_t idx = 0; idx < data.size(); ++idx)
            {
                if(data[idx] != '\'')
                    continue;   
                // 等于 '
                if(!inValue)
                {
                    start = idx + 1;
                    inValue = true;
                }else{
                    len = idx - start;
                    inValue = false;
                    labels.push_back(data.substr(start, len));
                }
            }
            return labels;
        }
    }
}