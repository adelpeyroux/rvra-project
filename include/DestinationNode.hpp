#ifndef DESTINATIONNODE_HPP
#define DESTINATIONNODE_HPP

#include "AudioNode.hpp"

class DestinationNode : public AudioNode
{
public:
    DestinationNode(int id, double time);

    double play (double input, double time) { return input; }
};

#endif // DESTINATIONNODE_HPP
