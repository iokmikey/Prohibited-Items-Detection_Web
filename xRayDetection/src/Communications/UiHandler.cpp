#include "Communications/UiHandler.h"


#include <filesystem> // c++17


#include "MainContext.h"

#include "Common/Logger.hpp"
#include "Communications/UiUtils.h"

namespace Communications
{
    bool UiHandler::handle()
    {
        std::string cmd = getRequestHeader("cmd");   
        log("cmd:%s\n", cmd.c_str());
        
        if(cmd.empty()) {
            err("Failed to get the cmd in headers!\n");
            return false;
        }

        if(cmd == "QueryResult") {
            log("handle QueryResult\n");
            return handleQueryResult();
        }

        if(cmd == "Init") {
            log("handle Init\n");
            return handleInit();
        }
        
        if(cmd == "SwitchModel") {
            log("handle switch Model\n");
            std::string name = getRequestHeader("ModelName");
            return handleSwitchModel(name);
        }
        
        if(cmd == "UpdateSettings") {
            log("handle update settings\n");
            return handleUpdateSettings();
        }

        

        log("\n\n");
		return false;
    }
    
    bool UiHandler::handleInit()
    { 
        // 模拟模型数量
        auto* ins = MainContext::getInstance();
        auto recMgr = ins->GetResoucesManager();
        if(recMgr == nullptr)
            return false;

        std::vector<std::string>modelNameList =  recMgr->GetModelManager().Keys();

        std::string res = UiUtils::CreateInitRes(modelNameList);

        sendJson(conn_, res);

        return true;
    }

    bool UiHandler::handleSwitchModel(const std::string& modelName)
    {   
        auto* ins = MainContext::getInstance();
        auto resMgr = ins->GetResoucesManager();
        if(resMgr == nullptr) {
            err("Invalid Resource Manager Pointer!\n");
            return false;
        }

        std::string modelPath = resMgr->GetModelManager()[modelName];
        if(modelPath.empty()) {
            err("Can`t find the ModelPath, Please Check the ModelName[%s]\n", 
                    modelName.c_str());
            return false;
        }
            
        
        if(!ins->CreateDetector(modelPath)) {
            err("Failed to Create Detector!, Check the ModelPath[%s]\n", 
                    modelPath.c_str());
            return false;
        }
            
        
        auto session = ins->GetCurrentSession();
        auto ModelLabels = session->GetModel()->labels;
        std::string ans = UiUtils::CreateSwitchModelRes(ModelLabels);
        if(ans.empty()) {
            err("Failed to Create the SwitchModel Response Json Text, Check labels\n");
            return false;
        }
            
        
        sendJson(conn_, ans);
        
        log("Model Loaded:[%s], ModelPath:[%s]\n", 
                modelName.c_str(), modelPath.c_str());
        return true;
    }

     bool UiHandler::handleUpdateSettings()
     {
        sendOK(conn_);
        
        return true;
     }

    bool UiHandler::handleQueryResult()
    {
        // get the resultS
        auto* ins = MainContext::getInstance();
        auto& result = ins->GetResultCollection();

        if(result.empty())
            return false;

        static int idx = 0;
        if(idx >= result.size())
            idx = 0;

        
        auto node = result[idx++];
        std::string ans = UiUtils::CreateQueryResultRes(node);
        sendJson(conn_, ans);
    
        return true;
    }


    bool UiHandler::handleGetResources(const std::string& path)
    {
        auto* ctx = MainContext::getInstance();
        if(ctx == nullptr)
            return false;

        auto srv = ctx->GetHttpServer();
        if(srv==nullptr)
            return false;
        
        if(!std::filesystem::exists(path))
            return false;
        
        sendFile(conn_, path);

        return true;
    }

    bool UiHandler::handleGetPic(const std::string& picName)
    {
        std::string path;
        auto* ctx = MainContext::getInstance();
        auto resMgr = ctx->GetResoucesManager();
        if(resMgr == nullptr) {
            err("Invalid Resource Manager Pointer!\n");
            return false;
        }
        
        path = resMgr->GetImageManager()[picName];
        if(path.empty())
            return false;

        sendFile(conn_, path);
        return true;
    }
};