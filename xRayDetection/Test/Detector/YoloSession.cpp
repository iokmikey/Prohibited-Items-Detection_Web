#include "YoloSession.h"

#include "DefaultModel.h"

#include <algorithm>

#include "Common/Logger.hpp"

using namespace Ortw::Detection;




bool YoloSession::initialize(const std::string& modelPath, bool useGpu, size_t intra_op_num_threads)
{
    modelPath_ = modelPath;
    env_ = Ort::Env(OrtLoggingLevel::ORT_LOGGING_LEVEL_WARNING, "envName"/*modelPath.c_str()*/);
    Ort::SessionOptions sessionOpt = Ort::SessionOptions();
    sessionOpt.SetIntraOpNumThreads(intra_op_num_threads);

    // 增加使用gpu推理选项
    bool gpuAvail = addGpuOpt(sessionOpt);
    log("inference device: %s\n", gpuAvail ? "GPU":"CPU");
    
    // 创建onnxruntime 会话
    ortSession_ = Ort::Session(env_, modelPath.c_str(), sessionOpt);
    log("Model loaded: ", modelPath .c_str());
    
    // create memory info
    memoryInfo_ = Ort::MemoryInfo::CreateCpu(OrtAllocatorType::OrtDeviceAllocator, 
          OrtMemType::OrtMemTypeCPUInput);
    
    // TODO: 最后加载、解析模型
    model_ = std::make_shared<Ortw::Detection::DefaultModel>();
    return model_->initialize(ortSession_);
}

bool YoloSession::addGpuOpt(Ort::SessionOptions& sessionOpt)
{
    std::vector<std::string> availableProviders = Ort::GetAvailableProviders();
    auto cudaAvailable = std::find(availableProviders.begin(), availableProviders.end(),
        "CUDAExecutionProvider");

    OrtCUDAProviderOptions cudaOption;
    cudaOption.device_id = 0;
    cudaOption.arena_extend_strategy = 0;
    cudaOption.gpu_mem_limit = std::numeric_limits<size_t>::max();
    cudaOption.cudnn_conv_algo_search = OrtCudnnConvAlgoSearchDefault;
    cudaOption.do_copy_in_default_stream = 1;


    // Inference device: GPU
    if(cudaAvailable != availableProviders.end()){
        sessionOpt.AppendExecutionProvider_CUDA(cudaOption);
        return true;
    }
         
    return false;
}