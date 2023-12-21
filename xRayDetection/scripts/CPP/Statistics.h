#pragma once
#include <string>
#include <unordered_map>

class Statistics
{
public:
    Statistics() = default;
    ~Statistics() = default;

    /// @brief 统计指定csv下的数据
    /// @return 返回<标签,数量>的map
    std::unordered_map<std::string, size_t> Count(const std::string& startTime, const std::string& endTime);


    /// @brief 增加数据到csv中
    /// @param timestamp 时间戳，以 2023-09-01 06:52:19 格式保存
    /// @param label 类别标签
    /// @param confidence 置信度
    /// @param filepath 文件路径, 可以省略
    /// @return 返回是否执行成功
    bool Append(const std::string& timestamp, const std::string& label, float confidence, const std::string& filepath = "");


    /// @brief 初始化这个统计类
    /// @param scriptPath 执行的python 脚本路径
    /// @param csv_path 需要保存数据的csv路径
    /// @return 返回是否执行成功
    bool Initialize(const std::string& scriptPath = "DataAnalyzer.py", const std::string& csv_path = "xRayData.csv");

private:

    /// @brief 执行cmd命令(采用popen管道执行)
    /// @param cmd 需要执行的命令
    /// @param outBuffer 执行cmd后输出的buffer
    /// @return 返回是否执行成功
    bool Execute(const char* cmd, std::string& outBuffer);

private:

    /// @brief 解释器的名称
    const std::string executor_ = "python";
    
    std::string scriptRelativePath_;
    std::string csv_path_;

    std::string outputFile= "xRayCountOutput.txt";
};
