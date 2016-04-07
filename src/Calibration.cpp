
#include "Calibration.hpp"
#include "constants.hpp"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
using namespace cv;

#define DEBUG2

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
        exit(0);
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
    int** pupil_loc = new int*[calib_points];  //, botleft, midleft, topleft, midtop, center
     int counter = 0,input = 1;

     cout << " number of points for calibration = " << calib_points << endl;

    Mat img  = Mat::zeros(100,100, CV_8U);
    namedWindow("calib");
    resizeWindow("calib", 100,100);
    imshow("calib", img);

    //TO DO; CALL PYTHON CALIB GUI


      // Wait until user press some key
      while ((counter < calib_points) && (input != 0)){
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

      destroyAllWindows();

      return pupil_loc;

}
