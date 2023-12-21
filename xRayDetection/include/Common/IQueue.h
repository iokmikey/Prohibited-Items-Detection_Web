#pragma once
#include <queue>
#include <mutex>


namespace Common
{
    
    /// @brief 提供一个安全的队列
    /// @tparam T 

    template<typename T>
    class IQueue
    {
    public:
        IQueue() = default;
        ~IQueue() = default;

        /// @brief 向队列压入一个数据
        /// @param value 压入的值
        void Push(const T& value)
        {
            std::unique_lock<std::mutex> locker(m_mtx);
            
            m_data.push(value);
        }

        /// @brief 如果存在数据，则弹出并返回队首的值
        /// @return 返回队首值
        T Pop()
        {
            T value = {};
            std::unique_lock<std::mutex> locker(m_mtx);

            if(!m_data.empty()) {
                value = m_data.front();
                m_data.pop();    
            }
                
            return value;
        }

        size_t Size() {
            return m_data.size();
        }

        bool Empty() {
            return m_data.empty();
        }

    private:
        std::queue<T> m_data;
        std::mutex m_mtx;
    };
};