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
    Mat src, video_src, gray_video_src, threshold_image, edge, dilate_image;
    int input = 1;
    int dilation_size = 2;

    cap.open(0);
    if(!cap.isOpened()) {  // check if we succeeded
       return -1;
    }
    //if the user wants to use a debug image
    src = imread(argv[1]);
    namedWindow("Video",1);
    namedWindow("Gray", 1);
    namedWindow("Threshold", 1);
    namedWindow("Canny",1);
    namedWindow("Dilation",1);

    while(input != 0) {
        //stream video instance into matrix
        cap >> video_src;

        //turn video instance into gray image
        cvtColor(~video_src, gray_video_src, CV_BGR2GRAY);
        threshold(gray_video_src, threshold_image, 225, 255, THRESH_BINARY);

        //use the canny filter
        Canny(gray_video_src, edge, 50, 150, 3);

        Mat element = getStructuringElement(2, Size(2 * dilation_size + 1, 2 * dilation_size + 1),
                  Point(dilation_size, dilation_size));     // dilation_type = MORPH_ELLIPSE
        dilate(edge, dilate_image, element);
        //dilate canny filtered image
        //dilate(edge, dilate_image, NULL, 4);

        //show normal video instance
        imshow("Video", video_src);
        imshow("Gray", gray_video_src);
        imshow("Threshold", threshold_image);
        imshow("Canny", edge);
        imshow("Dilation", dilate_image);
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
