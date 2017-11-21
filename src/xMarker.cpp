#include "xMarker.hpp"

xMarker::xMarker(int h, int w)
{
    _type = TYPE_END;
    _center = cv::Point(w/2, h/2);


    _angle = 0;
    _size = 0;
}

xMarker::xMarker(aruco::Marker m)
{
    _type = id2type(m.id);
    _center = m.getCenter();
    m.calculateExtrinsics(MarkerSize, CameraParams);

    _angle = std::acos(m.Rvec.dot(cv::Vec3f(0,1,0)));
    _size = m.getPerimeter() / 4.;
    _marker = m;
}
