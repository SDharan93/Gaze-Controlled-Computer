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
  scaley = Vert/(row2 - row1) ;// 25 grids
  return scaley;
}

 //Returns the horizontal scaling factor between input image and output monitor;
double Scalex(int col1, int col2){
  double scalex;
  int Horiz = 1252; //1252 pixels horizontally in the monitor
  scalex = Horiz/(col2 - col1) ; //25 grids
  return scalex;
}

/*Creates a 250x250 black image with randomly placed white dot, then searches for the whitedot, then outputs
cursor XY  based on scaling factor. */
int main(int argc, char** argv){
  Mat pupil_img;
  int i, image_width, image_height, cursorx, cursory;//, j, dotx, doty, ;
  double scalex, scaley;

  image_width=250;
  image_height = 250;

  pupil_img = Mat::zeros(image_width,image_height, CV_8U);


    int boundary[4][2] = { {100,100},
                            {100,200},
                            {150,100},
                            {150,200} };
    int pupil_loc[2] = {130,142};


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

   scaley = Scaley(boundary[0][0], boundary[3][0]);
   scalex = Scalex(boundary [0][1], boundary[3][1]);

   cout<< "scale x = " << scalex << " scale y = " << scaley << endl;

   cursorx = (pupil_loc[0] - boundary[0][0])*scalex;
   cursory = (pupil_loc[1] - boundary[0][1])* scaley;

  cout<< "cursor x = " << cursorx << " cursor y = " << cursory << endl;



  //waitKey(0);
  }


  /*
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
      ssdf
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
}*/
