#ifndef DESTINATIONNODE_HPP
#define DESTINATIONNODE_HPP

#include "AudioNode.hpp"

class DestinationNode : public AudioNode
{
public:
    DestinationNode();

    double * play (double * input) { return input; }
};

#endif // DESTINATIONNODE_HPP
