#include "OscNode.hpp"
#include "MiscConsts.hpp"

OscNode::OscNode(int id, double freq, int type, double time)
    : AudioNode(id, time), _freq(freq), _initTime(time), _type(type)
{
     _osc.phaseReset(PHI[_id]);
}

double OscNode::play(AudioParams input, double time) {


    double value = 0.;

    switch (_type) {
    case OSC_SAW:
        value = _osc.sawn(_freq);
        break;
    case OSC_SQUARE:
        value = _osc.square(_freq);
        break;
    case OSC_TRIANGLE:
        value = _osc.triangle(_freq);
        break;
    case OSC_SINE:
    default:
        value = _osc.sinewave(_freq);
        break;
    }


    incr_phi(_id, _freq);
    return value;
}
