#pragma once
#include <string>
#include <vector>

#include <onnxruntime_cxx_api.h>

#include "Detection/Model.h"

namespace Detection
{

class ModelParser
{
private:
    /* data */
public:
    ModelParser() = default;
    ~ModelParser() = default;

    /// @brief 解析模型
    /// @param session 执行onnxruntime的session指针
    /// @return 返回解析完成的Model指针
    static Model* parse(Ort::Session* session);

private:
    /// @brief 解析这个session会话中的输入结构，将结果保存到这个model指向的地址中
    /// @param session 已加载的Ort会话
    /// @param model 需要用于存储的Model指针
    /// @return 返回是否成功
    static bool parseInput(Ort::Session* session, Model* model);


    /// @brief 解析这个session会话中输出结构，将结果保存到这个model指向的地址中
    /// @param session 已加载的Ort会话
    /// @param model 需要用于存储的Model指针
    /// @return 返回是否成功
    static bool parseOutput(Ort::Session* session, Model* model);

    /// @brief 在这个ort::session中如解析这个模型的标签集合，并且存储在这个model中
    /// @param session 已加载的Ort会话
    /// @param model 输出的Model指针
    /// @param labelKey 这个标签在模型中的key值
    /// @return 返回是否成功
    static bool parseLabels(Ort::Session* session, Model* model, const std::string& labelKey = "names");

    /// @brief 解析json格式的标签，并且以std::vector<std::string>类型的数据返回
    /// @param rawData 字符串原始json数据
    /// @return 解析到的标签
    static std::vector<std::string> parseLabelsRaw(const std::string& rawData);

};

}
