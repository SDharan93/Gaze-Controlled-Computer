#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/objdetect.hpp"
#include <opencv2/videoio.hpp>

#include <iostream>
#include <stdio.h>
#include <cmath>

using namespace std;
using namespace cv;

//GLOBAL VARIABLES
CascadeClassifier face_cascade;
CascadeClassifier eye_cascade;

//function headers
int* FaceDetect (Mat image);
int* EyeDetect (Mat face_image);

int main(int argc, char** argv) {
  // Declaration of VARIABLES
    Mat image, face_image, eyeimage;

    image = imread("./screenshot.jpg", 1); //reading the original image from the file
    //imshow("image", image);   //displaying the image

    //Loading the HARR cascade files
    if ((!face_cascade.load("./haarcascade_frontalface_alt.xml") ) || (!eye_cascade.load("./haarcascade_eye_tree_eyeglasses.xml") ))
     {
      cout << "ERROR loading the the classifiers";
      return 0;
     }
    else
      cout << "loaded both classifiers" << endl;

    //calling on function to do face detection
    int *facerect = FaceDetect(image);

    //cropping to the face
    face_image = image(Rect(facerect[0],facerect[1],facerect[2],facerect[3]));
    imshow("face1", face_image);

    //calling on a function to do eye detection
    int *eyerect = EyeDetect(face_image);

    //cropping to the eye based on the face_image input
    eyeimage = face_image(Rect(eyerect[0],eyerect[1],eyerect[2],eyerect[3]));

    //Resizing the cropped eye image to twice the size
    resize(eyeimage, eyeimage, eyeimage.size()*2, 0,0, INTER_NEAREST);

    imshow("Eyes", eyeimage);

    waitKey(0);  //need this or, the output images will be terminated too quickly
}

//This method finds the location of the face and returns it to main
int * FaceDetect (Mat image){
   Mat gray_image;
   std::vector<Rect> face;  // a vector to store face coordinates
   int *facerect = new int [4];  //array that will be passed back to main

   cvtColor( image, gray_image, COLOR_BGR2GRAY ); //converting image into gray_image
   equalizeHist( gray_image, gray_image ); //equalizing the histogram of gray_image

  //-- Detect a face
  face_cascade.detectMultiScale( gray_image, face, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(100, 100) );

  // storing the coordinates of the face
  for( size_t i = 0; i < face.size(); i++ ){
    facerect [0] = face[i].x ;
    facerect [1] = face[i].y;
    facerect [2] = face[i].width;
    facerect [3] = face[i].height;
  }

  return facerect;
}

//This method finds the location of the eys and returns it to main
int * EyeDetect (Mat face_image){
   std::vector<Rect> eyes;  // a vector to store face coordinates
   int *eyerect = new int [4];  //array that will be passed back to main

  //-- Detect eyes
  eye_cascade.detectMultiScale( face_image, eyes, 1.1, 2, 0 |CASCADE_SCALE_IMAGE, Size(30, 30) );

  // storing the coordinates of the eyes
  for( size_t i = 0; i < eyes.size(); i++ ){
    eyerect [0] = eyes[i].x ;
    eyerect [1] = eyes[i].y;
    eyerect [2] = eyes[i].width;
    eyerect [3] = eyes[i].height;
  }

  return eyerect;
}
