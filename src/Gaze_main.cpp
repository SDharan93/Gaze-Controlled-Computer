#include <iostream>
#include <stdio.h>

#include "Calibration.hpp"
#include "gaze_lib.hpp"

int main(int argc, char** argv){

    int** calibration_box = Calibrate();

    int image_width = 250;
    int image_height = 250;
    int pupil_loc[2] = {100,100};


    int* cursor_loc = Cursor_Coordinates(image_width, image_height, calibration_box, pupil_loc);

    cout << "move cursor loc  x:" << cursor_loc[1] << " y:" << cursor_loc[0] << endl;
    return 1;
}
