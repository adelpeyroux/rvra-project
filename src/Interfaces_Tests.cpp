#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <thread>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "Interfaces.hpp"
#include <marker.h>

using namespace cv;
using namespace std;
const int H = 720, W = 1280;


int main(int argc, char **argv) {
	Mat Im = Mat::zeros(H, W, CV_8UC3);
	Interfaces Inter;
	Inter.SetInterfaceSize(H,W);

	vector<aruco::Marker> MarkerVec;
	vector<pair<int, int>> EdgeVec;



//	Inter.DrawInterfaces(Im);
	imshow("Im", Im);
	waitKey(0);
}
