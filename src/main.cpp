#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/objdetect.hpp>

#include <iostream>
#include <cmath>

#include "constants.hpp"
#include "detect.hpp"

using namespace cv;
using namespace std; 

void initWindows();
void displayWindows(Detect camera);
void destroyWindows();
int userInput(char input);
void debug(Detect camera);
Detect factory_detect(bool debug);
void debug_runnable(Detect camera);
void tk1_runnable(Detect camera);

Mat source;
bool debug_flag;
bool tk1_flag;

int main(int argc, char** argv) {
    int input = 0;
    debug_flag = false; 
    tk1_flag = true; 
    initWindows();
    if(argc > 1){
    	if(DEBUG.compare(argv[1]) == 0) {
        	tk1_flag = false;
    	}
    }
    Detect camera = factory_detect(tk1_flag);

    while(input != CLOSE_PROGRAM) {
        if(tk1_flag) {
            tk1_runnable(camera);
        } else {
            debug_runnable(camera);
        }
        char input_char = (static_cast<char>(waitKey(75)));
        input = userInput(input_char);
    }
    return 0;
}

void debug_runnable(Detect camera) {
    camera.capture_image();
    camera.findEye(EYE_CASCADE_NAME);
    //camera.findFeatures(FACE_CASCADE_NAME, EYE_CASCADE_NAME);
    displayWindows(camera);
    debug(camera);
}

void tk1_runnable(Detect camera) {
    camera.nv_capture_image();
    camera.findEye(EYE_CASCADE_NAME);
    //camera.findFeatures(FACE_CASCADE_NAME, EYE_CASCADE_NAME);
    displayWindows(camera);
    debug(camera);
}

void initWindows() {
    namedWindow(IMAGE_WINDOW_NAME, 1);
}

void displayWindows(Detect camera) {
   imshow(IMAGE_WINDOW_NAME, camera.get_video_image()); 
}

void destoryWindows() {
    destroyAllWindows();
}

void debug(Detect camera) {
    if(debug_flag) {
        camera.display_windows();
    } else {
        camera.destroy_windows();
    }
}

int userInput(char input) {
    switch(input) {
        case 27: { //User has hit esc key
            return 27;
        }
        case 'c': { //User has hit the c key 
            return 99;
        }
        case 'd': { //User has hit d key 
            debug_flag = !debug_flag; 
            return 100;
        }
    }
}

Detect factory_detect(bool debug) {
    if(debug) {
        Detect detect(LOCATION, WIDTH, HEIGHT);
        return detect;
    } else {
        Detect detect;
        return detect;
    }
}
