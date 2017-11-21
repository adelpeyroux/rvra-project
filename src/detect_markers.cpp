/*****************************************************************************************
Copyright 2011 Rafael Muñoz Salinas. All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are
permitted provided that the following conditions are met:

   1. Redistributions of source code must retain the above copyright notice, this list of
      conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright notice, this list
      of conditions and the following disclaimer in the documentation and/or other materials
      provided with the distribution.

THIS SOFTWARE IS PROVIDED BY Rafael Muñoz Salinas ''AS IS'' AND ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL Rafael Muñoz Salinas OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those of the
authors and should not be interpreted as representing official policies, either expressed
or implied, of Rafael Muñoz Salinas.
********************************************************************************************/
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <thread>

#include "aruco.h"
#include "cvdrawingutils.h"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <maximilian.h>
#include <player.h>
#include "MarkerGraph.hpp"

using namespace cv;
using namespace aruco;

MarkerDetector MDetector;
VideoCapture TheVideoCapturer;
vector< Marker > TheMarkers;
Mat TheInputImage, TheInputImageCopy;
CameraParameters TheCameraParameters;
void cvTackBarEvents(int pos, void *);

float TheMarkerSize;
char key;


pair< double, double > AvrgTime(0, 0); // determines the average time required for detection
 int iThresParam1, iThresParam2;
int waitTime = 0;
class CmdLineParser{int argc; char **argv; public: CmdLineParser(int _argc,char **_argv):argc(_argc),argv(_argv){}  bool operator[] ( string param ) {int idx=-1;  for ( int i=0; i<argc && idx==-1; i++ ) if ( string ( argv[i] ) ==param ) idx=i;    return ( idx!=-1 ) ;    } string operator()(string param,string defvalue="-1"){int idx=-1;    for ( int i=0; i<argc && idx==-1; i++ ) if ( string ( argv[i] ) ==param ) idx=i; if ( idx==-1 ) return defvalue;   else  return ( argv[  idx+1] ); }};


cv::Mat resize(const cv::Mat &in,int width){
    if (in.size().width<=width) return in;
    float yf=float(  width)/float(in.size().width);
    cv::Mat im2;
    cv::resize(in,im2,cv::Size(width,float(in.size().height)*yf));
    return im2;

}

maxiOsc mySine[50];//One oscillator - can be called anything. Can be any of the available waveforms.
void setup() {//some inits
    //nothing to go here this time
}

void play(double *output) {
    output[0] = 0.;

    if (TheMarkers.size() > 0)
        for (int i = 0; i < TheMarkers.size(); ++i)
            output[0] += mySine[i].sinewave(TheMarkers[i].id * 2) / TheMarkers.size();

    output[1]=output[0];

}

void detect_markers() {
    while (true) {
        TheVideoCapturer >> TheInputImage;
        // copy image
        double tick = (double)getTickCount(); // for checking the speed
        // Detection of markers in the image passed
        TheMarkers= MDetector.detect(TheInputImage, TheCameraParameters, TheMarkerSize);
        // chekc the speed by calculating the mean speed of all iterations
        MarkerGraph g(TheMarkers, TheInputImage.size());

        // print marker info and draw the markers in image
        TheInputImage.copyTo(TheInputImageCopy);


        // print marker info and draw the markers in image
        TheInputImage.copyTo(TheInputImageCopy);

        for (unsigned int i = 0; i < TheMarkers.size(); i++) {
            cout << TheMarkers[i]<<endl;
            TheMarkers[i].draw(TheInputImageCopy, Scalar(0, 0, 255));
        }

        // draw a 3d cube in each marker if there is 3d info
        if (TheCameraParameters.isValid() && TheMarkerSize>0)
            for (unsigned int i = 0; i < TheMarkers.size(); i++) {
                CvDrawingUtils::draw3dCube(TheInputImageCopy, TheMarkers[i], TheCameraParameters);
                CvDrawingUtils::draw3dAxis(TheInputImageCopy, TheMarkers[i], TheCameraParameters);
            }

        // DONE! Easy, right?
        // show input with augmented information and  the thresholded image
        cv::imshow("in", resize(TheInputImageCopy,1280));
        cv::imshow("thres", resize(MDetector.getThresholdedImage(),1280));


        key = cv::waitKey(waitTime); // wait for key to be pressed
        if(key=='s')  waitTime= waitTime==0?10:0;

        AvrgTime.first += ((double)getTickCount() - tick) / getTickFrequency();
        AvrgTime.second++;
        cout << "\rTime detection=" << 1000 * AvrgTime.first / AvrgTime.second << " milliseconds nmarkers=" << TheMarkers.size() << std::endl;
    }
}

