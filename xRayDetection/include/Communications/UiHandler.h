#pragma once
#include "External/Civet/CivetServer.h"
#include "External/Civet/Civetweb.h"

#include "Communications/Handler.h"

namespace Communications
{

    // enum UiHandlerCmd
    // {

    // };

    // 用于处理前端的请求
    class UiHandler: public Handler
    {
    protected:
        bool handle() override;
    private:
        /// @brief 处理初始化事件
        /// @return 返回是否成功
        bool handleInit();

        /// @brief 处理切换模型事件
        /// @param modelName 模型名称
        /// @return 返回是否切换成功
        bool handleSwitchModel(const std::string& modelName);

        /// @brief 处理更新设置事件
        /// @return 返回是否设置成功
        bool handleUpdateSettings();

        /// @brief 处理查询是否有新结果事件
        /// @return 返回是否查询成功
        bool handleQueryResult();

        /// @brief 处理获取资源事件
        /// @param path 资源路径
        /// @return 返回是否获取成功
        bool handleGetResources(const std::string& path);

        /// @brief 处理获取图片事件
        /// @param picName 图片名称
        /// @return 返回是否获取成功
        bool handleGetPic(const std::string& picName);

    };
}