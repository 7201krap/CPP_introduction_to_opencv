#include <opencv2/core.hpp>	
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>	
#include <iostream>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

int main() {
	Mat image; // 입력 이미지를 저장할 Mat 객체인 image 선언.
	image = imread("example_picture.jpg", IMREAD_GRAYSCALE);	// 이미지를 grayscale 로 바꾸어줌 

	if (image.empty()) {
		cout << "Could not open or find the image" << endl;
		return -1;
	}
	// 이미지가 어떻게 프로세싱 되는지 보기 위해서 중간 과정의 image 를 출력
	imshow("original image", image);

	// // 이미지를 보여줄 윈도우를 생성 
	// namedWindow("Original", WND_PROP_FULLSCREEN);
	// setWindowProperty("Original", WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);

	// Canny edge detector 
	Canny(image, image, 50, 150);
	imshow("Canny edge detection", image);
	waitKey(0);

	return 0;

}


