#pragma once

namespace Detection
{
    /// @brief 用于表示检测的结果
    typedef struct _DetectionResultNode
    {
        float x, y, w, h;  // 左上角坐标x,y 和矩形的宽高
        int classIdx;
        float confidence;
    }ResultNode, *pResultNode;


    // 这个可以用来结构化显示这个yolo系列输出的原始数据结构
    struct RawResult
    {
        float cx;       // center x
        float cy;       // center y
        float w;        // width
        float h;        // height
        float cls_conf; // class confidence
    }__attribute__((packed));

    typedef RawResult* pRawResult;

// 占用多少个， 一个box中占用5个元素
#define YOLOV5_OUTBOX_ELEMENT_COUNT 5


   
}



