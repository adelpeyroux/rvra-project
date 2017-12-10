#include "SampleNode.hpp"
#include "MiscConsts.hpp"

SampleNode::SampleNode(int id, double freq, std::string sample, double time)
    : AudioNode(id, time), _freq(freq)
{
    _phasor.phaseReset(PHI[id]);
    _sample.load(sample);

    _sample.setPosition(POS[id]);
}

double SampleNode::Play (AudioParams input, double time) {

    int trigger = (int)_phasor.phasor(_freq / 60.);

    double value = 0.;
    if (trigger != PREV[_id] && trigger == 1) {
        _sample.trigger();
        reset_pos(_id);
    }

    PREV[_id] = trigger;

    IncrPhi(_id, _freq);
    incr_pos(_id, _sample.length);

    return _sample.playOnce();
}
