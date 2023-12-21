
#pragma once

#include <memory>

#include <mutex>

#include "Detection/ISession.h"
#include "Detection/yolov5/Yolov5Session.h"

#include "Communications/HttpServer.h"

#include "Resources/ResourceManager.h"

#include "Communications/Structure.hpp"
#include "Communications/DetectResultQueue.hpp"

#include "Common/INI/INIReader.h"

class MainContext
{
    friend class App;

public:
    

    bool initialize();

public:
    

    /// @brief 获取全局唯一Context实例
    /// @return 如果已初始化或者初始化成功则返回该指针，否则返回空指针
    static inline MainContext *&getInstance() { 
        std::unique_lock<std::mutex> lock(m_mtx);

        if (m_instance == nullptr)
        {
            m_instance = new (std::nothrow)MainContext;
            bool valid = m_instance->initialize();
            

            log("initialize state:%s\n", valid ? "Sucess" : "Unsucess");
            if(!valid && m_instance) {
                delete m_instance;
                m_instance = nullptr;
                exit(1);
            }
        }

        return m_instance;
    };

    inline void deleteInstance()
    {
        std::unique_lock<std::mutex> lock(m_mtx);
        
        if(m_instance != nullptr)
        {
            delete m_instance;
            m_instance = nullptr;
        }
    }

    /// @brief 获取资源管理器
    /// @return 返回资源管理器指针
    inline std::shared_ptr<Resources::ResourceManager>
        GetResoucesManager() { return m_resMgr; };

    /// @brief 获取Http服务器的指针
    /// @return 返回服务器指针
    inline std::shared_ptr<Communications::HttpServer> 
        GetHttpServer() { return m_srv; };


    /// @brief 创建一个Detector
    /// @param modelPath 模型的完整路径
    /// @return 返回是否创建成功
    bool CreateDetector(const std::string& modelPath);

    /// @brief 获取当前的会话
    /// @return 返回当前会话的指针
    inline std::shared_ptr<Detection::ISession> 
        GetCurrentSession() { return m_session; };

    /// @brief 检测当前的会话是否已经初始化
    /// @return 返回true 如果已经初始化了
    inline bool IsValidDetector() { return !m_curSessionId.empty(); };

    /*
    
    /// @brief 获取这个检测结果的队列
    /// @return 返回这个结果queue
    inline DetectResultQueue& GetResultQueue() { return results; };
    
    /// @brief 获取图像待检测队列
    /// @return 返回图像队列
    inline ImageQueue& GetImageQueue() { return imageQue_; };
*/

    inline void InsertResult(const DetectResults& result) {
        m_result.push_back(result);
    };

    inline const std::vector<DetectResults>& GetResultCollection() {
        return m_result;
    }

private:
    
    /// @brief 创建http 服务，UI界面
    /// @param rootDoc http document的根目录
    /// @param listenPort 监听端口
    /// @return 返回是否启动成功
    bool CreateService(const std::string& rootDoc, ushort listenPort);

    /// @brief 根据配置文件创建这个资源管理器
    /// @param config 配置文件
    /// @return 返回是否创建成功
    bool CreateResourceManager(const INIReader& config);

    

private:
    MainContext() = default;
    ~MainContext() = default;

    MainContext(const MainContext& other) = delete;
    MainContext &operator=(const MainContext& other) = delete;
    
    /// @brief 当前会话的名称
    std::string m_curSessionId;

    /// @brief 当前会话指针
    std::shared_ptr<Detection::ISession> m_session;

    /// @brief http服务
    std::shared_ptr<Communications::HttpServer> m_srv;

    /// @brief 资源管理器
    std::shared_ptr<Resources::ResourceManager> m_resMgr = nullptr;

    /// @brief 
    std::vector<DetectResults> m_result;


    /// @brief 全局唯一实例
    static MainContext *m_instance;
    static std::mutex m_mtx;
};




