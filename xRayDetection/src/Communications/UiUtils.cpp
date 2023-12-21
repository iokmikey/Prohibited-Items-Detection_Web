#include "Communications/UiUtils.h"

#include "Common/Jsonw.h"

#include "Common/Logger.hpp"

namespace Communications
{


    std::string UiUtils::CreateInitRes(const std::vector<std::string>& modelNamesList)
    {
        Common::Jsonw js = Common::Jsonw("");
        js["cmd"] = "InitResponse";
        
        js["args"]["ModelNames"] = modelNamesList;

        return js.toString();
    }

    std::string UiUtils::CreateSwitchModelRes(const std::unordered_map<std::string, int> statisticsData)
    {
        Common::Jsonw js = Common::Jsonw("");
        
        js["cmd"] = "SwitchResponse";

        std::vector<std::string> labels;
        for(const auto& data: statisticsData)
            labels.push_back(data.first);

        js["args"]["label"] = labels;
        js["args"]["statistics"] = statisticsData;

        
        return js.toString();
    }

    
    std::string UiUtils::CreateSwitchModelRes(const std::vector<std::string> labels)
    {
        Common::Jsonw js = Common::Jsonw("");
        
        js["cmd"] = "SwitchResponse";

        std::unordered_map<std::string, int> statistics;
        for(const auto& name : labels)
            statistics[name] = 0;

        js["args"]["label"] = labels;
        js["args"]["statistics"] = statistics;

        
        return js.toString();
    }
    struct Result
    {
        std::string label;          // 标签
        float confidence;           // 置信度
        std::array<int, 4> coords;  // 左上坐标 和 右下坐标
    };
    
    struct ResultInfo
    {
        std::string imageName;
        std::vector<Result> result;
    };

    std::string UiUtils::CreateQueryResultRes(const DetectResults& results)
    {
        Common::Jsonw js = Common::Jsonw("");
        js["cmd"] = "QueryResultResponse";
        js["args"]["OriginalImage"] = results.filename;

        auto& DetectedItem = js["args"]["DetectedItem"];


        for(int idx = 0; idx < results.node.size(); ++idx)
        {   
            DetectedItem[idx]["label"] = results.node[idx].label;
            DetectedItem[idx]["confidence"] = results.node[idx].confidence;
            DetectedItem[idx]["coordinate"] = results.node[idx].coordinate;
        }

        if(results.node.empty()) {
            DetectedItem = std::vector<std::string>();
        }

        log("%s\n", js.toString().c_str());
        return js.toString();
    } 
}