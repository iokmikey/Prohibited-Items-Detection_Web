#include "JsonHelper.h"
#include <QDebug>

int main(int argc, char* argv[])
{
    JsonHelper helper;

    helper.addVersion();
    helper.addElement("cmd", "InitRes");
    
    qDebug() <<helper.toQString();

    QVector<QString> modelNames = {
        "yolov5.onnx",
        "yolov6.onnx",
        "yolov7.onnx"
    };
    helper.addArray("ModelNames", modelNames);

    qDebug() << helper.toQString();
    return 0;
}