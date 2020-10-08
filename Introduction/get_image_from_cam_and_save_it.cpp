// ���� ĸ�Ŀ� ���� 
#include <opencv2/opencv.hpp>
#include <iostream>

#ifdef _DEBUG 
#pragma comment(lib, "opencv_world440d.lib")
#else
#pragma comment(lib, "opencv_world440.lib")
#endif

using namespace cv;
using namespace std;

int main()
{
    // Open the default video camera
    VideoCapture cap(0);

    // if not success, exit program
    if (cap.isOpened() == false)
    {
        cout << "Cannot open the video camera" << endl;
        return -1;
    }

    // ���⼭ int ������ casting �� ���ش�.
    // Ȥ�ó� cap.get(CAP_PROP_FRAME_WIDTH) �̰� int���� �ƴҼ��� �����ϱ� 
    int frame_width = static_cast<int>(cap.get(CAP_PROP_FRAME_WIDTH)); //get the width of frames of the video
    int frame_height = static_cast<int>(cap.get(CAP_PROP_FRAME_HEIGHT)); //get the height of frames of the video

    // ������ ����� �����ְ� 
    Size frame_size(frame_width, frame_height);
    // fps == 10 �̶�� �Ŵ� �ʸ��� 10���� ������ ��ڴٴ� ���̴�. 
    int frames_per_second = 10;

    //Create and initialize the VideoWriter object 
    // �̰Ŵ� �׳� ������ �̷��� ���ָ� �ȴ�. 
    VideoWriter oVideoWriter("MyVideo.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'),
        frames_per_second, frame_size, true);

    //If the VideoWriter object is not initialized successfully, exit the program
    if (oVideoWriter.isOpened() == false)
    {
        cout << "Cannot save the video to a file" << endl;
        return -1;
    }

    string window_name = "My Camera Feed";
    namedWindow(window_name); //create a window called "My Camera Feed"

    while (true)
    {
        Mat frame;

        //Breaking the while loop if frames cannot be read from the camera
        if (cap.read(frame) == false)
        {
            cout << "Video camera is disconnected" << endl;
            break;
        }

        // contrast
        frame.convertTo(frame, -1, 2, 0); //increase the contrast by 4

        // blurring 
        // GaussianBlur(frame, frame, Size(9, 9), 1.0);
        //write the video frame to the file
        oVideoWriter.write(frame);

        //show the frame in the created window
        imshow(window_name, frame);

        if (waitKey(10) == 27)
        {
            cout << "Esc key is pressed by the user. Stopping the video" << endl;
            break;
        }
    }

    //Flush and close the video file
    oVideoWriter.release();

    return 0;
}