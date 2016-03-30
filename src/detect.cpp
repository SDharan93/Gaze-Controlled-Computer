#include "detect.hpp"
#include "constants.hpp"

using namespace cv;
using namespace std;

Detect::Detect() {
    this->cap.open(0);
}

Detect::Detect(int number) {
    cap.open(number);
}

Mat Detect::get_face_image() {
    return this->face_image.clone(); 
}

void Detect::set_face_image(Mat face) {
   this->face_image = face.clone();  
}

Mat Detect::get_eye_image() {
    return this->eye_image.clone();
}

void Detect::set_eye_image(Mat eye) {
    this->eye_image = eye.clone(); 
}

Mat Detect::get_video_image() {
    return video_image.clone();
}

bool Detect::capture_image() {
    if(!cap.isOpened()) {
        cout << "Could not open camera" << endl; 
        return false; 
    } else {
        cap >> video_image; 
        //if the image did not load properly, it would be empty.
        if(video_image.empty()) {
            cout << "IMAGE DID NOT LOAD PROPERLY FROM CAMERA" << endl;
            return false; 
        }
    }
    return true;
}

bool Detect::findFace(String face_cascade_name) {
    Mat gray_image;
    vector<Mat> rgb;

    split(this->video_image, rgb);
    gray_image = rgb[2].clone();

    if(!face_cascade.load(face_cascade_name)) {
        cout << "ERROR: could not load face classifier" << endl;
        return false;
    }

    face_cascade.detectMultiScale(gray_image, faces_vector, 1.1, 2, 0|CASCADE_SCALE_IMAGE|CV_HAAR_FIND_BIGGEST_OBJECT, Size(30, 30));
    //if face was found.
    if(!faces_vector.empty()) {
       this->face_image = gray_image(Rect(faces_vector[0].x, faces_vector[0].y, faces_vector[0].width, faces_vector[0].height));
       rectangle(video_image, faces_vector[0], CV_RGB(0, 255, 0), 1);
    } else {
        cout << "COULD NOT FIND FACE THIS FRAME." << endl; 
        return false; 
    }
    return true; 
}

bool Detect::findEye(String face_cascade_name, String eye_cascade_name) {

}

void Detect::display_windows() {
    imshow(VIDEO_WINDOW_NAME, video_image);
}

void Detect::destroy_windows() {
    destroyWindow(VIDEO_WINDOW_NAME);
}
