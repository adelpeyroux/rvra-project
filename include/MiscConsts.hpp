#pragma once

#include <opencv2/core/core.hpp>
#include "aruco.h"

#include "Nodes.hpp"
#include <vector>
#include <memory>

//***********************************
//********** Trigonométrie **********
//***********************************
#define TWO_PI		6.28318530717958647693
#define RAD2DEG		57.29577951308232087680
#define M_PI_180	0.01745329251994329577
#define SQRT_2		1.41421356237309504880
#define PROXIMITY	250


//******************************
//********** Couleurs **********
//******************************
const vector<cv::Scalar> COLORS = {
	cv::Scalar(0, 0, 0), cv::Scalar(125, 125, 125), cv::Scalar(255, 255, 255),	// Noir		Gris		Blanc
	cv::Scalar(255, 0, 0), cv::Scalar(0, 255, 0), cv::Scalar(0, 0, 255),		// Rouge	Vert		Bleu
	cv::Scalar(0, 255, 255), cv::Scalar(255, 0, 255), cv::Scalar(255, 255, 0),	// Cyan		Magenta		Jaune
	cv::Scalar(255, 125, 0), cv::Scalar(0, 255, 125), cv::Scalar(125, 0, 255),	// Orange	Turquoise	Indigo
	cv::Scalar(255, 0, 125), cv::Scalar(125, 255, 0), cv::Scalar(0, 125, 255),	// Fushia	Lime		Azur
	cv::Scalar(125, 0, 0), cv::Scalar(0, 125, 0), cv::Scalar(0, 0, 125)			// Blood	Grass		Deep
};

enum MY_COLORS
{
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

static cv::Scalar BGR2RGB(const cv::Scalar& color)
{
	return cv::Scalar(color[3], color[2], color[1]);
}


//*****************************
//********** Markers **********
//*****************************
#define NB_MARKERS 1024
static float MarkerSize;
static aruco::CameraParameters CameraParams;


enum MARKER_TYPE
{
	NO_TYPE = -1,
    // Oscillateurs
    TYPE_SOURCE_SINUS = 0,
    TYPE_SOURCE_SAW = 1,
    TYPE_SOURCE_SQUARE = 2,
    TYPE_SOURCE_TRIANGLE = 3,
    TYPE_SOURCE_NOISE = 4,
    TYPE_SOURCE_NUMERICAL = 5,
    TYPE_SOURCE_SAMPLE0 = 6,
    TYPE_SOURCE_SAMPLE1 = 7,
    TYPE_SOURCE_SAMPLE2 = 8,
    TYPE_SOURCE_SAMPLE3 = 9,

    // Effets
    TYPE_EFFECT_AM = 10,
    TYPE_EFFECT_FM = 11,
    TYPE_EFFECT_ADD = 12,


	// Filtres
	TYPE_FILTER_COLOR = 20,

