#include "constants.hpp"
#include <stdio.h>

#include "gaze_lib.hpp"
using namespace std;
using namespace cv;

//#define DEBUG

 //Returns the vertical scaling factor between input image and output monitor;
double Scaley(int height){
  double scaley;

  scaley = Monitor_height/height ;// Monitor_height stored in constants.hpp

  #ifdef DEBUG
    cout << "height = " << height << " scaley= " << scaley << endl;
  #endif

  return scaley;
}

 //Returns the horizontal scaling factor between input image and output monitor;
double Scalex(int width){
  double scalex;
  scalex = Monitor_width /width ; //stored in constants.hpp

  #ifdef DEBUG
      cout << "width = " << width << " scalex= " << scalex << endl;
  #endif

  return scalex;
}


//Displays the an image with the boundary box and the location of the pupil
void  Draw_Gaze(int image_width, int image_height, int** boundary, int bound_width, int bound_height, int* pupil_loc){
  Mat gaze_img;
  int i;

    if ((image_width >0) && (image_height >0 )) {
      gaze_img = Mat::zeros(image_width,image_height, CV_8U); }
    else{
      cout << "invalid image size"; }

      Rect rect(boundary[2][1], boundary[1][0], bound_width, bound_height);
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

  int bound_height = (boundary[0][0] - boundary[1][0]) *2;
  int bound_width = (boundary[0][1] - boundary[2][1]) *2;

  #ifdef DEBUG
    cout << "height = " << bound_height << " width = " << bound_width << endl;
  #endif

   Draw_Gaze(image_width, image_height, boundary, bound_width, bound_height, pupil_loc);


   scaley = Scaley(bound_height);
   scalex = Scalex(bound_width);

   #ifdef DEBUG
      cout<< "scale x = " << scalex << " scale y = " << scaley << endl;
   #endif

   cursor_loc[0] = (pupil_loc[0] - boundary[1][0])* scaley;
   cursor_loc[1] = (pupil_loc[1] - boundary[2][1])* scalex;


   if (cursor_loc[0] < 0){
     cursor_loc[0] = 0;
   }
   else if (cursor_loc[0] > Monitor_height){
     cursor_loc[0] = Monitor_height;
   }

   if (cursor_loc[1] < 0){
     cursor_loc[1] = 0;
   }
   else if (cursor_loc[1] > Monitor_width){
     cursor_loc[1] = Monitor_width;
   }


  #ifdef DEBUG
    cout<< "cursor x = " << cursor_loc[1] << " cursor y = " << cursor_loc[0] << endl;
  #endif


  return cursor_loc;

}
