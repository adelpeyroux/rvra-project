#include "NumericalNode.hpp"

NumericalNode::NumericalNode(int id, double value, double time)
    : AudioNode(id, time), _value(value)
{

}

double NumericalNode::play(AudioParams input, double time) {
    return _value;
}