	// Root
	TYPE_END = 99,
};


static MARKER_TYPE ID2TYPE(int id)
{
    /*
	if (001 <= id && id <= 200) return TYPE_SOURCE_SINUS;
	if (201 <= id && id <= 300) return TYPE_SOURCE_NOISE;
    if (301 <= id && id <= 500) return TYPE_SOURCE_SAMPLE;
	if (501 <= id && id <= 550) return TYPE_EFFECT_AM;
	if (551 <= id && id <= 554) return TYPE_EFFECT_FM;
	if (555 <= id && id <= 600) return TYPE_EFFECT_ADD;
	return TYPE_SOURCE_SINUS;
    */

    switch (id) {
    case 31:
    case 105:
    case 107:
        return TYPE_SOURCE_SINUS;
    case 179:
        return TYPE_SOURCE_SAW;
    case 232:
        return TYPE_SOURCE_SQUARE;
    case 258:
        return TYPE_SOURCE_TRIANGLE;
    case 388:
    case 459:
        return TYPE_SOURCE_NOISE;
    case 466:
    case 494:
        return TYPE_SOURCE_NUMERICAL;
    case 504:
    case 520:
        return TYPE_EFFECT_AM;
    case 552:
    case 553:
        return TYPE_EFFECT_FM;
    case 555:
    case 592:
        return TYPE_EFFECT_ADD;
    case 619:
        return TYPE_SOURCE_SAMPLE0;
    case 824:
        return TYPE_SOURCE_SAMPLE1;
    case 827:
        return TYPE_SOURCE_SAMPLE2;
    case 942:
        return TYPE_SOURCE_SAMPLE3;
    default:
        return TYPE_SOURCE_SINUS;
        break;
    }

}

static cv::Scalar TYPE2COLOR(MARKER_TYPE T)
{
    switch (T) {
        case TYPE_SOURCE_SINUS:
        case TYPE_SOURCE_SAMPLE0:
        case TYPE_SOURCE_SAMPLE1:
        case TYPE_SOURCE_SAMPLE2:
        case TYPE_SOURCE_SAMPLE3:
        case TYPE_SOURCE_SAW:
        case TYPE_SOURCE_SQUARE:
        case TYPE_SOURCE_TRIANGLE:	return COLORS[3];
		case TYPE_SOURCE_NOISE:		return COLORS[4];
		case TYPE_SOURCE_NUMERICAL:	return COLORS[5];
		case TYPE_EFFECT_AM:		return COLORS[6];
		case TYPE_EFFECT_FM:		return COLORS[7];
		case TYPE_EFFECT_ADD:		return COLORS[8];
		case TYPE_FILTER_COLOR:		return COLORS[9];
		default:					return COLORS[2];

	}
}

static string TYPE2LETTER(MARKER_TYPE T)
{
    switch (T) {
        case TYPE_SOURCE_SINUS:		return "Si";
        case TYPE_SOURCE_SAMPLE0:   return "F0";
        case TYPE_SOURCE_SAMPLE1:   return "F1";
        case TYPE_SOURCE_SAMPLE2:   return "F2";
        case TYPE_SOURCE_SAMPLE3:   return "F3";
        case TYPE_SOURCE_SAW:		return "Sa";
        case TYPE_SOURCE_SQUARE:	return "Sq";
        case TYPE_SOURCE_TRIANGLE:	return "T";
        case TYPE_SOURCE_NOISE:		return "R";
        case TYPE_SOURCE_NUMERICAL:	return "N";
		case TYPE_EFFECT_AM:		return "A";
		case TYPE_EFFECT_FM:		return "F";
        case TYPE_EFFECT_ADD:		return "+";
		case TYPE_FILTER_COLOR:		return "C";
		default:					return "";
	}
}

static std::shared_ptr<AudioNode> GetAudioNode(MARKER_TYPE type, float param, double time, int id) {
    switch (type) {
    case TYPE_EFFECT_AM :
        return std::shared_ptr<AudioNode>(new AmNode(id, fabs(param * 880 / 180), time));
    case TYPE_EFFECT_FM :
        return std::shared_ptr<AudioNode>(new FmNode(id, fabs(param * 880 / 180), time));
    case TYPE_SOURCE_SINUS :
        return std::shared_ptr<AudioNode>(new OscNode(id, fabs(param * 880 / 180), OSC_SINE, time));
    case TYPE_SOURCE_SAW :
        return std::shared_ptr<AudioNode>(new OscNode(id, fabs(param * 880 / 180), OSC_SAW, time));
    case TYPE_SOURCE_SQUARE :
        return std::shared_ptr<AudioNode>(new OscNode(id, fabs(param * 880 / 180), OSC_SQUARE, time));
    case TYPE_SOURCE_TRIANGLE :
        return std::shared_ptr<AudioNode>(new OscNode(id, fabs(param * 880 / 180), OSC_SQUARE, time));
    case TYPE_SOURCE_NOISE :
        return std::shared_ptr<AudioNode>(new NoiseNode(id, fabs(param * 32 / 180.), time));
    case TYPE_SOURCE_NUMERICAL :
        return std::shared_ptr<AudioNode>(new NumericalNode(id, fabs(param / 180.), time));
    case TYPE_SOURCE_SAMPLE0 :
        return std::shared_ptr<AudioNode>(new SampleNode(id, fabs(param * 220 / 180.), DATA_DIR"/bd_909dwsd.wav", time));
    case TYPE_SOURCE_SAMPLE1 :
        return std::shared_ptr<AudioNode>(new SampleNode(id, fabs(param * 220 / 180.), DATA_DIR"/hat_vintagespread.wav", time));
    case TYPE_SOURCE_SAMPLE2 :
        return std::shared_ptr<AudioNode>(new SampleNode(id, fabs(param * 220 / 180.), DATA_DIR"/snr_analogging.wav", time));
    case TYPE_SOURCE_SAMPLE3 :
        return std::shared_ptr<AudioNode>(new SampleNode(id, fabs(param * 220 / 180.), DATA_DIR"/tom_madisonave.wav", time));
    case TYPE_EFFECT_ADD :
    case TYPE_FILTER_COLOR:
    case TYPE_END :
        return std::shared_ptr<AudioNode>(new DestinationNode(id, time));
    default :
        return std::shared_ptr<AudioNode>(new DestinationNode(id, time));
    }
}

static bool IsSource(MARKER_TYPE m)
{
	return m < 10;
}


//***************************
//********** Audio **********
//***************************

static double PHI[NB_MARKERS];

static void Init_Phi()
{
	for (double& i : PHI) i = 0.0;
}

static void IncrPhi(int id, double freq)
{
	PHI[id] += freq / double(maxiSettings::sampleRate);
	if (PHI[id] >= 1.0) {
		PHI[id] -= 1.0;
	}
}

static double POS[NB_MARKERS];

static void init_pos()
{
    for (double &i : POS)
        i = 0.0;
}

static void incr_pos(int id, long length) {
    POS[id] += 1. / double(length);
}

static void reset_pos(int id) {
    POS[id] = 0.0;
}

static int PERIODS[1024];

static void init_periods()
{
    for (int &i : PERIODS)
        i = 0;
}

static int PREV[NB_MARKERS];

static void GetSignalsAndNumerics (AudioParams params, double & signal, double & num) {
    double inVal = 0.;
    int nbVal = 0;
    double c = 0.;
    int nbC = 0;

    for (auto pair : params.GetParams()) {
        if (pair.type != (int)TYPE_SOURCE_NUMERICAL) {
            inVal += pair.value;
            nbVal ++;
        } else {
            c += pair.value;
            nbC ++;
        }
    }

    if (nbVal > 0) inVal /= (double)nbVal;

    if (nbC > 0) c /= (double)nbC;

    signal = inVal;
    num = c;
}

//**************************
//********** Misc **********
//**************************
template <typename T>
int SIGN(T val)
{
	return (T(0) < val) - (val < T(0));
}


#define TIME_RESIDUEL 15
static vector<pair<aruco::Marker, int>> OLD;

static void UpdateInfo(vector<aruco::Marker>& markers)
{
    // cas init
    if (OLD.size() == 0) {
        for (aruco::Marker &m : markers) {
            OLD.push_back(std::pair<aruco::Marker, int>(m, 15));
        }
        return;
    }

    //cas normal
    for (aruco::Marker m : markers) {
        bool already = false;

        for (uint i = 0; i < OLD.size(); ++i) {
            if (m.id == OLD[i].first.id) {
                OLD[i].second = TIME_RESIDUEL;
                OLD[i].first = m;
                already = true;
                break;
            }
        }
        if (!already) {
            OLD.push_back(std::pair<aruco::Marker, int>(m, TIME_RESIDUEL));
        }
    }

    vector<pair<aruco::Marker, int>> new_old;

    for (uint i = 0; i < OLD.size(); ++i) {
        bool already = false;
        for (const aruco::Marker& m : markers) {
            if (m.id == OLD[i].first.id) {
                already = true;
                OLD[i].first = m;
                new_old.push_back(OLD[i]);

                break;
            }
        }
        if (!already) {
            OLD[i].second --;
            if (OLD[i].second > 0) {
                markers.push_back(OLD[i].first);
                new_old.push_back(OLD[i]);
            }
        }
    }
    OLD = new_old;
}
