#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core.hpp"
using namespace cv;
using namespace std;


double Scaley(int row1, int row2);
double Scalex(int col1, int col2);
void  Draw_Gaze(int image_width, int image_height, int** boundary, int* pupil_loc);
int * Cursor_Coordinates(int image_width, int image_height, int** boundary, int* pupil_loc);
