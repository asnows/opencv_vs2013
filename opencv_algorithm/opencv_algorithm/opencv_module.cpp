
#include"include.h"



void opencv_module(cv::Mat srcImg, cv::Mat srcImg1)
{
#ifdef SOBEL
	cv::Mat sobel3x3_Img(srcImg.rows, srcImg.cols,CV_8U);
	opencv_sobel3x3(srcImg, sobel3x3_Img);
	cv::imshow("sobel3x3_opencv", sobel3x3_Img);


	cv::imwrite("Opencv_sobel3x3.bmp", sobel3x3_Img);

	//opencv_sobel5x5(srcImg);
	//opencv_sobel7x7(srcImg);
#endif

#ifdef CANNY
	cv::Mat cannyImg;

	Canny(srcImg, cannyImg, 150, 200);
	cv::imshow("cannyOpencv", cannyImg);
	cv::imwrite("opencv_canny.bmp", cannyImg);
#endif
	
	//opencv_laplacian(srcImg);
	//opencv_sobleSharp(srcImg, sobel3x3_Img);
#ifdef SIFT

	//cv::getGaussianKernel(3, 1);
	opencv_sift(srcImg, srcImg1);

#endif


}


