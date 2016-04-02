#include "constants.hpp"
#include <iostream>

using namespace cv;
using namespace std; 

class PupilLoc {
    public:
        Mat get_ref_image();
        Mat get_illuminationRM();
        int get_histoPeakIndex();
        Mat get_result_image();
        Mat get_postProc();

        void removeLight();
        void isoPupil();
        void highlightPupil();
        void display_windows();
        void destory_windows();

        PupilLoc(Mat eye_image);

    private: 
        Mat ref_image;
        Mat illuminationRM; 
        int histoPeakIndex;
        Mat postProc;
        Mat result_image; 
        Mat open_element; 
        Mat close_element; 
        int close_size;
        int open_size;
};
