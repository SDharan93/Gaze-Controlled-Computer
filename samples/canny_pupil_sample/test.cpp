#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

bool openCamera(VideoCapture cap);
int userInput(int input);

int main( int argc, char** argv ) {
    VideoCapture cap;
    Mat src, video_src;
    int input = 1;

    cap.open(0);
    if(!cap.isOpened()) {  // check if we succeeded
       return -1;
    }
    //if the user wants to use a debug image
    src = imread(argv[1]);
    namedWindow("Video",1);

    while(input != 0) {
        //switch case used to handle the users input
        cap >> video_src;
        

        imshow("Video", video_src);
        input = userInput(waitKey(10));
    }

    return 0;
}

bool openCamera(VideoCapture cap) {
    cap.open(0); // open the default camera
    if(!cap.isOpened()) {  // check if we succeeded
       return false;
   }
   return true;
}

int userInput(int input) {
    switch(input) {
        case 27: {
            return 0;
        }
        default: {
            return 1;
        }
    }
}
