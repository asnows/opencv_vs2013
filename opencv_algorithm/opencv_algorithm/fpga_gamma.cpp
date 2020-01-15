#include"include.h"
void fpga_gamma(cv::Mat srcImg, cv::Mat dstImg, float gamma)
{
	uchar srcVal = 0;
	float f_val = 0;
	uchar dstVal = 0;

	for (unsigned int rows = 0; rows < srcImg.rows;rows++)
	{
		for (unsigned int cols = 0; cols < srcImg.cols;cols++)
		{
			srcVal = srcImg.at<uchar>(rows, cols);

			f_val = powf(srcVal, gamma);

			if (f_val > 255)
			{
				f_val = 255;
			}
			dstImg.at<uchar>(rows, cols) = f_val;

		}
	}


}