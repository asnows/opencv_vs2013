#include"include.h"

float get_var(cv::Mat srcImg, unsigned int row, unsigned int cols, float aver, uchar k_size)
{
	float tmp1 = 0;
	float value1 = 0;

	for (unsigned int i = 0; i < k_size;i++)
	{
		for (unsigned int j = 0; j < k_size; j++)
		{
			tmp1 = aver - srcImg.at<uchar>(row + i - 1, cols + j - 1);

			value1 += tmp1*tmp1;
		}
	}

	return value1;
}

void localHist(cv::Mat srcImg,cv::Mat dstImg)
{
//	unsigned int local_average = 0;
//	unsigned int glob_aver = 0;
	double glob_aver = 0;
	float glob_variance = 0;
	float glob_tmp = 0;



	float local_aver = 0;
	float local_variance = 0;

	float E = 20;//4
	float k0 = 0.9;
	float k1 = 0.00;//0.02
	float k2 = 0.4;



	//获取全图平均值
	for (unsigned int rows = 0; rows < srcImg.rows;rows++)
	{

		for (unsigned int cols = 0; cols<srcImg.cols; cols++)
		{
			
			glob_aver += srcImg.at<uchar>(rows, cols);
		

		}
	}


	glob_aver /= srcImg.rows*srcImg.cols;




	//获取全图方差
	for (unsigned int rows = 0; rows < srcImg.rows;rows++)
	{
		for (unsigned int cols = 0; cols < srcImg.cols;cols++)
		{
			glob_tmp = glob_aver - srcImg.at<uchar>(rows, cols);

			glob_variance += glob_tmp * glob_tmp;

		}
	}

	glob_variance /= srcImg.rows*srcImg.cols;

	printf("glob_variance1 = %f \r\n", glob_variance);






	//增强处理
	
	for (unsigned int rows = 1; rows < srcImg.rows - 1;rows++)
	{
		for (unsigned int cols = 1; cols < srcImg.cols - 1; cols++)
		{
			//获取局部平均值
			local_aver = srcImg.at<uchar>(rows - 1, cols - 1) + srcImg.at<uchar>(rows - 1, cols) + srcImg.at<uchar>(rows - 1, cols + 1)
				+ srcImg.at<uchar>(rows, cols - 1) + srcImg.at<uchar>(rows, cols) + srcImg.at<uchar>(rows, cols + 1)
				+ srcImg.at<uchar>(rows + 1, cols - 1) + srcImg.at<uchar>(rows + 1, cols) + srcImg.at<uchar>(rows + 1, cols + 1);

			local_aver /= 9;
			//获取局部方差	
			local_variance = get_var(srcImg, rows, cols, local_aver, 3);

			if ((local_aver <= k0*glob_aver) && (((k1*glob_variance) <= local_variance)) && (local_variance <= (k2*glob_variance)))
			{
				dstImg.at<uchar>(rows, cols) = E*srcImg.at<uchar>(rows, cols);
			}
			else
			{
				dstImg.at<uchar>(rows, cols) = srcImg.at<uchar>(rows, cols);
			}
		}
	}

}

//针对FPGA处理做的优化
void localHist2(cv::Mat srcImg, cv::Mat dstImg)
{

	double glob_aver = 0;
	double glob_variance = 0;
	float  glob_tmp = 0;
	double glob_A = 0;
	double glob_B = 0;
	float tmp_val = 0;


	float local_aver = 0;
	float local_variance = 0;

	float E = 20;//4
	float k0 = 0.4;
	float k1 = 0.00;//0.02
	float k2 = 0.4;

	//获取全图平均值
	for (unsigned int rows = 0; rows < srcImg.rows; rows++)
	{

		for (unsigned int cols = 0; cols<srcImg.cols; cols++)
		{

			tmp_val = srcImg.at<uchar>(rows, cols);

			//glob_aver += srcImg.at<uchar>(rows, cols);
			//glob_A += srcImg.at<uchar>(rows, cols) * srcImg.at<uchar>(rows, cols);
			glob_aver += tmp_val;
			glob_A += tmp_val * tmp_val;
			if (tmp_val != 255)
			{
			
			 //printf("srcImg = %d \r\n", srcImg.at<uchar>(rows, cols));
			 //printf("glob_A = %f \r\n", glob_A);

			}
		}
	}
	printf("glob_aver1 = %f \r\n", glob_aver);
	glob_B = glob_aver;
	glob_aver /= srcImg.rows*srcImg.cols;



	/*
	//获取全图方差
	for (unsigned int rows = 0; rows < srcImg.rows; rows++)
	{
		for (unsigned int cols = 0; cols < srcImg.cols; cols++)
		{
			glob_tmp = glob_aver - srcImg.at<uchar>(rows, cols);

			glob_variance += glob_tmp * glob_tmp;

		}
	}

	glob_variance /= srcImg.rows*srcImg.cols;

	printf("glob_variance1 = %f \r\n", glob_variance);

	*/

	//glob_variance = glob_A - 2 * glob_B*glob_aver + srcImg.rows*srcImg.cols*glob_aver*glob_aver;
	glob_variance = glob_A / (srcImg.rows*srcImg.cols) - glob_aver*glob_aver;

	printf("glob_A = %f \r\n", glob_A);
	printf("glob_B = %f \r\n", glob_B);
	printf("glob_aver = %f \r\n", glob_aver);
	printf("glob_variance2 = %f \r\n", glob_variance);





	//增强处理

	for (unsigned int rows = 1; rows < srcImg.rows - 1; rows++)
	{
		for (unsigned int cols = 1; cols < srcImg.cols - 1; cols++)
		{
			//获取局部平均值
			local_aver = srcImg.at<uchar>(rows - 1, cols - 1) + srcImg.at<uchar>(rows - 1, cols) + srcImg.at<uchar>(rows - 1, cols + 1)
				+ srcImg.at<uchar>(rows, cols - 1) + srcImg.at<uchar>(rows, cols) + srcImg.at<uchar>(rows, cols + 1)
				+ srcImg.at<uchar>(rows + 1, cols - 1) + srcImg.at<uchar>(rows + 1, cols) + srcImg.at<uchar>(rows + 1, cols + 1);

			local_aver /= 9;
			//获取局部方差	
			local_variance = get_var(srcImg, rows, cols, local_aver, 3);

			if ((local_aver <= k0*glob_aver) && (((k1*glob_variance) <= local_variance)) && (local_variance <= (k2*glob_variance)))
			{
				dstImg.at<uchar>(rows, cols) = E*srcImg.at<uchar>(rows, cols);
			}
			else
			{
				dstImg.at<uchar>(rows, cols) = srcImg.at<uchar>(rows, cols);
			}
		}
	}

}