#include"../include.h"
void draw_feat(cv::Mat srcImg, cv::Mat srcfeat)
{

	


	for (unsigned int y = 2; y < srcImg.rows - 1; y++)
	{
		for (unsigned int x = 2; x < srcImg.cols - 1; x++)
		{
			if (srcfeat.at<float>(y,x) >0)
			{
				line(srcImg, cvPoint(x - 2, y), cvPoint(x + 2, y), cv::Scalar(255, 255, 255), 1, CV_AA, 0);
				line(srcImg, cvPoint(x, y - 2), cvPoint(x, y + 2), cv::Scalar(255, 255, 255), 1, CV_AA, 0);




			}
		}

	}

	//cv::imshow("draw_feat", dstImg);




}


