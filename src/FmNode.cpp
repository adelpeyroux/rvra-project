#include "FmNode.hpp"
#include "MiscConsts.hpp"

FmNode::FmNode(int id, double freq, double time)
    : AudioNode(id, time), _freq(freq), _initTime(time)
{

}

double FmNode::play(AudioParams input, double time) {
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

    double value = sin (PHI[_id] + c * inVal);
    PHI[_id] += TWO_PI * _freq / double(maxiSettings::sampleRate);
    if (PHI[_id] >= TWO_PI)
    {
        PHI[_id] -= TWO_PI;
    }
    return value;
}
