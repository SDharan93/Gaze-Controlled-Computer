#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/objdetect.hpp>

#include <iostream>
#include <cmath>
#include <fstream>

using namespace cv; 
using namespace std; 

class PupilDetect {
    public:
    void run_pupil_detection(int argc, char** argv);
    Mat get_result();
    bool isPupil();

    PupilDetect();

    private:
    Mat resultingImage;
    bool pupil_flag;
};
