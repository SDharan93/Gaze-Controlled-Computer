# Gaze Controlled Mouse

A computer mouse that is controlled from where you look on the screen! This project was done for our engineering capstone project, applying our knowledge of hardware, software design, image processing and sensors. The gaze controlled mouse uses a simple gaze estimation algorithm to estimate the user's approximate gaze on screen and moves the mouse accordingly. 

The gaze controlled mouse was primarily created for a proof of concept and should not be assumed to be a viable replacement for your mouse currently. The application is tested on the Dragonboard 410C and cannot garuntee full functionality on other systems. 

### Prerequisities

To run the application correctly, please have the following available: 
* OpenCV
* Camera
* Linux Distro
* (Sensor)
* Dragonboard 410C

## Installation

To install the application, run the following:
```
mod +x /path/to/yourscript.sh
```

```
./build.sh
```

## Deployment

To run the application, run the following:
```
make run
```

## Built With

* OpenCV - Image Processing Library
* Dragonboard 410C - Platform for detecting pupil

## Authors

* **Shane Dharan** - *Group Member* - ShaneDharan@gmail.com
* **Jibin Jacob** - *Group Member* - 
* **Christopher Reid** - *Group Member* - 
* **Jacob Wighton** - *Group Member* - 

## Acknowledgments

* **Dr.April Khademi** - *Group Advisor* - Advisor and Mentor to the group. Provided amazing support to the group and motivated the group to strive for the best.
