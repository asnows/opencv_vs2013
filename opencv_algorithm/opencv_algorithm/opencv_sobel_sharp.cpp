#include"include.h"
void opencv_sobleSharp(cv::Mat srcImg,cv::Mat sobelImg)
{
	cv::Mat sobel_Sharp(srcImg.rows, srcImg.cols, CV_8U);

	sobel_Sharp = srcImg + sobelImg;
	cv::imshow("sobel_Sharp", sobel_Sharp);


}