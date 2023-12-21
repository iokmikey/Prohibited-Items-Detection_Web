#pragma once
#include <unordered_map>
#include <vector>
#include <mutex>

namespace Common
{
    template<typename KeyType, typename ValueType>
    class UMapper
    {
    public:
        UMapper() = default;
        ~UMapper() = default;


        /// @brief 插入数据
        /// @param key 
        /// @param value 
        void Insert(KeyType key, ValueType value) {
            std::unique_lock locker(m_mtx);
            m_data.insert(std::make_pair(key, value));
        }


        /// @brief 删除数据
        /// @param key 
        /// @return 
        bool Remove(KeyType key) {
            std::unique_lock locker(m_mtx);
            return m_data.erase(key);
        };  


        /// @brief 清空所有数据
        void Clear() {
            std::unique_lock locker(m_mtx);
            m_data.clear();
        };


        /// @brief 查找
        /// @param make_pair 
        /// @return 
        ValueType& operator[](KeyType key) {
            std::unique_lock locker(m_mtx);
            return m_data[key];
        }

        const ValueType& Get(KeyType key) {
            std::unique_lock locker(m_mtx);
            const auto& value = m_data[key];
            return value;
        }

        /// @brief 获取所有key值
        /// @return 
        std::vector<KeyType> Keys() {
            std::unique_lock locker(m_mtx);

            std::vector<KeyType> keys;
            for(const auto& item : m_data)  
                keys.push_back(item.first);

            return keys;
        }

        
        /// @brief 获取所有的value值
        /// @return 
        std::vector<ValueType> Values() {
            std::unique_lock locker(m_mtx);

            std::vector<ValueType> values;
            for(const auto& item : m_data) 
                values.push_back(item.second);

            return values;
        }


    private:
        std::unordered_map<KeyType, ValueType> m_data;
        std::mutex m_mtx;
    };

}