#ifndef NUMERICALNODE_H
#define NUMERICALNODE_H

#include "AudioNode.hpp"

class NumericalNode : public AudioNode
{
private:
    double _value;

public:
    NumericalNode(int id, double value, double time);
    virtual ~NumericalNode() = default;

    double play (AudioParams input, double time);
};

#endif // NUMERICALNODE_H