/************************************
 *
 *
 *
 *
 ************************************/
int main(int argc, char **argv) {
    try {
        CmdLineParser cml(argc,argv);
        if (argc < 2  || cml["-h"]) {
            cerr << "Invalid number of arguments" << endl;
            cerr << "Usage: (in.avi|live[:idx_cam=0]) [-c camera_params.yml] [-s  marker_size_in_meters] [-d dictionary:ARUCO by default] [-h]" << endl;
            cerr<<"\tDictionaries: "; for(auto dict:aruco::Dictionary::getDicTypes())    cerr<<dict<<" ";cerr<<endl;
            cerr<<"\t Instead of these, you can directly indicate the path to a file with your own generated dictionary"<<endl;
            return false;
        }

        ///////////  PARSE ARGUMENTS
        string TheInputVideo = argv[1];
        // read camera parameters if passed
        if (cml["-c"] )  TheCameraParameters.readFromXMLFile(cml("-c"));
        TheMarkerSize = std::stof(cml("-s","-1"));
        //aruco::Dictionary::DICT_TYPES  TheDictionary= Dictionary::getTypeFromString( cml("-d","ARUCO") );

        ///////////  OPEN VIDEO
        // read from camera or from  file
        if (TheInputVideo.find("live") != string::npos) {
            int vIdx = 0;
            // check if the :idx is here
            char cad[100];
            if (TheInputVideo.find(":") != string::npos) {
                std::replace(TheInputVideo.begin(), TheInputVideo.end(), ':', ' ');
                sscanf(TheInputVideo.c_str(), "%s %d", cad, &vIdx);
            }
            cout << "Opening camera index " << vIdx << endl;
            TheVideoCapturer.open(vIdx);
            waitTime = 10;
        }
        else TheVideoCapturer.open(TheInputVideo);
        // check video is open
        if (!TheVideoCapturer.isOpened())  throw std::runtime_error("Could not open video");


        ///// CONFIGURE DATA
        // read first image to get the dimensions
        TheVideoCapturer.retrieve(TheInputImage);
        if (TheCameraParameters.isValid())
            TheCameraParameters.resize(TheInputImage.size());

        MDetector.setDictionary(cml("-d","ARUCO"));//sets the dictionary to be employed (ARUCO,APRILTAGS,ARTOOLKIT,etc)
        MDetector.setThresholdParams(7, 7);
        MDetector.setThresholdParamRange(2, 0);
       //  MDetector.setCornerRefinementMethod(aruco::MarkerDetector::SUBPIX);

        //gui requirements : the trackbars to change this parameters
        iThresParam1 = MDetector.getParams()._thresParam1;
        iThresParam2 = MDetector.getParams()._thresParam2;
        cv::namedWindow("in");

        // capture until press ESC or until the end of the video


        //go!
        char key = 0;
        int index = 0;
        // capture until press ESC or until the end of the video

        std::thread detection_thread (detect_markers);
        std::thread sound_thread (start_player);

        detection_thread.join();                // pauses until first finishes
        sound_thread.join();               // pauses until second finishes

    } catch (std::exception &ex)

    {
        cout << "Exception :" << ex.what() << endl;
    }
}
/************************************
 *
 *
 *
 *
 ************************************/

void cvTackBarEvents(int pos, void *) {
    (void)(pos);
    if (iThresParam1 < 3)  iThresParam1 = 3;
    if (iThresParam1 % 2 != 1)  iThresParam1++;
    if (iThresParam1 < 1)  iThresParam1 = 1;
    MDetector.setThresholdParams(iThresParam1, iThresParam2);
    // recompute
    MDetector.detect(TheInputImage, TheMarkers, TheCameraParameters);
    TheInputImage.copyTo(TheInputImageCopy);
    for (unsigned int i = 0; i < TheMarkers.size(); i++)
        TheMarkers[i].draw(TheInputImageCopy, Scalar(0, 0, 255));

    // draw a 3d cube in each marker if there is 3d info
    if (TheCameraParameters.isValid())
        for (unsigned int i = 0; i < TheMarkers.size(); i++)
            CvDrawingUtils::draw3dCube(TheInputImageCopy, TheMarkers[i], TheCameraParameters);

    cv::imshow("in", resize(TheInputImageCopy,1280));
    cv::imshow("thres", resize(MDetector.getThresholdedImage(),1280));
}
