#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/objdetect.hpp>

#include <iostream>
#include <cmath>
#include <stdio.h>
#include "v4ldevice.h"
#include<time.h>

using namespace cv; 
using namespace std; 

//Global variables 
Mat src, video_src, image, gray_video_src, demosaic, otsu_image, threshold_image, dilate_image, edge, blur_image, face_image, eye_image, inv_gray_video, adapt_image;

static String SOURCE = "Video Source";
static String GRAY = "GRAY VIDEO";
static String THRESHOLD = "MANUAL THRESHOLD";
static String OTSU = "OTSU VIDEO THRESHOLD";
static String CANNY_WINDOW = "Canny Output";
static String RED_WINDOW = "Red Window";
static String BLUE_WINDOW = "Blue Window";
static String GREEN_WINDOW = "Green Window";
static String FACE_CASCADE_NAME = "./haarcascade_frontalface_alt.xml";
static String EYE_CASCADE_NAME = "./haarcascade_eye_tree_eyeglasses.xml";
static String ADAPTIVE_NAME = "ADAPTIVE THRESHOLD";
static String LIGHT_NAME = "LIGHT IMAGE";
static String DIVIDED_NAME = "DIVIDED IMAGE";
static String FILTER_NAME = "FILTERED WINDOW";

CascadeClassifier face_cascade;
CascadeClassifier eye_cascade;
vector<Mat> rgb;

vector<Rect> faces;
vector<Rect> eyes;

