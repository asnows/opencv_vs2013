#include"include.h"

/*****************************************************
void rgb2gray_averag(cv::Mat srcImg,cv::Mat dstImg)
���ܣ�
	RGBתgray��ƽ��ֵ�� gray = (R + G + B)/3
������
	cv::Mat srcImg
		����ͼ��
	cv::Mat dstImg
		���ͼ��
����ֵ��
	��
******************************************************/

void rgb2gray_averag(cv::Mat srcImg,cv::Mat dstImg)
{

	for (int rows = 0; rows < srcImg.rows; rows++)
	{
		for (int cols = 0; cols < srcImg.cols;cols++)
		{
			dstImg.at<uchar>(rows, cols) = (srcImg.at<Vec3b>(rows, cols)[0] + srcImg.at<Vec3b>(rows, cols)[0] + srcImg.at<Vec3b>(rows, cols)[0]) / 3;

		}
	}

}

/*****************************************************
void rgb2gray_formula(cv::Mat srcImg,cv::Mat dstImg)
���ܣ�
	RGBתgray�Ĺ�ʽ�� gray = R*0.299 + G*0.587 + B*0.114
������
	cv::Mat srcImg
		����ͼ��
	cv::Mat dstImg
		���ͼ��
����ֵ��
	��
******************************************************/

void rgb2gray_formula(cv::Mat srcImg, cv::Mat dstImg)
{
	double f_R;
	double f_G;
	double f_B;

	for (int rows = 0; rows < srcImg.rows; rows++)
	{
		for (int cols = 0; cols < srcImg.cols; cols++)
		{
			f_B = (double)srcImg.at<Vec3b>(rows, cols)[0] * 0.299;
			f_G = (double)srcImg.at<Vec3b>(rows, cols)[1] * 0.587;
			f_R = (double)srcImg.at<Vec3b>(rows, cols)[2] * 0.114;
			dstImg.at<uchar>(rows, cols) = f_B + f_G + f_R;

		}
	}

}


/*****************************************************
void rgb2gray_Adobe(cv::Mat srcImg,cv::Mat dstImg)
���ܣ�
	RGBתgray��Adobe��ʽ�� gray = (R^2.2*0.2973 + G^2.2*0.6274 + B^2.2*0.0753)^(1/2.2)
������
	cv::Mat srcImg
		����ͼ��
	cv::Mat dstImg
		���ͼ��
����ֵ��
	��
******************************************************/

void rgb2gray_Adobe(cv::Mat srcImg, cv::Mat dstImg)
{
	double f_R;
	double f_G;
	double f_B;

	for (int rows = 0; rows < srcImg.rows; rows++)
	{
		for (int cols = 0; cols < srcImg.cols; cols++)
		{
			f_B = (double)srcImg.at<Vec3b>(rows, cols)[0];
			f_B = pow(f_B, 2.2) * 0.2973;

			f_G = (double)srcImg.at<Vec3b>(rows, cols)[1];
			f_G = pow(f_G, 2.2) * 0.6247;

			f_R = (double)srcImg.at<Vec3b>(rows, cols)[2];
			f_R = pow(f_R, 2.2) * 0.0753;

			dstImg.at<uchar>(rows, cols) = (short)sqrt(f_B + f_G + f_R);

		}
	}

}










/*****************************************************************
void fpga_rgb2gray(cv::Mat srcImg,cv::Mat dstImg,uchar sel)
���ܣ�
	RGB ת gray
������
	cv::Mat srcImg
		����ͼ��
	cv::Mat dstImg
		���ͼ��
	uchar sel
		����ѡ��0=ƽ��ֵ����1=��ʽ����2= photoshop ��ʽ��
����ֵ��
	��
****************************************************************/
void fpga_rgb2gray(cv::Mat srcImg,cv::Mat dstImg,uchar sel)
{




	switch (sel)
	{
	case 0:
		rgb2gray_averag(srcImg, dstImg);
		break;

	case 1 :
		rgb2gray_formula(srcImg, dstImg);
		break;

	case 2:
		rgb2gray_Adobe(srcImg, dstImg);
		break;
	default:
		break;
	}


}