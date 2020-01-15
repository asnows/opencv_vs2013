
#include"../include.h"
void remove_edgeByHessian(cv::Mat srcImg,int r,int c, int curv_thr, cv::Mat dstImg)
{
	float  v, dxx, dyy, dxy, tr, det;
	int counts = 0;


	//for (int r = 2; r < srcImg.rows - 1; r++)
	{
		//for (int c = 2; c < srcImg.cols - 1; c++)
		{
			v = srcImg.at<float>(r, c);

			dxx = srcImg.at<float>(r, c + 1)
				+ srcImg.at<float>(r, c - 1)
				- 2 * v;

			dyy = srcImg.at<float>(r + 1, c)
				+ srcImg.at<float>(r - 1, c)
				- 2 * v;

			dxy = (srcImg.at<float>(r + 1, c + 1)
				- srcImg.at<float>(r + 1, c - 1)
				- srcImg.at<float>(r - 1, c + 1)
				+ srcImg.at<float>(r - 1, c - 1)) / 4.0;

			tr = dxx + dyy;
			det = dxx * dyy - dxy * dxy;

			if (det <= 0)
			{
				dstImg.at<float>(r, c) = 0;
			}
			if (tr * tr / det < (curv_thr + 1.0)*(curv_thr + 1.0) / curv_thr)
			{
				dstImg.at<float>(r, c) = 255;
				counts++;
			}
			else
			{
				dstImg.at<float>(r, c) = 0;
			}


		}
	}

	


}