#include <iostream>

#include <opencv2/imgproc/imgproc.hpp>

#include "Interfaces.hpp"

#ifdef _WIN32
#endif

using namespace cv;
using namespace std;

//***************************************
//***** Constructeurs / Destructeurs ****
//***************************************
Interfaces::Interfaces(int radiusCenter, int radiusButton, int nbsegments, bool segmentation, Scalar Color, double alpha)
	: _RadiusCenter(radiusCenter), _RadiusButton(radiusButton), _Segmentation(segmentation), _Color(Color), _Alpha(alpha)
{
	SetNbSegments(nbsegments);
}

Interfaces::~Interfaces() {}

//****************************
//***** Getters / Setters ****
//****************************
int Interfaces::GetNbSegments() const
{
	return _nbSegments;
}

void Interfaces::SetNbSegments(int nbsegments)
{
	_nbSegments = nbsegments;
	_pasSegments = TWO_PI / nbsegments;
	if (_nbSegments <= 1) _Segmentation = false;
}

void Interfaces::SetInterfaceSize(int h, int w)
{
	_h = h;
	_w = w;
	_Center.x = int(round(1.0 * _w / 2));
	_Center.y = int(round(1.0 * _h / 2));
	_r = _Center.x * _Center.x + _Center.y * _Center.y;
}

//****************
//***** Draws ****
//****************
void Interfaces::DrawInterfaces(Mat& Im, const std::vector<xMarker> &Mi, const std::vector<std::pair<int, int>> &edges) const
{
	Mat Im2 = Mat::zeros(Im.size(), Im.type());
	drawCenter(Im2);
	drawSegmentation(Im2);
	drawLinks(Im2, Mi, edges);
	drawMarkers(Im2, Mi);
	addWeighted(Im2, _Alpha, Im, 1 - _Alpha, 0, Im);
}

void Interfaces::drawCenter(Mat& Im) const
{
	circle(Im, _Center, _RadiusCenter, _Color, -1);
}

void Interfaces::drawSegmentation(Mat& Im) const
{
	if (_Segmentation) {
		for (int i = 0; i < _nbSegments; ++i) {
			Point P2;
			double angle = _pasSegments * i;
			P2.x = int(round(_Center.x + _r * cos(angle)));
			P2.y = int(round(_Center.y + _r * sin(angle)));
			line(Im, _Center, P2, _Color);
		}
	}
}

void Interfaces::drawLinks(Mat& Im, const vector<xMarker>& Mi, const vector<pair<int, int>>& Edges) const
{
	for (int i = 0; i < Edges.size(); ++i) {
        Point P1 = Edges[i].first == -1 ? _Center : Mi[Edges[i].first].GetCenter(),
            P2 = Edges[i].second == -1 ? _Center : Mi[Edges[i].second].GetCenter();
        line(Im, P1, P2, _Color, 2);
	}
}

void Interfaces::drawMarkers(Mat& Im, const vector<xMarker>& Mis) const
{
	for (int i = 0; i < Mis.size(); ++i) drawMarker(Im, Mis[i]);
}

void Interfaces::drawMarker(Mat& Im, const xMarker& Mi) const
{
	//switch draw en fonction du type de marker
	drawSquareMarker(Im, Mi);
	drawMarkerCircle(Im, Mi);
}

void Interfaces::drawMarkerCircle(Mat& Im, const xMarker& Mi) const
{
    const Scalar Color = Type2Color(Mi.GetType());
    const double radius = Mi.GetSize() * SQRT_2 / 2;
    const double new_angle = (Mi.GetAngle() - 90) * M_PI_180;
    const Point P1(Mi.GetCenter().x, Mi.GetCenter().y - int(round(radius)));

	Point P2;
    P2.x = int(round(Mi.GetCenter().x + radius * cos(new_angle)));
    P2.y = int(round(Mi.GetCenter().y + radius * sin(new_angle)));

    circle(Im, Mi.GetCenter(), radius, _Color, 1);
    ellipse(Im, Mi.GetCenter(), Size(radius, radius), -90, 0, Mi.GetAngle(), Color, 3);
	circle(Im, P1, _RadiusButton, _Color, -1);
	circle(Im, P2, _RadiusButton, Color, -1);
}

//***** Markers Type ****
void Interfaces::drawSquareMarker(Mat& Im, const xMarker& Mi) const
{
    const Scalar Color = Type2Color(Mi.GetType());
    RotatedRect rotatedRectangle(Mi.GetCenter(), Size2f(Mi.GetSize(), Mi.GetSize()), Mi.GetAngle());
	Point2f vertices2f[4];
	rotatedRectangle.points(vertices2f);
	Point vertices[4];
	for (int i = 0; i < 4; ++i) vertices[i] = vertices2f[i];
	fillConvexPoly(Im, vertices, 4, Color);
}

Scalar Interfaces::Type2Color(MARKER_TYPE T)
{
	switch (T) {
	case TYPE_OSCILL_SINUS:		return COLORS[3];
	case TYPE_OSCILL_SQUARE:	return COLORS[4];
	case TYPE_OSCILL_TRIANGLE:	return COLORS[5];
	case TYPE_OSCILL_SAW:		return COLORS[6];
	case TYPE_OSCILL_IMPULSE:	return COLORS[7];
	case TYPE_EFFECT_NOISE:		return COLORS[8];
	case TYPE_FILTER_COLOR:		return COLORS[9];
	default:					return COLORS[2];
	}
}

