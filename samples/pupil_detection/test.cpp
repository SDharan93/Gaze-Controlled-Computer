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
    string croppedEye = "noGlare.png";
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

            else if(status == 4) {
                src = imread(sourceName);
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
            vector<Vec4i> hierarchy;
            vector<Vec3f> circles;

            if(status == 5) {
                /*HoughCircles(src, circles, HOUGH_GRADIENT, 1, 10,
                 100, 30, 1, 30 // change the last two parameters
                                // (min_radius & max_radius) to detect larger circles
                );
                for( size_t i = 0; i < circles.size(); i++ )
                {
                    Vec3i c = circles[i];
                    circle( graySource, Point(c[0], c[1]), c[2], Scalar(0,0,255), 3, LINE_AA);
                    circle( graySource, Point(c[0], c[1]), 2, Scalar(0,255,0), 3, LINE_AA);
                }
                imshow("detected circles", graySource);
                */
                cv::Mat img,img2;
                std::vector<cv::Vec3f> cir_vec;
                img = cv::imread("cropped_high_quality.png",1);
                //cv::bilateralFilter(img, img2, 15, 1000, 1000);
                cv::cvtColor(~img, img2,CV_BGR2GRAY);
                threshold(img2, thresholdImage, 230, 255, THRESH_BINARY);
                cv::HoughCircles(thresholdImage, cir_vec, CV_HOUGH_GRADIENT, 1,300,150, 10);
                cv::circle(thresholdImage,cv::Point(cir_vec[0][0],cir_vec[0][1]),cir_vec[0][2],cv::Scalar(126),2);
                cv::imshow("test",thresholdImage);
            }
            //findContours(thresholdImage.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

            else if(status == 6) {
                /*Mat capturedImg = imread(sourceName,1);
                Mat grayscaleImg;
                vector<Vec3f> storage;

                cvtColor(capturedImg, grayscaleImg, CV_BGR2GRAY);
                // Gaussian filter for less noise
                cvSmooth(grayscaleImg, grayscaleImg, CV_GAUSSIAN,9, 9 );

                //Detect the circles in the image
                CvSeq* circles_u = cvHoughCircles(grayscaleImg,
                        storage,
                        CV_HOUGH_GRADIENT,
                        2,
                        grayscaleImg->height/4,
                        200,
                        100 );

                for (int i = 0; i < circles_u->total; i++)
                {
                     float* p = (float*)cvGetSeqElem( circles_u, i );
                     cvCircle( capturedImg, cvPoint(cvRound(p[0]),cvRound(p[1])),
                        3, CV_RGB(0,255,0), -1, 8, 0 );
                     cvCircle( capturedImg, cvPoint(cvRound(p[0]),cvRound(p[1])),
                         cvRound(p[2]), CV_RGB(0,0,255), 3, 8, 0 );
                }
                // cvCircle( img,cvPoint( r->x, r->y ),67, CV_RGB(255,0,0), 3, 8, 0 );
                cvNamedWindow( "circles", 1 );
                cvShowImage( "circles", capturedImg );*/
            }

            else if(status == 7) {
                Mat src, src_gray;
                Mat dst, detected_edges;

                int edgeThresh = 1;
                int lowThreshold;
                int const max_lowThreshold = 100;
                int ratio = 3;
                int kernel_size = 3;
                string window_name = "Edge Map";

                /// Load an image
                src = imread( sourceName );

                if( !src.data )
                {
                    return -1;
                 }

                 /// Create a matrix of the same type and size as src (for dst)
                dst.create( src.size(), src.type() );

                /// Convert the image to grayscale
                cvtColor( src, src_gray, CV_BGR2GRAY );

                /// Create a window
                namedWindow( window_name, CV_WINDOW_AUTOSIZE );

                /// Create a Trackbar for user to enter threshold
                createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold );

                /// Reduce noise with a kernel 3x3
                blur( src_gray, detected_edges, Size(3,3) );

                /// Canny detector
                Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );

                /// Using Canny's output as a mask, we display our result
                dst = Scalar::all(0);

                src.copyTo( dst, detected_edges);
                imshow( window_name, dst );
            }

            else {
                findContours( thresholdImage.clone(), contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

                //Fill in the holes for each contour
                drawContours(thresholdImage, contours, -1, CV_RGB(255, 255, 255), CV_CHAIN_APPROX_SIMPLE);

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
                namedWindow(sourceDisplay, 0);
                namedWindow(thresholdDisplay, CV_WINDOW_AUTOSIZE);
                namedWindow(grayDisplay, CV_WINDOW_AUTOSIZE);

                resizeWindow(sourceDisplay, 1000, 1000);

                imshow(sourceDisplay, src);
                imshow(inversedSourceDisplay, graySource);
                imshow(thresholdDisplay, thresholdImage);
            }

            cout << "Press any key to exit" << endl;

            //Add input keys here

            switch(waitKey(30)) {
                case 27: { //'esc' key has been pressed, exit program.
                    status = 1;
        			return 0;
                }

                case 104: {
                    status = 5; //h has been pressed, will find circles via hough.
                    break;
                }

                case 112: { //p has been pressed, use webcam
                    status = 2;
                    break;
                }

                case 115: { //s has been pressed, use sample pic
                    status = 3;
                    break;
                }

                case 116: {
                    status = 4; //t has been pressed.
                    break;
                }

                case 117: {
                    status = 6; //u has been pressed
                    break;
                }

                case 118: {
                    status = 7;
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
