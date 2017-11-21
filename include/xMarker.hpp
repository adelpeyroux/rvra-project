#ifndef XMARKER_HPP
#define XMARKER_HPP

#include <aruco.h>
#include "MiscConsts.hpp"
class xMarker
{
public:
    xMarker(){}
    xMarker(aruco::Marker m);
    xMarker(int h, int w);

    MARKER_TYPE GetType() const{
        return _type;
    }

    bool IsSource() const{
        return isSource(_type);
    }

    cv::Point GetCenter() const{
        return _center;
    }

    double GetSize() const{
        return _size;
    }

    double GetAngle() const{
        return _angle;
    }

    aruco::Marker GetMarker() const{
        return _marker;
    }

private:
    MARKER_TYPE _type;
    cv::Point _center;
    double _size;
    double _angle; // degre
    aruco::Marker _marker;
};

#endif // XMARKER_HPP
