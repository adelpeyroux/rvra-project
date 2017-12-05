#ifndef AMNODE_HPP
#define AMNODE_HPP

#include "AudioNode.hpp"
#include "AudioParams.hpp"
#include "maximilian.h"

class AmNode : public AudioNode
{
private :
    maxiOsc _osc;
    double _freq;
    double _initTime;
    double _phi0;

public:
    AmNode(int id, double freq, double time);

    double play (AudioParams input, double time);
};

#endif // AMNODE_HPP
