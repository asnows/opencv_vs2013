#include"include.h"
/*
#include <stdio.h>
#include <stdlib.h>
#include <math.h>			 
#define PI 3.1415926	

int N;	//�������г��ȱ���
double Input_Squence[100];	//�����ԭʼ�������� 
double Ampl[100];   	//�洢��ֵ������

typedef struct				//���帴���ṹ,����ͨ��ŷ����ʽ����
{
	double real, imag;
}complex;
complex Result_Point[100];

void DFT_Calculate_Point(int k)
{
	int n = 0;
	complex Sum_Point;
	complex One_Point[N];
	Sum_Point.real = 0;
	Sum_Point.imag = 0;
	for (n = 0; n<N; n++)
	{
		One_Point[n].real = cos(2 * PI / N*k*n)*Input_Squence[n];  //������ʵ��
		One_Point[n].imag = -sin(2 * PI / N*k*n)*Input_Squence[n]; //�������鲿

		Sum_Point.real += One_Point[n].real;	//��ʵ�����
		Sum_Point.imag += One_Point[n].imag;	//���鲿���		
	}
	Result_Point[k].real = Sum_Point.real;
	Result_Point[k].imag = Sum_Point.imag;
}

void DFT_Calculate()
{
	int i = 0;
	for (i = 0; i<N; i++)
	{
		DFT_Calculate_Point(i);
		Ampl[i] = sqrt(Result_Point[i].real * Result_Point[i].real + Result_Point[i].imag * Result_Point[i].imag);  //�����ֵ
	}
}

int main(int argc, char *argv[])
{
	N = atoi(argv[1]);  //atoi,���ַ���ת��Ϊ����ֵ�� 
	//argv[ ]���������ָ������ַ���������ָ��
	int i = 0;
	for (i = 0; i<N; i++)//������������ 
	{
		Input_Squence[i] = i;
	}
	DFT_Calculate(); //����DFT���� 
	for (i = 0; i<N; i++)
	{
		printf("%d\t%lf\n", i, Ampl[i]); //���������
	}
	return 0;
}
*/


double DFT_Calculate_Point(cv::Mat srcImg, unsigned int u, unsigned int v)
{
	double PI = 3.1415926;
	unsigned int rows = srcImg.rows;
	unsigned int cols = srcImg.cols;
	double real_am = 0;
	double img_am = 0;
	uchar value = 0;
	double rad = 0;
	double f_am = 0;
	double move = 0;
	
	real_am = 0;
	img_am = 0;
	for (unsigned int y = 0; y < rows;y++)
	{
		for (unsigned int x = 0; x < cols; x++)
		{
			rad = -2 * PI*((double)(u*x) / (double)cols + (double)(v*y) / (double)rows);


			value = srcImg.at<uchar>(y, x);
			
			move = ((x + y) %2 == 0) ? 1 : -1;
			
			real_am += value * cos(rad)*move;
			img_am += value * sin(rad)*move;
			//if (u == 0 & v==0)
			//printf("y=%d,x=%d,rad= %f,value =%d, real_am = %f, img_am = %f  \r\n",y,x,rad,value,real_am,img_am);


		}

	}


	f_am = sqrt(real_am*real_am + img_am * img_am) / sqrt(rows *cols);



		return f_am;
}


double IDFT_Calculate_Point(cv::Mat srcImg, unsigned int u, unsigned int v)
{
	double PI = 3.1415926;
	unsigned int rows = srcImg.rows;
	unsigned int cols = srcImg.cols;
	double real_am = 0;
	double img_am = 0;
	uchar value = 0;
	double rad = 0;
	double f_am = 0;
	double move = 0;

	real_am = 0;
	img_am = 0;
	for (unsigned int y = 0; y < rows; y++)
	{
		for (unsigned int x = 0; x < cols; x++)
		{
			rad = 2 * PI*((double)(u*x) / (double)cols + (double)(v*y) / (double)rows);

			value = srcImg.at<uchar>(y, x);	

			real_am += value * cos(rad);
			img_am += value * sin(rad);
			//real_am += value * cos(rad) + value * sin(rad);

		}

	}


	f_am = real_am / sqrt(rows *cols);



	return f_am;
}

void fpga_DFT(cv::Mat srcImg, cv::Mat dstImg)
{
	double f_am = 0;

	for (unsigned int v = 0; v < srcImg.rows;v++)
	{
		for (unsigned int u = 0; u < srcImg.cols; u++)
		{
			f_am = DFT_Calculate_Point(srcImg,u,v);

			dstImg.at<uchar>(v, u) = f_am;
		}
	}

}

