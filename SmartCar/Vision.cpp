#include "Vision.h"
#include "opencv2\opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Vision::Vision(Mat& img)
{
	src = img;
}


Vision::~Vision()
{
}


void Vision::showVision() {

	namedWindow("Source image", 1);
	imshow("Source image", src);
	waitKey(0);

	namedWindow("Binary image", 1);
	imshow("Binary image", bin);
	waitKey(0);

	namedWindow("Raw Midline", 1);
	imshow("Raw Midline", rawMidline);
	waitKey(0);
}


void Vision::bgrBinarization(int b, int g, int r, int allowence) {

	Mat dst(src.rows, src.cols, CV_8UC1, Scalar(0));

	int rows = src.rows;
	for (int row = 0; row < rows; row++) {

		uchar *srcPtr = src.ptr<uchar>(row);
		uchar *dstPtr = dst.ptr<uchar>(row);

		int cols = src.cols;
		for (int col = 0; col < cols; col++) {

			int error = abs(srcPtr[col * 3] - 0 - b)
				+ abs(srcPtr[col * 3 + 1] - 0 - g)
				+ abs(srcPtr[col * 3 + 2] - 0 - r);

			if (error <= allowence) {
				dstPtr[col] = 255;
			}
			else {
				dstPtr[col] = 0;
			}
		}

		bin = dst;
	}
}


void Vision::getRawMidline() {

	int leftPoint, rightPoint;

	Mat dst(bin.rows, bin.cols, CV_8UC1, Scalar(0));
	vector<Point> A;
	vector<Point> B;

	// ��ȥ���
	blur(bin, bin, Size(10, 10));

	int rows = bin.rows;
	for (int row = 0; row < rows; row++) {

		uchar *srcPtr = bin.ptr<uchar>(row);
		uchar *dstPtr = dst.ptr<uchar>(row);

		// �������Ҳ���ɨ��ֱ����⵽��ɫ���������Ե
		int col = 0;
		int cols = bin.cols;
		while (srcPtr[col] == 0 && col < cols - 1)
			col++;

		// ����������û������Ե
		if (col != cols - 1) {

			// ���˵���Ϊ���
			leftPoint = col;

			// ������������ҵ�
			col = cols - 1;
			while (srcPtr[col] == 0 && col > leftPoint)
				col--;

			// ����������㲻���غ�
			if (leftPoint != col) {
				// �õ��ҵ�
				rightPoint = col;
				// �������ͼ�����
				dstPtr[(leftPoint+rightPoint)/2] = 255;
				// �������ݼ�
				A.push_back(Point(row));
				B.push_back(Point(col));
			} else {
				continue;
			}
		}
	}

	rawMidline = dst;
}

