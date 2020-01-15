
#include"../include.h"

void sift_test()
{
	double sigma = 1.6;
	double sig[3 + 3], sig_total, sig_prev;
	double k;
	int i;

	k = pow(2.0, 1.0 / 3);
	sig[0] = sigma;
	sig[1] = sigma * sqrt(k*k - 1);

	for (i = 2; i < 3 + 3; i++)
	{
		sig[i] = sig[i - 1] * k;
		
	}

	for (i = 0; i < 6;i++)
	{
		printf("sig[%d] = %f \r\n ", i, sig[i]);
	}
		


}
// 获取尺度空间一张图
void get_scaleImg(float* gaus, cv::Mat srcImg,cv::Mat dstImg,float sigma)
{
	unsigned int col;
	unsigned int row;

	float tmp;
	float total = 0;

	//cv::GaussianBlur(srcImg, dstImg, cv::Size(3, 3), sigma, sigma);

	//return;

	for (uchar i = 0; i < 9;i++)
	{
		total += gaus[i];
	}
	

	for (unsigned int y = 2; y < srcImg.rows - 1; y++)
	{
		for (unsigned int x = 2; x < srcImg.cols - 1; x++)
		{
			tmp = srcImg.at<float>(y - 1, x - 1)*gaus[0] + srcImg.at<float>(y - 1, x)  *gaus[1] + srcImg.at<float>(y - 1, x + 1)*gaus[2]
				+ srcImg.at<float>(y, x - 1)*gaus[3] + srcImg.at<float>(y, x) *gaus[4] + srcImg.at<float>(y, x + 1)*gaus[5]
				+ srcImg.at<float>(y + 1, x - 1)*gaus[6] + srcImg.at<float>(y + 1, x) *gaus[7] + srcImg.at<float>(y + 1, x + 1)*gaus[8];
			tmp /= total;

			//if (tmp > 255)
			//{
			//	tmp = 255;
			//	
			//}
			dstImg.at<float>(y, x) = tmp;
			//printf("%f \r\n", tmp);

		}

	}


}


// 获取 Dog 图像
void get_DogImg(cv::Mat srcImg0, cv::Mat srcImg1, cv::Mat dstImg)
{
	float tmp;

	for (unsigned int y = 2; y < srcImg0.rows - 1; y++)
	{
		for (unsigned int x = 2; x < srcImg0.cols - 1; x++)
		{
			tmp = srcImg1.at<float>(y, x) - srcImg0.at<float>(y, x);
			dstImg.at<float>(y, x) = abs(tmp);

			//printf("%f- %f= %f \r\n", srcImg1.at<float>(y, x), srcImg0.at<float>(y, x), dstImg.at<float>(y, x));
		}

	}

}



void downsample(cv::Mat srcImg,cv::Mat dstImg)
{
	int y_tmp, x_tmp;


	printf("downsample \r\n");
	for (int y = 0; y < srcImg.rows;y++)
	{
		y_tmp = y % 2;
		for (int x = 0; x < srcImg.cols;x++)
		{
			x_tmp = x % 2;
			if ((y_tmp == 0) && (x_tmp == 0))
			{
				dstImg.at<float>(y / 2, x / 2) = srcImg.at<float>(y, x);

			}

		}
	}







}

