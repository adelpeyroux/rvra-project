#pragma once
#include "opencv2/opencv.hpp"

class AudioNode
{    
protected:
    double _phi;
    int _id;
public:
    AudioNode(int id, double time);
    virtual ~AudioNode() = default;
    virtual double play (double input, double time) = 0;
};
