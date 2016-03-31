#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/objdetect.hpp>

#include <iostream>
#include <cmath>
#include <stdio.h>
#include "v4ldevice.h"

using namespace cv;
using namespace std;


//Global variables 
Mat src, video_src, gray_video_src, otsu_image, threshold_image, dilate_image, edge, blur_image, face_image, eye_image, inv_gray_video, adapt_image;


	Mat image;
	Mat bayer16BitMat;

vector<Mat> rgb;

int main ()
{
	
    Size ImageSize;
    int wKey = -1;

    ImageSize.width = 1280;
    ImageSize.height = 800;
    //Mat c_image(ImageSize, CV_8UC3);
	
    printf("Program started\n");
   // namedWindow("Sample", CV_WINDOW_AUTOSIZE);

    open_device((char*)"/dev/video0");
    init_device(ImageSize.width, ImageSize.height);


    printf("Start capturing\n");

    start_capturing();
	
    while(wKey == -1 )
    {
	bayer16BitMat = Mat(ImageSize, CV_16UC1, snapFrame());
	image = bayer16BitMat.clone();
	image.convertTo(image, CV_16UC4, 1.0625, 10);	
	//Split the RBG Channels
        //split(image, rgb);
        //equalizeHist(rgb[2], rgb[2]);
        //gray_video_src = rgb[2].clone();
        //equalizeHist(gray_video_src, gray_video_src);
        //inv_gray_video = ~gray_video_src.clone();

	// Create a color image from the raw data... not working
        //cvtColor(image,image,CV_YUV2RGB_YUYV);
	/*CV_BayerGB2RGB additional */ 
	//currently greyscale
	imshow("RGB 0", image);
	//imshow("RGB 1", rgb[1]);
	//imshow("RGB 2", rgb[2]);
        wKey = waitKey(10);
    }

    destroyWindow("Sample");
    stop_capturing();
    uninit_device();
    close_device();

    printf("Program ended\n");

    return 0;

}
