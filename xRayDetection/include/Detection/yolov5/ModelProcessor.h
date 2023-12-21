#pragma once
#include <vector>
#include <onnxruntime_cxx_api.h>
#include <opencv2/opencv.hpp>

#include "Detection/YoloDefine.h"
#include "Detection/Model.h"


namespace Detection
{
    
class ModelProcessor
{
public:
    ModelProcessor(Model* model);
    ModelProcessor() = delete;
    ~ModelProcessor();

    // yolov5 模型的预处理函数(归一化图像存储格式为RGB、图像大小为模型指定大小、生成Onnxruntime需要的Ort::Value类型并且返回)
    std::vector<Ort::Value> Preprocess(const cv::Mat& image);

    // yolov5后处理(主要是读取原始onnxruntime生成的数据并解析后经nms处理 的到符合阈值的结果集合并返回)
    std::vector<ResultNode> Postprocess(const std::vector<Ort::Value>& outTensor, 
            const cv::Size& originalImageShape, 
            float confThreshold, float iouThreshold);

private:
    
    /// @brief 将图像归一画为统一大小，符合这个模型的输入维度的尺寸
    /// @param image 输入图像
    /// @param newShape 这个模型需要输入的形状大小
    /// @param color 填充颜色
    /// @param scaleFill 是否
    /// @param scaleUp 
    /// @param stride 
    /// @return 
    cv::Mat Letterbox(const cv::Mat& image, const cv::Size& newShape = cv::Size(640, 640), 
          const cv::Scalar& color = cv::Scalar(114, 114, 114), bool scaleFill = false, bool scaleUp = true,
          int stride = 32);

    /// @brief 图像由opencv读取的格式， 转换为RGB
    /// @param image 输入图像
    /// @param outImage 输出的图像
    /// @return 返回是否成功
    bool ConvertToRGB(const cv::Mat& image, cv::Mat& outImage);


    /// @brief 计算原始图像中的坐标
    /// @param currentShape 当前的图像形状
    /// @param originalShape 原始的图像形状
    /// @param outCoords 将原始图像中的坐标返回到outCoords
    void GetOriCoords(const cv::Size& currentShape, 
                    const cv::Size& originalShape, cv::Rect& outCoords);

    /// @brief  获取 当前box框中 score 最高的一个 类别
    /// @param it 
    /// @param numClasses 
    /// @param bestConf 
    /// @param bestClassId 
    void GetBestClassInfo(std::vector<float>::iterator it, const int& numClasses, float& bestConf, int& bestClassId);


    /// @brief 解析模型的输出
    /// @param tensor 
    /// @param conf_threshold 
    /// @param boxes 
    /// @param confs 
    /// @param classIds 
    void ParseRawOutput(const std::vector<Ort::Value>& tensor, float conf_threshold,std::vector<cv::Rect>& boxes, std::vector<float>& confs, std::vector<int>& classIds);

private:

    Model* model_ = nullptr;

    float* blob_ = nullptr;
    size_t blobSize_ = 0;

    Ort::MemoryInfo memInfo_{nullptr};
};
}
