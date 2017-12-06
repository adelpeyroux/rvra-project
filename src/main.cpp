#include <string>
#include <iostream>
#ifdef WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif
#include <thread>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"

#include <maximilian.h>
#include <player.h>

#include "MiscConsts.hpp"
#include "MarkerGraph.hpp"
#include "Interfaces.hpp"

using namespace std;
using namespace cv;
using namespace aruco;

Interfaces Inter;

shared_ptr<MarkerGraph> tmpGraph = nullptr;
shared_ptr<MarkerGraph> graph = nullptr;
shared_ptr<MarkerGraph> toDelete = nullptr;


MarkerDetector MDetector;
VideoCapture VideoCapturer;
vector<Marker> Markers;
Mat InputImage, InputImageCopy;
void cvTackBarEvents(int pos, void*);
void detect_markers();

char key;
double CurrentTime;

pair<double, double> AvrgTime(0, 0); // determines the average time required for detection
int iThresParam1, iThresParam2;
int waitTime = 0;

//****************************
//***** Parser Arguments *****
//****************************
class CmdLineParser
{
	int argc;
	char** argv;
public:
	CmdLineParser(int _argc, char** _argv)
		: argc(_argc), argv(_argv) {}

	bool operator[](string param) const
	{
		int idx = -1;
		for (int i = 0; i < argc && idx == -1; ++i) if (string(argv[i]) == param) idx = i;
		return (idx != -1);
	}

	string operator()(string param, string defvalue = "-1") const
	{
		int idx = -1;
		for (int i = 0; i < argc && idx == -1; ++i) if (string(argv[i]) == param) idx = i;
		if (idx == -1) return defvalue;
		else return (argv[ idx + 1]);
	}
};

int main(int argc, char** argv)
{
	Init_Phi();

	try {
		const CmdLineParser cml(argc, argv);
		if (argc < 2 || cml["-h"]) {
			cerr << "Invalid number of arguments" << endl;
			cerr <<
				"Usage: (in.avi|live[:idx_cam=0]) [-c camera_params.yml] [-s  marker_size_in_meters] [-d dictionary:ARUCO by default] [-h]"
				<< endl;
			cerr << "\tDictionaries: ";
			for (const auto dict : aruco::Dictionary::getDicTypes()) cerr << dict << " ";
			cerr << endl;
			cerr << "\t Instead of these, you can directly indicate the path to a file with your own generated dictionary" <<
				endl;
			return false;
		}

		///////////  PARSE ARGUMENTS
		string InputVideo = argv[1];
		// read camera parameters if passed
		if (cml["-c"]) CameraParams.readFromXMLFile(cml("-c"));
		MarkerSize = stof(cml("-s", "-1"));
		//aruco::Dictionary::DICT_TYPES  TheDictionary= Dictionary::getTypeFromString( cml("-d","ARUCO") );

		///////////  OPEN VIDEO
		// read from camera or from  file
		if (InputVideo.find("live") != string::npos) {
			int vIdx = stoi(cml("-i", "0"));
			// check if the :idx is here
			char cad[100];
			if (InputVideo.find(":") != string::npos) {
				replace(InputVideo.begin(), InputVideo.end(), ':', ' ');
				sscanf(InputVideo.c_str(), "%s %d", cad, &vIdx);
			}
			cout << "Opening camera index " << vIdx << endl;
			VideoCapturer.open(vIdx);
			waitTime = 10;
		} else VideoCapturer.open(InputVideo);
		// check video is open
		if (!VideoCapturer.isOpened()) throw runtime_error("Could not open video");


		///// CONFIGURE DATA
		// read first image to get the dimensions
		VideoCapturer >> InputImage;
		if (CameraParams.isValid()) CameraParams.resize(InputImage.size());

		MDetector.setDictionary(cml("-d", "ARUCO"));//sets the dictionary to be employed (ARUCO,APRILTAGS,ARTOOLKIT,etc)
		MDetector.setThresholdParams(7, 7);
		MDetector.setThresholdParamRange(2, 0);
		//  MDetector.setCornerRefinementMethod(aruco::MarkerDetector::SUBPIX);

		//gui requirements : the trackbars to change this parameters
		iThresParam1 = MDetector.getParams()._thresParam1;
		iThresParam2 = MDetector.getParams()._thresParam2;
		namedWindow("in");

		// capture until press ESC or until the end of the video
		const Size SizeIm = InputImage.size();
		cout << SizeIm << "/" << SizeIm.width << endl;

		Inter.SetInterfaceSize(SizeIm.height, SizeIm.width);


		// capture until press ESC or until the end of the video

		CurrentTime = 0.0f;

		thread detection_thread(detect_markers);
#ifdef WIN32
		Sleep(1000);
#else
        sleep(1);
#endif
		thread sound_thread(start_player);

		detection_thread.join();

	} catch (exception& ex) {
		cout << "Exception :" << ex.what() << endl;
	}
}


