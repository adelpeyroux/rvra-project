# Pre-requisites:

To compile and run this project you need to install the following dependancies: 

* OpenCV 3.x with ArUco module ([how to compile and install OpenCV with modules](https://github.com/opencv/opencv_contrib#how-to-build-opencv-with-extra-modules))

Also you will need a camera or video files with moving markers and the goods markers (you can find some examples in the [markers](./markers) directory).

# Compilation: 

## Linux / MacOS: 

```shell
mkdir build
cd build
cmake ..
make
```

## Windows:

Thibaut, je te laisse remplir.

# Usage:

## Detect a marker in a video file:

```shell
./detect -c="../out_camera_calibration.yml" -d=10 -l=0.042 -v=../one_marker.webm
```

## Detect a marker in live stream (camera):

```shell
./detect -c="../out_camera_calibration.yml" -d=10 -l=0.042 
```
