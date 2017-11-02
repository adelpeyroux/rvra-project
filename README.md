# Compilation: 

mkdir build
cd build
cmake ..
make

# Usage:

./detect -c="../out_camera_data.xml" -d=11 --dp="../detector_params.yml" -l=0.033 -r -v=../one_marker.webm