//void fpga_fft()
// �ѳ�����չΪ2�������η�������0 ���
cv::Mat img_resize(cv::Mat srcImg)
{
	unsigned int rows = 1;
	unsigned int cols = 1;



	while (rows *2 <= srcImg.rows)
	{
		rows *= 2;
	}

	while (cols * 2 <= srcImg.cols)
	{
		cols *= 2;
	}

	if (rows < srcImg.rows)
	{
		rows *= 2;
	}

	if (cols < srcImg.cols)
	{
		cols *= 2;
	}

	//ʹ�������
	if (cols < rows)
	{
		cols = rows;
	}
	else
	{
		rows = cols;
	}

	printf("resize_rows = %d ,resize_cols = %d \r\n",rows,cols);
	cv::Mat dstImg(rows, cols, CV_8U);

	uchar *src_ptr = 0;
	uchar *dst_ptr = 0;


	
	for (int y = 0; y < rows;y++)
	{
		dst_ptr = dstImg.ptr<uchar>(y);

		if (y < srcImg.rows)
		{
			src_ptr = srcImg.ptr<uchar>(y);
		}
		
		for (int x = 0; x < cols;x++)
		{


			if ((x < srcImg.cols )&& (y<srcImg.rows))
			{
				dst_ptr[x] = src_ptr[x];
			}
			else
			{
				//0���
				dst_ptr[x] = 255;
			}
			
		}
	}

	return dstImg;


}

/*************************************************************
void fpga_fft(Complex<double> * TD, Complex<double> * FD, int r)
����
	һά���ٸ���Ҷ�任
����
	Complex<double> * TD
		ʱ������ͼ��ָ��
	Complex<double> * FD
		Ƶ�����ͼ��ָ��
	int r
		2����������������
����ֵ
	��
**************************************************************/
void fpga_fft(Complex<double> * TD, Complex<double> * FD, int r)
{
	// ����Ҷ�任����
	long	count;
	
	// ѭ������
	int		i, j, k;

	// �м����
	int		bfsize, p;

	// �Ƕ�
	double	angle;

	Complex<double> *W, *X1, *X2, *X;
	double PI = 3.1415926;

	// ���㸵��Ҷ�任����
	count = 1 << r;

	// ������������洢��
	W = new Complex<double>[count / 2];
	X1 = new Complex<double>[count];
	X2 = new Complex<double>[count];

	// �����Ȩϵ��
	for (i = 0; i < count / 2; i++)
	{
		angle = -i * PI * 2 / count;
		W[i] = Complex<double>(cos(angle), sin(angle));
	}

	// ��ʱ���д��X1
	memcpy(X1, TD, sizeof(Complex<double>) * count);

	// ���õ����㷨���п��ٸ���Ҷ�任
	for (k = 0; k < r; k++)
	{
		for (j = 0; j < 1 << k; j++)
		{
			bfsize = 1 << (r - k);
			


			for (i = 0; i < bfsize / 2; i++)
			{
				p = j * bfsize;
				X2[i + p] = X1[i + p] + X1[i + p + bfsize / 2];
				X2[i + p + bfsize / 2] = (X1[i + p] - X1[i + p + bfsize / 2]) * W[i * (1 << k)];

			}
		}


		X = X1;
		X1 = X2;
		X2 = X;
	}

	// ��������
	for (j = 0; j < count; j++)
	{
		p = 0;
		for (i = 0; i < r; i++)
		{
			if (j&(1 << i))
			{
				p += 1 << (r - i - 1);
			}
		}
		FD[j] = X1[p];
	}

	// �ͷ��ڴ�
	delete W;
	delete X1;
	delete X2;
}

