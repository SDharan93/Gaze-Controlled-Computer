#include "pupilLoc.hpp"

using namespace cv; 
using namespace std;

int histoPeak(Mat image);

PupilLoc::PupilLoc(Mat eye_image) {
    histoPeakIndex = 0;
    close_size = 3;
    open_size = 6;
    
    open_element = getStructuringElement(2, Size(2 * close_size + 1, 2 * close_size +1), Point(close_size, close_size));
    close_element = getStructuringElement(2, Size(2 * open_size + 1, 2 * open_size +1), Point(open_size, open_size));

    ref_image = eye_image.clone();
}

Mat PupilLoc::get_ref_image() {
    return ref_image;
}

Mat PupilLoc::get_illuminationRM() {
    return illuminationRM;
}

int PupilLoc::get_histoPeakIndex() {
    return histoPeakIndex;
}

Mat PupilLoc::get_result_image() {
    return result_image;
}

Mat PupilLoc::get_postProc() {
    return postProc;
}

void PupilLoc::removeLight() {
    Mat light, divided_image; 

    //GaussianBlur(ref_image, ref_image, Size(3,3), 2, 2);
    blur(ref_image, light, Size(201, 201));
    imshow("LIGHT WINDOW", light);
    divide(ref_image, light, divided_image, 1, -1); 
    histoPeakIndex = histoPeak(ref_image);
    cout << "peak in histo: " << histoPeakIndex << endl;
    illuminationRM = divided_image.mul(histoPeakIndex);
    equalizeHist(illuminationRM, illuminationRM);
}

void PupilLoc::isoPupil() {
    Mat inv_ill = ~illuminationRM; 
    adaptiveThreshold(inv_ill, postProc, 255, ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 15, -5);
    medianBlur(postProc, result_image, 7);
    //morphologyEx(result_image, result_image, MORPH_OPEN, open_element);
    morphologyEx(result_image, result_image, MORPH_CLOSE, open_element);
}

void PupilLoc::highlightPupil() {
    vector< vector<Point> > contours; 
    vector<Vec4i> hierarchy; 
    vector<Vec3f> circles;

    findContours(result_image.clone(), contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0,0));

    //go through every contour 
    for(int i=0; i<contours.size(); i++) {
        double area = contourArea(contours[i]);
        Rect rect = boundingRect(contours[i]);
        int radius = rect.width/2;

        //search if any contour is circular. 
        if(area >=30 && abs(1 - ((double)rect.width / (double)rect.height)) <= 0.2 && abs( 1 - (area/(CV_PI * pow(radius,2)))) <= 0.2) {
    circle(ref_image, Point(rect.x+radius, rect.y+radius), radius, CV_RGB(255,0,0),2);
        }
    }

    HoughCircles(result_image, circles, HOUGH_GRADIENT, 1, 10, 100, 30, 1, 70);
    for(size_t i = 0; i< circles.size(); i++) {
        Vec3i c = circles[i];
        circle(ref_image, Point(c[0], c[1]), c[2], Scalar(0,0,255), 3, LINE_AA);
        circle(ref_image, Point(c[0], c[1]), 2, Scalar(0,255,0), 3, LINE_AA);
    }
}

void PupilLoc::display_windows() {
    if(!ref_image.empty()) {
        imshow(EYE_RESULT_NAME, ref_image);
    }

    if(!result_image.empty()) {
        imshow(POST_PROCESSES_NAME, result_image);
    }

    if(!illuminationRM.empty()) {
        imshow(LIGHT_REMOVAL_NAME, illuminationRM);
    }
}

void PupilLoc::destory_windows() {
    destroyWindow(EYE_RESULT_NAME);
    destroyWindow(POST_PROCESSES_NAME);
}

int histoPeak(Mat image) {
    int histSize = 256; 
    float range[] = {0, 255};
    const float *ranges[] = {range};

    MatND hist; 
    calcHist(&image, 1, 0, Mat(), hist, 1, &histSize, ranges, true, false);
    
    double total; 
    float highest = 0; 
    int index = 0; 
    total = image.rows * image.cols; 
    for(int i = 0; i < histSize; i++) {
        float binVal = hist.at<float>(i);
        if(binVal > highest) {
            highest = binVal; 
            index = i;
        }
        cout << "index: " << index << " value: " << binVal << endl;
    }
    return index;
}