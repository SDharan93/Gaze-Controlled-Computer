#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/objdetect.hpp"
#include <opencv2/videoio.hpp>

#include <iostream>
#include <stdio.h>


using namespace std;
using namespace cv;

//GLOBAL VARIABLES
CascadeClassifier face_cascade;
CascadeClassifier eye_cascade;

//ONLY USE IF NEED TO TROUBLESHOOT
//#define DEBUG 1


void DynamicCrop(){

  #ifdef DEBUG
    cout<<"Inside DynamicCrop()" << endl;
  #endif

  Mat image, gray_image, face_image, eye_image;
  std::vector <Rect> face_rect;  // a vector to store face coordinates
  std::vector <Rect> eye_rect;  // a vector to store face coordinates

  VideoCapture capture;

  capture.open(0);

  // keepin the image display size constant
  namedWindow( "Eye", WINDOW_NORMAL );

  //Exit if stream is not working
  if(!capture.isOpened())   { cout << "Capture is not working" << endl; return ;}
  else{

    #ifdef DEBUG
      cout<<"Capture is open and working" << endl;
    #endif

    for(;;)   {
      capture >> image;

      if(image.empty()) {break ;}

      #ifdef DEBUG
        cout<<"image successfully captured" << endl;
      #endif

      cvtColor( image, gray_image, COLOR_BGR2GRAY ); //converting image into gray_image

      #ifdef DEBUG
        cout<<"image conv to grayscale" << endl;
      #endif

      equalizeHist( gray_image, gray_image ); //equalizing the histogram of gray_image

      //identifying the face and croping the original image
      try{
          face_cascade.detectMultiScale( gray_image, face_rect, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(100, 100) );
          face_image = gray_image(Rect(face_rect[0].x, face_rect[0].y, face_rect[0].width, face_rect[0].height));
        }
      catch (...){
        #ifdef DEBUG
          cout<<"Exception caught for face detection/crop" << endl;
        #endif
      }

      #ifdef DEBUG
        cout<<"face detection done, and face is cropped" << endl;
      #endif

      //identifying the eye and cropping the face image
      try{
        eye_cascade.detectMultiScale( face_image, eye_rect, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );
        eye_image = face_image(Rect(eye_rect[0].x, eye_rect[0].y, eye_rect[0].width, eye_rect[0].height));
      }
      catch(...){
        #ifdef DEBUG
          cout<<"Exception caught for eye detection/crop" << endl;
        #endif
      }

      #ifdef DEBUG
        cout<<"eye detection done, and eye is cropped" << endl;
      #endif

      //Resizing the cropped eye image to twice the size
      resize(eye_image, eye_image, eye_image.size()*2, 0,0, INTER_NEAREST);
      #ifdef DEBUG
        cout<<"successfully zoomed into croped eye" << endl << endl;
      #endif

      imshow("Eye", eye_image);
      if(waitKey(5) >= 0) {  break; }
    }

  }
}



void StaticCrop(){
  Mat image, gray_image, face_image, eye_image;
  std::vector <Rect> face_rect;  // a vector to store face coordinates
  std::vector <Rect> eye_rect;  // a vector to store face coordinates

  image = imread("./screenshot.jpg", 1); //reading the original image from the file

  if (image.empty()) {cout << "IMAGE NOT FOUND" << endl; return;}

  cvtColor( image, gray_image, COLOR_BGR2GRAY ); //converting image into gray_image
  equalizeHist( gray_image, gray_image ); //equalizing the histogram of gray_image

  //cropping to the face and saving it as a new image.
  face_cascade.detectMultiScale( gray_image, face_rect, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(100, 100) );
  face_image = gray_image(Rect(face_rect[0].x, face_rect[0].y, face_rect[0].width, face_rect[0].height));

  //cropping to the eye and saving it as a new image;
  eye_cascade.detectMultiScale( gray_image, eye_rect, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );
  eye_image = gray_image(Rect(eye_rect[0].x, eye_rect[0].y, eye_rect[0].width, eye_rect[0].height));

  //Resizing the cropped eye image to twice the size
  resize(eye_image, eye_image, eye_image.size()*2, 0,0, INTER_NEAREST);


  imshow("gray", eye_image);


  waitKey(0);
}



int main(int argc, char** argv){

  #ifdef DEBUG
      cout << "debug enabled" << endl;
  #endif

  //attempting to load the HAAR cascades for face and eye detection
  if ((!face_cascade.load("./haarcascade_frontalface_alt.xml") ) || (!eye_cascade.load("./haarcascade_eye_tree_eyeglasses.xml") ))
  {     cout << "ERROR loading the the classifiers";    return 0;   }

  #ifdef DEBUG
      cout << "done loading cascades" << endl;
  #endif


  //Call DynamicCrop to perform face and then eyedetcion on live camera stream
  DynamicCrop();

  //Call StaticCrop to perform face and then eyedetcion on still images
  // StaticCrop();

  cout << "exiting" <<endl;
}
