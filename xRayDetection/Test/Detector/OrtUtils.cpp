#include "OrtUtils.h"

#include <unordered_map>

static std::unordered_map<ONNXTensorElementDataType, size_t> TypeToSize = 
{
    { ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT, sizeof(float) },
    { ONNX_TENSOR_ELEMENT_DATA_TYPE_UINT8, sizeof(uint8_t) },
    { ONNX_TENSOR_ELEMENT_DATA_TYPE_INT8, sizeof(int8_t) },
    { ONNX_TENSOR_ELEMENT_DATA_TYPE_UINT16, sizeof(uint16_t) },
    { ONNX_TENSOR_ELEMENT_DATA_TYPE_INT16, sizeof(int16_t) },
    { ONNX_TENSOR_ELEMENT_DATA_TYPE_INT32, sizeof(int32_t) },
    { ONNX_TENSOR_ELEMENT_DATA_TYPE_INT64, sizeof(int64_t) },
    { ONNX_TENSOR_ELEMENT_DATA_TYPE_STRING, sizeof(std::string) },
    { ONNX_TENSOR_ELEMENT_DATA_TYPE_BOOL, sizeof(bool) },
    { ONNX_TENSOR_ELEMENT_DATA_TYPE_FLOAT16, sizeof(ushort) }, // 没有就还short就行
    { ONNX_TENSOR_ELEMENT_DATA_TYPE_DOUBLE, sizeof(double) },
    { ONNX_TENSOR_ELEMENT_DATA_TYPE_UINT32, sizeof(uint32_t) },
    { ONNX_TENSOR_ELEMENT_DATA_TYPE_UINT64, sizeof(uint64_t) },
};


Ort::Value Ortw::Detection::CreateTensor(const OrtMemoryInfo& info, 
            void* data, size_t elementCount, 
            const std::vector<int64_t> shape, 
            ONNXTensorElementDataType type
        )
{
    
    return Ort::Value::CreateTensor(&info, data, elementCount * TypeToSize[type], shape.data(), shape.size(), type);       
}

