#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/objdetect.hpp>

#include <iostream>
#include <cmath>

using namespace cv; 
using namespace std; 

//Global variables 
Mat src, video_src, gray_video_src, otsu_image, threshold_image, dilate_image, edge, blur_image, face_image, eye_image, inv_gray_video, adapt_image;

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

int userInput(int input);
void highlight_eye(Mat image);
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
    namedWindow("INV GRAY VIDEO", 1);
    //namedWindow(THRESHOLD, 1);
    namedWindow(OTSU, 1);
    //namedWindow(CANNY_WINDOW,1);
    namedWindow(ADAPTIVE_NAME, 1);
    namedWindow(LIGHT_NAME, 1);
    namedWindow(FILTER_NAME, 1);

    resizeWindow("INV GRAY VIDEO", 500, 500);
    resizeWindow(SOURCE, 500, 500);
    resizeWindow(OTSU, 500, 500);
    resizeWindow(GRAY, 500, 500);
    resizeWindow("FACE", 500, 500);
    resizeWindow(ADAPTIVE_NAME, 500, 500);
    resizeWindow(LIGHT_NAME, 500, 500);
    resizeWindow(FILTER_NAME, 500, 500);

    while(input != 0) {
        //cap >> video_src;
        video_src = imread("image-13.png", CV_LOAD_IMAGE_UNCHANGED); 
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
        try{
            face_cascade.detectMultiScale(gray_video_src, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE|CV_HAAR_FIND_BIGGEST_OBJECT, Size(150, 150));
            face_image = gray_video_src(Rect(faces[0].x, faces[0].y, faces[0].width, faces[0].height));
            rectangle(video_src, faces[0], CV_RGB(0,255,0),1);
        } catch(...) {
        }
    
        //find eyes
        try {
            eye_cascade.detectMultiScale(face_image, eyes, 1.1, 2, 0|CASCADE_SCALE_IMAGE|CV_HAAR_FIND_BIGGEST_OBJECT, Size(30,30) );
            eye_image = face_image(Rect(eyes[0].x, eyes[0].y, eyes[0].width, eyes[0].height));
            rectangle(video_src,eyes[0], CV_RGB(0,255,0),1);
        } catch (...) {
        }

        //Temp variables --
        Mat temp, light_image, divided_image, divided_image2;
        //medianBlur(eye_image, eye_image, 5);
        GaussianBlur( adapt_image, blur_image, Size(5, 5), 2, 2 );
        blur(~eye_image, light_image, Size(151,151));
        //divide(~eye_image, light_image, divided_image, 1, -1);
        subtract(~eye_image, light_image, divided_image);
        subtract(~eye_image, ~light_image, divided_image2);
        equalizeHist(divided_image, divided_image);
        equalizeHist(divided_image2, divided_image2);
        //divided_image = ~eye_image.mul(light_image.inv());

        Mat element = getStructuringElement(2, Size(2 * dilation_size + 1, 2 * dilation_size +1), Point(dilation_size, dilation_size));
        //dilate(edge, dilate_image, element);
        morphologyEx( divided_image, divided_image, MORPH_OPEN , element );
        morphologyEx( divided_image2, divided_image2, MORPH_OPEN , element );

        adaptiveThreshold(divided_image2, adapt_image, 255, ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 15, -5);
        threshold(divided_image2, otsu_image, 200, 255, CV_THRESH_BINARY | CV_THRESH_OTSU); 
        threshold(divided_image2, threshold_image,240, 255, THRESH_BINARY);

        //blur(adapt_image, blur_image, Size(7,7));
        //blur image to elimnate unwanted edges.
        medianBlur(adapt_image, blur_image, 7);
        /// Reduce the noise so we avoid false circle detection
        //GaussianBlur( adapt_image, blur_image, Size(15, 15), 2, 2 );
        Canny(blur_image, edge, 7, 21, 3);
        //Canny(adapt_image, edge, 40, 160, 3);

        //Mat element = getStructuringElement(2, Size(2 * dilation_size + 1, 2 * dilation_size +1), Point(dilation_size, dilation_size));
        dilate(edge, dilate_image, element);
        //morphologyEx( adapt_image, dilate_image, MORPH_TOPHAT , element );
        highlight_eye(edge);

        //imshow(RED_WINDOW, rgb[2]);
        //imshow(GREEN_WINDOW, rgb[1]);
        //imshow(BLUE_WINDOW, rgb[0]);
        imshow("FACE", face_image);
        imshow("EYE", eye_image);
        imshow(SOURCE,video_src);
        imshow(GRAY, gray_video_src);
        //imshow("INV GRAY VIDEO", temp);
        //imshow("INV GRAY VIDEO", ~eye_image);
        //imshow(GRAY, gray_video_src);
        imshow(OTSU, otsu_image);
        imshow(THRESHOLD, threshold_image);
        imshow(CANNY_WINDOW, edge);
        imshow(ADAPTIVE_NAME, adapt_image);
        imshow(LIGHT_NAME, light_image);
        imshow(DIVIDED_NAME, divided_image);
        imshow("DIVIDED IMAGE 2", divided_image2);
        //imshow("DILATED IMAGE", dilate_image);
        imshow(FILTER_NAME, blur_image);

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

void highlight_eye(Mat image) {
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    findContours(image.clone(), contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

    //Fill in the holes for each contour
    drawContours(eye_image, contours, -1, CV_RGB(255, 255, 255), CV_CHAIN_APPROX_SIMPLE);
    //drawContours(eye_image, contours, -1, CV_RGB(255, 255, 255), CV_FILLED);

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
            circle(eye_image, Point(rect.x + radius, rect.y + radius), radius, CV_RGB(255, 0, 0),2);
        }
    }

    vector<Vec3f> circles;
    HoughCircles(image.clone(), circles, HOUGH_GRADIENT, 1, 10,
                 100, 30, 1, 30 // change the last two parameters
                                // (min_radius & max_radius) to detect larger circles
                 );
    for( size_t i = 0; i < circles.size(); i++ )
    {
        Vec3i c = circles[i];
        circle( eye_image, Point(c[0], c[1]), c[2], Scalar(0,0,255), 3, LINE_AA);
        circle( eye_image, Point(c[0], c[1]), 2, Scalar(0,255,0), 3, LINE_AA);
    }
}


