#ifndef XMARKER_HPP
#define XMARKER_HPP

#include <aruco.h>
#include "MiscConsts.hpp"
class xMarker
{
public:
    xMarker(aruco::Marker m);

private:
    MARKER_TYPE _type;
    cv::Point _center;
    double _size;
    double _angle; // degre
    aruco::Marker _marker;
};

#endif // XMARKER_HPP
