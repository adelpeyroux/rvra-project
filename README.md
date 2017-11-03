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