Mat resize(const Mat& in, int width)
{
	if (in.size().width <= width) return in;
	const float yf = float(width) / float(in.size().width);
	Mat im2;
	cv::resize(in, im2, Size(width, float(in.size().height) * yf));
	return im2;
}

maxiOsc mySine[50];//One oscillator - can be called anything. Can be any of the available waveforms.

void setup()
{
	//some inits
	//nothing to go here this time
}

void play(double* output, int size, double time)
{
	tmpGraph = graph;

	for (int i = 0; i < size; ++i) {
		//output[i] = osc.sinewave(440);
		output[i] = tmpGraph->Play(output[i], 0);
	}
}


void detect_markers()
{
	while (true) {
		const double tick = double(getTickCount()); // for checking the speed
		VideoCapturer >> InputImage;
		// copy image
		// Detection of markers in the image passed
		Markers = MDetector.detect(InputImage, CameraParams, MarkerSize);

		// chekc the speed by calculating the mean speed of all iterations

		// print marker info and draw the markers in image
		InputImage.copyTo(InputImageCopy);


		// print marker info and draw the markers in image
		InputImage.copyTo(InputImageCopy);

		Size SizeIm = InputImage.size();

		UpdateInfo(Markers);
		graph = make_shared<MarkerGraph>(Markers, SizeIm, 0.0);

		Inter.DrawInterfaces(InputImageCopy, graph->GetMarkers(), graph->GetEdges());
		// show input with augmented information and  the thresholded image
		imshow("in", resize(InputImageCopy, 1280));
		//imshow("thres", resize(MDetector.getThresholdedImage(),1280));


		key = waitKey(waitTime); // wait for key to be pressed
		if (key == 's') waitTime = waitTime == 0 ? 10 : 0;
		if (key == 'q') break;

		AvrgTime.first += ((double)getTickCount() - tick) / getTickFrequency();
		AvrgTime.second++;
		//cout << "\rTime detection=" << 1000 * AvrgTime.first / AvrgTime.second << " milliseconds nmarkers=" << Markers.size() << endl;
	}
}

void cvTackBarEvents(int pos, void*)
{
	(void)(pos);
	if (iThresParam1 < 3) iThresParam1 = 3;
	if (iThresParam1 % 2 != 1) iThresParam1++;
	if (iThresParam1 < 1) iThresParam1 = 1;
	MDetector.setThresholdParams(iThresParam1, iThresParam2);
	// recompute
	MDetector.detect(InputImage, Markers, CameraParams);
	InputImage.copyTo(InputImageCopy);
	for (unsigned int i = 0; i < Markers.size(); i++) Markers[i].draw(InputImageCopy, Scalar(0, 0, 255));

	// draw a 3d cube in each marker if there is 3d info
	if (CameraParams.isValid())
		for (unsigned int i = 0; i < Markers.size(); i++)
			CvDrawingUtils::draw3dCube(
				InputImageCopy, Markers[i], CameraParams);

	imshow("in", resize(InputImageCopy, 1280));
	imshow("thres", resize(MDetector.getThresholdedImage(), 1280));
}
