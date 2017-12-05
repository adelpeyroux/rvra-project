#include "AmNode.hpp"
#include "MiscConsts.hpp"

AmNode::AmNode(int id, double freq, double time)
    : AudioNode(id, time), _freq(freq), _initTime(time)
{

}

double AmNode::play(double input, double time) {
    double value = input * sin (PHI[_id]);
    PHI[_id] += TWO_PI * _freq / double(maxiSettings::sampleRate);
    if (PHI[_id] >= TWO_PI)
    {
        PHI[_id] -= TWO_PI;
    }
    return value;
}
