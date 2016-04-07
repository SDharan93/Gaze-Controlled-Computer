#include "pupil_detect.hpp"
#include "detect.hpp"
#include "pupilLoc.hpp"

using namespace cv;
using namespace std; 

void initWindows();
void displayWindows(Detect camera, PupilLoc pupil);
void displayWindows(Detect camera);
void destroyWindows();
int userInput(char input);
void debug(Detect camera, PupilLoc pupil);
void debug(Detect camera);
Detect factory_detect(bool debug);
void debug_runnable(Detect camera, Mat result);
void tk1_runnable(Detect camera, Mat result);

Mat source;
bool debug_flag;
bool tk1_flag;

PupilDetect::PupilDetect() {
    pupil_flag = false;
}

Mat PupilDetect::get_result() {
    return resultingImage;
}

bool PupilDetect::isPupil() {
    return pupil_flag;
}

void PupilDetect::run_pupil_detection(int argc, char** argv) {
    int input = 0;
    debug_flag = false; 
    tk1_flag = true; 
    initWindows();
    //check if user wants to enter debug mode
    if(argc > 1){
    	if(DEBUG.compare(argv[1]) == 0) {
        	tk1_flag = false;
    	}
    }
    //creates the correct object(Nvidia vs PC)
    Detect camera = factory_detect(tk1_flag);

    while(input != CLOSE_PROGRAM) {
        //depending on the flag it will run either Nvidia code or PC
        if(tk1_flag) {
            tk1_runnable(camera, resultingImage);
        } else {
            debug_runnable(camera, resultingImage);
        }
        //converts 8 bit input into a character 
        char input_char = (static_cast<char>(waitKey(75)));
        input = userInput(input_char);
    }
}

//runable function for PC...mainly used for debugging 
void debug_runnable(Detect camera, Mat result) {
    //camera.capture_image();
    camera.load_image(DEBUG_IMAGE_NAME);
    camera.findEye(EYE_CASCADE_NAME);
    Mat eye_image = camera.get_eye_image();

    //if the image loaded correctly...
    if(!eye_image.empty()) {
        PupilLoc locatePupil(eye_image);
        locatePupil.removeLight();
        locatePupil.isoPupil();
        locatePupil.highlightPupil();
        result = locatePupil.get_result_image().clone();
        displayWindows(camera, locatePupil);
        debug(camera, locatePupil);
    } else {
        displayWindows(camera);
        debug(camera);
    }
}

//runnable function for the Nvidia TK1 Board
void tk1_runnable(Detect camera, Mat result) {
    camera.nv_capture_image();
    camera.findEye(EYE_CASCADE_NAME);
    Mat eye_image = camera.get_eye_image();

    if(!eye_image.empty()) {
        PupilLoc locatePupil(eye_image);
        locatePupil.removeLight();
        locatePupil.isoPupil();
        locatePupil.highlightPupil();
        result = locatePupil.get_result_image().clone();
        displayWindows(camera, locatePupil);
        debug(camera, locatePupil);
    } else {
        displayWindows(camera);
        debug(camera);
    }
}

void initWindows() {
    namedWindow(IMAGE_WINDOW_NAME, 1);
}

void displayWindows(Detect camera, PupilLoc pupil) {
   imshow(IMAGE_WINDOW_NAME, camera.get_video_image()); 
}

void displayWindows(Detect camera) {
   imshow(IMAGE_WINDOW_NAME, camera.get_video_image()); 
}

void destoryWindows() {
    destroyAllWindows();
}

//opens additional windows for debugging purposes (If the pupil was located) 
void debug(Detect camera, PupilLoc pupil) {
    if(debug_flag) {
        camera.display_windows();
        pupil.display_windows();
    } else {
        camera.destroy_windows();
        pupil.display_windows();
    }
}

//opens additional windows for debugging without pupil detection
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

//factory for creating either pc capture or Nvidia capture object 
Detect factory_detect(bool debug) {
    if(debug) {
        Detect detect(LOCATION, WIDTH, HEIGHT);
        return detect;
    } else {
        Detect detect;
        return detect;
    }
}
