#include "NoiseNode.hpp"

NoiseNode::NoiseNode(int id, double samples, double time)
    : AudioNode(id, time), _samples(samples)
{

}

double NoiseNode::play(AudioParams input, double time) {
    double value = double(rand()) / double(RAND_MAX);

    for (int i = 0; i < int(_samples); ++i) {
        value += double(rand()) / double(RAND_MAX);
    }
    return value / int(_samples + 1);
}
