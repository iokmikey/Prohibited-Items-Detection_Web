#include "Common/Jsonw.h"

#include <iostream>

namespace Common
{
    
    Jsonw::Jsonw()
    {

    }

    Jsonw::Jsonw(const std::string& rawJson)
    {
        if(!rawJson.empty())
            rootObj_ = parseFromString(rawJson);
    }

    json& Jsonw::operator[](const std::string& key)
    {
        return rootObj_[key];
    }


    std::string Jsonw::toString() const
    {
        return rootObj_.dump();
    }

    json Jsonw::parseFromString(const std::string& rawJson) const
    {
        json data;
        try 
        {
            data = json::parse(rawJson);
        } catch (const std::exception& e) {
            std::cerr << "JSON parsing error: " << e.what() << std::endl;
            return data;
        }

        return data;
    }
}
