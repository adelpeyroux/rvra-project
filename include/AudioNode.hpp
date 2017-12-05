#pragma once
#include "opencv2/opencv.hpp"
#include "AudioParams.hpp"
class AudioNode
{    
protected:
    double _phi;
    int _id;
public:
    AudioNode(int id, double time);

    virtual double play (AudioParams input, double time) = 0;
};