void fpga_sift(cv::Mat srcImg)
{
	float gasu_00[9][9];
	float sigma[6],raw_sigma[6];
	float k;
	
	struct octvs_def gausImg;// 高斯图像组
	struct octvs_def dogImg; //dog 图像组
	struct octvs_def featImg;//特征点图像组
	struct octvs_def featImg2;//去除边缘效应的特征点图像组
	struct octvs_def gaus_img_show;//gaus显示图像组
	struct octvs_def dog_img_show;//显示图像组
	struct octvs_def featImg1_img_show;//显示图像组
	struct octvs_def featImg2_img_show;//显示图像组













	
	
	int size = 0;

	//创建初始高斯数组
	for (int o = 0; o < 5;o++)
	{
		if (o>0)
		{
			size = o * 2;
		}
		else
		{
			size = 1;
		}

		for (int s = 0; s < 6;s++)
		{
			//创建gaus图像组
			gausImg.octvsImg[o].layersImg[s] = cv::Mat(srcImg.rows / size, srcImg.cols / size, CV_32FC1);

			if (s<5)
			{
				//创建DOG图像组
				dogImg.octvsImg[o].layersImg[s] = cv::Mat(srcImg.rows / size, srcImg.cols / size, CV_32FC1);
			}

			if (s<3)
			{
				//创建特征图像组
				featImg.octvsImg[o].layersImg[s] = cv::Mat(srcImg.rows / size, srcImg.cols / size, CV_32FC1);
				//创建去除特征图像组
				featImg2.octvsImg[o].layersImg[s] = cv::Mat::zeros(srcImg.rows / size, srcImg.cols / size, CV_32FC1);

			}
			
			//创建用于调试显示图像组
			gaus_img_show.octvsImg[o].layersImg[s] = cv::Mat(srcImg.rows / size, srcImg.cols / size, CV_8UC1);
			dog_img_show.octvsImg[o].layersImg[s] = cv::Mat(srcImg.rows / size, srcImg.cols / size, CV_8UC1);
			featImg1_img_show.octvsImg[o].layersImg[s] = cv::Mat(srcImg.rows / size, srcImg.cols / size, CV_8UC1);
			featImg2_img_show.octvsImg[o].layersImg[s] = cv::Mat(srcImg.rows / size, srcImg.cols / size, CV_8UC1);
		}
		
	}
	

	



	//生成sigma
	k = pow(2, 1.0 / 3);
	sigma[0] = 1.6;
	sigma[1] = sigma[0]*sqrt(k*k - 1);

	for (uchar i = 2; i < 6;i++)
	{
		sigma[i] = sigma[i - 1] * k;
	}


	//sqrt( sigma * sigma - SIFT_INIT_SIGMA * SIFT_INIT_SIGMA );
	sigma[0] = sqrt(1.6*1.6-SIFT_INIT_SIGMA * SIFT_INIT_SIGMA);


	printf("--------sigma---------- \r\n ");
	for (uchar i = 0; i < 6; i++)
	{
		printf("%f, ", sigma[i]);
	}
	printf("\r\n ");




	// 原始sigma
	raw_sigma[0] = 1.6;

	for (uchar i = 1; i < 6;i++)
	{
		raw_sigma[i] = 1.6* pow(k, i);	
	}
	printf("--------raw_sigma-------- \r\n ");
	for (uchar i = 0; i < 6; i++)
	{
		printf("%f, ", raw_sigma[i]);
	}
	printf("\r\n ");

	float si0 = 1.6;
	float si1 = 2.015874;
	float si2 = 2.539842;
	float si3 = 3.200000;
	float si4 = 4.031748;
	float si5 = 5.079684;


	

	
	//生成高斯核
	for (uchar i = 0; i < 6; i++)
	{
		get_gaus_kernel(3, raw_sigma[i], gasu_00[i]);
	}

	cv::Mat srcImg_32f(srcImg.rows, srcImg.cols, CV_32FC1);
#if 1
	//像素值转化成32float型
	srcImg.convertTo(srcImg_32f, CV_32FC1);

#else
	// 图像拉伸，8位变32位
	IplImage* gray8, *gray32;
	 gray8 = &IplImage(srcImg);
	

	gray32 = cvCreateImage(cvGetSize(gray8), IPL_DEPTH_32F, 1);
	cvConvertScale(gray8, gray32, 1.0 / 255.0, 0);
	srcImg_32f = cvarrToMat(gray32);
#endif

#if 1	



	// 获取高斯尺度空间
	for (uchar o = 0; o < 5;o++)// 5组
	{

		for (uchar i = 0; i < 6;i++)//每组6层
		{
			if (i == 0)
			{
				if (o==0)
				{
					//原图经过gaus生成第一组第一层
					get_scaleImg(gasu_00[0], srcImg_32f, gausImg.octvsImg[0].layersImg[0], sigma[i]);

				}
				else
				{
					//降采样上一组的倒数第三层，作为当前组的第一层
					downsample(gausImg.octvsImg[o - 1].layersImg[4], gausImg.octvsImg[o].layersImg[0]);
				}
				
			}
			else
			{
				//在同一组中，用前一层经过高斯后生成当前层
				get_scaleImg(gasu_00[i], gausImg.octvsImg[o].layersImg[i - 1], gausImg.octvsImg[o].layersImg[i], sigma[i]);
			}

			//转化为CV_8UC1 以便调试显示
			gausImg.octvsImg[o].layersImg[i].convertTo(gaus_img_show.octvsImg[o].layersImg[i],CV_8UC1);		

		}

	}
#else

	// 获取高斯尺度空间
	for (uchar o = 0; o < 5; o++)// 5组
	{

		for (uchar i = 0; i < 6; i++)//每组6层
		{
			if (i == 0)
			{
				if (o == 0)
				{
					//原图经过gaus生成第一组第一层
					//get_scaleImg(gasu_00[0], srcImg_32f, gausImg.octvsImg[0].layersImg[0]);
					cv::GaussianBlur(srcImg_32f, gausImg.octvsImg[0].layersImg[0], cv::Size(3, 3), sigma[0], sigma[0]);

				}
				else
				{
					//降采样上一组的倒数第三层，作为当前组的第一层
					printf("o = %d \r\n",o);
					downsample(gausImg.octvsImg[o-1].layersImg[4], gausImg.octvsImg[o].layersImg[0]);
				}

			}
			else
			{
				//在同一组中，用前一层经过高斯后生成当前层
				//get_scaleImg(gasu_00[i], gausImg.octvsImg[o].layersImg[i - 1], gausImg.octvsImg[o].layersImg[i]);
				cv::GaussianBlur(srcImg_32f, gausImg.octvsImg[o].layersImg[i], cv::Size(3, 3), sigma[i], sigma[i]);
			}

			//转化为CV_8UC1 以便调试显示
			//gausImg.octvsImg[o].layersImg[i].convertTo(img_show.octvsImg[o].layersImg[i],CV_8UC1);		

		}

	}

#endif
	//opencvDispMutPic(img_show, 5, 6);


	for (int o = 0; o < 5;o++)
	{
		for (int s = 0; s < 5;s++)
		{
			get_DogImg(gausImg.octvsImg[o].layersImg[s], gausImg.octvsImg[o].layersImg[s + 1], dogImg.octvsImg[o].layersImg[s]);
			//转化为CV_8UC1 以便调试显示
			dogImg.octvsImg[o].layersImg[s].convertTo(dog_img_show.octvsImg[o].layersImg[s], CV_8UC1,255);

			
		}

	}


	get_extrPoint(dogImg, 5, 5, featImg, featImg2);


	cv::Mat draw_feat1 = srcImg.clone();
	cv::Mat draw_feat2 = srcImg.clone();
	draw_feat(draw_feat1, featImg2.octvsImg[0].layersImg[0]);
	draw_feat(draw_feat2, featImg2.octvsImg[0].layersImg[2]);

	cv::imshow("draw_feat1", draw_feat1);
	cv::imshow("draw_feat2", draw_feat2);

	cv::imwrite("IMG_SIFT2.bmp", draw_feat2);
	

	//write_imgData("txt_fpga_srcImg.txt", (char *)srcImg.data, 307200);
	////write_imgData("txt_fpga_gray32.txt", gray32->imageData, 307200 * 4);
	//write_imgData("txt_fpga_srcImg_32f.txt", (char *)srcImg_32f.data, 307200 * 4);
	//write_imgData("txt_fpga_gauss[0][0].txt", (char *)gausImg.octvsImg[0].layersImg[0].data, 307200 * 4);
	//write_imgData("txt_fpga_gauss[0][1].txt", (char *)gausImg.octvsImg[0].layersImg[1].data, 307200 * 4);
	//write_imgData("txt_fpga_gauss[0][2].txt", (char *)gausImg.octvsImg[0].layersImg[2].data, 307200 * 4);
	//write_imgData("txt_fpga_gauss[0][3].txt", (char *)gausImg.octvsImg[0].layersImg[3].data, 307200 * 4);

	////cvSmooth(gray32, gray32, CV_GAUSSIAN, 0,0, sigma[0], sigma[0]);
	//cv::GaussianBlur(srcImg_32f, srcImg_32f, cv::Size(3, 3), sigma[0], sigma[0]);
	////write_imgData("txt_fpga_gray32_cvSmooth.txt", gray32->imageData, 307200 * 4);
	////write_imgData("txt_fpga_srcImg_32f_GaussianBlur.txt", (char *)srcImg_32f.data, 307200 * 4);

	//cv::Mat kernelX = cv::getGaussianKernel(0, sigma[0]);
	//uchar width;

	//width = cvRound(sigma[0] *3 * 2 + 1) | 1;
	//printf("width = %d depth =%d \r\n", width, srcImg_32f.depth());

	//printf("rows = %d, cols = %d \r\n",kernelX.rows, kernelX.cols);
	//uchar *p_dptr = kernelX.data;
	//for (uchar y = 0; y < kernelX.rows;y++)
	//{
	//	for (uchar x = 0; x < kernelX.cols;x++)
	//	{
	//		printf(" %f ", *p_dptr);
	//		p_dptr++;
	//	}
	//}

	opencvDispMutPic(gaus_img_show, 5, 6, "gausImg");
	opencvDispMutPic(dog_img_show, 5, 5, "dogImg");
	opencvDispMutPic(featImg, 5, 3, "featImg");
	opencvDispMutPic(featImg2, 5, 3, "featImg2");
	
	cv::Mat src(3,3,CV_32FC1);
	cv::Mat dst(3, 3, CV_32FC1);
	cv::Mat dst1(3, 3, CV_32FC1);

	float f_val[3][3] = { { 4, 2, 1 }, { 8, 7, 2 }, { 4, 8, 3 } };
	

	for (uchar y = 0; y < 3; y++)
	{
		for (uchar x = 0; x < 3;x++)
		{
			src.at<float>(y, x) = f_val[y][x];
		}
	}

	

	get_InvMatrix(src, dst);

	//cv::invert(src, dst1, DECOMP_LU);

	//printf("------dst1------- \r\n");
	//for (uchar y = 0; y < 3; y++)
	//{
	//	for (uchar x = 0; x < 3; x++)
	//	{
	//		printf("%f  ,", dst1.at<float>(y, x));
	//	}
	//	printf("\r\n");

	//}






	//opencvWriteMutPic(gausImg, 1, 2,  "IMG_gausImg");
	//opencvWriteMutPic(dogImg,  1,  2,   "IMG_dogImg");
	//opencvWriteMutPic(featImg, 1, 2, "IMG_featImg");
	//opencvWriteMutPic(featImg2, 1, 2, "IMG_featImg2");
	



	//cv::Mat hessian_3D (3,3,CV_32FC1);
	//get_hessian_3D(dogImg, 0, 1, 320, 240, hessian_3D);
	
	//cv::imshow("img_show.octvsImg[0].layersImg[0]", dogImg.octvsImg[0].layersImg[0]);
	//cv::imshow("img_show.octvsImg[0].layersImg[1]", dogImg.octvsImg[0].layersImg[1]);
	//cv::imshow("img_show.octvsImg[0].layersImg[2]", dogImg.octvsImg[0].layersImg[2]);
	//opencvDispMutPic(img_show, 5, 6);

	//cv::imwrite("dogImg0.bmp", dogImg.octvsImg[0].layersImg[0]);
	//cv::imwrite("dogImg1.bmp", dogImg.octvsImg[0].layersImg[1]);
	//cv::imwrite("dogImg2.bmp", dogImg.octvsImg[0].layersImg[2]);
	//cv::imwrite("dogImg3.bmp", dogImg.octvsImg[0].layersImg[3]);
	//cv::imwrite("dogImg4.bmp", dogImg.octvsImg[0].layersImg[4]);
	//cv::imwrite("dogImg5.bmp", dogImg.octvsImg[0].layersImg[5]);


}

