#include "opencv2/highgui/highgui.hpp"
#include <iostream>

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

//Replace main with another function
int main(int argc, char** argv)
{
    int pupil_loc [4][2];
     int counter = 0,input = 1;

     namedWindow("const");
      // Wait until user press some key4make
      while ((counter < 4)&&(input != 0)){
         char input_char = (static_cast<char>(waitKey(0)));
          input = KeyPress(input_char);
          if (input == 2){
            int x = 0;//capture the x pupil location;
            int y = 0;//capture the y pupil location

            pupil_loc[counter][0] = y;
            pupil_loc[counter][1] = x;

            counter++;
          }
      }

      waitKey(0);
      return 0;

}
