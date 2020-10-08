#include <iostream>
#include <opencv2/opencv.hpp>
#include <stdio.h>

#ifdef _DEBUG  
#pragma comment(lib, "opencv_world440d.lib")
#else
#pragma comment(lib, "opencv_world440.lib")
#endif 
using namespace cv;
using namespace std;
int main()
{
    VideoCapture stream1(0); // 0 is the id of video device.0 if you have only one camera
    if (!stream1.isOpened()) { // check if video device has been initialised
        cout << "cannot open camera";
    }

    //unconditional loop
    while (true) {
        Mat cameraFrame;
        stream1.read(cameraFrame); // get one frame form video
        imshow("Origin", cameraFrame);

        Mat sobel_frame_x = cameraFrame.clone();
        Mat sobel_frame_y = cameraFrame.clone();

        Sobel(sobel_frame_x, sobel_frame_x, CV_8U, 1, 0); // sobel processing: dx 방향 
        Sobel(sobel_frame_y, sobel_frame_y, CV_8U, 0, 1); // sobel processing: dy 방향 
        imshow("Processing_x", sobel_frame_x);
        imshow("Processing_y", sobel_frame_y);

        if (waitKey(30) >= 0)
            break;
    }

    destroyAllWindows();
    return 0;
}