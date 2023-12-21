#pragma once
#include <string>
#include <filesystem>
#include <onnxruntime_cxx_api.h>
#include <opencv2/opencv.hpp>

#include "Detection/YoloDefine.h"

#include "ModelProcessor.h"
#include "ModelParser.h"
#include "Detection/ISession.h"

namespace Detection
{
    
class Yolov5Session: public ISession
{
public:
    Yolov5Session();
    ~Yolov5Session();

    /// @brief 初始化会话
    /// @param modelPath 需要初始化的模型路径
    /// @return 是否成功
    bool Initialize(const std::string& modelPath);

    /// @brief 进行推理检测
    /// @param image 输入的图像
    /// @return 返回检测的结果
    std::vector<ResultNode> Detect(const cv::Mat& image);

private:
    /// @brief 创建一个ort::session会话
    /// @param modelPath 模型路径
    /// @return 是否初始化成功
    bool CreateSession(const std::filesystem::path& modelPath);

    /// @brief 从已初始化好的session上解析模型的输入、输出、以及标签，并且初始化这个预处理和后处理器
    /// @return 是否初始化成功 
    bool ParseModel();

    /// @brief 创建一个带有gpu支持的ortoption
    /// @return OrtCUDAProviderOptions
    OrtCUDAProviderOptions CreateCudaOptions();

    /// @brief 检测gpu是否可用
    /// @return 返回是否可用gpu
    bool IsGPUAvailable();

protected:
    /// @brief 对模型进行预热(有点问题)
    /// @return 
    bool WarmUpModel() override;

private:


    Ort::Session session_{nullptr};
    Ort::SessionOptions sessionOpt {nullptr};
    Ort::Env env_{nullptr};
    std::string envName_;

    ModelProcessor *processor_ = nullptr;

    float confidence = 0.5;
    float iou = 0.6;
    

    bool useGpu = true;
    bool warmup = true;
};
}