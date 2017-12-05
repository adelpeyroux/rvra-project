#include "AmNode.hpp"
#include "MiscConsts.hpp"

AmNode::AmNode(int id, double freq, double time)
    : AudioNode(id, time), _freq(freq), _initTime(time)
{

}

double AmNode::play(AudioParams input, double time) {
    double inVal = 0.;
    int nbVal = 0;
    double c = 0.;
    int nbC = 0;

    for (auto pair : input.GetParams()) {
        if (pair.type != TYPE_SOURCE_NUMERICAL) {
            inVal += pair.value;
            nbVal ++;
        } else {
            c += pair.value;
            nbC ++;
        }
    }

    if (nbVal > 0)
        inVal /= nbVal;

    if (nbC > 0)
        c /= nbC;

    double value = (c + inVal) * sin (PHI[_id]);
    PHI[_id] += TWO_PI * _freq / double(maxiSettings::sampleRate);
    if (PHI[_id] >= TWO_PI)
    {
        PHI[_id] -= TWO_PI;
    }
    return value;
}
