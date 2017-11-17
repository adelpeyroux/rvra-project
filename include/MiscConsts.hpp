#pragma once

/**
* \file MiscServices.hpp
* \brief Fichier contenant diverses fonctions utiles de conversion de type, gestion de fichiers...
* \author Thibaut Monseigne
* \version 0.1
* \date 01 Septembre 2017
*/
#pragma once

#include <opencv2/core/core.hpp>

//***********************************
//********** Trigonométrie **********
//***********************************
#define TWO_PI 6.28318530718
#define SQRT_2 1.414213562

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