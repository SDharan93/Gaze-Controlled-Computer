#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "Calibration.hpp"

using namespace std;
using namespace cv;

// Desgined to work using key press at the moment,
int KeyPress(char input){
    switch (input){
      case 'c':{
        cout << "Pupil location stored" << endl;
        return 2;
      }
      case 27:{
        cout << "ESC" << endl;
        return 0;
      }
    }
    return 3;
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
            int row = 1*counter;//capture the x pupil location;
            int col = 1*counter;//capture the y pupil location

            pupil_loc[counter] = new int [2];
            pupil_loc[counter][0] = row;
            pupil_loc[counter][1] = col;

            counter++;
          }
      }

      waitKey(0);
      return pupil_loc;

}
