// opencv_inflearn04.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <opencv2/opencv.hpp>

#ifdef _DEBUG 
#pragma comment(lib, "opencv_world440d.lib")
#else
#pragma comment(lib, "opencv_world440.lib")
#endif

using namespace std;
using namespace cv;

int main()
{
    namedWindow("image", 0);    // 보여줄 창을 만든다 
    namedWindow("image_sobel_dx", 0);
    namedWindow("image_sobel_dy", 0);
    namedWindow("image_sobel_dx_dy", 0);
    namedWindow("image_fliped", 0);

    Mat img = imread("example.jpg");    // 이미지를 불러온다 
    Mat img_sobel_dx;
    Mat img_sobel_dy;
    Mat img_sobel_dx_dy;
    Mat img_fliped;

    Sobel(img, img_sobel_dx, img.depth(), 1, 0); // 가로로 스캔 
    Sobel(img, img_sobel_dy, img.depth(), 0, 1); // 세로로 스캔 
    Sobel(img_sobel_dx, img_sobel_dx_dy, img.depth(), 0, 1); // 가로 세로 둘다 적용
    flip(img, img_fliped, 1);

    imshow("image", img);        // 원본 
    imshow("image_sobel_dx", img_sobel_dx);  // 창을 만든것에 불러온 img 를 나오게 한다. Sobel edge 적용된것 
    imshow("image_sobel_dy", img_sobel_dy);
    imshow("image_sobel_dx_dy", img_sobel_dx_dy);
    imshow("image_fliped", img_fliped);

    waitKey(0); // 키보드 인풋이 올때까지 영원히 기다린다 

    destroyAllWindows();

    return 0;
}

