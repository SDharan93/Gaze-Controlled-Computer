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
double Scaley(){
  double scaley;
  int Vert = 704;  //704 pixels vertically in the monitor
  scaley = Vert/25 ;// 25 grids
  return scaley;
}

 //Returns the horizontal scaling factor between input image and output monitor;
double Scalex(){
  double scalex;
  int Horiz = 1252; //1252 pixels horizontally in the monitor
  scalex = Horiz/25 ; //25 grids
  return scalex;
}

/*Creates a 250x250 black image with randomly placed white dot, then searches for the whitedot, then outputs
cursor XY  based on scaling factor. */
int main(int argc, char** argv){
  Mat image;
  int i , j, dotx, doty, cursorx, cursory;
  double scalex, scaley;

  image = Mat::zeros(250, 250, CV_8U); //creating a black image

  srand (time(NULL));
  image.at<uchar>(rand() % 250,rand() % 250) = 250;  //randomly placing a white dot in the image
  imshow("image",image);

            //finding the white dot in the image
  for (i = 0; i <250; i++){
    for (j = 0; j <250; j++){
      if (image.at<uchar>(i,j) == 250){
        dotx = j;
        doty = i;

        #ifdef DEBUG
          cout << "dotx = " << dotx << "  doty = " << doty << endl;
        #endif
      }
    }
  }

          //find the scaling factor for horiz and vertical
  scalex = Scalex();
  scaley = Scaley();

          //calculating which grid (size = [10 px, 10px]) the dot is
  #ifdef DEBUG
    cout << "gridx = " << dotx/10 << "   gridy = " << doty/10 << endl;
  #endif

        //the calculated cursor X Y
  cursorx = (dotx/10) * scalex;
  cursory = (doty/10) * scaley;

  cout << "cursorx = " << cursorx << "   cursory = " << cursory << endl;


  waitKey(0);
}
