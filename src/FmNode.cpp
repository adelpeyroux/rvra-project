#include "FmNode.hpp"
#include "MiscConsts.hpp"

FmNode::FmNode(int id, double freq, double time)
    : AudioNode(id, time), _freq(freq), _initTime(time)
{

}

double FmNode::play(double input, double time) {
    double value = sin (PHI[_id] + 5 * input);
    PHI[_id] += TWO_PI * _freq / double(maxiSettings::sampleRate);
    if (PHI[_id] >= TWO_PI)
    {
        PHI[_id] -= TWO_PI;
    }
    return value;
}
