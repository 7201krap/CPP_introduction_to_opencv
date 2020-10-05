#include <iostream>
#include <opencv2/opencv.hpp>
#include <ctime>

#ifdef _DEBUG 
#pragma comment(lib, "opencv_world440d.lib")
#else
#pragma comment(lib, "opencv_world440.lib")
#endif

using namespace std;
using namespace cv;

void draw_rect(Mat& img, vector<Rect>& v_rect) {
	for (auto it : v_rect) {
		rectangle(img, it, CV_RGB(255, 0, 0), 2);
	}
}
int main() {

	// These are magic values 
	int TH1 = 70;	// 이 변수를 너무 낮게 잡으면 조그마한 변화에도 그것이 intruder 라고 생각한다. // you might need to change this value 
	int TH_WIDTH;
	int TH_HEIGHT;
	int TH_AREA;
	double detection_ratio = 0.02;	// you might need to change this value 
	double detection_area = 0.0001;	// you might need to change this value 
	double alpha = 0.01;
	double beta = 1.0 - alpha;
	// These are magic values 

	// Morphology 를 적용하기 위한 마스크를 만듬 
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5), Point(2, 2));

	Mat frame, frame_binary;
	Mat old_frame, bg_frame_binary;
	Mat absdiff_frame;

	// 웹캠 영상을 가져온다. 
	VideoCapture stream1(0);

	if (!stream1.isOpened()) {
		cout << "cannot open camera 1" << endl;
	}

	namedWindow("frame", 0);
	namedWindow("sub_frame", 0);

	int count = 0;
	int SKIP = 50;

	while (1) {
		if (!(stream1.read(frame))) {
			break;
		}

		if (old_frame.empty()) {
			old_frame = frame.clone();
			// 올드 프레임을 이진화 해준다.
			cvtColor(old_frame, bg_frame_binary, COLOR_BGR2GRAY);
			TH_WIDTH = int(old_frame.cols * detection_ratio); 
			TH_HEIGHT = int(old_frame.rows * detection_ratio);

			TH_AREA = int(old_frame.cols * old_frame.rows * detection_area);
			continue;
		}
		// 프레임을 이진화 해준다.
		cvtColor(frame, frame_binary, COLOR_BGR2GRAY);
		// 영상이 서서히 변할때 (해의 움직임등 자연적인 영향) 그것을 핸들링 해주기 위해 이전영상과 현재영상의 적절한 비율을 통하여 background 를 정해준다.
		addWeighted(frame_binary, alpha, bg_frame_binary, beta, 0.0, bg_frame_binary);

		// 50 프레임동안 배경이 업데이트 된다. 
		count++;
		if (count < SKIP) {
			continue;
		}

		// 이전영상과 현재영상의 차이를 구해서 sub_frame 에 넣는다 
		absdiff(bg_frame_binary, frame_binary, absdiff_frame);
		// 빼기값이 일정한 수준 이상일때만 그것이 intruder detect 되어야 한다. 노이즈 제거가 필요하다 
		threshold(absdiff_frame, absdiff_frame, TH1, 255, THRESH_BINARY);	// 차이값이 75 이상일때만 이진화 시켜라. 70 ~ 255 => 255 (흰색) 
		// morphology OPEN : 침식 -> 팽창 
		morphologyEx(absdiff_frame, absdiff_frame, MORPH_OPEN, element);
		

		// find contour 
		// vector<vector<>> : 선으로 생각하면 쉽다. 1차원 
		// vector<> 면으로 생각하면 쉽다. 2차원 
		vector<vector<Point>> contours;
		vector<Vec4i> hierarchy;
		findContours(absdiff_frame.clone(), contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
		// contours 대신에 사각형을 그려줄거다. 
		// drawContours(frame, contours, -1, CV_RGB(255, 0, 0), 5, 8, hierarchy);

		// Blob labeling 
		vector<Rect> v_rect;
		for (auto it : contours) {
			Rect mr = boundingRect(Mat(it));

			// 사각형의 사이즈가 일정 이상일때만 push_back 하여 사각형을 그린다. 
			/* 1
			if (mr.width > TH_WIDTH || mr.height > TH_HEIGHT) {
				v_rect.push_back(mr);
			}
			*/
			// 사각형의 크기(Area)가 일정 이상일때만 push_back 하여 사각형을 그린다. 
			/* 2 */
			double area = contourArea(it, false);
			if (area > TH_AREA)
				v_rect.push_back(mr);
			
		}
		draw_rect(frame, v_rect);

		// upload intruder image to hardisk 
		if (v_rect.size() > 0) {
			char str[255];
			struct tm now;
			time_t rawtime = time(0);
			localtime_s(&now, &rawtime);

			sprintf_s(str, "%d_%d_%d_%d_%d_%d.jpg", 
				now.tm_year, now.tm_mon, now.tm_mday, now.tm_hour, now.tm_min, now.tm_sec);
			imwrite(str, frame);
		}

		imshow("frame", frame);
		imshow("absdiff_frame", absdiff_frame);

		if (waitKey(5) >= 0) {
			break;
		}
	}

	return 0;

}
//
