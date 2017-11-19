#ifndef OSCNODE_HPP
#define OSCNODE_HPP

#include "AudioNode.hpp"
#include "maximilian.h"



class OscNode : public AudioNode
{
private:
    maxiOsc _osc;
    double _freq;

public:
    OscNode(double freq);

    double* play (double * input);

    void operator<<(const cv::FileNode& n);
};

#endif // OSCNODE_HPP
