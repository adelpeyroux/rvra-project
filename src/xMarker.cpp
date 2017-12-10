#include "xMarker.hpp"

//****************************************
//***** Constructeurs / Destructeurs *****
//****************************************
xMarker::xMarker(int h, int w)
	: _type(TYPE_END), _center(cv::Point(w / 2, h / 2)), _size(1), _angle(0) {}

xMarker::xMarker(aruco::Marker m)
{
	_type = ID2TYPE(m.id);
	_center = m.getCenter();

	cv::Vec2f rVec = m[1] - m[0];

	_angle = SIGN(rVec[1]) * (RAD2DEG * acos(rVec.dot(cv::Vec2f(1, 0)) / sqrt(rVec[0] * rVec[0] + rVec[1] * rVec[1])));
	_size = m.getPerimeter() / 4.;
	_marker = m;
}