//functions
//int userInput(int input);
void highlight_eye(Mat image);
int find_peak(Mat image);
int main( int argc, char** argv) {

    //VideoCapture cap;
    int wKey = -1;
    //int input = 1;
    int dilation_size = 3;
    int bigger = 6;
    //Start and end times
    time_t start,end;
    // Set Camera Resolution
    Size ImageSize;
    ImageSize.width = 1280;
    ImageSize.height = 720;
    // Set Camera Resolution
    Size EyeSize;
    EyeSize.width = 70;
    EyeSize.height = 70;

    //cap.open(0);
    //if(!cap.isOpened()) {
    //    return -1;
    //}
    // Open and Initialize Camera
    open_device((char*)"/dev/video0");    
    init_device(ImageSize.width, ImageSize.height);
    // Start the Camera Capture Sequence
    start_capturing();


    //namedWindow(SOURCE, 1);
    //namedWindow(GRAY, 1);
   // namedWindow("INV GRAY VIDEO", 1);
    //namedWindow(THRESHOLD, 1);
    //namedWindow(OTSU, 1);
    //namedWindow(CANNY_WINDOW,1);
    //namedWindow(ADAPTIVE_NAME, 1);
    //namedWindow(LIGHT_NAME, 1);
    //namedWindow(FILTER_NAME, 1);

    //resizeWindow("INV GRAY VIDEO", 500, 500);
   // resizeWindow(SOURCE, 500, 500);
   // resizeWindow(OTSU, 500, 500);
   // resizeWindow(GRAY, 500, 500);
    //resizeWindow("FACE", 500, 500);
    //resizeWindow(ADAPTIVE_NAME, 500, 500);
    //resizeWindow(LIGHT_NAME, 500, 500);
   // resizeWindow(FILTER_NAME, 500, 500);

	//Start the clock
	time(&start);
	int counter=0;
	double sec = 0;
	double fps = 0;

	// Setup a rectangle to define your region of interest
	Rect myROI(200, 10, 700, 300);

    while(wKey == -1) {
        //cap >> video_src;
        //video_src = imread("image-10.png", CV_LOAD_IMAGE_UNCHANGED); 
        //video_src = imread("Colour_Polarizer_Dark.png", CV_LOAD_IMAGE_UNCHANGED);
	src = Mat(ImageSize, CV_16UC1, snapFrame());
	waitKey(75);
	src.convertTo(image, CV_8UC4, 1.0625);
	Mat demosaic = image(myROI);
	// Demosaic frame for RGB Values
	demosaicing(demosaic,video_src,COLOR_BayerBG2RGB);

        if(video_src.empty()) {
            cout << "IMAGE DID NOT LOAD PROPERLY" << endl;
        }
        //Split the RBG Channels
        split(video_src, rgb);
        //equalizeHist(rgb[2], rgb[2]);
        gray_video_src = rgb[2].clone();
        //equalizeHist(gray_video_src, gray_video_src);
        inv_gray_video = ~gray_video_src.clone();

        if((!face_cascade.load(FACE_CASCADE_NAME)) || (!eye_cascade.load(EYE_CASCADE_NAME)) ) {
            cout << "ERROR loading the classifiers load" <<endl;
            return 0;
        }
    
        //medianBlur(gray_video_src, gray_video_src, 3);
        //find face.

        //find eyes
        try {
            eye_cascade.detectMultiScale(gray_video_src, eyes, 1.1, 2, 0|CASCADE_SCALE_IMAGE|CV_HAAR_FIND_BIGGEST_OBJECT, Size(30,30) );
            eye_image = gray_video_src(Rect(eyes[0].x, eyes[0].y, eyes[0].width, eyes[0].height));
            rectangle(video_src,eyes[0], CV_RGB(0,255,0),1);
        } catch (...) {
        }

        //Temp variables --
        Mat temp, light_image, divided_image, divided_image2;
        //medianBlur(eye_image, eye_image, 5);
        GaussianBlur( eye_image, eye_image, Size(3, 3), 2, 2 );
        blur(eye_image, light_image, Size(201,201));
        divide(eye_image, light_image, divided_image, 1, -1);
        
        //imwrite("cropped_eye.png", eye_image);

        Mat no_light;
        Mat eq_divided;
        int peak_number = find_peak(eye_image);
        no_light = divided_image.mul(peak_number);
        //subtract(~eye_image, light_image, divided_image);
        //equalizeHist(divided_image, divided_image);
        divided_image = ~no_light;
        equalizeHist(no_light, eq_divided);
        //divided_image = ~eye_image.mul(~light_image);
        //divided_image = divided_image.mul(255);

        Mat element = getStructuringElement(2, Size(2 * dilation_size + 1, 2 * dilation_size +1), Point(dilation_size, dilation_size));
        Mat element2 = getStructuringElement(2, Size(2 * bigger + 1, 2 * bigger +1), Point(bigger, bigger));
        //dilate(edge, dilate_image, element);
        //morphologyEx( divided_image, divided_image, MORPH_CLOSE , element );
        //morphologyEx( divided_image2, divided_image2, MORPH_CLOSE , element2 );
        //morphologyEx( divided_image, divided_image, MORPH_OPEN , element );
        //morphologyEx( divided_image2, divided_image2, MORPH_OPEN , element2 );

        adaptiveThreshold(divided_image, adapt_image, 255, ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 15, -5);
        threshold(divided_image, otsu_image, 200, 255, CV_THRESH_BINARY | CV_THRESH_OTSU); 
        threshold(divided_image, threshold_image,240, 255, THRESH_BINARY);

        //blur(adapt_image, blur_image, Size(7,7));
        //blur image to elimnate unwanted edges.
        medianBlur(adapt_image, blur_image, 7);
        /// Reduce the noise so we avoid false circle detection
        //GaussianBlur( adapt_image, blur_image, Size(15, 15), 2, 2 );
        //Canny(blur_image, edge, 7, 21, 3);
        //Canny(adapt_image, edge, 40, 160, 3);

        //Mat element = getStructuringElement(2, Size(2 * dilation_size + 1, 2 * dilation_size +1), Point(dilation_size, dilation_size));
        //dilate(blur_image, dilate_image, element);
        //morphologyEx( adapt_image, dilate_image, MORPH_TOPHAT , element );
        morphologyEx( blur_image, dilate_image, MORPH_OPEN , element );
        morphologyEx( blur_image, dilate_image, MORPH_CLOSE , element );
        //highlight_eye(blur_image);
        highlight_eye(dilate_image);

        //imshow(RED_WINDOW, rgb[2]);
        //imshow(GREEN_WINDOW, rgb[1]);
        //imshow(BLUE_WINDOW, rgb[0]);
        //imshow("FACE", face_image);

       // imshow("EYE", eye_image);
        //imwrite( "final_Image.jpg", eye_image);

       // imshow(SOURCE,video_src);
        //imshow(GRAY, gray_video_src);
        //imshow("INV GRAY VIDEO", temp);
        //imshow("INV GRAY VIDEO", ~eye_image);
        //imshow(GRAY, gray_video_src);
       // imshow(OTSU, otsu_image);
        //imshow(THRESHOLD, threshold_image);
        //imshow(CANNY_WINDOW, edge);

       // imshow(ADAPTIVE_NAME, adapt_image);
        //imwrite("Threshold_image.png", adapt_image);

       // imshow(LIGHT_NAME, light_image);

        //imshow("inverted light elimination", divided_image);
        //imwrite("inv_light_elim_image.png", divided_image);

        //imshow("inverted equalized image", ~eq_divided);
        //imwrite("inverted_eq_image.png", ~eq_divided);

        imshow("DILATED IMAGE", dilate_image);
        //imwrite("cleaned_image.png", dilate_image);

        //imshow(FILTER_NAME, blur_image);

        //imshow("LIGHT ELIMINATION", no_light);
        //imwrite("light_elimination.png", no_light);

	Size s = eye_image.size();
	printf("\n H: %d W: %d",s.height, s.width);

		//Stop the clock and show FPS
		time(&end);
		++counter;
		sec=difftime(end,start);
		fps=counter/sec;
		//printf("\n%lf",fps);

        //input = userInput(waitKey(10));
	wKey = waitKey(1);
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

int find_peak(Mat image) {
    //Initialize parameters
    int histSize = 256;    // bin size
    float range[] = { 0, 255 };
    const float *ranges[] = { range };
                 
    // Calculate histogram
    MatND hist;
    calcHist( &image, 1, 0, Mat(), hist, 1, &histSize, ranges, true, false );
    // Show the calculated histogram in command window
    double total;
    float highest = 0;  
    int index = 0;
    total =image.rows *image.cols;
    for( int h = 0; h < histSize; h++ ) {
        float binVal = hist.at<float>(h);
        if(binVal > highest) {
            highest = binVal;
            index = h;
        }
        //cout<<"binVal: "<<binVal << "index: " << h;
    }
    //cout << "index is: " << index << endl;
    return index;
}

void highlight_eye(Mat image) {
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    findContours(image.clone(), contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

    //Fill in the holes for each contour
    drawContours(image.clone(), contours, -1, CV_RGB(255, 255, 255), CV_CHAIN_APPROX_SIMPLE);
    //drawContours(eye_image, contours, -1, CV_RGB(255, 255, 255), CV_FILLED);

    //cv::HoughCircles( gray, circles, CV_HOUGH_GRADIENT, 1, 60);

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
            circle(eye_image, Point(rect.x + radius, rect.y + radius), radius, CV_RGB(255, 0, 0),2);
        }
    }

    vector<Vec3f> circles;
    /*HoughCircles(image.clone(), circles, HOUGH_GRADIENT, 1, 10,
                 100, 30, 1, 45 // change the last two parameters
                                // (min_radius & max_radius) to detect larger circles
                 );
    for( size_t i = 0; i < circles.size(); i++ )
    {
        Vec3i c = circles[i];
        circle( eye_image, Point(c[0], c[1]), c[2], Scalar(0,0,255), 3, LINE_AA);
        circle( eye_image, Point(c[0], c[1]), 2, Scalar(0,255,0), 3, LINE_AA);
    }*/
}


