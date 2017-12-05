#ifndef DESTINATIONNODE_HPP
#define DESTINATIONNODE_HPP

#include <stdlib.h>

#include "AudioNode.hpp"

class DestinationNode : public AudioNode
{
public:
    DestinationNode(int id, double time);
    virtual ~DestinationNode() = default;

    double play (AudioParams input, double time);
};

#endif // DESTINATIONNODE_HPP
