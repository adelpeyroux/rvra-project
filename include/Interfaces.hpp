#pragma once

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "MiscConsts.hpp"

class Interfaces {
public:
	int _RadiusCenter;
	bool _Segmentation;
	cv::Scalar _Color;

	//***** Constructeurs / Destructeurs ****
	Interfaces(int radiusCenter = 5, int nbsegments = 4, bool segmentation = true, cv::Scalar Color = COLORS[MY_COLOR_WHITE]);
	virtual ~Interfaces();

	//***** Getters / Setters ****
	int GetNbSegments() const;
	void SetNbSegments(int _nbSegments);
	void SetInterfaceSize(int h, int w);

	//***** Draws ****
	void DrawInterfaces(cv::Mat &Im/*, graphe*/);

private:
	int _nbSegments;
	double _pasSegments;
	int _w, _h, _r;
	cv::Point _Center;

	//***** Draws ****
	void drawCenter(cv::Mat &Im);
	void drawSegmentation(cv::Mat &Im);
	void drawLinks(cv::Mat &Im);
	void drawLink(cv::Mat &Im);
	void drawMarkers(cv::Mat &Im);
	void drawMarker(cv::Mat &Im);
	void drawMarkerCircle(cv::Mat &Im);

	//Marker Type
	void drawSquareMarker(cv::Mat &Im);
};
