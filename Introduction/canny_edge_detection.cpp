#include <opencv2/core.hpp>	
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>	
#include <iostream>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

int main() {
	Mat image; // �Է� �̹����� ������ Mat ��ü�� image ����.
	image = imread("example_picture.jpg", IMREAD_GRAYSCALE);	// �̹����� grayscale �� �ٲپ��� 

	if (image.empty()) {
		cout << "Could not open or find the image" << endl;
		return -1;
	}
	// �̹����� ��� ���μ��� �Ǵ��� ���� ���ؼ� �߰� ������ image �� ���
	imshow("original image", image);

	// // �̹����� ������ �����츦 ���� 
	// namedWindow("Original", WND_PROP_FULLSCREEN);
	// setWindowProperty("Original", WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);

	// Canny edge detector 
	Canny(image, image, 50, 150);
	imshow("Canny edge detection", image);
	waitKey(0);

	return 0;

}


