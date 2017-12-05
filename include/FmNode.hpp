#ifndef FMNODE_HPP
#define FMNODE_HPP

#include "AudioNode.hpp"
#include "maximilian.h"

class FmNode : public AudioNode
{
private :
    maxiOsc _osc;
    double _freq;
    double _initTime;
    double _phi0;

public:
    FmNode(int id, double freq, double time);
    virtual ~FmNode() = default;

    double play (AudioParams input, double time);
};

#endif // AMNODE_HPP
