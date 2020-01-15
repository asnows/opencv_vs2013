#include"include.h"
void laplacian_sharp(cv::Mat srcImg, cv::Mat dstImg)
{

	int lalp_delt1;
	int lalp_delt2;
	int value;

	cv::Mat tmpImg(srcImg.rows,srcImg.cols,CV_8U);


	unsigned int rows = srcImg.rows;
	unsigned int cols = srcImg.cols;



	for (int y = 1; y < rows - 1; y++)
	{

		for (int x = 1; x < cols - 1; x++)
		{

			lalp_delt1 = srcImg.at<unsigned char>(y - 1, x - 1) + srcImg.at<unsigned char>(y - 1, x) + srcImg.at<unsigned char>(y - 1, x + 1)
				+ srcImg.at<unsigned char>(y, x - 1) + srcImg.at<unsigned char>(y, x + 1)
				+ srcImg.at<unsigned char>(y + 1, x - 1) + srcImg.at<unsigned char>(y + 1, x) + srcImg.at<unsigned char>(y + 1, x + 1);

			
			lalp_delt2 = 8 * srcImg.at<unsigned char>(y, x) - lalp_delt1;

			if (lalp_delt2 < 0)
			{
				lalp_delt2 = 0;
			}

			lalp_delt2 = srcImg.at<unsigned char>(y, x) + lalp_delt2;

			if (lalp_delt2 > 255)
			{
				lalp_delt2 = 255;
			}

			dstImg.at<unsigned char>(y, x) = lalp_delt2;
		


		}


	}


}