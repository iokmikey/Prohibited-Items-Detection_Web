#pragma once
#include <string>
#include <onnxruntime_cxx_api.h>

#include "IModel.h"

namespace Ortw
{
    namespace Detection
    {
        class ISession
        {
        public:
            ISession() = default;
            ~ISession() = default;

        public:
            
            // 包括解析和初始化这个会话
            virtual bool initialize(const std::string& modelPath, bool useGpu = true, size_t intra_op_num_threads = 0) = 0;


            inline std::vector<Ort::Value> run(
                const Ort::RunOptions& run_options, 
                const char* const* input_names, const Ort::Value* input_values, size_t input_count,
                const char* const* output_names, size_t output_count
            )
            {
                if(ortSession_) 
                {
                    return ortSession_.Run(run_options, 
                        input_names, input_values, input_count,
                        output_names, output_count);
                }

                return std::vector<Ort::Value>();
            };
            

            inline std::vector<Ort::Value> run(
                const Ort::RunOptions& run_options,
                const std::vector<const char*>& input_names, 
                const std::vector<Ort::Value>& input_value,
                const std::vector<const char*>& ouput_names
            )
            {
                return run(run_options, input_names.data(), input_value.data(), input_value.size(), 
                        ouput_names.data(), ouput_names.size()
                    );
            }


            inline std::vector<Ort::Value> operator() (
                const Ort::RunOptions& run_options,
                const std::vector<const char*>& input_names, 
                const std::vector<Ort::Value>& input_value,
                const std::vector<const char*>& ouput_names)
            {
                return run(run_options, input_names, input_value, ouput_names);
            }

            // 在创建这个tensor 的时候会使用到这个memoryInfo, 用于指定这个->设备和内存类型
            inline const Ort::MemoryInfo& GetDefaultMemoryInfo() { return memoryInfo_; };
            
            inline std::shared_ptr<IModel> GetModel() { return model_; };

        protected:
            
            // Description of memory information
            Ort::MemoryInfo memoryInfo_{nullptr};  
            
            //const std::string m_EnvDefaultName = "envName";
            std::string modelPath_ = ""; // default test

            // ort core session used to inference
            Ort::Session ortSession_{nullptr};

            Ort::Env env_;

            // OnnxModel
            std::shared_ptr<IModel> model_;
        };
    };
};
