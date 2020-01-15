
#include"include.h"

void opencv_laplacian(cv::Mat srcImg)
{
	cv::Mat laplImg(srcImg.rows, srcImg.cols, CV_8U);
	cv::Mat lap2Img(srcImg.rows, srcImg.cols, CV_8U);

	cv::Mat gaus3x3(srcImg.rows, srcImg.cols, CV_8U);
	cv::Mat gaus5x5(srcImg.rows, srcImg.cols, CV_8U);
	cv::Mat lapl_gaus3x3(srcImg.rows, srcImg.cols, CV_16S);
	cv::Mat lapl_gaus5x5(srcImg.rows, srcImg.cols, CV_16S);

	cv::Mat laplSharp_gaus3x3(srcImg.rows, srcImg.cols, CV_8U);
	cv::Mat laplSharp_gaus5x5(srcImg.rows, srcImg.cols, CV_8U);

	cv::GaussianBlur(srcImg, gaus3x3, cv::Size(3, 3), 0, 0);
	cv::GaussianBlur(srcImg, gaus5x5, cv::Size(5, 5), 0, 0);

	cv::Laplacian(gaus3x3, lapl_gaus3x3, CV_16S, 3);
	cv::Laplacian(gaus5x5, lapl_gaus5x5, CV_16S, 3);



	for (unsigned int y = 1; y < laplSharp_gaus3x3.rows - 1; y++)
	 {
		for (unsigned int x = 1; x < laplSharp_gaus3x3.cols - 1; x++)
		 {
			 

			if (lapl_gaus3x3.at<short int>(y, x) < 0)
			 {
				 laplImg.at<uchar>(y, x) = 0;
			 }
			 else
			 {
				 laplImg.at<uchar>(y, x) = lapl_gaus3x3.at<short int>(y, x);
				 
			 }		 
			
		 }
	 }


	for (unsigned int y = 1; y < laplSharp_gaus3x3.rows - 1; y++)
	{
		for (unsigned int x = 1; x < laplSharp_gaus3x3.cols - 1; x++)
		{


			if (lapl_gaus5x5.at<short int>(y, x) < 0)
			{
				lap2Img.at<uchar>(y, x) = 0;
			}
			else
			{
				lap2Img.at<uchar>(y, x) = lapl_gaus5x5.at<short int>(y, x);
				

			}

		}
	}




	laplSharp_gaus3x3 = srcImg + laplImg;
	laplSharp_gaus5x5 = srcImg + lap2Img;
	

	
	cv::imshow("laplSharp_gaus3x3", laplSharp_gaus3x3);
	cv::imshow("laplSharp_gaus5x5", laplSharp_gaus5x5);

}