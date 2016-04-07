#include "pupilLoc.hpp"

using namespace cv; 
using namespace std;

int histoPeak(Mat image);

PupilLoc::PupilLoc(Mat eye_image) {
    histoPeakIndex = 0;
    close_size = 6;
    open_size = 3;
    
    open_element = getStructuringElement(2, Size(2 * close_size + 1, 2 * close_size +1), Point(close_size, close_size));
    close_element = getStructuringElement(2, Size(2 * open_size + 1, 2 * open_size +1), Point(open_size, open_size));

    ref_image = eye_image.clone();

    namedWindow(EYE_RESULT_NAME, CV_WINDOW_NORMAL);
    moveWindow(EYE_RESULT_NAME, 1350, 600);
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

//Removes illumination variation from eye image 
void PupilLoc::removeLight() {
    Mat light, divided_image, temp, contrast; 

    //removes noise from the image 
    bilateralFilter(ref_image, temp, 15, 75, 75);
    imshow("NOISE REDUCTION", temp);
    //captures the illumination variation of the image using a large kernal and LPF
    blur(temp, light, Size(315, 315));
    divide(temp, light, divided_image, 1, -1); 
    histoPeakIndex = histoPeak(temp);
    illuminationRM = divided_image.mul(255);
    equalizeHist(illuminationRM, illuminationRM);

    //erode the image to stop the blobs from merging 
    int erode_size = 3;
    Mat erode_element = getStructuringElement(2, Size(2 * erode_size + 1, 2 * erode_size +1), Point(erode_size, erode_size));
    erode( illuminationRM, illuminationRM, erode_element );
}

//Tries isolating the pupil from the eye image. 
void PupilLoc::isoPupil() {
    //Take the inverse of the image 
    Mat inv_ill = ~illuminationRM; 

    //Using OTSU method for thresholding 
    threshold(inv_ill, postProc, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);

    //Filters image to lower the number of edges in the image 
    medianBlur(postProc, result_image, 7);

    //Morphological operations for isolating the pupil 
    morphologyEx(result_image, result_image, MORPH_OPEN, open_element);
    //imshow("AFTER OPEN", result_image);
    morphologyEx(result_image, result_image, MORPH_CLOSE, open_element);
    //imshow("AFTER CLOSE", result_image);
}

//Responsible for Blob Detection and showing the blob to the user 
void PupilLoc::highlightPupil() {
    vector< vector<Point> > contours; 
    vector<Vec4i> hierarchy; 
    vector<Vec3f> circles;
    fstream file;
    int largest_area = 0;
    int largest_contour_index = 0; 
    Rect bounding_rect;

    findContours(result_image.clone(),  contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);

    //go through every contour 
    for(int i=0; i<contours.size(); i++) {
        double area = contourArea(contours[i], false);
        //keep reference to the largest contour in the image 
        if(area > largest_area) {
            largest_area = area;
            largest_contour_index = i; 
            //Rectangle for the largest blob
            bounding_rect = boundingRect(contours[i]); 
        }
    }

    drawContours(ref_image, contours, largest_contour_index, Scalar(255), CV_FILLED, 8, hierarchy); 

    //Draw a circle and pinpoint where the center of the blob is 
    int radius = bounding_rect.width/2;
    circle(ref_image, Point(bounding_rect.x+radius, bounding_rect.y+radius), radius, CV_RGB(255,0,0),2);
    cout << "POINTS: Y= " << bounding_rect.y+radius << " X= " << bounding_rect.x+radius << endl;
    
    //TODO: Move gaze communication to queue instead of file
    file.open("coordinates.txt", fstream::out | fstream::trunc);
    file << bounding_rect.y+radius << " " << bounding_rect.x+radius << endl;
    file.close();
}

void PupilLoc::display_windows() {
    if(!ref_image.empty()) {
        imshow(EYE_RESULT_NAME, ref_image);
    }

    if(!result_image.empty()) {
        imshow(POST_PROCESSES_NAME, result_image);
    }
}

void PupilLoc::destory_windows() {
    destroyWindow(EYE_RESULT_NAME);
    destroyWindow(POST_PROCESSES_NAME);
}

//find the highest peak in the histogram
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
    }
    return index;
}
