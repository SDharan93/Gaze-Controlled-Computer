# Gaze Controlled Mouse

A computer mouse that is controlled from where you look on the screen! This project was done for our engineering capstone project, applying our knowledge of hardware, software design, image processing and sensors. The gaze controlled mouse uses a simple gaze estimation algorithm to estimate the user's approximate gaze on screen and moves the mouse accordingly. 

The gaze controlled mouse was primarily created for a proof of concept and should not be assumed to be a viable replacement for your mouse currently. The application is tested on the Nvidia TK1 and cannot garuntee full functionality on other systems. 

## Motivation 

All members of the design team are constantly on our computers and avid gamers! The team realized that the mouse cannot be the best option to control the computer cursor since it is the leading cause of wrist and shoulder pains. As such we decided to make a device that controls the cursor via gaze (we already look to where we want to move our cursor already)!

For a detailed report on this project [click here](https://google.com). <- The actual link will be updated once the design course is completed.

## Prerequisities

To run the application correctly, please have the following available: 
* OpenCV
* CMake (Version 2.8)
* Camera
* Linux Distro (Tested on Ubuntu)
* Flex sensor
* Arduino (Tested on Uno)
* Nvidia TK1  

## Installation

To install the application, run the following:
```
chmod +x build.sh
```

```
./build.sh
```

## Deployment

To run the application, run the following:
```
./build/bin/gaze_controller
```

## Built With

* OpenCV - Image Processing Library
* Nvidia TK1 - Platform for controlling mouse pointer with gaze
* Flex Sensor - The sensor used to control the clicking actions
* Arduino Uno - Used as a median of communication between the Nvidia TK1 and Flex Sensor 

## Authors

* **Shane Dharan** - *Group Member* - ShaneDharan@gmail.com
* **Jibin Jacob** - *Group Member* - 
* **Christopher Reid** - *Group Member* - 
* **Jacob Wighton** - *Group Member* - jwighton@mail.uoguelph.ca

## Acknowledgments

* **Dr.April Khademi** - *Group Advisor* - Advisor and Mentor to the group. Provided amazing support to the group and motivated us to strive for the best.
