#include <opencv2/opencv.hpp>
#include <iostream>

#ifdef _DEBUG 
#pragma comment(lib, "opencv_world440d.lib")
#else
#pragma comment(lib, "opencv_world440.lib")
#endif

// mat simple operation
// + - / * 
// Inverse 
// Transpose 

using namespace std;
using namespace cv;

int main() {
	Mat m0 = Mat::ones(3, 3, CV_64F);
	m0 = m0 + 3;

	Mat m1 = Mat::zeros(3, 3, CV_64F);
	m1 = m1 + 30;

	double dm[3][3] = { {7,2,1},{1,5,1},{1,2,3} };
	Mat m2 = Mat(3, 3, CV_64F, dm); // 생성했던 것을 넣어줌. 넣어줄때 주소를 넣어준다. 
	
	cout << "RESULT" << endl << endl;
	cout << "m0" << endl;
	cout << m0 << endl << endl;

	cout << "m1" << endl;
	cout << m1 << endl << endl;

	cout << "m2" << endl;
	cout << m2 << endl << endl;

	// 유의하여야 할 점은 dm 이랑 m2 가 주소가 같아서, 여기서 m2 에 변화를 주면 dm 에도 그 변화가 그대로 적용된다. 
	m2 = m2 + 10;
	
	cout << "dm" << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << dm[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	cout << "m0 + m1" << endl;
	cout << m0 + m1 << endl << endl;

	// This is matrix multiplication
	cout << "m0 * m1" << endl;
	cout << m0 * m1 << endl << endl;

	// This is element-wise multiplication 
	cout << "m0.mul(m1)" << endl;
	cout << m0.mul(m1) << endl << endl;

	cout << "m0 / m2" << endl;
	cout << m0 / m2 << endl << endl;

	// inverse
	cout << "inv(m2)" << endl;
	cout << m2.inv() << endl << endl;

	// transpose
	cout << "m2.t()" << endl;
	cout << m2.t() << endl << endl;




}