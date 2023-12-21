#pragma once
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVector>
#include <QString>


class JsonHelper
{
public:
    JsonHelper();
    ~JsonHelper() = default;

    void addVersion(const QString& version = "1.0");

    template<typename T>
    void addElement(const QString& name, const T& value)
    {
        obj_.insert(name, value);
    }

    template<typename T>
    void addArray(const QString& name, QVector<T> array)
    {
        tmpData.push_back(new QJsonArray());
        auto& jsonArr = tmpData.back(); 
        
        for(const auto& ele : array)
            jsonArr->append(ele);

        obj_.insert(name, *jsonArr);
    }

    inline void clear()
    {
        for(auto& ptr: tmpData)
        {
            if(ptr)
                delete ptr;
        }

        tmpData.clear();
    }

    QString toQString();

    std::string toStdString();


private:
    QJsonDocument doc_;
    QJsonObject obj_;

    QVector<QJsonArray*> tmpData;
};