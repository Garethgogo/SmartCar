#include "dataprocess.h"

#include <stdio.h>
#include <tchar.h>
#include <opencv2\opencv.hpp>
#include <math.h>
#include <time.h>   
#include <windows.h> 
#include "stdafx.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

#define PI 3.141592653589792
#define ROW_MIN 600
#define ROW_MAX 1000
#define COL_MIN 0
#define COL_MAX 960
#define MIDLINE_LENGTH ROW_MAX - ROW_MIN

vector<int> midLine;    //����
int startLine;			//�����յ���
int nowRoad;			//��ǰ�����ܵ���ɫ�� 
						//  0����ɫ
						//  1����ɫ
						//  2����ɫ

void showVideo();

int main() {

	//showVideo();
	
    return 0;
}

/*
	��������ͷ
*/
void showVideo() {

	VideoCapture capture(1);
	namedWindow("video", 1);

	while (1) {
		Mat frame;
		capture >> frame;
		imshow("video", frame);
		waitKey(30);
	}

}
