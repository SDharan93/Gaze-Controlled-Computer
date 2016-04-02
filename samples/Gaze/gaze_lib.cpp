#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/objdetect.hpp"
#include <opencv2/videoio.hpp>

#include <iostream>
#include <stdio.h>
#include <time.h>



using namespace std;
using namespace cv;

 //Returns the vertical scaling factor between input image and output monitor;
double Scaley(int row1, int row2){
  double scaley;
  int Vert = 704;  //704 pixels vertically in the monitor
  scaley = Vert/(row2 - row1) ;
  return scaley;
}

 //Returns the horizontal scaling factor between input image and output monitor;
double Scalex(int col1, int col2){
  double scalex;
  int Horiz = 1252; //1252 pixels horizontally in the monitor
  scalex = Horiz/(col2 - col1) ;
  return scalex;
}


// replace main with another function,  input = image_width, image_height, boundary, pupil_loc
int main(int argc, char** argv){

  Mat pupil_img;
  int image_width, image_height, cursorx, cursory;
  double scalex, scaley;

  image_width=250;
  image_height = 250;

  pupil_img = Mat::zeros(image_width,image_height, CV_8U);

   //Should be getting from calibration.cpp
    int boundary[4][2] = { {100,100},
                            {100,200},
                            {150,100},
                            {150,200} };

    int pupil_loc[2] = {101,200};

  if ((pupil_loc[0] < boundary[0][0] )|| (pupil_loc[0] > boundary[4][0])){
    cout << "horizontally outside calibrated area" << endl;}
  else if ((pupil_loc[1] < boundary[0][1]) || (pupil_loc[1] > boundary[4][1])){
    cout << "vert outside calibrated area" << endl;
  }

/*
  //Drwing the top and bottom boudary line
  for (i = boundary[0][1]; i<=boundary[1][1]; i++){
      pupil_img.at<uchar>(boundary[0][0],i) = 250;
      pupil_img.at<uchar>(boundary[3][0],i) = 250;
  }

  //Drawing the left and right boundary line
  for (i = boundary[0][0]; i<=boundary[3][0]; i++){
      pupil_img.at<uchar>(i,boundary[0][1]) = 250;
      pupil_img.at<uchar>(i,boundary[1][1]) = 250;
  }

    pupil_img.at<uchar>(pupil_loc[0],pupil_loc[1]) = 250;
//   imshow("grid", pupil_img);
*/
   scaley = Scaley(boundary[0][0], boundary[3][0]);
   scalex = Scalex(boundary [0][1], boundary[1][1]);

   cout<< "scale x = " << scalex << " scale y = " << scaley << endl;

   cursorx = (pupil_loc[1] - boundary[0][1])*scalex;
  cursory = (pupil_loc[0] - boundary[0][0])* scaley;
  cout << "rel x " << (pupil_loc[0] - boundary[0][0]) << " rel y " << (pupil_loc[1] - boundary[0][1]) << endl;
  cout<< "cursor x = " << cursorx << " cursor y = " << cursory << endl;

  imshow("sce", pupil_img);
 waitKey(0);
  return 1;
}
