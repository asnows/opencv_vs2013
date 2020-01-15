#include"../include.h"
void find_extrPoint(cv::Mat srcImg0, cv::Mat srcImg1, cv::Mat srcImg2, cv::Mat dstImg, cv::Mat dstImg2)
{
	unsigned int MaxCount = 0;
	unsigned int minCount = 0;
	unsigned int limCount = 0;
	unsigned int limCount2 = 0;


	for (unsigned int y = 2; y < srcImg0.rows - 1; y++)
	{
		for (unsigned int x = 2; x < srcImg0.cols - 1; x++)
		{
			if (abs(srcImg1.at<float>(y, x)) <= 0.0067)
			{

				dstImg.at<float>(y, x) = 0;
				limCount++;
			}
			else
			{




				if ((srcImg1.at<float>(y, x) < srcImg0.at<float>(y - 1, x - 1)) && (srcImg1.at<float>(y, x) < srcImg0.at<float>(y - 1, x)) && (srcImg1.at<float>(y, x) < srcImg0.at<float>(y - 1, x + 1))
					&& (srcImg1.at<float>(y, x) < srcImg0.at<float>(y, x - 1)) && (srcImg1.at<float>(y, x) < srcImg0.at<float>(y, x)) && (srcImg1.at<float>(y, x) < srcImg0.at<float>(y, x + 1))
					&& (srcImg1.at<float>(y, x) < srcImg0.at<float>(y + 1, x - 1)) && (srcImg1.at<float>(y, x) < srcImg0.at<float>(y + 1, x)) && (srcImg1.at<float>(y, x) < srcImg0.at<float>(y + 1, x + 1))

					&& (srcImg1.at<float>(y, x) < srcImg1.at<float>(y - 1, x - 1)) && (srcImg1.at<float>(y, x) < srcImg1.at<float>(y - 1, x)) && (srcImg1.at<float>(y, x) < srcImg1.at<float>(y - 1, x + 1))
					&& (srcImg1.at<float>(y, x) < srcImg1.at<float>(y, x - 1)) && (srcImg1.at<float>(y, x) < srcImg1.at<float>(y, x + 1))
					&& (srcImg1.at<float>(y, x) < srcImg1.at<float>(y + 1, x - 1)) && (srcImg1.at<float>(y, x) < srcImg1.at<float>(y + 1, x)) && (srcImg1.at<float>(y, x) < srcImg1.at<float>(y + 1, x + 1))

					&& (srcImg1.at<float>(y, x) < srcImg2.at<float>(y - 1, x - 1)) && (srcImg1.at<float>(y, x) < srcImg2.at<float>(y - 1, x)) && (srcImg1.at<float>(y, x) < srcImg2.at<float>(y - 1, x + 1))
					&& (srcImg1.at<float>(y, x) < srcImg2.at<float>(y, x - 1)) && (srcImg1.at<float>(y, x) < srcImg2.at<float>(y, x)) && (srcImg1.at<float>(y, x) < srcImg2.at<float>(y, x + 1))
					&& (srcImg1.at<float>(y, x) < srcImg2.at<float>(y + 1, x - 1)) && (srcImg1.at<float>(y, x) < srcImg2.at<float>(y + 1, x)) && (srcImg1.at<float>(y, x) < srcImg2.at<float>(y + 1, x + 1))

					)
				{
					//printf("min(%d ,%d ) \r\n",y,x);
					dstImg.at<float>(y, x) = 255;
					minCount++;

				}
				else if ((srcImg1.at<float>(y, x) > srcImg0.at<float>(y - 1, x - 1)) && (srcImg1.at<float>(y, x) > srcImg0.at<float>(y - 1, x)) && (srcImg1.at<float>(y, x) > srcImg0.at<float>(y - 1, x + 1))
					&& (srcImg1.at<float>(y, x) > srcImg0.at<float>(y, x - 1)) && (srcImg1.at<float>(y, x) > srcImg0.at<float>(y, x)) && (srcImg1.at<float>(y, x) > srcImg0.at<float>(y, x + 1))
					&& (srcImg1.at<float>(y, x) > srcImg0.at<float>(y + 1, x - 1)) && (srcImg1.at<float>(y, x) > srcImg0.at<float>(y + 1, x)) && (srcImg1.at<float>(y, x) > srcImg0.at<float>(y + 1, x + 1))

					&& (srcImg1.at<float>(y, x) > srcImg1.at<float>(y - 1, x - 1)) && (srcImg1.at<float>(y, x) > srcImg1.at<float>(y - 1, x)) && (srcImg1.at<float>(y, x) > srcImg1.at<float>(y - 1, x + 1))
					&& (srcImg1.at<float>(y, x) > srcImg1.at<float>(y, x - 1)) && (srcImg1.at<float>(y, x) > srcImg1.at<float>(y, x + 1))
					&& (srcImg1.at<float>(y, x) > srcImg1.at<float>(y + 1, x - 1)) && (srcImg1.at<float>(y, x) > srcImg1.at<float>(y + 1, x)) && (srcImg1.at<float>(y, x) > srcImg1.at<float>(y + 1, x + 1))

					&& (srcImg1.at<float>(y, x) > srcImg2.at<float>(y - 1, x - 1)) && (srcImg1.at<float>(y, x) > srcImg2.at<float>(y - 1, x)) && (srcImg1.at<float>(y, x) > srcImg2.at<float>(y - 1, x + 1))
					&& (srcImg1.at<float>(y, x) > srcImg2.at<float>(y, x - 1)) && (srcImg1.at<float>(y, x) > srcImg2.at<float>(y, x)) && (srcImg1.at<float>(y, x) > srcImg2.at<float>(y, x + 1))
					&& (srcImg1.at<float>(y, x) > srcImg2.at<float>(y + 1, x - 1)) && (srcImg1.at<float>(y, x) > srcImg2.at<float>(y + 1, x)) && (srcImg1.at<float>(y, x) > srcImg2.at<float>(y + 1, x + 1))
					)
				{

					//printf("Max(%d ,%d ) \r\n", y, x);
					dstImg.at<float>(y, x) = 255;
					MaxCount++;

				}
				else
				{
					dstImg.at<float>(y, x) = 0;
				}


				if (dstImg.at<float>(y, x) == 255)
				{




					if (abs(srcImg1.at<float>(y, x)) < 0.0133)
					{
						dstImg.at<float>(y, x) == 0;
						limCount2++;
					}

				}



				if (dstImg.at<float>(y, x) == 255)
				{

					remove_edgeByHessian(srcImg1, y, x, 10, dstImg2);
				}

			}
		}

	}
	printf("MaxCount = %d ,minCount= %d, limCount = %d ,limCount2 = %d,toatl = %d \r\n", MaxCount, minCount, limCount, limCount2, MaxCount + minCount - limCount2);




}


void get_extrPoint(struct octvs_def srcImg, int octv, int intvl, struct octvs_def dstImg, struct octvs_def dstImg2)
{



	

	for (int o = 0; o < octv;o++)
	{
		for (int i = 0; i < intvl - 2;i++)
		{
			printf("octv = %d ,intvl= %d ,", o, i+1);
			find_extrPoint(srcImg.octvsImg[o].layersImg[i], srcImg.octvsImg[o].layersImg[i + 1], srcImg.octvsImg[o].layersImg[i + 2], dstImg.octvsImg[o].layersImg[i], dstImg2.octvsImg[o].layersImg[i]);
		}
	}

	

}