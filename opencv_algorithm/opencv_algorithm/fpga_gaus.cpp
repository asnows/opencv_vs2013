#include"include.h"
void fpga_gaus3x3(cv::Mat srcImg,cv::Mat dstImg)
{

	unsigned int kernel[3][3] = { { 1, 2, 1 },{ 2, 4, 2 },{ 1, 2, 1 } };

	unsigned int rows = srcImg.rows;
	unsigned int cols = srcImg.cols;
	unsigned int tmpVal = 0;

	
	/*
	for (uchar i = 0; i < 3; i++)
	{
		for (uchar j = 0; j < 3; j++)
		{
			printf("kernel[%d][%d] = %d ,", i, j, kernel[i][j]);
		}
		printf("\r\n");
	}
	*/

	for (unsigned int y = 1; y < rows - 1;y++)
	{
		for (unsigned int x = 1; x < cols - 1;x++ )
		{
			tmpVal = srcImg.at<uchar>(y - 1, x - 1)*kernel[0][0] + srcImg.at<uchar>(y - 1, x)*kernel[0][1] + srcImg.at<uchar>(y - 1, x + 1)*kernel[0][2]
				+ srcImg.at<uchar>(y, x - 1)*kernel[1][0] + srcImg.at<uchar>(y, x)*kernel[1][1] + srcImg.at<uchar>(y, x + 1)*kernel[1][2]
				+ srcImg.at<uchar>(y + 1, x - 1)*kernel[2][0] + srcImg.at<uchar>(y + 1, x)*kernel[2][1] + srcImg.at<uchar>(y + 1, x + 1)*kernel[2][2];
			tmpVal >>= 4;// 1/16

			dstImg.at<uchar>(y, x) = tmpVal;

		}
	}



}

void fpga_gaus5x5(cv::Mat srcImg,cv::Mat dstImg)
{
	unsigned int kernel[5][5] = { { 1, 2, 3, 2, 1 }, { 2, 5, 6, 5, 2, }, { 3, 6, 8, 6, 3, }, { 2, 5, 6, 5, 2, }, { 1, 2, 3, 2, 1 } };

	unsigned int tmpVal = 0;

	for (unsigned int rows = 2; rows < srcImg.rows - 2;rows++)
	{
		for (unsigned int cols = 2; cols < srcImg.cols -2;cols++)
		{

			tmpVal = srcImg.at<uchar>(rows - 2, cols - 2)*kernel[0][0] + srcImg.at<uchar>(rows - 2, cols - 1)*kernel[0][1] + srcImg.at<uchar>(rows - 2, cols)*kernel[0][2] + srcImg.at<uchar>(rows - 2, cols + 1)*kernel[0][3] + srcImg.at<uchar>(rows - 2, cols + 2)*kernel[0][4] +
				srcImg.at<uchar>(rows - 1, cols - 2)*kernel[1][0] + srcImg.at<uchar>(rows - 1, cols - 1)*kernel[1][1] + srcImg.at<uchar>(rows - 1, cols)*kernel[1][2] + srcImg.at<uchar>(rows - 1, cols + 1)*kernel[1][3] + srcImg.at<uchar>(rows - 1, cols + 2)*kernel[1][4] +
				srcImg.at<uchar>(rows, cols - 2)*kernel[2][0] + srcImg.at<uchar>(rows, cols - 1)*kernel[2][1] + srcImg.at<uchar>(rows, cols)*kernel[2][2] + srcImg.at<uchar>(rows, cols + 1)*kernel[2][3] + srcImg.at<uchar>(rows, cols + 2)*kernel[2][4] +
				srcImg.at<uchar>(rows + 1, cols - 2)*kernel[3][0] + srcImg.at<uchar>(rows + 1, cols - 1)*kernel[3][1] + srcImg.at<uchar>(rows + 1, cols)*kernel[3][2] + srcImg.at<uchar>(rows + 1, cols + 1)*kernel[3][3] + srcImg.at<uchar>(rows + 1, cols + 2)*kernel[3][4] +
				srcImg.at<uchar>(rows + 2, cols - 2)*kernel[4][0] + srcImg.at<uchar>(rows + 2, cols - 1)*kernel[4][1] + srcImg.at<uchar>(rows+ 2, cols)*kernel[4][2] + srcImg.at<uchar>(rows + 2, cols + 1)*kernel[4][3] + srcImg.at<uchar>(rows + 2, cols + 2)*kernel[4][4];

			tmpVal = tmpVal / 84;
			dstImg.at<uchar>(rows, cols) = tmpVal;



		}
	}






}