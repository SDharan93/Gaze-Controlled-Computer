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
void displayWindows();
int userInput(int input);
void debug();

Mat source;
Detect camera; 
bool debug_flag;

int main(int argc, char** argv) {
    int input = 0;
    debug_flag = false; 

    //Check if the user put any image input 
    if(argc > 0) {
        source = imread(argv[1]);    
    }
    
    initWindows();
    while(input != CLOSE_PROGRAM) {
        camera.capture_image();
        //camera.findEye(EYE_CASCADE_NAME);
        camera.findFeatures(FACE_CASCADE_NAME, EYE_CASCADE_NAME);
        displayWindows();
        debug();
        input = userInput(waitKey(10));
    }
    return 0;
}

void initWindows() {
    namedWindow(IMAGE_WINDOW_NAME, 1);
}

void displayWindows() {
   //imshow(IMAGE_WINDOW_NAME, source); 
}

void destoryWindows() {
    destroyAllWindows();
}

void debug() {
    if(debug_flag) {
        camera.display_windows();
    } else {
        camera.destroy_windows();
    }
}

int userInput(int input) {
    switch(input) {
        case 27: { //User has hit esc key
            return 27;
        }
        case 99: { //User has hit the c key 
            return 99;
        }
        case 100: { //User has hit d key 
            debug_flag = !debug_flag; 
            return 100;
        }
    }
}
