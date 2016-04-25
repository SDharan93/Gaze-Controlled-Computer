#include <fstream>
#include <sstream>
#include <string>

#include "Calibration.hpp"
#include "constants.hpp"

using namespace std;
using namespace cv;

#define DEBUG2

/* The calibration procedure is desgined to work using key press at the moment. to record
the location of the pupil for each calibration point press c and ESC to terminate the procedure*/
int KeyPress(char input){
    switch (input){
      //To record the pupil location and to advance to the next point
      case 'c':{

        #ifdef DEBUG
        cout << "Pupil location stored" << endl;
        #endif

        return 2;
      }
      //To Exit
      case 27:{
        #ifdef DEBUG
          cout << "ESC" << endl;;
        #endif

        exit(0);
        return 0;
      }
    }

    #ifdef DEBUG
      cout << "random input" << endl;
    #endif

    return 3;
}

/*This function retrives the location of the pupil stored in coordinates.txt*/
string ParseText_Calib(){
  std::ifstream infile("coordinates.txt");
  std::string line;

  while (std::getline(infile, line))
  {
    std::istringstream iss (line);
    int a,b;

    //Verifying if the information in the txtfile is valid by attempting to seperate it into 2 ints.
    //Somtimes the file contains multiple lines, and only the first valid line is returned
    if (iss >> a >> b) {
        return line;
      }
  }

  #ifdef DEBUG
   cout << "something went wrong while parsing" << endl;
  #endif

  return line;
}

/*This function records the position of the pupil at each of the calibration points*/
int** Calibrate()
{
    //calib_points is the ttl number of points and are declared in constants.hpp
    //There is no GUI to instruct the user about the procedure
    //The current calibration locations are: botleft, midleft, topleft, midtop, topright, center

    int** pupil_loc = new int*[calib_points];
    int counter = 0,input = 1;

    cout << " number of points for calibration = " << calib_points << endl;

    //A small image is created to run eventdetection through Opencv
    Mat img  = Mat::zeros(100,100, CV_8U);
    namedWindow("calib");
    resizeWindow("calib", 100,100);
    imshow("calib", img);

    // Wait until user press some key
      while ((counter < calib_points) && (input != 0)){
         char input_char = (static_cast<char>(waitKey(0)));

          input = KeyPress(input_char);

          //The User pressed c, so storing the current location of the pupil
          if (input == 2){
            string str;
            str =  ParseText_Calib();
            std::istringstream iss (str);

            int row, col;
            //If the information from the coordinates.txt is not valid
            if (!(iss >> row >> col)) {
              cout << "error during calib" << endl;
            }

            #ifdef DEBUG
              cout << "row =" << row << " col=" << col << endl;
            #endif

            //storing the informatin from the txtfile in row,col format
            pupil_loc[counter] = new int [2];
            pupil_loc[counter][0] = row;
            pupil_loc[counter][1] = col;

            cout << "Point " << counter +1 << " : " << pupil_loc[counter][0] << " " << pupil_loc[counter][1] << endl;
            counter++;
          }
      }

      waitKey(0);

      #ifdef DEBUG2
        {
          cout << "the calib rect is ";
          for (int i =0; i <counter; i++){
            cout << " {" << pupil_loc[i][0] << "," << pupil_loc[i][1] << "} ";
          }
          cout << endl;
        }
      #endif

      //closing the calib image to proceed with the rest of the program
      destroyAllWindows();

      return pupil_loc;

}
