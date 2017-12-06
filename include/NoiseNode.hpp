#ifndef NOISENODE_HPP
#define NOISENODE_HPP

#include "AudioNode.hpp"
#include <cstdlib>

class NoiseNode : public AudioNode
{
private:
    double _samples;

public:
    NoiseNode(int id, double samples, double time);
    virtual ~NoiseNode() = default;

    double play (AudioParams input, double time);
};
#endif // NOISENODE_HPP