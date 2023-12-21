
#pragma once
#include <string>
#include <vector>
#include <array>

/*
        filename P9923.jpg
        label gun
        confience 98
        coordinate []
    */

struct DetectNode
{
    std::string label;
    float confidence;
    std::array<int, 4> coordinate;
};

struct DetectResults
{
    std::string filename;
    std::vector<DetectNode> node;
};
