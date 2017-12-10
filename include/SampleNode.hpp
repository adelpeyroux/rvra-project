#ifndef SAMPLENODE_HPP
#define SAMPLENODE_HPP

#include <stdlib.h>
#include <string>

#include "AudioNode.hpp"
#include "maximilian.h"

class SampleNode : public AudioNode
{
public:
    SampleNode(int id, double freq, std::string sample, double time);

    double Play (AudioParams input, double time);
private:
    maxiOsc _phasor;
    maxiSample _sample;

    double _freq;
};

#endif // SAMPLENODE_HPP
