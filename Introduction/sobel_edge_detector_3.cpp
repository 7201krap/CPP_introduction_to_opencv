// opencv_inflearn05.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
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

int main() {
 
	Mat A, C;

	A = imread("example.jpg", IMREAD_COLOR);

	C = A;
	// 여기서 C 에 대해서 Sobel processing 하면 A 도 영향을 받아서 A 자체가 변한다.

	// 이미지 변경 예시 
	Mat D = A(Rect(100, 100, 100, 100));
	Mat E = A(Range::all(), Range(1, 500));	// row, column 

	// 이렇게 하면 F 나 G 에 변경을 가해도 A 자체는 변하지 않는다. 
	Mat F = A.clone();
	Mat G;
	A.copyTo(G);

	// sobel processing to G --> A 의 이미지는 바뀌지 않는다. 
	Sobel(G, G, A.depth(), 1, 0);

	imshow("example image C", C);
	imshow("example image D", D);
	//imshow("example image E", E);
	imshow("example image F", F);
	imshow("example image G", G);
	imshow("example image A", A);


	waitKey(0);
}
