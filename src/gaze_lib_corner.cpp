#include "constants.hpp"
#include <stdio.h>

#include "gaze_lib.hpp"
using namespace std;
using namespace cv;

//#define DEBUG

 //Returns the vertical scaling factor between input image and output monitor;
double Scaley_corner(int row1, int row2){
  double scaley;
   scaley = Monitor_height/(row2 - row1) ; // Monitor_height stored in constants.hpp

   #ifdef DEBUG
     cout << "row1= " << row1 << " row2= " << row2 << " scaley= " << scaley << endl;
   #endif

   return scaley;
}

 //Returns the horizontal scaling factor between input image and output monitor;
double Scalex_corner(int col1, int col2){
  double scalex;
    scalex = Monitor_width/(col2 - col1) ;// Monitor_width stored in constants.hpp

    #ifdef DEBUG
        cout << "col1= " << col1 << " col2= " << col2 << " scalex= " << scalex << endl;
    #endif

    return scalex;
}


//Displays the an image with the boundary box and the location of the pupil
void  Draw_Gaze_corner(int image_width, int image_height, int** boundary, int* pupil_loc){
    #ifdef DEBUG
      cout << "reached Draw_Gaze_corner" << endl;
    #endif

  Mat gaze_img;
    int i;

      if ((image_width >0) && (image_height >0 )) {
        gaze_img = Mat::zeros(image_width,image_height, CV_8U); }
      else{
        cout << "invalid image size"; }

        Rect rect(boundary[0][1], boundary[0][0], (boundary[1][1]-boundary[0][1]), (boundary[1][0] - boundary[0][0]));

        rectangle (gaze_img, rect,  CV_RGB(255,255,255), 1, 8, 0);
      //Drwing the top and bottom boudary line
    /*  for (i = boundary[0][1]; i<=boundary[1][1]; i++){
          gaze_img.at<uchar>(boundary[0][0],i) = 250;
          gaze_img.at<uchar>(boundary[3][0],i) = 250;
      }
      #ifdef DEBUG
        cout << "done drawing top and bottom calibration box line"<< endl;
      #endif
      //Drawing the left and right boundary line
      for (i = boundary[0][0]; i<=boundary[3][0]; i++){
          gaze_img.at<uchar>(i,boundary[0][1]) = 250;
          gaze_img.at<uchar>(i,boundary[1][1]) = 250;
      }*/

      #ifdef DEBUG
        cout << "done drawing left and right calibration box line"<< endl;
      #endif

        gaze_img.at<uchar>(pupil_loc[0],pupil_loc[1]) = 250;

       imshow("gaze_img", gaze_img);
       waitKey(100);
}


// replace main with another function,  input = image_width, image_height, boundary, pupil_loc
int * Cursor_Coordinates_corner(int image_width, int image_height, int** boundary, int * pupil_loc){

    #ifdef DEBUG
      cout << "image_width=" << image_width << " image_height=" << image_height << " pupil_loc=" << pupil_loc[0] << "," << pupil_loc[1] << endl;
      cout << "boundary = " << endl;

      for (int i=0; i < calib_points; i++){

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


     Draw_Gaze_corner(image_width, image_height, boundary, pupil_loc);


     scaley = Scaley_corner(boundary[0][0], boundary[1][0]);
     scalex = Scalex_corner(boundary [0][1], boundary[1][1]);

     #ifdef DEBUG
        cout<< "scale x = " << scalex << " scale y = " << scaley << endl;
     #endif

     cursor_loc[0] = (pupil_loc[0] - boundary[0][0])* scaley;
     cursor_loc[1] = (pupil_loc[1] - boundary[0][1])* scalex;

     if (cursor_loc[0] < 0){
       cursor_loc[0] = 0;
     }
  /*   else if (cursor_loc[0] > Monitor_height){
       cursor_loc[0] = Monitor_height;
     }*/

     if (cursor_loc[1] < 0){
       cursor_loc[1] = 0;
     }
     /*else if (cursor_loc[1] > Monitor_width){
       cursor_loc[1] = Monitor_width;
     }*/



    #ifdef DEBUG
      cout<< "cursor x = " << cursor_loc[1] << " cursor y = " << cursor_loc[0] << endl;
    #endif


    return cursor_loc;

}
