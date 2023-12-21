#pragma once

#include "ISession.h"


namespace Ortw
{
    namespace Detection
    {
        class YoloSession: public ISession
        {
        public:
            YoloSession() = default;
            ~YoloSession() = default;

            
            bool initialize(const std::string& modelPath, bool useGpu = true, size_t intra_op_num_threads = 0) override;

        private:
            bool addGpuOpt(Ort::SessionOptions& sessionOpt);

        };
    }
}