#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>

#include "Calibration.hpp"
#include "constants.hpp"
#include "cursor_coordinates.hpp"

//#define DEBUG

/*The location of the pupil is constantly updated in the coordinates.txt
This function parses the txtfile during operation */
string ParseText_Operation(){
  std::ifstream infile("coordinates.txt");

  std::string line;
  while (std::getline(infile, line))
  {
    std::istringstream iss (line);
    int a,b;

    //Verifying if the information in the txtfile is valid by attempting to seperate it into 2 ints.
    //Somtimes the file contains multiple lines, and only the first valid line is returned
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

/*The main function initiates the calibration procedure during startup, parses
the txtfile conitnously for the location of the pupil and then moves the cursor using the
xdotool  */
int main(int argc, char** argv){

  //The function Calibrate(), from Calibration.cpp, returns the 4 cooridantes
  //of the calibration box determined during the calibration procedure
  int** calibration_box = Calibrate();
  //The pupil location in the image is acquired in the from (row, col)
  int pupil_loc[2];

  while (true) {
    string str;
    str =  ParseText_Operation();
    std::istringstream iss (str);
    int row, col;

    //if the information in the textfile cannot be seperated into 2 ints
    if (!(iss >> pupil_loc[0] >> pupil_loc[1])) {
      cout << "error in txt file" << endl;
    }
    #ifdef DEBUG
    cout << "row =" << pupil_loc[0] << " col=" << pupil_loc[1] << endl;
    #endif

    //The function Cursor_Coordinates_corner(), from gaze_lib_corner.cpp, returns
    //the coordinate that the cursor to move to on the monitor screen
    //calibimg_width = calibimg_height = 400,   declared in constants.hpp
    int* cursor_loc = Cursor_Coordinates(calibimg_width, calibimg_height, calibration_box, pupil_loc);

    //Moving the curosr by excecuting xdotool (3rd party tool) command
    ostringstream ss;
    ss  << cursor_loc[1] <<  " " << cursor_loc[0];
    string str2 = "xdotool mousemove " + ss.str();
    const char * command = str2.c_str();
    system (command);

  }
  return 1;
}
