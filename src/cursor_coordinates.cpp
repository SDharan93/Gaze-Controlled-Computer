#include <stdio.h>

#include "cursor_coordinates.hpp"
#include "constants.hpp"

using namespace std;
using namespace cv;

//#define DEBUG

/*Returns the vertical scaling factor between input image and output monitor;*/
double ScaleY(int row1, int row2){
  double scaley;
  scaley = (Monitor_height/2)/(row2 - row1) ; // Monitor_height stored in constants.hpp

  #ifdef DEBUG
  cout << "row1= " << row1 << " row2= " << row2 << " scaley= " << scaley << endl;
  #endif

  return scaley;
}

/*Returns the horizontal scaling factor between input image and output monitor;*/
double ScaleX(int col1, int col2){
  double scalex;
  scalex = (Monitor_width/2)/(col2 - col1) ;// Monitor_width stored in constants.hpp

  #ifdef DEBUG
  cout << "col1= " << col1 << " col2= " << col2 << " scalex= " << scalex << endl;
  #endif

  return scalex;
}


/*Displays an 400x400 black image with the calculated calibration box and the acquired gaze
location. This allows for the visualization of the location of the user's gaze on the monitor screen.
The presence of this image also proved to improve the user's control over the cursor */
void  Draw_Gaze(int image_width, int image_height, int leftboun_avg, int topboun_avg, int** boundary, int* pupil_loc){
  #ifdef DEBUG
  cout << "reached Draw_Gaze_corner" << endl;
  #endif

  Mat gaze_img;
  int i;

  if ((image_width >0) && (image_height >0 )) {
    gaze_img = Mat::zeros(image_width,image_height, CV_8U); }
    else{
      cout << "invalid image size"; }

      //drawing the rectanlge using OpenCV commands
      Rect rect(leftboun_avg, topboun_avg, (boundary[4][1]-leftboun_avg), (boundary[0][0] - topboun_avg));
      rectangle (gaze_img, rect,  CV_RGB(255,255,255), 1, 8, 0);

      #ifdef DEBUG
      cout << "done drawing left and right calibration box line"<< endl;
      #endif

      //displaying a the gaze location as a small circle
      circle(gaze_img, Point(pupil_loc[1], pupil_loc[0]), 2, Scalar(255,255,255),-1,8,0);

      imshow("gaze_img", gaze_img);
      waitKey(100);
    }


/*This function determines the coordinates to where the cursor should move based on the pupil locations
arguments.  It also calls Draw_Gaze() to aid with the demo and development purposes */
    int * Cursor_Coordinates(int image_width, int image_height, int** boundary, int * pupil_loc){

      #ifdef DEBUG
      cout << "image_width=" << image_width << " image_height=" << image_height << " pupil_loc=" << pupil_loc[0] << "," << pupil_loc[1] << endl;
      cout << "boundary = " << endl;
      for (int i=0; i < calib_points; i++){
        cout << "    {" << boundary[i][0] << "," << boundary[i][1] << "}" << endl;
      }
      #endif

      int shiftfactor_y , shiftfactor_x;
      int * cursor_loc  = new int[2] ;
      double scalex, scaley;

      //Using multiple coordinates to find the average of the left and the top boundary
      //inorder to draw the calibration box
      int leftboun_avg = (boundary[0][1] + boundary[1][1] + boundary[2][1])/3; //affects the x direction
      int topboun_avg = (boundary [2][0] + boundary[3][0] + boundary [4][0])/3; //affects the y direction

      //To aid with development and the performance during demo day
      Draw_Gaze(image_width, image_height, leftboun_avg, topboun_avg, boundary, pupil_loc);

      //Get the scaling factors to multiply with the gaze locations
      scaley = ScaleY(topboun_avg, boundary[5][0]);
      scalex = ScaleX(leftboun_avg,boundary [5][1]);

      #ifdef DEBUG
      cout<< "scale x = " << scalex << " scale y = " << scaley << endl;
      #endif

      //The method to calculte where on the screen the user is looking unorder to move the cursor there
      int gaze_row = pupil_loc[0] - topboun_avg;
      int gaze_col = pupil_loc[1] - leftboun_avg;
      cursor_loc[0] = gaze_row* scaley;
      cursor_loc[1] = gaze_col* scalex;

      //Need this clause?
      if (cursor_loc[0] < 0){
        cursor_loc[0] = 0;
      }
      if (cursor_loc[1] < 0){
        cursor_loc[1] = 0;
      }

      #ifdef DEBUG
      cout<< "cursor x = " << cursor_loc[1] << " cursor y = " << cursor_loc[0] << endl;
      #endif

      return cursor_loc;

    }
