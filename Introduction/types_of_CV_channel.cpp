// Open CV Mat 
// Image, values 는 다 matrix 형태로 표현할 수 있다.

#include <opencv2/opencv.hpp>
#include <iostream>

#ifdef _DEBUG 
#pragma comment(lib, "opencv_world440d.lib")
#else
#pragma comment(lib, "opencv_world440.lib")
#endif

using namespace cv;
using namespace std;

int main() {
	// CV_8UC1 == gray scale == uchar 
	// CV_<bit-depth>{U|S|F}C(<number_of_channels>)
	// CV_8U - 8 - bit unsigned integers(0..255)
	// CV_8S - 8 - bit signed integers(-128..127)
	// CV_16U - 16 - bit unsigned integers(0..65535)
	// CV_16S - 16 - bit signed integers(-32768..32767)
	// CV_32S - 32 - bit signed integers(-2147483648..2147483647)
	// CV_32F - 32 - bit floating - point numbers(-FLT_MAX..FLT_MAX, INF, NAN)
	// CV_64F - 64 - bit floating - point numbers(-DBL_MAX..DBL_MAX, INF, NAN)

	Mat mtx(3, 3, CV_32F);	// make a 3 x 3 floating point matrix
	mtx.setTo(10);

	Mat cmtx(10, 1, CV_64FC2);	// 2-channels
	cmtx.setTo(128);

	Mat img(Size(500, 300), CV_8UC3);	// make a 3-channels (color) image 
	img.setTo(125);

	// section 02 - at
	for (int i = 0; i < img.rows; i++) {
		for (int j = 0; j < img.cols; j++) {
			// Vec3b means 'unsigned char 3 channels'
			// Vec3b : 사진에 맞는 타입을 써줘야 한다.
			img.at<Vec3b>(i, j)[0] = i;
			img.at<Vec3b>(i, j)[1] = j;
			img.at<Vec3b>(i, j)[2] = i + j;
		}
	}

	Mat mtx2;
	mtx2 = Mat(3, 3, CV_32F);

	Mat cmtx2;
	cmtx2 = Mat(10, 1, CV_64FC1);
	cmtx2.setTo(255);

	// create a pointer 
	Mat* mtx3 = new Mat(3, 3, CV_32F);	// mtx3 에는 주소가 담기고, *mtx3 에는 저 객체가 담기게 된다. 
	delete mtx3;

	// value set and print 
	
	cout << "mtx" << endl;
	cout << mtx << endl << endl;	// 인스턴스 자체를 출력 

	cout << "mtx2" << endl;
	cout << mtx2 << endl << endl;	// 인스턴스 자체를 출력 

	// 이거는 채널이 두개라서 (10,1) 행렬이 두개가 출력 된다. 
	cout << "cmtx" << endl;
	cout << cmtx << endl << endl;	// 인스턴스 자체를 출력 

	cout << "cmtx2" << endl;
	cout << cmtx2 << endl;	// 인스턴스 자체를 출력 

	cout << "img" << endl;
	imshow("img", img);

	waitKey(0);

	return 0;
	 
}