#include "DestinationNode.hpp"
#include "MiscConsts.hpp"

DestinationNode::DestinationNode(int id, double time)
  : AudioNode(id, time)
{

}

double DestinationNode::play (AudioParams input, double time) {
    double inVal = 0.;
    int nbVal = 0;

    for (int i = 0; i < input.GetParams().size(); ++i) {
        if (input.GetParams()[i].type != TYPE_SOURCE_NUMERICAL) {
            inVal += input.GetParams()[i].value;
            nbVal ++;
        }
    }

    if (nbVal > 0)
        return inVal / nbVal;


    return 0.;
}
