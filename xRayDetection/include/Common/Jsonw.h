#pragma once

#include "External/json.hpp"

using json = nlohmann::json;


namespace Common
{
class Jsonw
{
public:
    Jsonw();

    /// @brief 从这个元数据(字符串类型的json)解析为json对象
    /// @param rawJson 字符串原数据
    explicit Jsonw(const std::string& rawJson = "");

    //Jsonw() = delete;

    ~Jsonw() = default;

    /// @brief 根据这个key访问jsonValue对象
    /// @param key key
    /// @return 返回nlohmann::json对象
    json& operator[](const std::string& key);

    /// @brief 这个json对象转换为字符串形式返回
    /// @return 返回的字符串的值 
    std::string toString() const;

private:
    /// @brief 从字符串解析json格式的数据
    /// @param rawJson 字符串类型的原始json
    /// @return 返回解析好的json对象
    json parseFromString(const std::string& rawJson) const;

private:
    /// @brief 保存root json节点
    json rootObj_;
};
}

