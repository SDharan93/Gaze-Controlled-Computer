#include "detect.hpp"
#include "constants.hpp"

using namespace cv;
using namespace std;

Mat cascade_search(String name, Mat video_image, Mat gray_image, int size, Mat saved_image);
Mat get_red_channel(Mat source);

Detect::Detect() {
    cap.open(0);
}

Detect::Detect(char* dest, int width, int height) {
    open_device(dest);
    imageSize.width = width; 
    imageSize.height = height;

    init_device(width, height);
    start_capturing();
}

Mat Detect::get_face_image() {
    return face_image; 
}

void Detect::set_face_image(Mat face) {
   face_image = face;  
}

Mat Detect::get_eye_image() {
    return eye_image;
}

void Detect::set_eye_image(Mat eye) {
    eye_image = eye; 
}

Mat Detect::get_video_image() {
    return video_image;
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

//TODO: Implement the capture method for TK1 board.
bool Detect::nv_capture_image() {
    Mat input, conversion, demosiac;

    Rect myROI(320, 10, 720, 300);

    input = Mat(imageSize, CV_16UC1, snapFrame());
    waitKey(75);
    input.convertTo(conversion, CV_8UC4, alpha);
    conversion = conversion(myROI); 
    
    demosaicing(conversion, video_image, COLOR_BayerBG2RGB);
    flip(video_image, video_image, 1); 

    if(video_image.empty()) {
        return false;
    } else {
        return true;
    }
}

bool Detect::load_image(String image) {
    video_image = imread(image);
    if(video_image.empty()) {
        cout << "COULD NOT LOAD IMAGE" << endl;
        return false;
    } else {
        return true;
    }
}

bool Detect::findFace(String face_cascade_name) {
    Mat gray_image;
    gray_image = get_red_channel(video_image);
    face_image = cascade_search(face_cascade_name, video_image, gray_image, 150, face_image);

    //check if the matrix is empty or not 
    if(face_image.empty()) {
        return false;
    } else {
        return true; 
    }
}

bool Detect::findEye(String eye_cascade_name) {
    Mat gray_image;
    gray_image = get_red_channel(video_image);
    eye_image = cascade_search(eye_cascade_name, video_image, gray_image, 30, eye_image);

    //check if the matrix is empty or not
    if(eye_image.empty()) {
        return false;
    } else {
        return true;
    }
}

bool Detect::findFeatures(String face_cascade_name, String eye_cascade_name) {
    Mat gray_image;
    gray_image = get_red_channel(video_image);

    //search for face then eye within face region 
    face_image = cascade_search(face_cascade_name, video_image, gray_image, 150, face_image);
    if(face_image.empty()) {
        return false;
    } else {
        eye_image = cascade_search(eye_cascade_name, video_image, face_image, 30, eye_image);
        if(eye_image.empty()) {
            return false;
        } else {
            return true; 
        }
    }
}

void Detect::display_windows() {
    if(!video_image.empty()) {
        imshow(VIDEO_WINDOW_NAME, video_image);
    }
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

Mat cascade_search(String name, Mat video_image, Mat search_image, int size, Mat saved_image) {
    Mat result;
    CascadeClassifier cascade;
    vector<Rect> cascade_vec;

    if(cascade.load(name)) {
        cascade.detectMultiScale(search_image, cascade_vec, 1.1, 2,0|CASCADE_SCALE_IMAGE|CV_HAAR_FIND_BIGGEST_OBJECT, Size(size, size));
        //if feature was found.
        if(!cascade_vec.empty()) {
            result = search_image(Rect(cascade_vec[0].x, cascade_vec[0].y, cascade_vec[0].width, cascade_vec[0].height)).clone();
            rectangle(video_image, cascade_vec[0], CV_RGB(0, 255, 0), 1);
        } else {
            cout << "COULD NOT FIND FEATURE IN THIS FRAME." << endl; 
        }    
    } else {
        cout << "ERROR: could not load feature classifier" << endl;
    }
    return result;
}

Mat get_red_channel(Mat source) {
    vector<Mat> rgb; 
    split(source, rgb);
    return rgb[2];
}
