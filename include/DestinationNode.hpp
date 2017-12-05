#ifndef DESTINATIONNODE_HPP
#define DESTINATIONNODE_HPP

#include <stdlib.h>

#include "AudioNode.hpp"
#include "AudioParams.hpp"

class DestinationNode : public AudioNode
{
public:
    DestinationNode(int id, double time);

    double play (AudioParams input, double time);
};

#endif // DESTINATIONNODE_HPP
