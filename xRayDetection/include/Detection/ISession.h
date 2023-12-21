#pragma once
#include <vector>
#include <string>

#include <opencv2/opencv.hpp>

#include "YoloDefine.h"
#include "Model.h"

#include "Common/Logger.hpp"

namespace Detection
{
    
class ISession
{
public:
    ISession() = default;
    ~ISession() = default;


public:
    /// @brief 初始化[推理会话 、 解析模型]
    /// @param modelPath 模型路径
    /// @return 返回是否初始化成功
    virtual bool Initialize(const std::string& modelPath) = 0;

    /// @brief 执行一次推理
    /// @param image 推理输入的图像
    /// @return 返回结果
    virtual std::vector<ResultNode> Detect(const cv::Mat& image) = 0;

    
    /// @brief 执行推理
    /// @param filepath 图像路径 
    /// @return 
    inline std::vector<ResultNode> Detect(const std::string& filepath) {
        cv::Mat image;
        try {
            image = cv::imread(filepath);    
        }
        catch(const std::exception& e) {
            std::cerr << "Failed to read the file:" << filepath.c_str() << "\t error:"<< e.what() << '\n';
        }
        
        log("detect path: %s\n", filepath.c_str());
        return Detect(image);
    };

    /// @brief 获取模型参数
    /// @return 返回Model指针 
    virtual Model* GetModel()  { return model_; };

    /// @brief 设置confidence 阈值
    /// @param conf 置信度
    virtual void SetConfidence(float conf) { confidenceThreshold_ = conf; };

    /// @brief 设置iou阈值
    /// @param iou 交并比
    virtual void SetIOU(float iou) { iouThreshold_ = iou; };

protected:
    /// @brief 预热
    /// @return 是否成功
    virtual bool WarmUpModel() = 0;

protected:
    Model *model_;

    float confidenceThreshold_;
    float iouThreshold_;
};
}
