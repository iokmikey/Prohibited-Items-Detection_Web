#include "Statistics.h"
#include <iostream>
#include <sstream>
#include <filesystem>
#include <algorithm>


std::unordered_map<std::string, size_t> Statistics::Count(const std::string& startTime, const std::string& endTime)
{
    std::unordered_map<std::string, size_t> result;
    char cmd[256] = {0};
    std::string buffer;

    std::string key;
    char delimiter;
    size_t value;
    std::istringstream iss;

    sprintf(cmd, "%s %s --mode=count --csv_file=%s --startTime=\"%s\" --endTime=\"%s\"", 
        executor_.c_str(), scriptRelativePath_.c_str(), csv_path_.c_str(), startTime.c_str(), endTime.c_str());

    
    if(!Execute(cmd, buffer))
        return result;
    
    buffer.erase(std::remove_if(buffer.begin(), buffer.end(), [](char c) {
        return c == ':' || c == ',' || c == '{' || c == '}' || c == '\'' || c == '\n';
    }), buffer.end());
    
    
    iss = std::istringstream(buffer);
    // 循环解析每个键值对
    while (iss >> key >> value) {
        result[key] = value;
    }

    return result; // 这里暂时没有返回
}


bool Statistics::Append(const std::string& timestamp, const std::string& label, float confidence, const std::string& filepath)
{
    std::string outBuffer;
    char cmd[256] = {0};
    sprintf(cmd, "%s %s --mode=append --csv_file=%s --timestamp=\"%s\" --conf=%.2f --label=%s --filepath=%s", 
        executor_.c_str(), scriptRelativePath_.c_str(), csv_path_.c_str(), timestamp.c_str(), confidence, label.c_str(), filepath.c_str());
    
    printf("execute cmd:%s\n", cmd);
    return Execute(cmd, outBuffer);
}

bool Statistics::Execute(const char* cmd, std::string& outBuffer)
{
    FILE* pipe = popen(cmd, "r");
    
    if(!pipe) {
        std::cout  << "filed to execute the cmd:" << cmd << std::endl;
        return false;
    }

    char buffer[128] = {0};
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        outBuffer += buffer;
    }
    fclose(pipe);
    
    return true;
}

bool Statistics::Initialize(const std::string& scriptPath, const std::string& csv_path)
{
    scriptRelativePath_ = scriptPath;
    csv_path_ = csv_path;

    return true;
}