# Compilation: 

mkdir build
cd build
cmake ..
make

# Usage:

## Detect a marker in a video file:

./detect -c="../out_camera_data.xml" -d=11 --dp="../detector_params.yml" -l=0.033 -r -v=../one_marker.webm

## Detect a marker in live stream (camera):

./detect -c="../out_camera_data.xml" -d=11 --dp="../detector_params.yml" -l=0.033 -r -v=../one_marker.webm
