#pragma once
#include "IModel.h"

namespace Ortw
{
    namespace Detection
    {

        //  这里对preprocessing 和 postprocessing 还没实现
        class DefaultModel: public IModel
        {
        public:
            DefaultModel() = default;
            ~DefaultModel() = default;

            bool initialize(const Ort::Session& session, const std::string& labelPath = "") override;

        private:
            // 加载模型的标签
            std::vector<std::string> loadLabelFromModel(const Ort::Session& session, const std::string& labelKey = "names");
            std::vector<std::string> loadLabelFromFile(const std::string& filePath);

            void reserveProperty(size_t inputCount, size_t outputCount);

            void parseInputProperty(const Ort::Session& session, size_t inputCnt, const Ort::AllocatorWithDefaultOptions& allocator);
            void parseOutputProperty(const Ort::Session& session, size_t outputCnt, const Ort::AllocatorWithDefaultOptions& allocator);
            
        };
    } // namespace Detection
    
} // namespace Ortw
