#include "OscNode.hpp"
#include "MiscConsts.hpp"

void OscNode::operator<<(const cv::FileNode& n) {
    n["frequency"] >> _freq;
}

OscNode::OscNode(int id, double freq, double time)
    : AudioNode(id, time), _freq(freq), _initTime(time)
{

}

double OscNode::play(AudioParams input, double time) {
    double value = sin (PHI[_id]);
    PHI[_id] += TWO_PI * _freq / double(maxiSettings::sampleRate);
    if (PHI[_id] >= TWO_PI)
    {
        PHI[_id] -= TWO_PI;
    }
    return value;
}