/**************************************************
void fpga_IFFT(complex<double> * FD, complex<double> * TD, int r)

���ܣ�
	һά���ٸ���Ҷ���任

������
	complex<double> * FD
		ָ��Ƶ�������ָ��
	complex<double> * TD
		ָ��ʱ�������ָ��
	r
		2������������������
����ֵ��
	��
***************************************************/
void fpga_IFFT(Complex<double> * FD, Complex<double> * TD, int r)
{
	// ����Ҷ�任����
	long	count;

	// ѭ������
	int		i;

	Complex<double> *X;

	// ���㸵��Ҷ�任����
	count = 1 << r;

	// ������������洢��
	X = new Complex<double>[count];

	// ��Ƶ���д��X
	memcpy(X, FD, sizeof(Complex<double>) * count);

	// ����
	for (i = 0; i < count; i++)
	{
		//X[i] = Complex<double>(X[i].real(), -X[i].imag());
		X[i] = Complex<double>(X[i].re, -X[i].im);
	}

	// ���ÿ��ٸ���Ҷ�任
	fpga_fft(X, TD, r);

	// ��ʱ���Ĺ���
	for (i = 0; i < count; i++)
	{
		//TD[i] = Complex<double>(TD[i].real() / count, -TD[i].imag() / count);
		TD[i] = Complex<double>(TD[i].re / count, -TD[i].im / count);
	}

	// �ͷ��ڴ�
	delete X;
}

/*************************************************
void fpga_FFT2(cv::Mat srcImg, cv::Mat dstImg,Complex<double> *pOut)
���ܣ�
	���ٸ���Ҷ�仯
������
	cv::Mat srcImg
		����ͼ��,cv::MaMat ��ʽ
	cv::Mat dstImg 
		���ͼ��(������ʾ)��cv::Mat ��ʽ
	Complex<double> *pOut
		���ͼ��ָ��(�����˲���IFFT)��������ʽ
����ֵ��
	�޷���ֵ
*************************************************/
void fpga_FFT2(cv::Mat srcImg, cv::Mat dstImg,Complex<double> *pOut)
{


	// ѭ������
	long		i;
	long		j;

	long		x;
	long		y;

	// FFT2�Ŀ�Ⱥ͸߶ȣ�2�������η���
	long w = 0;
	long h = 0;

	int		wp;
	int		hp;
	double dTemp;
	double dMax;
	double dMin;

	// ����ֵ
	w = 1;
	h = 1;
	wp = 0;
	hp = 0;
	

	// ������и���Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2�������η���
	while (w * 2 <= srcImg.cols)
	{
		w *= 2;
		wp++;
	}

	while (h * 2 <= srcImg.rows)
	{
		h *= 2;
		hp++;
	}

	if (h != srcImg.rows)
	{
		h *= 2;
		hp++;
	}

	if (w != srcImg.cols)
	{
		w *= 2;
		wp++;
	}

	printf("w = %d ,h =%d \r\n", w, h);


	Complex<double> *TD = new Complex<double>[w * h];
	Complex<double> *FD = new Complex<double>[w * h];

	// ���ʱ��ͼ��
	for (i = 0; i < h;i++)
	{
		for (j = 0; j < w;j++)
		{
						
			TD[i*h + j].re = srcImg.at<uchar>(i, j);
			

		}
	}
	
	for ( i = 0; i < h; i++)
	{
		// ��y������п��ٸ���Ҷ�任
		fpga_fft(&TD[w * i], &FD[w * i], wp);
	}

	// ����任���ʹ X��Y λ�û���
	for ( i = 0; i < h; i++)
	{
		for ( j = 0; j < w; j++)
		{
			TD[i + h * j] = FD[j + w * i];
			
		}
	}

	for ( i = 0; i < w; i++)
	{
		// ��x������п��ٸ���Ҷ�任
		fpga_fft(&TD[i * h], &FD[i * h], hp);
	}


	// ����任�����ʹ X��Y λ�û���
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
		{
			TD[i + h * j] = FD[j + w * i];

		}
	}


	dMax = 0; dMin = 0;
	//ȡ���ֵ��Сֵ
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
		{


			pOut[i*h + j] = TD[i*h + j];

			// ���������
			dTemp = sqrt(TD[i*h + j].re * TD[i*h + j].re + TD[i*h + j].im * TD[i*h + j].im) / 100;
			
			// �����任
			dTemp = log(1 + dTemp);

			// Ѱ��������Сֵ
			dMax = max(dMax, dTemp);
			dMin = min(dMin, dTemp);
		}



	}

	//����ģ ��ƽ��ͼ��
	for (i = 0; i < h;i++)
	{
		for (j = 0; j < w; j++)
		{
			if (i<h/2)
			{
				y = i + h / 2;
			}
			else
			{
				y = i - h / 2;
			}

			if (j<w / 2)
			{
				x = j + w / 2;
			}
			else
			{
				x = j - w / 2;
			}
			//ԭʼ�任���
			//dstImg.at<uchar>(i, j) = sqrt(TD[i*h + j].re * TD[i*h + j].re + TD[i*h + j].im * TD[i*h + j].im) / sqrt(h*w);// 
			//���任���ԭ���Ƶ�����
			//dstImg.at<uchar>(y, x) = sqrt(TD[i*h + j].re * TD[i*h + j].re + TD[i*h + j].im * TD[i*h + j].im) / sqrt(h*w);
			dTemp = sqrt(TD[i*h + j].re * TD[i*h + j].re + TD[i*h + j].im * TD[i*h + j].im) / 100;


			//printf("%f	", dTemp);
			dTemp =  log(1+ dTemp);
			//printf("%f  ", dTemp);

			// �ı䶯̬��Χ����һ����0~255
			dTemp = (dTemp - dMin) / (dMax - dMin) * 255;
			//printf("%f \r\n", dTemp);


			if (dTemp > 255)
			{
				dTemp = 255;
			}

			dstImg.at<uchar>(y, x) = dTemp;
			
		}

		

	}



}


