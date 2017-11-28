#pragma once

#include <opencv2/core/core.hpp>

#include "MiscConsts.hpp"
#include "xMarker.hpp"

struct MarkerInfos
{
	cv::Point _Center;
	double _Size;
	double _Angle;
	MARKER_TYPE _Type;
};

class Interfaces
{
public:
	int _RadiusCenter;
	int _RadiusButton;
	bool _Segmentation;
	cv::Scalar _Color;
	double _Alpha;

	//***** Constructeurs / Destructeurs ****
	Interfaces(int radiusCenter = 10, int radiusButton = 5, int nbsegments = 4, bool segmentation = false,
	           cv::Scalar Color = COLORS[MY_COLOR_WHITE], double alpha = 0.5);
	virtual ~Interfaces();

	//***** Getters / Setters ****
	int GetNbSegments() const;
	void SetNbSegments(int _nbSegments);
	void SetInterfaceSize(int h, int w);

	//***** Draws ****
    void DrawInterfaces(cv::Mat& Im, const std::vector<xMarker> &Mis, const std::vector<std::pair<int,int>> &Edges) const;

private:
	int _nbSegments;
	double _pasSegments;
	int _w, _h, _r;
	cv::Point _Center;

	//***** Draws ****
	void drawCenter(cv::Mat& Im) const;
	void drawSegmentation(cv::Mat& Im) const;
    void drawLinks(cv::Mat& Im, const std::vector<xMarker> &Mis, const std::vector<std::pair<int,int>> &Edges) const;
    void drawMarkers(cv::Mat& Im, const vector<xMarker>& Mis) const;
    void drawMarker(cv::Mat& Im, const xMarker &Mi) const;
    void drawMarkerCircle(cv::Mat& Im, const xMarker & Mi) const;

	//Marker Type (pour l'instant un seul)
    void drawSquareMarker(cv::Mat& Im, const xMarker & Mi) const;

	//Misc
	static cv::Scalar Type2Color(MARKER_TYPE T);
};
