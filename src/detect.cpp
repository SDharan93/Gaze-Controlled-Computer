#include "detect.hpp"
#include "constants.hpp"

using namespace cv;
using namespace std;

bool cascade_search(String name, Mat video_image, Mat gray_image, int size, Mat saved_image);

Detect::Detect() {
    cap.open(0);
}

Detect::Detect(int number) {
    cap.open(number);
}

Mat Detect::get_face_image() {
    return face_image.clone(); 
}

void Detect::set_face_image(Mat face) {
   face_image = face.clone();  
}

Mat Detect::get_eye_image() {
    return eye_image.clone();
}

void Detect::set_eye_image(Mat eye) {
    eye_image = eye.clone(); 
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

    split(video_image, rgb);
    gray_image = rgb[2].clone();

    if(!face_cascade.load(face_cascade_name)) {
        cout << "ERROR: could not load face classifier" << endl;
        return false;
    }

    face_cascade.detectMultiScale(gray_image, faces_vector, 1.1, 2, 0|CASCADE_SCALE_IMAGE|CV_HAAR_FIND_BIGGEST_OBJECT, Size(30, 30));
    //if face was found.
    if(!faces_vector.empty()) {
       face_image = gray_image(Rect(faces_vector[0].x, faces_vector[0].y, faces_vector[0].width, faces_vector[0].height));
       rectangle(video_image, faces_vector[0], CV_RGB(0, 255, 0), 1);
    } else {
        cout << "COULD NOT FIND FACE IN THIS FRAME." << endl; 
        return false; 
    }
    return true; 
}

bool Detect::findEye(String eye_cascade_name) {
    if(cascade_search(eye_cascade_name, video_image, face_image, 30, eye_image)){
        return true; 
    }
    return false;
}

bool cascade_search(String name, Mat video_image, Mat gray_image, int size, Mat saved_image) {
    CascadeClassifier cascade;
    vector<Rect> cascade_vec;
    //Mat result;

    if(!cascade.load(name)) {
        cout << "ERROR: could not load face classifier" << endl;
        return false;
    }

    cascade.detectMultiScale(gray_image, cascade_vec, 1.1, 2, 0|CASCADE_SCALE_IMAGE|CV_HAAR_FIND_BIGGEST_OBJECT, Size(size, size));
    //if face was found.
    if(!cascade_vec.empty()) {
       saved_image = gray_image(Rect(cascade_vec[0].x, cascade_vec[0].y, cascade_vec[0].width, cascade_vec[0].height));
       rectangle(video_image, cascade_vec[0], CV_RGB(0, 255, 0), 1);
    } else {
        cout << "COULD NOT FIND FACE IN THIS FRAME." << endl; 
        return false; 
    }
    return true;
}

void Detect::display_windows() {
    imshow(VIDEO_WINDOW_NAME, video_image);
    //make sure that the face image has some value 
    if(!face_image.empty()) {
        imshow(FACE_WINDOW_NAME, face_image);
    }

    if(!eye_image.empty()) {
        imshow(EYE_WINDOW_NAME, eye_image);
    }
}

void Detect::destroy_windows() {
    destroyWindow(VIDEO_WINDOW_NAME);
    destroyWindow(FACE_WINDOW_NAME);
    destroyWindow(EYE_WINDOW_NAME);
}
