#pragma once
#include <string>
#include <vector>
#include <sys/inotify.h>


namespace Common
{
    class FileWatcher
    {
    public:
        FileWatcher() = default;
        ~FileWatcher();

        bool Initialize(const std::string& path, const std::vector<std::string>& exts, int flag = IN_CREATE);

        void stop();
        
    private:
        int fd_;
        std::string path_; // monitor path
        
        int flag_; // create | move | copy 

        std::vector<std::string> exts_;

        bool run_ = false;
    };
}