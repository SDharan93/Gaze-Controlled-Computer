#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>

#include <iostream>
#include <cmath>

using namespace std;
using namespace cv; 

int main(int argc, char** argv) {
    string sourceName = "eye.jpg";
    string sourceDisplay = "Source image";
    
    Mat src = imread(sourceName);
    //If the source image could not load...
    if(!src.data) {
       cout << "ERROR: could not load: " << sourceName << endl; 
       return -1;
    }

    namedWindow(sourceDisplay, CV_WINDOW_AUTOSIZE);
    imshow(sourceDisplay, src);
    cout << "Press any key to exit" << endl;
    
    waitKey(0);

    return 0;
}
