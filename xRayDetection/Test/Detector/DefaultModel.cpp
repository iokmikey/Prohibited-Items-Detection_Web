#include "DefaultModel.h"

#include <fstream>
#include <iostream>

#include "Utils.h"

using namespace Ortw::Detection;


bool DefaultModel::initialize(const Ort::Session& session, const std::string& labelPath)
{
    Ort::AllocatorWithDefaultOptions allocator;
    size_t inputCnt = session.GetInputCount();
    size_t outputCnt = session.GetOutputCount();

    //reserveProperty(inputCnt, outputCnt);
    
    parseInputProperty(session, inputCnt, allocator);
    parseOutputProperty(session, outputCnt, allocator);
    
    labels_ = labelPath.empty() ?  loadLabelFromModel(session) : loadLabelFromFile(labelPath);

    return !labels_.empty();
}


std::vector<std::string> DefaultModel::loadLabelFromModel(const Ort::Session& session, const std::string& labelKey)
{
    std::string rawJson;
    Ort::AllocatorWithDefaultOptions allocator;
    Ort::ModelMetadata metaData = session.GetModelMetadata();
    auto keys = metaData.GetCustomMetadataMapKeysAllocated(allocator);
     
    for(const auto& key: keys)
    {
        if(labelKey == key.get())
        {
            auto labelsRaw = metaData.LookupCustomMetadataMapAllocated(labelKey.c_str(), allocator);
            rawJson = std::string(labelsRaw.get());
            return Share::parseLabel(rawJson);
        }
    }

    return std::vector<std::string>();
}

std::vector<std::string> DefaultModel::loadLabelFromFile(const std::string& filePath)
{
    std::vector<std::string> labels;
    std::ifstream file(filePath, std::ios_base::in);
    std::string label;
   
    if(!file.is_open()) 
        return labels;
  
    while (std::getline(file, label))
    {
        label = Share::strip(label);
        if(label.empty())
            continue;
        
        // 可能回报错(待测试) 因为这个采用移动构造， 这个label所有权被移交给了labels
        labels.emplace_back(label); 
    } 
    file.close();

    return labels;
}   

void DefaultModel::reserveProperty(size_t inputCount, size_t outputCount)
{
    inputNames_.reserve(inputCount);
    inputNamesPtr_.reserve(inputCount);
    inputShapes_.reserve(inputCount);

    outputNames_.reserve(outputCount);
    outputNamesPtr_.reserve(outputCount);
    outputShapes_.reserve(outputCount);
}


void DefaultModel::parseInputProperty(const Ort::Session& session, size_t inputCnt, const Ort::AllocatorWithDefaultOptions& allocator)
{
    // 获取输入维度的 信息
    for(size_t idx = 0; idx < inputCnt; ++idx)
    {
        inputNames_.emplace_back(session.GetInputNameAllocated(idx, allocator));
        inputNamesPtr_.push_back(inputNames_[idx].get());
       
        auto TypeInfo = session.GetInputTypeInfo(idx);
        auto TypeAndShape = TypeInfo.GetTensorTypeAndShapeInfo();

        eleType_ = TypeAndShape.GetElementType(); // 修正或则忽略为一次

        inputShapes_.emplace_back(TypeAndShape.GetShape());
    }
}

void DefaultModel::parseOutputProperty(const Ort::Session& session, size_t outputCnt, const Ort::AllocatorWithDefaultOptions& allocator)
{
    // 获取输出维度的信息
    for(size_t idx = 0; idx < outputCnt; ++idx)
    {
        outputNames_.emplace_back(session.GetOutputNameAllocated(idx, allocator));
        outputNamesPtr_.push_back(outputNames_[idx].get());

        auto TypeInfo = session.GetInputTypeInfo(idx); 
        auto TypeAndShape = TypeInfo.GetTensorTypeAndShapeInfo();

        eleType_ = TypeAndShape.GetElementType(); // 修正或则忽略为一次
        outputShapes_.emplace_back(TypeAndShape.GetShape());
    }
}
