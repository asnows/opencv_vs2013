#include"include.h"



void opencv_sobel3x3(cv::Mat srcImg, cv::Mat dstImg )
{
	cv::Mat sobel_x(srcImg.rows, srcImg.cols, CV_8U);
	cv::Mat sobel_y(srcImg.rows, srcImg.cols, CV_8U);
	cv::Mat sobel_3x3(srcImg.rows, srcImg.cols, CV_8U);

	cv::Sobel(srcImg, sobel_x, CV_8U, 1, 0, 3, 1, 0, BORDER_DEFAULT);
	cv::Sobel(srcImg, sobel_y, CV_8U, 0, 1, 3, 1, 0, BORDER_DEFAULT);
	cv::addWeighted(sobel_x, 1, sobel_y, 1, 1, dstImg);

}


void opencv_sobel5x5(cv::Mat srcImg)
{

	cv::Mat sobel_x(srcImg.rows, srcImg.cols, CV_8U);
	cv::Mat sobel_y(srcImg.rows, srcImg.cols, CV_8U);
	cv::Mat sobel_5x5(srcImg.rows, srcImg.cols, CV_8U);

	cv::Sobel(srcImg, sobel_x, CV_8U, 1, 0, 5, 1, 0, BORDER_DEFAULT);
	cv::Sobel(srcImg, sobel_y, CV_8U, 0, 1, 5, 1, 0, BORDER_DEFAULT);
	cv::addWeighted(sobel_x, 1, sobel_y, 1, 1, sobel_5x5);
	cv::imshow("sobel_5x5_opencv", sobel_5x5);


}


void opencv_sobel7x7(cv::Mat srcImg)
{

	cv::Mat sobel_x(srcImg.rows, srcImg.cols, CV_8U);
	cv::Mat sobel_y(srcImg.rows, srcImg.cols, CV_8U);
	cv::Mat sobel_7x7(srcImg.rows, srcImg.cols, CV_8U);

	cv::Sobel(srcImg, sobel_x, CV_8U, 1, 0, 7, 1, 0, BORDER_DEFAULT);
	cv::Sobel(srcImg, sobel_y, CV_8U, 0, 1, 7, 1, 0, BORDER_DEFAULT);
	cv::addWeighted(sobel_x, 1, sobel_y, 1, 1, sobel_7x7);
	cv::imshow("sobel_7x7_opencv", sobel_7x7);


}

