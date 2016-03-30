#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/objdetect.hpp>

#include <iostream>

using namespace cv; 
using namespace std;

class Detect {
    public: 
        //getter and setter for image of face. 
        Mat get_face_image();
        void set_face_image(Mat face);

        //getter and setter for image of eye.
        Mat get_eye_image();
        void set_eye_image(Mat eye);

        Mat get_video_image();
        void set_video_image();

        //Constructors
        Detect();

        Detect(int number);
        
        //function call for finding face. If face cannot be found, false is returned. If it is found, it will return true.
        bool findFace(String face_cascade_name);
        
        //function call for finding eye from the face image. If eye cannot be found false is returned, else true. 
        bool findEye(String face_cascade_name, String eye_cascade_name);

        //function to grab image from camera. If there is an issue, return false, else true. 
        bool capture_image();

        //displays images used by detect for debugging. 
        void display_windows(); 

        //destory windows created for debugging. 
        void destroy_windows();
    private:
        Mat face_image; 
        Mat eye_image;
        Mat video_image;

        vector<Rect> faces_vector; 
        vector<Rect> eyes_vector;

        VideoCapture cap; 

        CascadeClassifier face_cascade;
        CascadeClassifier eye_cascade;
};
