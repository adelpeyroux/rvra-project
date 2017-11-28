#pragma once
#include "opencv2/opencv.hpp"

class AudioNode
{    
protected:
    double _phi;

public:
    AudioNode(double time);

    virtual double play (double input, double time) = 0;
};
