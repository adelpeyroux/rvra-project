#pragma once

#include "MiscConsts.hpp"

class xMarker
{
private:
	MARKER_TYPE _type;
	cv::Point _center;
	double _size;
	double _angle; // degre
	aruco::Marker _marker;

public:
	//***** Constructeurs / Destructeurs *****
	xMarker()
		: _type(NO_TYPE), _size(1), _angle(0) {}
	xMarker(int h, int w);
	explicit xMarker(aruco::Marker m);
	virtual ~xMarker() = default;


	//***** Getters / Setters *****
	MARKER_TYPE GetType() const { return _type; }
	cv::Point GetCenter() const { return _center; }
	double GetSize() const { return _size; }
	double GetAngle() const { return _angle; }
	aruco::Marker GetMarker() const { return _marker; }

	//***** Misc *****
	bool isSource() const { return IsSource(_type); }
};
