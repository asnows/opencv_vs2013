#include"include.h"

//tmpVal = srcImg(x,y) - gaus(x,y)
//dstImg(x,y) = srcImg(x,y) + k*tmpVal
void unsharpMaking(cv::Mat srcImg,cv::Mat gaus,cv::Mat dstImg,uchar k)
{
	short int tmpVal = 0;

	for (unsigned int rows = 0; rows < srcImg.rows; rows++)
	{
		for (unsigned int cols = 0; cols < srcImg.cols;cols++)
		{

			tmpVal = srcImg.at<uchar>(rows, cols) - gaus.at<uchar>(rows, cols);

			tmpVal = k*tmpVal;
			tmpVal = srcImg.at<uchar>(rows, cols) + tmpVal;

			if (tmpVal < 0)
			{
				tmpVal = 0;
			}
			if (tmpVal >255)
			{
				tmpVal = 255;
			}

			dstImg.at<uchar>(rows, cols) = tmpVal;


		}


	}

}