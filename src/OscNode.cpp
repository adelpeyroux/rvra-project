#include "OscNode.hpp"

void OscNode::operator<<(const cv::FileNode& n) {
    n["frequency"] >> _freq;
}

OscNode::OscNode(double freq, double time)
  : AudioNode(time), _freq(freq), _initTime(time)
{
}

double OscNode::play(double input, double time) {

    return _osc.sinewave(_freq);
}
