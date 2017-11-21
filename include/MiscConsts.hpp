#pragma once

#include <opencv2/core/core.hpp>

//***********************************
//********** Trigonométrie **********
//***********************************
#define TWO_PI		 6.28318530717958647693
#define RAD2DEG		57.29577951308232087680
#define M_PI_180	 0.01745329251994329577
#define SQRT_2		 1.41421356237309504880

//******************************
//********** Couleurs **********
//******************************
const std::vector<cv::Scalar> COLORS = {
		cv::Scalar(0, 0, 0),		cv::Scalar(125, 125, 125),	cv::Scalar(255, 255, 255),	// Noir		Gris		Blanc
		cv::Scalar(255, 0, 0),		cv::Scalar(0, 255, 0),		cv::Scalar(0, 0, 255),		// Rouge	Vert		Bleu
		cv::Scalar(0, 255, 255),	cv::Scalar(255, 0, 255),	cv::Scalar(255, 255, 0),	// Cyan		Magenta		Jaune
		cv::Scalar(255, 125, 0),	cv::Scalar(0, 255, 125),	cv::Scalar(125, 0, 255),	// Orange	Turquoise	Indigo
		cv::Scalar(255, 0, 125),	cv::Scalar(125, 255, 0),	cv::Scalar(0, 125, 255),	// Fushia	Lime		Azur
		cv::Scalar(125, 0, 0),		cv::Scalar(0, 125, 0),		cv::Scalar(0, 0, 125)		// Blood	Grass		Deep
};

enum MY_COLORS {
			MY_COLOR_BLACK = 0,
			MY_COLOR_GRAY = 1,
			MY_COLOR_WHITE = 2,
			MY_COLOR_RED = 3,
			MY_COLOR_GREEN = 4,
			MY_COLOR_BLUE = 5,
			MY_COLOR_CYAN = 6,
			MY_COLOR_MAGENTA = 7,
			MY_COLOR_YELLOW = 8,
			MY_COLOR_ORANGE = 9,
			MY_COLOR_TURQUOISE = 10,
			MY_COLOR_INDIGO = 11,
			MY_COLOR_FUSHIA = 12,
			MY_COLOR_LIME = 13,
			MY_COLOR_AZUR = 14,
			MY_COLOR_BLOOD = 15,
			MY_COLOR_GRASS = 16,
			MY_COLOR_DEEP = 17,
};

static cv::Scalar BGR2RGB(const cv::Scalar &color)
{
	return cv::Scalar(color[3],color[2],color[1]);
}

//*****************************
//********** Markers **********
//*****************************
enum MARKER_TYPE
{
	// Oscillateurs
	TYPE_OSCILL_SINUS = 0,
	TYPE_OSCILL_SQUARE = 1,
	TYPE_OSCILL_TRIANGLE = 2,
	TYPE_OSCILL_SAW = 3,
	TYPE_OSCILL_IMPULSE = 4,

	// Effets
	TYPE_EFFECT_NOISE = 10,

	// Filtres
	TYPE_FILTER_COLOR = 20,
};