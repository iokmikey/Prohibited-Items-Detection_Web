#pragma once

#include <string>
#include <vector>
#include <onnxruntime_cxx_api.h>

namespace Ortw
{
    namespace Detection
    {
        /*
            这个最主要还是存储模型的一些信息， 比如输入输出维度、名字
        */ 
        class IModel
        {
        public:
            
        public:
            IModel() = default;
            ~IModel() = default;

            /* 
                根据模型解析出模型的输入输出的名字、形状、标签等
                session: 已经加载模型的session
                labelPath: 如果模型中不存在标签这项， 可以手动制定标签的路径
            */
            virtual bool initialize(const Ort::Session& session, const std::string& labelPath = "") = 0;


            

        protected:
            

            /* 由于这个inputNamesPtr必须是 const char* const char*类型， 故这个不能改为合并存储， 不方便使用 */
            // 输入
            std::vector<Ort::AllocatedStringPtr>    inputNames_;
            std::vector<const char*>                inputNamesPtr_;  // 指向前面的std::string data头部
            std::vector<std::vector<int64_t>>       inputShapes_;

            // 输出
            std::vector<Ort::AllocatedStringPtr>    outputNames_;
            std::vector<const char*>                outputNamesPtr_; // 指向前面的std::string data头部
            std::vector<std::vector<int64_t>>       outputShapes_;

            // 一般来说同一模型输入的所有元素的类型都是一致的
            ONNXTensorElementDataType               eleType_; 

            // 标签 (onnx模型中也许会不存在这项)
            std::vector<std::string>                labels_;
        };
    }
}