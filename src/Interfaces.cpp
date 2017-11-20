#include <iostream>

#include <opencv2/imgproc.hpp>

#include "Interfaces.hpp"

#ifdef _WIN32
#endif

using namespace cv;
using namespace std;

//***************************************
//***** Constructeurs / Destructeurs ****
//***************************************
Interfaces::Interfaces(int radiusCenter, int nbsegments, bool segmentation, Scalar Color)
	: _RadiusCenter(radiusCenter), _Segmentation(segmentation), _Color(Color)
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
void Interfaces::DrawInterfaces(Mat& Im) const
{
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
	Mi[1] = {Point(150, 125), 75, 90, TYPE_OSCILL_SQARE};
	Mi[2] = {Point(300, 50), 60, 45, TYPE_OSCILL_SAW};
	Mi[3] = {Point(125, 250), 80, -180, TYPE_OSILLC_IMPULSE};
	Mi[4] = {Point(300, 250), 100, 60, TYPE_EFFECT_NOISE};
	Mi[5] = {Point(1000, 50), 65, -60, TYPE_FILTER_COLOR};
	Mi[6] = {Point(1200, 50), 70, -30, TYPE_OSCILL_SINUS};
	Mi[7] = {Point(900, 150), 75, -45, TYPE_OSCILL_SQARE};
	Mi[8] = {Point(1000, 300), 90, 0, TYPE_OSCILL_SAW};
	Mi[9] = {Point(700, 150), 95, -90, TYPE_OSILLC_IMPULSE};

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

void Interfaces::drawLinks(Mat& Im, vector<MarkerInfos>& Mi, vector<pair<int, int>>& Edges) const
{
	for (int i = 0; i < Edges.size(); ++i) {
		Point P1 = Edges[i].first == -1 ? _Center : Mi[Edges[i].first]._Center,
			P2 = Edges[i].second == -1 ? _Center : Mi[Edges[i].second]._Center;
		line(Im, P1, P2, _Color);
	}
}

void Interfaces::drawMarkers(Mat& Im, vector<MarkerInfos>& Mis) const
{
	for (int i = 0; i < Mis.size(); ++i) drawMarker(Im, Mis[i]);
}

void Interfaces::drawMarker(Mat& Im, MarkerInfos& Mi) const
{
	//switch draw en fonction du type de marker
	drawSquareMarker(Im, Mi);
	drawMarkerCircle(Im, Mi);
}

void Interfaces::drawMarkerCircle(Mat& Im, MarkerInfos& Mi) const
{
	const Scalar Color = Type2Color(Mi._Type);
	const double radius = Mi._Size * SQRT_2 / 2;
	const double new_angle = (Mi._Angle - 90) * M_PI_180;
	const Point P1(Mi._Center.x, Mi._Center.y - int(round(radius)));

	Point P2;
	P2.x = int(round(Mi._Center.x + radius * cos(new_angle)));
	P2.y = int(round(Mi._Center.y + radius * sin(new_angle)));

	circle(Im, Mi._Center, radius, _Color, 1);
	ellipse(Im, Mi._Center, Size(radius, radius), -90, 0, Mi._Angle, Color, 3);
	circle(Im, P1, _RadiusCenter, _Color, -1);
	circle(Im, P2, _RadiusCenter, Color, -1);
}

//***** Markers Type ****
void Interfaces::drawSquareMarker(Mat& Im, MarkerInfos& Mi) const
{
	const Scalar Color = Type2Color(Mi._Type);
	RotatedRect rotatedRectangle(Mi._Center, Size2f(Mi._Size, Mi._Size), Mi._Angle);
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
	case TYPE_OSCILL_SQARE:		return COLORS[4];
	case TYPE_OSCILL_SAW:		return COLORS[5];
	case TYPE_OSILLC_IMPULSE:	return COLORS[6];
	case TYPE_EFFECT_NOISE:		return COLORS[7];
	case TYPE_FILTER_COLOR:		return COLORS[8];
	default:					return COLORS[2];
	}
}
