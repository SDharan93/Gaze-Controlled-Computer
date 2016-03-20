#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

#include <iostream>
#include <cmath>

using namespace cv; 
using namespace std; 

//Global variables 
Mat src, video_src, gray_video_src, otsu_image, threshold_image, dilate_image, edge, blur_image;

String SOURCE = "Video Source";
String GRAY = "GRAY VIDEO";
String THRESHOLD = "MANUAL THRESHOLD";
String OTSU = "OTSU VIDEO THRESHOLD";
String CANNY_WINDOW = "Canny Output";

int userInput(int input);
int main( int argc, char** argv) {

    VideoCapture cap;
    int input = 1;
    int dilation_size = 3;

    cap.open(0);
    if(!cap.isOpened()) {
        return -1;
    }

   namedWindow(SOURCE, 1);
   namedWindow(GRAY, 1);
   namedWindow(THRESHOLD, 1);
   namedWindow(OTSU, 1);

  while(input != 0) {
    cap >> video_src;
    cvtColor(~video_src, gray_video_src, CV_BGR2GRAY);

    threshold(gray_video_src, otsu_image, 200, 255, CV_THRESH_BINARY | CV_THRESH_OTSU); 

    threshold(gray_video_src, threshold_image, 200, 255, THRESH_BINARY);

    medianBlur(otsu_image, blur_image, 3);

    Canny(blur_image, edge, 50, 150, 3);

    imshow(SOURCE,video_src);
    imshow(GRAY, gray_video_src);
    imshow(OTSU, otsu_image);
    imshow(THRESHOLD, threshold_image);
    imshow(CANNY_WINDOW, edge);

    input = userInput(waitKey(10));
  }
  return 0;
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