/**********************************************************
void fpga_IFFT2(Complex<double> *pInput, cv::Mat dstImg)
���ܣ�
	��ά���ٸ���Ҷ���任
������
	Complex<double> *pInput
		����ͼ��ָ�룬������ʽ
	cv::Mat dstImg
		���ͼ��cv::Mat ��ʽ
����ֵ��
	��
**********************************************************/
void fpga_IFFT2(Complex<double> *pInput, cv::Mat dstImg)
{
	// ѭ������
	long		i;
	long		j;

	// IFFT2�Ŀ�Ⱥ͸߶ȣ�2�������η���
	long		w;
	long		h;

	int		wp;
	int		hp;
	double dTemp;
	double dMax;
	double dMin;

	// ����ֵ
	w = 1;
	h = 1;
	wp = 0;
	hp = 0;

	// ������з�����Ҷ�任�Ŀ�Ⱥ͸߶ȣ�2�������η���
	while (w * 2 <= dstImg.cols)
	{
		w *= 2;
		wp++;
	}

	while (h * 2 <= dstImg.rows)
	{
		h *= 2;
		hp++;
	}

	// �����ڴ�
	Complex<double> *TD = new Complex<double>[w * h];
	Complex<double> *FD = new Complex<double>[w * h];

	// ��ֱ����
	for (i = 0; i < h; i++)
	{
		// ˮƽ����
		for (j = 0; j < w; j++)
		{
			// ��Ƶ��ֵ
			FD[j + w * i] = pInput[j + w * i];
		}
	}

	for (i = 0; i < h; i++)
	{
		// ��y������п��ٷ�����Ҷ�任
		fpga_IFFT(&FD[w * i], &TD[w * i], wp);
	}

	// ����任���
	// ��ֱ����
	for (i = 0; i < h; i++)
	{
		// ˮƽ����
		for (j = 0; j < w; j++)
		{
			FD[i + h * j] = TD[j + w * i];
		}
	}

	for (i = 0; i < w; i++)
	{
		// ��x������п��ٷ�����Ҷ�任
		fpga_IFFT(&FD[i * h], &TD[i * h], hp);
	}



	dMax = 0; dMin = 0;



	//ȡ���ֵ��Сֵ
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
		{

			// ȡʵ������
			dTemp = TD[i*h + j].re;
			// Ѱ��������Сֵ
			dMax = max(dMax, dTemp);
			dMin = min(dMin, dTemp);
		}



	}

	//����ģ ��ƽ��ͼ��
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
		{
			
			dTemp = TD[j*w + i].re/h*w;
			if (i== 10)
			{
				printf("%f	", dTemp);

			}

			// �ı䶯̬��Χ����һ����0~255
			dTemp = (dTemp - dMin) / (dMax - dMin) * 255;

			if (i== 10)
			{
				printf("%f \r\n", dTemp);
			}
			


			if (dTemp > 255)
			{
				dTemp = 255;
			}

			dstImg.at<uchar>(i, j) = dTemp;

		}



	}


	 





}



void fpga_IDFT(cv::Mat srcImg, cv::Mat dstImg)
{

	double f_am = 0;

	for (unsigned int v = 0; v < srcImg.rows; v++)
	{
		for (unsigned int u = 0; u < srcImg.cols; u++)
		{
			f_am = IDFT_Calculate_Point(srcImg, u, v);

			dstImg.at<uchar>(v, u) = f_am;
		}
	}

}