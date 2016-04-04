#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/objdetect.hpp>

#include "v4ldevice.h"

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

        Detect(char* location, int width, int height);
        
        //function call for finding face. If face cannot be found, false is returned. If it is found, it will return true.
        bool findFace(String face_cascade_name);
        
        //function call for finding eye from the face image. If eye cannot be found false is returned, else true. 
        bool findEye(String eye_cascade_name);

        //finds the face from video source then finds eyes from the recognized face.
        bool findFeatures(String face_cascade_name, String eye_cascade_name);

        //function to grab image from camera. If there is an issue, return false, else true. 
        bool capture_image();

        //function to grab frame from camera on the Nvidia board/camera.
        bool nv_capture_image();

        bool load_image(String image);

        //displays images used by detect for debugging. 
        void display_windows(); 

        //destory windows created for debugging. 
        void destroy_windows();

        static Rect eye_crop;
        static int search_count;
        static bool search_flag;
    private:
        Mat face_image; 
        Mat eye_image;
        Mat video_image;

        vector<Rect> faces_vector; 
        vector<Rect> eyes_vector;

        VideoCapture cap; 
        Size imageSize;

        CascadeClassifier face_cascade;
        CascadeClassifier eye_cascade;

        
};

//int Detect::search_count = 0;
//bool Detect::search_flag = true;
//Rect Detect::eye_crop = Rect(Point(0,0), Point(40,40));
