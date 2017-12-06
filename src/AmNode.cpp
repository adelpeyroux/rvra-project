#include "AmNode.hpp"
#include "MiscConsts.hpp"

AmNode::AmNode(int id, double freq, double time)
    : AudioNode(id, time), _freq(freq), _initTime(time)
{
    _osc.phaseReset(PHI[_id]);
}

double AmNode::play(AudioParams input, double time) {
    double inVal = 0.;
    double c = 0.;
    GetSignalsAndNumerics(input, inVal, c);

    c /= 32.;

    double value = (c + inVal) * _osc.sinewave(_freq);

    incr_phi(_id, _freq);
    return value;
}
