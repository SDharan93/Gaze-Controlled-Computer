#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

#include <iostream>
#include <cmath>

using namespace std;
using namespace cv; 

int main(int argc, char** argv) {
    string sourceName = "eye.jpg";
    string sourceDisplay = "Source image";
    string inversedSourceDisplay = "Inversed Source Image";
    string thresholdDisplay = "Threshold Image";
    
    Mat src = imread(sourceName);
    Mat graySource; 
    Mat thresholdImage;
    VideoCapture cap;
    cap.open(0);

    //If the source image could not load...
    if(!cap.isOpened()) {
       cout << "ERROR: could not open camera" << endl; 
       return -1;
    }
    
    else {
        //The '~' inverts the image. 
        cvtColor(~src, graySource, CV_BGR2GRAY);

        //Calculate Threshold of the image.
        threshold(graySource, thresholdImage, 220, 255, THRESH_BINARY);

        //Remove the noise in the image
        //Find all the contours
        vector<vector<Point> > contours;
        findContours(thresholdImage.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

        //Fill in the holes for each contour 
        drawContours(thresholdImage, contours, -1, CV_RGB(255, 255, 255), -1);

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
                circle(src, Point(rect.x + radius, rect.y + radius), radius, CV_RGB(255, 0, 0),2); 
            }
        }

        namedWindow(inversedSourceDisplay, CV_WINDOW_AUTOSIZE);
        namedWindow(sourceDisplay, CV_WINDOW_AUTOSIZE);
        namedWindow(thresholdDisplay, CV_WINDOW_AUTOSIZE);

        imshow(sourceDisplay, src);
        imshow(inversedSourceDisplay, graySource);
        imshow(thresholdDisplay, thresholdImage);

        cout << "Press any key to exit" << endl;
    
        //Add input keys here
        waitKey(0);
    }
    return 0;
}
