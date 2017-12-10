#include "SampleNode.hpp"
#include "MiscConsts.hpp"

SampleNode::SampleNode(int id, double freq, std::string sample, double time)
    : AudioNode(id, time), _freq(freq / 60.)
{

    _period = round((1. / _freq) / (1. / maxiSettings::sampleRate));
    std::cout << _period << std::endl;

    _sample.load(sample);

    _sample.setPosition(POS[id]);
}

double SampleNode::Play (AudioParams input, double time) {

    PERIODS[_id] ++;
    if (PERIODS[_id] >= _period) {
        reset_pos(_id);
        _sample.trigger();
        PERIODS[_id] = 0;
    }


    IncrPhi(_id, _freq);
    incr_pos(_id, _sample.length);

    return _sample.playOnce();
}
