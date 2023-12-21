#pragma once
#include <onnxruntime_cxx_api.h>

namespace Ortw
{
    namespace Detection
    {
        // 根据这个type区创建Tensor
        Ort::Value CreateTensor(const OrtMemoryInfo& info, 
            void* data, size_t dataSize, 
            const std::vector<int64_t> shape, 
            ONNXTensorElementDataType type
        );


        // 简化这个输入的参数， 默认数据类型float
        template <typename T>
        Ort::Value CreateTensor(const OrtMemoryInfo& info, 
            std::vector<T>data, std::vector<int64_t> shape, ONNXTensorElementDataType type = ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT)
        {
            return CreateTensor(info, data.data(), data.size(), shape, type);
        }


        // 从这个数据类型到这个数据 被擦出类型之后所占用空间大小  的映射
        //static std::unordered_map<ONNXTensorElementDataType, size_t> TypeToSize;
    }
}
