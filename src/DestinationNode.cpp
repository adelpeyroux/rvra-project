#include "DestinationNode.hpp"

DestinationNode::DestinationNode(int id, double time)
  : AudioNode(id, time)
{

}

double DestinationNode::play (AudioParams input, double time) {
    double inVal = 0.;
    int nbVal = 0;
    double c = 0.;
    int nbC = 0;

    for (auto pair : input.GetParams()) {
        if (pair.first != TYPE_SOURCE_NUMERICAL) {
            inVal += pair.second;
            nbVal ++;
        } else {
            c += pair.second;
            nbC ++;
        }
    }

    inVal /= nbVal;
    c /= nbC;

    return inVal;
}
