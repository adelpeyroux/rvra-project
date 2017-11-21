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
Interfaces::Interfaces(int radiusCenter, int radiusButton, int nbsegments, bool segmentation, Scalar Color)
	: _RadiusCenter(radiusCenter), _RadiusButton(radiusButton), _Segmentation(segmentation), _Color(Color)
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
    /*
	vector<pair<int, int>> edges(10);
	edges[0] = make_pair(0, 1);
	edges[1] = make_pair(1, 2);
	edges[2] = make_pair(2, 3);
	edges[3] = make_pair(3, 4);
	edges[4] = make_pair(-1, 4);

	edges[5] = make_pair(5, 6);
	edges[6] = make_pair(6, 7);
	edges[7] = make_pair(7, 8);
	edges[8] = make_pair(8, 9);
	edges[9] = make_pair(-1, 9);

	vector<MarkerInfos> Mi(10);
	Mi[0] = {Point(50, 50), 50, 180, TYPE_OSCILL_SINUS};
	Mi[1] = {Point(150, 125), 75, 90, TYPE_OSCILL_SQUARE};
	Mi[2] = {Point(300, 50), 60, 45, TYPE_OSCILL_SAW};
	Mi[3] = {Point(125, 250), 80, -180, TYPE_OSCILL_IMPULSE};
	Mi[4] = {Point(300, 250), 100, 60, TYPE_EFFECT_NOISE};
	Mi[5] = {Point(1000, 50), 65, -60, TYPE_FILTER_COLOR};
	Mi[6] = {Point(1200, 50), 70, -30, TYPE_OSCILL_SINUS};
	Mi[7] = {Point(900, 150), 75, -45, TYPE_OSCILL_SQUARE};
	Mi[8] = {Point(1000, 300), 90, 0, TYPE_OSCILL_SAW};
	Mi[9] = {Point(700, 150), 95, -90, TYPE_OSCILL_TRIANGLE};
    //*/

	drawCenter(Im);
	drawSegmentation(Im);
	drawLinks(Im, Mi, edges);
	drawMarkers(Im, Mi);
}

void Interfaces::drawCenter(Mat& Im) const
{
	circle(Im, _Center, _RadiusCenter, _Color, -1);
}

void Interfaces::drawSegmentation(Mat& Im) const
{
	if (_Segmentation) {
		cout << "Yolo" << endl;
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

