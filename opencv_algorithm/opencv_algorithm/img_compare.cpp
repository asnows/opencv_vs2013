#include"include.h"
void img_compare(cv::Mat srcImg1,cv::Mat srcImg2)
{
	unsigned int diff_counts = 0;
	for (unsigned int rows = 0; rows < srcImg1.rows;rows++)
	{
		for (unsigned int cols = 0; cols < srcImg1.cols;cols++)
		{
			if (srcImg1.at<uchar>(rows,cols) != srcImg2.at<uchar>(rows,cols))
			{
				diff_counts++;
				//printf("(%d,%d) \r\n", rows, cols);
			}
		}
	}

	printf("diff_counts = %d,percent = %d\r\n", diff_counts, (diff_counts*100) / (srcImg1.rows*srcImg1.cols));


}