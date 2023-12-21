#include "App.h"
#include <thread>
#include <chrono>
#include <filesystem>
#include "Common/Logger.hpp"
#include "Common/IQueue.h"
#include "Common/Filesystem.h"
#include "Detection/Mics.h"

App::App(int &argc, char **argv)
{
    // initialize

    ctx_ = MainContext::getInstance();
}

App::~App()
{

}



bool App::Run()
{
    auto resMgr = ctx_->GetResoucesManager();
    auto& imageMgr = resMgr->GetImageManager();
    
    std::vector<std::string> imageNames = imageMgr.Keys();
    Common::IQueue<std::string> imageQueue;
    for(const auto& name : imageNames) {
        imageQueue.Push(name);
    }

    while(1)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
               
        if(ctx_->IsValidDetector() && !imageQueue.Empty())
        {
            std::string filename = imageQueue.Pop();            

            auto session = ctx_->GetCurrentSession();
            auto label = session->GetModel()->labels;
            auto pred = session->Detect(imageMgr[filename]);
            

            DetectResults result;
            result.filename = filename;
            

            cv::Mat outImage =  Detection::RenderBoundingBoxes(imageMgr[filename], pred, label);
            std::string outPath = Common::IFilesystem::ConcatPath(imageMgr.GetOutputPath(), filename);
            cv::imwrite(outPath, outImage);
            
            // 这里是 是否绘制图像
            imageMgr[filename] = outPath;
            
            for(const auto& node: pred)
            {
                std::array<int, 4> coord = {(int)node.x, (int)node.y, (int)node.w, (int)node.h};
                result.node.push_back({
                    label[node.classIdx],
                    node.confidence,
                    coord
                });
            }
            ctx_->InsertResult(result); 
        }

    }

    return true;
}
