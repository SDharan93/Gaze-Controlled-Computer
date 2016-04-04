#include "constants.hpp"
#include <stdio.h>

#include "gaze_lib.hpp"
using namespace std;
using namespace cv;

//#define DEBUG

 //Returns the vertical scaling factor between input image and output monitor;
double Scaley(int row1, int row2){
  double scaley;
  int Vert = Monitor_height; // stored in constants.hpp
  scaley = Vert/(row2 - row1) ;

  #ifdef DEBUG
    cout << "row1= " << row1 << " row2= " << row2 << " scaley= " << scaley << endl;
  #endif

  return scaley;
}

 //Returns the horizontal scaling factor between input image and output monitor;
double Scalex(int col1, int col2){
  double scalex;
  int Horiz = Monitor_width; //stored in constants.hpp
  scalex = Horiz/(col2 - col1) ;

  #ifdef DEBUG
      cout << "col1= " << col1 << " col2= " << col2 << " scalex= " << scalex << endl;
  #endif

  return scalex;
}

//Displays the an image with the boundary box and the location of the pupil
void  Draw_Gaze(int image_width, int image_height, int** boundary, int* pupil_loc){
  Mat gaze_img;
  int i;

    if ((image_width >0) && (image_height >0 )) {
      gaze_img = Mat::zeros(image_width,image_height, CV_8U); }
    else{
      cout << "invalid image size"; }

      Rect rect(boundary[0][1], boundary[0][0], (boundary[1][1]-boundary[0][1]), (boundary[1][0] - boundary[0][0]));

      cout << "width = " << (boundary[1][1]-boundary[0][1]) << " height " << (boundary[1][0] - boundary[0][0]) << endl;

      rectangle (gaze_img, rect,  CV_RGB(255,255,255), 1, 8, 0);


    #ifdef DEBUG
      cout << "done drawing left and right calibration box line"<< endl;
    #endif

      gaze_img.at<uchar>(pupil_loc[0],pupil_loc[1]) = 250;

     imshow("gaze_img", gaze_img);
     waitKey(100);
}


// replace main with another function,  input = image_width, image_height, boundary, pupil_loc
int * Cursor_Coordinates(int image_width, int image_height, int** boundary, int * pupil_loc){

  #ifdef DEBUG
    cout << "image_width=" << image_width << " image_height=" << image_height << " pupil_loc=" << pupil_loc[0] << "," << pupil_loc[1] << endl;
    cout << "boundary = " << endl;

    for (int i=0; i < 4; i++){
      cout << "    {" << boundary[i][0] << "," << boundary[i][1] << "}" << endl;
    }
  #endif

  int * cursor_loc  = new int[2] ;
  double scalex, scaley;

  if ((pupil_loc[1] < boundary[0][1])|| (pupil_loc[1] > boundary[1][1])){
    cout << "horizontally outside calibrated area" << endl;}
  if ((pupil_loc[0] < boundary[0][0]) || (pupil_loc[0] > boundary[1][0])){
    cout << "vert outside calibrated area" << endl;
  }

   Draw_Gaze(image_width, image_height, boundary, pupil_loc);


   scaley = Scaley(boundary[0][0], boundary[1][0]);
   scalex = Scalex(boundary [0][1], boundary[1][1]);

   #ifdef DEBUG
      cout<< "scale x = " << scalex << " scale y = " << scaley << endl;
   #endif

   cursor_loc[0] = (pupil_loc[0] - boundary[0][0])* scaley;
   cursor_loc[1] = (pupil_loc[1] - boundary[0][1])* scalex;


  #ifdef DEBUG
    cout<< "cursor x = " << cursor_loc[1] << " cursor y = " << cursor_loc[0] << endl;
  #endif


  return cursor_loc;

}
