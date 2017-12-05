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
    double _phi0;

public:
    OscNode(int id, double freq, double time);

    double play (AudioParams input, double time);

    void operator<<(const cv::FileNode& n);
};

#endif // OSCNODE_HPP
