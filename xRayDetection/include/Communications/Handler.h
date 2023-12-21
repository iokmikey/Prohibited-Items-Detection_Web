#pragma once


#include <string>

#include "External/Civet/CivetServer.h"

namespace Communications
{

    class Handler: public CivetHandler
    {
    public:
        Handler() = default;
        ~Handler() = default;

        /// @brief 这个属于是框架的回调函数，收到这个Get请求之后会调用这个函数
        /// @param server 
        /// @param conn 
        /// @return 
        bool handleGet(CivetServer* server, struct mg_connection* conn) override;


        /// @brief 获取请求头中的value
        /// @param name key
        /// @return value
        std::string getRequestHeader(const std::string& name);


        /// @brief 获取响应投头的value
        /// @param name key
        /// @return value
        std::string getResponseHeader(const std::string& name);


        /// @brief 发送Json数据
        /// @param conn mg_connection的指针
        /// @param jsonData 需要发送的数据
        /// @param optionalHeaders 额外需要发送的头部
        void sendJson(mg_connection *conn, const std::string& jsonData, 
            const std::vector<mg_header>& optionalHeaders = std::vector<mg_header>());

        /// @brief 只响应接受成功
        /// @param conn 
        void sendOK(mg_connection *conn);

        /// @brief 发送错误响应带有错误code
        /// @param conn mg_connection指针
        /// @param code 错误code
        void sendErr(mg_connection *conn, int code);

        /// @brief 向对端发送文件
        /// @param conn mg_connection指针
        /// @param path 文件的本地路径
        void sendFile(mg_connection *conn, const std::string& path);
    
    private:

        /// @brief 根据这个name获取这个mg_header中的value， 类似于map<std::string, string>, 使用框架所提供的获取值会报错
        /// @param headers 指向mg_header的指针
        /// @param numHeaders 总共有多少个值key, value对
        /// @param name 所需要获取的key的值
        /// @return 如果查询到了则返回对应的value， 否则返回空字符串
        std::string getHeader(const mg_header *headers, int numHeaders, const std::string& name);

    
    protected:
        virtual bool handle() = 0;

    protected:
        /// @brief 这个是每次handle的时候需要更新的
        mg_connection *conn_ = nullptr;
        CivetServer* server_ = nullptr;
    };

};
