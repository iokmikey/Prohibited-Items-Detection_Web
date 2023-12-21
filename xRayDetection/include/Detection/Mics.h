#pragma once
#include <vector>
#include <opencv2/opencv.hpp>

#include "YoloDefine.h"

namespace Detection
{
    /// @brief 对得到的结果进行框绘制
    /// @param image 检测图像
    /// @param boxes 得到的结果，包含坐标、类别id、置信度
    /// @param labels 所有的标签
    /// @return 返回绘制好的图像
    inline cv::Mat RenderBoundingBoxes(const cv::Mat& image, const std::vector<ResultNode>& boxes, 
        const std::vector<std::string>& labels)
    {
        cv::Mat out = image.clone();

        for (const auto& box : boxes) {
            int x = box.x > 0 ? box.x : 0;
            int y = box.y > 0 ? box.y : 0;
            int width = box.x + box.w < image.cols ? box.w : image.cols - box.x;
            int height = box.y + box.h < image.rows ? box.h : image.rows - box.h;

            cv::rectangle(out, cv::Rect(box.x, box.y, width, height), cv::Scalar(0, 255, 0), 2); // 绘制绿色边界框，线宽为2

            cv::Point labelPosition(box.x, box.y - 10); // 调整标签位置，使其位于边界框上方
            cv::putText(out, labels[box.classIdx], labelPosition, cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 255), 1);
        }
        return out;
    }

    inline cv::Mat RenderBoundingBoxes(const std::string& imagePath, const std::vector<ResultNode>& boxes, 
        const std::vector<std::string>& labels)
    {
        cv::Mat image = cv::imread(imagePath);
        return RenderBoundingBoxes(image, boxes, labels);
    }
}
