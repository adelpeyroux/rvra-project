#include "FmNode.hpp"
#include "MiscConsts.hpp"

FmNode::FmNode(int id, double freq, double time)
    : AudioNode(id, time), _freq(freq), _initTime(time)
{
    _osc.phaseReset(PHI[_id]);
}

double FmNode::play(AudioParams input, double time) {
    double inVal = 0.;
    double c = 0.;
    GetSignalsAndNumerics(input, inVal, c);

    double value = _osc.sinewave(_freq + (inVal * c));

    incr_phi(_id, _freq);
    return value;
}
