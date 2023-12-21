#pragma once
#include <mutex>
#include <queue>

#include "Communications/Structure.hpp"

class DetectResultQueue
{
private:
    /* data */
public:
    DetectResultQueue(/* args */) = default;
    ~DetectResultQueue() = default;
    
    inline void push(const DetectResults& node);

    inline DetectResults pop();

private:
    std::queue<DetectResults> data_;

    std::mutex mtx_;
};

void DetectResultQueue::push(const DetectResults& node)
{
    mtx_.lock();
    data_.push(node);
    mtx_.unlock();
}

DetectResults DetectResultQueue::pop()
{
    DetectResults ret = {};
    if(data_.empty())
        return ret;
    
    mtx_.lock();
    ret = data_.front();
    data_.pop();
    mtx_.unlock();

    return ret;  
}



