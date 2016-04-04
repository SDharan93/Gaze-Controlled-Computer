#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core.hpp"
using namespace cv;
using namespace std;


double Scaley_corner(int row1, int row2);
double Scalex_corner(int col1, int col2);
void  Draw_Gaze_corner(int image_width, int image_height, int** boundary, int* pupil_loc);
int * Cursor_Coordinates_corner(int image_width, int image_height, int** boundary, int* pupil_loc);
