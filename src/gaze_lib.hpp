#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core.hpp"
using namespace cv;
using namespace std;


double Scaley(int height);
double Scalex(int width);
void   Draw_Gaze(int image_width, int image_height, int** boundary, int bound_width, int bound_height, int* pupil_loc);
int * Cursor_Coordinates(int image_width, int image_height, int** boundary, int* pupil_loc);
