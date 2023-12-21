
#pragma once
#include <onnxruntime_cxx_api.h>
#include <opencv2/opencv.hpp>
#include <memory>

namespace Ortw
{
    namespace Detection
    {
        class ISession;

        typedef struct _DetectionResultNode
        {
            float x, y, w, h;
            int classIdx;
            float confidence;
        }ResultNode, *pResultNode;

        enum class DetectorType{
            Yolov5 = 0
        };

        class IDetector
        {
        public:
            IDetector() = default;
            ~IDetector() = default;
        
        public:
            /*
            描述: 传入图像， 返回检测结果, 
            参数: 模型需要输入的多个维度、(yolo系列一般只有一个输入)
            */
            virtual std::vector<ResultNode> detect(const std::vector<cv::Mat>& images) = 0;

        protected:
            virtual std::vector<Ort::Value> preprocessing(const std::vector<cv::Mat>& images) = 0;

            virtual std::vector<ResultNode> postprocessing(std::vector<Ort::Value>& tensors) = 0;

        private:
            std::shared_ptr<ISession> session_;
        };
    };
};