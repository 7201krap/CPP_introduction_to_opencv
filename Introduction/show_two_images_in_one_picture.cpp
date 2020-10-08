#include <iostream>
#include <opencv2/opencv.hpp>

#ifdef _DEBUG 
#pragma comment(lib, "opencv_world440d.lib")
#else
#pragma comment(lib, "opencv_world440.lib")
#endif

using namespace std;
using namespace cv;

int main() {
	Mat img = imread("example_picture.jpg");
	Mat img_cloned_reversed = img.clone();

	// bitwise_not 처리를 해주면 이미지가 반전 된다. 
	bitwise_not(img_cloned_reversed, img_cloned_reversed);

	// image2를 처음에 생성할때 사이즈를 조정한다.
	// image2에다가 왼쪽에는 original 오른쪽에는 bitwised_not 연산 된것을 그릴 것이다.
	Mat image2(Size(img.cols * 2, img.rows), img.type());	// colum row 
	image2.setTo(255);	// 이미지를 흰색으로 초기화.

	img.copyTo(image2(Range::all(), Range(0, img.cols)));	// row column
	img_cloned_reversed.copyTo(image2(Range::all(), Range(img.cols, img.cols * 2))); // row column

	imshow("Two photos", image2);

	waitKey(0);

}

