#include "Common/FileWatcher.h"
#include <filesystem>
#include <thread>
#include <atomic>

namespace Common
{
    // void loop(volatile bool run = true, const std::string& path)
    // {

    // }

    FileWatcher::~FileWatcher()
    {
        if(run_)
            stop();
    }

    bool FileWatcher::Initialize(const std::string& path, const std::vector<std::string>& exts, int flag)
    {

        return true;
    }

    void FileWatcher::stop()
    {
    }
}