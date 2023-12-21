#include "JsonHelper.h"


JsonHelper::JsonHelper()
{
    
}

void JsonHelper::addVersion(const QString& version)
{
    addElement("version", version);
}


QString JsonHelper::toQString()
{
    doc_.setObject(obj_);
    return QString::fromUtf8(doc_.toJson());
}

std::string JsonHelper::toStdString()
{
    doc_.setObject(obj_);
    return toQString().toStdString();
}