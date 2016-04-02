#include "pupil_detect.hpp"

using namespace cv;
using namespace std; 

int main(int argc, char** argv) {
    PupilDetect detect; 
    detect.run_pupil_detection(argc, argv); 
}

