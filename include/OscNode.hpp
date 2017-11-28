#ifndef OSCNODE_HPP
#define OSCNODE_HPP

#include "AudioNode.hpp"
#include "maximilian.h"



class OscNode : public AudioNode
{
private:
    maxiOsc _osc;
    double _freq;
    double _initTime;

public:
    OscNode(double freq, double time);

    double play (double input, double time);

    void operator<<(const cv::FileNode& n);
};

#endif // OSCNODE_HPP
