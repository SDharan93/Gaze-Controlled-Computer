#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/objdetect.hpp>

//Contains the global variables for the program. 
using namespace cv; 
using namespace std; 

//Window Names 
static String IMAGE_WINDOW_NAME = "Image Window";
static String VIDEO_WINDOW_NAME = "Video Window";
static String GRAY_WINDOW_NAME = "Gray Video Window";
static String EYE_WINDOW_NAME = "Eye Window"; 
static String FACE_WINDOW_NAME = "Face Window";

static String FACE_CASCADE_NAME = "res/haarcascade_frontalface_alt.xml";
static String EYE_CASCADE_NAME = "res/haarcascade_eye_tree_eyeglasses.xml";

static int CLOSE_PROGRAM = 27; //esc
static int DEBUG_WINDOWS = 100; //d
static int CLOSE_WINDOWS = 99; //c

static float alpha = 1.0625;
