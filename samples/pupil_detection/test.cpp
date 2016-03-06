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
    string croppedEye = "cropped_high_quality.png";
    string sourceDisplay = "Source image";
    string grayDisplay = "Grayed image";
    string inversedSourceDisplay = "Inversed Source Image";
    string thresholdDisplay = "Threshold Image";

    Mat src = imread(sourceName);
    Mat graySource;
    Mat thresholdImage;
    VideoCapture cap;
    int status = 0;
    cap.open(0);

    if (cap.isOpened()) {
        while(status != 1)
        {
            if(status == 2) {
                //take snapshot of image.
                cap >> src;
            }

            else {
                //default is sample pic
                src = imread(croppedEye);
            }

            if(src.empty()) {
                break;
            }

            //The '~' inverts the image.
            cvtColor(~src, graySource, CV_BGR2GRAY);

            //Calculate Threshold of the image.
            threshold(graySource, thresholdImage, 230, 255, THRESH_BINARY);

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
                if(area >= 50 &&
                    abs(1 - ((double)rect.width / (double)rect.height)) <= 0.2 &&
                    abs(1 - (area / (CV_PI * pow(radius,2)))) <= 0.2)
                {
                    circle(src, Point(rect.x + radius, rect.y + radius), radius, CV_RGB(255, 0, 0),2);
                }
            }

            namedWindow(inversedSourceDisplay, CV_WINDOW_AUTOSIZE);
            namedWindow(sourceDisplay, 0);
            namedWindow(thresholdDisplay, CV_WINDOW_AUTOSIZE);
            namedWindow(grayDisplay, CV_WINDOW_AUTOSIZE);

            resizeWindow(sourceDisplay, 1000, 1000);

            imshow(sourceDisplay, src);
            imshow(inversedSourceDisplay, graySource);
            imshow(thresholdDisplay, thresholdImage);

            cout << "Press any key to exit" << endl;

            //Add input keys here

            switch(waitKey(30)) {
                case 27: { //'esc' key has been pressed, exit program.
                    status = 1;
        			return 0;
                }

                case 112: { //p has been pressed, use webcam
                    status = 2;
                    break;
                }

                case 115: { //s has been pressed, use sample pic
                    status = 3;
                    break;
                }
            }
        }
    }

    //If the source image could not load...
    else {
       cout << "ERROR: could not open camera" << endl;
       return -1;
    }

    return 0;
}
