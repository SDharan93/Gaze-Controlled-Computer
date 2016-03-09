#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

#include <iostream>
#include <cmath>

using namespace cv;
using namespace std;

//Global Variables
Mat src, video_src, gray_video_src, threshold_image, dilate_image, edge, blur_image;

bool openCamera(VideoCapture cap);
int userInput(int input);
void thresh_callback(int, void*);
void highlight_eye();

int main( int argc, char** argv ) {
    VideoCapture cap;
    int input = 1;
    int dilation_size = 3;

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
    namedWindow("blur_image", 1);
    namedWindow("Dilation",1);

    while(input != 0) {
        if(!src.data ) {
            //stream video instance into matrix
            cap >> video_src;
        } else {
            video_src = src;
        }

        //turn video instance into gray image
        cvtColor(~video_src, gray_video_src, CV_BGR2GRAY);
        threshold(gray_video_src, threshold_image, 225, 255, THRESH_BINARY);

        //blur image to elimnate unwanted edges.
        medianBlur(threshold_image, blur_image, 3);
        /// Reduce the noise so we avoid false circle detection
        //GaussianBlur( threshold_image, blur_image, Size(9, 9), 2, 2 );

        //use the canny filter
        Canny(blur_image, edge, 50, 150, 3);

        Mat element = getStructuringElement(2, Size(2 * dilation_size + 1, 2 * dilation_size + 1),
                  Point(dilation_size, dilation_size));     // dilation_type = MORPH_ELLIPSE
        dilate(edge, dilate_image, element);

        //morph to replace dilate
        //cv::morphologyEx(edge, dilate_image, MORPH_CLOSE, cv::noArray(),cv::Point(-1,-1),2);
        //thresh_callback(0,0);
        highlight_eye();

        //show normal video instance
        imshow("Video", video_src);
        imshow("Gray", gray_video_src);
        imshow("Threshold", threshold_image);
        imshow("Canny", edge);
        imshow("blur_image", blur_image);
        imshow("Dilation", dilate_image);
        input = userInput(waitKey(10));
    }

    return 0;
}

void thresh_callback(int, void*)
{
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    // Find contours
    findContours(dilate_image, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    // Get the moments
    vector<Moments> mu(contours.size());
    for(int i = 0; i < contours.size(); i++) {
        mu[i] = moments(contours[i], false);
    }

    // Get the mass centers
    vector<Point2f> mc(contours.size());
    for(int i = 0; i < contours.size(); i++) {
        mc[i] = Point2f(mu[i].m10/mu[i].m00 , mu[i].m01/mu[i].m00);
    }

    // Draw mass centers
    Mat drawing = Mat::zeros(dilate_image.size(), CV_8UC1);
    for( int i = 0; i< contours.size(); i++ ) {
        Scalar color = Scalar(255, 255, 255);
        line(drawing, mc[i], mc[i], color, 1, 8, 0);
    }

    //namedWindow("Step 3: Mass Centers", CV_WINDOW_AUTOSIZE);
    //imshow("Step 3: Mass Centers", drawing);
}

void highlight_eye() {
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    findContours( dilate_image.clone(), contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

    //Fill in the holes for each contour
    drawContours(dilate_image, contours, -1, CV_RGB(255, 255, 255), CV_CHAIN_APPROX_SIMPLE);

    //cv::HoughCircles( gray, circles, CV_HOUGH_GRADIENT, 1, 60);

    //go through every circle to look for the pupil
    for(int i = 0; i < contours.size(); i++) {
        double area = contourArea(contours[i]);
        Rect rect = boundingRect(contours[i]);
        int radius = rect.width/2;

        //look for round shapes
        if(area >= 30 &&
            abs(1 - ((double)rect.width / (double)rect.height)) <= 0.2 &&
            abs(1 - (area / (CV_PI * pow(radius,2)))) <= 0.2)
        {
            circle(video_src, Point(rect.x + radius, rect.y + radius), radius, CV_RGB(255, 0, 0),2);
        }
    }
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
