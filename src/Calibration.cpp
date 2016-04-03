#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "Calibration.hpp"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
using namespace cv;

#define DEBUG

// Desgined to work using key press at the moment,
int KeyPress(char input){
    switch (input){
      case 'c':{

        #ifdef DEBUG
        cout << "Pupil location stored" << endl;
        #endif

        return 2;
      }
      case 27:{
        #ifdef DEBUG
          cout << "ESC" << endl;;
        #endif

        return 0;
      }
    }

    #ifdef DEBUG
      cout << "random input" << endl;
    #endif

    return 3;
}

string ParseText(){
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


int** Calibrate()
{
    int** pupil_loc = new int*[4];
     int counter = 0,input = 1;

    namedWindow("const");
    resizeWindow("const", 10,10);

    //TO DO; CALL PYTHON CALIB GUI


      // Wait until user press some key
      while ((counter < 4) && (input != 0)){
         char input_char = (static_cast<char>(waitKey(0)));
          input = KeyPress(input_char);
          if (input == 2){
            string str;
            str =  ParseText();
            std::istringstream iss (str);

            int row, col;

            if (!(iss >> row >> col)) {
              cout << "error during calib" << endl;
            }

            #ifdef DEBUG
              cout << "row =" << row << " col=" << col << endl;
            #endif

            pupil_loc[counter] = new int [2];
            pupil_loc[counter][0] = row;
            pupil_loc[counter][1] = col;

            counter++;

          }
      }

      waitKey(0);

      #ifdef DEBUG
        {
          cout << "the calib rect is ";
          for (int i =0; i <counter; i++){
            cout << " {" << pupil_loc[i][0] << "," << pupil_loc[i][1] << "} ";
          }
          cout << endl;
        }
      #endif


      return pupil_loc;

}
