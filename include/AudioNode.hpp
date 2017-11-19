#pragma once
#include "opencv2/opencv.hpp"

class AudioNode
{    
public:
    AudioNode();

    virtual double* play (double * input) = 0;
};
