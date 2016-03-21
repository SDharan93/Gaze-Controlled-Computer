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
Mat src, video_src, gray_video_src, otsu_image, threshold_image, dilate_image, edge, blur_image, face_image, eye_image, inv_gray_video;

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

CascadeClassifier face_cascade;
CascadeClassifier eye_cascade;
vector<Mat> rgb;

vector<Rect> faces;
vector<Rect> eyes;

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
   namedWindow("INV GRAY VIDEO", 1);
   //namedWindow(THRESHOLD, 1);
   namedWindow(OTSU, 1);
   //namedWindow(CANNY_WINDOW,1);

    resizeWindow("INV GRAY VIDEO", 500, 500);
    resizeWindow(SOURCE, 500, 500);
    resizeWindow(OTSU, 500, 500);
    resizeWindow(GRAY, 500, 500);
    resizeWindow("FACE", 500, 500);

  while(input != 0) {
    //cap >> video_src;
    video_src = imread("image-12.png", CV_LOAD_IMAGE_UNCHANGED); 
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
    face_cascade.detectMultiScale(gray_video_src, faces, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE|CV_HAAR_FIND_BIGGEST_OBJECT, Size(150, 150));

    cout << "detected images" <<endl;
    face_image = gray_video_src(Rect(faces[0].x, faces[0].y, faces[0].width, faces[0].height));
    rectangle(video_src, faces[0], CV_RGB(0,255,0),1);

    //find eyes
    //eye_cascade.detectMultiScale(face_image, eyes, 1.1, 2, 0|CASCADE_SCALE_IMAGE|CV_HAAR_FIND_BIGGEST_OBJECT, Size(30,30) );

    //cout <<"Found eyes" << endl;
    //eye_image = face_image(Rect(eyes[0].x, eyes[0].y, eyes[0].width, eyes[0].height));
    //rectangle(video_src,eyes[0], CV_RGB(0,255,0),1);

    threshold(~face_image, otsu_image, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU); 

    threshold(~face_image, threshold_image, 190, 255, THRESH_BINARY);

    medianBlur(otsu_image, blur_image, 3);

    Canny(blur_image, edge, 50, 150, 3);
   
    //imshow(RED_WINDOW, rgb[2]);
    //imshow(GREEN_WINDOW, rgb[1]);
    //imshow(BLUE_WINDOW, rgb[0]);
    imshow("FACE", face_image);
    //imshow("EYE", eye_image);
    imshow(SOURCE,video_src);
    imshow(GRAY, gray_video_src);
    imshow("INV GRAY VIDEO", inv_gray_video);
    //imshow(GRAY, gray_video_src);
    imshow(OTSU, otsu_image);
    imshow(THRESHOLD, threshold_image);
    //imshow(CANNY_WINDOW, edge);

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
