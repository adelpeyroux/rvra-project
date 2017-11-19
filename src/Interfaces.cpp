#include <iostream>

#include <opencv2/imgproc.hpp>

#include "Interfaces.hpp"

#ifdef _WIN32
#include <corecrt_math_defines.h>
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
	_pasSegments = (TWO_PI) / nbsegments;
	if (_nbSegments <=1)	_Segmentation = false;
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
void Interfaces::DrawInterfaces(Mat &Im)
{
	drawCenter(Im);
	drawSegmentation(Im);
	drawLinks(Im);
	drawMarkers(Im);
}

void Interfaces::drawCenter(Mat &Im)
{
	circle(Im, _Center, _RadiusCenter, _Color, -1);
}

void Interfaces::drawSegmentation(cv::Mat &Im)
{
	if (_Segmentation) {
		cout<<"Yolo"<<endl;
		for (int i = 0; i < _nbSegments; ++i) {
			Point P2;
			double angle = _pasSegments * i;
			P2.x = int(round(_Center.x + _r * cos(angle)));
			P2.y = int(round(_Center.y + _r * sin(angle)));
			line(Im,_Center,P2,_Color);
		}
	}
}

void Interfaces::drawLinks(cv::Mat &Im)
{

}

void Interfaces::drawLink(cv::Mat &Im)
{

}

void Interfaces::drawMarkers(cv::Mat &Im)
{
	drawMarker(Im);
}

void Interfaces::drawMarker(cv::Mat &Im)
{
	//switch draw en fonction du type de marker
	drawSquareMarker(Im);
	drawMarkerCircle(Im);
}

void Interfaces::drawMarkerCircle(cv::Mat &Im)
{
	const Point Center(200,200);
	const int Size = 50;
	const double radius = Size * SQRT_2 / 2;
	const double angle = M_PI_4;
	const Point P1(Center.x,Center.y-int(round(radius)));

	Point P2;
	P2.x = int(round(Center.x + radius * cos(angle-M_PI_2)));
	P2.y = int(round(Center.y + radius * sin(angle-M_PI_2)));

	circle(Im,Center,radius,_Color,1);
	circle(Im,P1,_RadiusCenter,_Color,-1);
	circle(Im,P2,_RadiusCenter,COLORS[MY_COLOR_DEEP],-1);


}

//***** Markers Type ****
void Interfaces::drawSquareMarker(cv::Mat &Im)
{
	const Point Center(200,200);
	const int Size = 50;
	const double angle = 45.0;


	RotatedRect rotatedRectangle(Center, Size2f(50,50), angle);
	Point2f vertices2f[4];
	rotatedRectangle.points(vertices2f);
	cv::Point vertices[4];
	for(int i = 0; i < 4; ++i)		vertices[i] = vertices2f[i];
	cv::fillConvexPoly(Im, vertices, 4, COLORS[MY_COLOR_LIME]);
}

