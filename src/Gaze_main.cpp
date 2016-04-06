#include <iostream>
#include <stdio.h>

#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>


#include "Calibration.hpp"
#include "constants.hpp"
#include "gaze_lib_corner.hpp"
#include "gaze_lib.hpp"

//#define DEBUG

string ParseText2(){
  std::ifstream infile("coordinates.txt");
  int a, b;

  std::string line;
  while (std::getline(infile, line))
  {
    std::istringstream iss (line);
    int a,b;
    if (iss >> a >> b) {

      #ifdef DEBUG
        cout << "read in " << line << endl;
      #endif

        return line;
      }
  }

  #ifdef DEBUG
   cout << "something went wrong while parsing" << endl;
  #endif

  return line;
}

int main(int argc, char** argv){


    int** calibration_box = Calibrate();

    int pupil_loc[2];

    while (true) {
        string str;
        str =  ParseText2();
        std::istringstream iss (str);
        int row, col;

            if (!(iss >> pupil_loc[0] >> pupil_loc[1])) {
              cout << "error during calib" << endl;
            }
            #ifdef DEBUG
              cout << "row =" << pupil_loc[0] << " col=" << pupil_loc[1] << endl;
            #endif


  //  int* cursor_loc = Cursor_Coordinates(calibimg_width, calibimg_height, calibration_box, pupil_loc);
     int* cursor_loc = Cursor_Coordinates_corner(calibimg_width, calibimg_height, calibration_box, pupil_loc);

    //  cout << "move cursor loc  x:" << cursor_loc[1] << " y:" << cursor_loc[0] << endl;

     ostringstream ss;
     ss  << cursor_loc[1] <<  " " << cursor_loc[0];
     string str2 = "xdotool mousemove " + ss.str();
     const char * command = str2.c_str();
     cout << "command = " << command << endl;
   system (command);

  }
    return 1;
}
