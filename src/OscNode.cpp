#include "OscNode.hpp"

void OscNode::operator<<(const cv::FileNode& n) {
    n["frequency"] >> _freq;
}

OscNode::OscNode(double freq)
  : _freq(freq)
{

}

double * OscNode::play(double *input) {
	double * Res = new double[1];
	return Res;
}
