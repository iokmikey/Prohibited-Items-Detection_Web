#pragma once


#include "Common/UMapper.h"

namespace Resources
{   

    /// @brief 用于保存文件路径并且分割出他的实际名称，提供使用key->path的映射
    class PathContainer: 
        public Common::UMapper<std::string, std::string>
        ///  是 <文件名 -> 文件完整路径> 的映射
    {
    public:
        PathContainer() = default;
        ~PathContainer() = default;
        
        void InsertPath(const std::string& fullPath);

        void InsertPaths(const std::vector<std::string>& paths);
        
    private:
        
    };  

    



}