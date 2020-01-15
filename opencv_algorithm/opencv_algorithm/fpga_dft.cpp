#include"include.h"
/*
#include <stdio.h>
#include <stdlib.h>
#include <math.h>			 
#define PI 3.1415926	

int N;	//定于序列长度变量
double Input_Squence[100];	//输入的原始数据序列 
double Ampl[100];   	//存储幅值计算结果

typedef struct				//定义复数结构,下面通过欧拉公式运算
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
		One_Point[n].real = cos(2 * PI / N*k*n)*Input_Squence[n];  //复数的实部
		One_Point[n].imag = -sin(2 * PI / N*k*n)*Input_Squence[n]; //复数的虚部

		Sum_Point.real += One_Point[n].real;	//对实部求和
		Sum_Point.imag += One_Point[n].imag;	//对虚部求和		
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
		Ampl[i] = sqrt(Result_Point[i].real * Result_Point[i].real + Result_Point[i].imag * Result_Point[i].imag);  //计算幅值
	}
}

int main(int argc, char *argv[])
{
	N = atoi(argv[1]);  //atoi,将字符串转换为整数值。 
	//argv[ ]，用来存放指向你的字符串参数的指针
	int i = 0;
	for (i = 0; i<N; i++)//产生输入序列 
	{
		Input_Squence[i] = i;
	}
	DFT_Calculate(); //进行DFT计算 
	for (i = 0; i<N; i++)
	{
		printf("%d\t%lf\n", i, Ampl[i]); //输出计算结果
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
// 把长宽扩展为2的整数次方，并用0 填充
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

	//使长宽相等
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
				//0填充
				dst_ptr[x] = 255;
			}
			
		}
	}

	return dstImg;


}

/*************************************************************
void fpga_fft(Complex<double> * TD, Complex<double> * FD, int r)
功能
	一维快速傅里叶变换
参数
	Complex<double> * TD
		时域输入图像指针
	Complex<double> * FD
		频域输出图像指针
	int r
		2的幂数，迭代次数
返回值
	无
**************************************************************/
void fpga_fft(Complex<double> * TD, Complex<double> * FD, int r)
{
	// 傅立叶变换点数
	long	count;
	
	// 循环变量
	int		i, j, k;

	// 中间变量
	int		bfsize, p;

	// 角度
	double	angle;

	Complex<double> *W, *X1, *X2, *X;
	double PI = 3.1415926;

	// 计算傅立叶变换点数
	count = 1 << r;

	// 分配运算所需存储器
	W = new Complex<double>[count / 2];
	X1 = new Complex<double>[count];
	X2 = new Complex<double>[count];

	// 计算加权系数
	for (i = 0; i < count / 2; i++)
	{
		angle = -i * PI * 2 / count;
		W[i] = Complex<double>(cos(angle), sin(angle));
	}

	// 将时域点写入X1
	memcpy(X1, TD, sizeof(Complex<double>) * count);

	// 采用蝶形算法进行快速傅立叶变换
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

	// 重新排序
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

	// 释放内存
	delete W;
	delete X1;
	delete X2;
}

/**************************************************
void fpga_IFFT(complex<double> * FD, complex<double> * TD, int r)

功能：
	一维快速傅立叶反变换

参数：
	complex<double> * FD
		指向频域数组的指针
	complex<double> * TD
		指向时域数组的指针
	r
		2的幂数，即迭代次数
返回值：
	无
***************************************************/
void fpga_IFFT(Complex<double> * FD, Complex<double> * TD, int r)
{
	// 傅立叶变换点数
	long	count;

	// 循环变量
	int		i;

	Complex<double> *X;

	// 计算傅立叶变换点数
	count = 1 << r;

	// 分配运算所需存储器
	X = new Complex<double>[count];

	// 将频域点写入X
	memcpy(X, FD, sizeof(Complex<double>) * count);

	// 求共轭
	for (i = 0; i < count; i++)
	{
		//X[i] = Complex<double>(X[i].real(), -X[i].imag());
		X[i] = Complex<double>(X[i].re, -X[i].im);
	}

	// 调用快速傅立叶变换
	fpga_fft(X, TD, r);

	// 求时域点的共轭
	for (i = 0; i < count; i++)
	{
		//TD[i] = Complex<double>(TD[i].real() / count, -TD[i].imag() / count);
		TD[i] = Complex<double>(TD[i].re / count, -TD[i].im / count);
	}

	// 释放内存
	delete X;
}

/*************************************************
void fpga_FFT2(cv::Mat srcImg, cv::Mat dstImg,Complex<double> *pOut)
功能：
	快速傅里叶变化
参数：
	cv::Mat srcImg
		输入图像,cv::MaMat 格式
	cv::Mat dstImg 
		输出图像(用于显示)，cv::Mat 格式
	Complex<double> *pOut
		输出图像指针(用于滤波及IFFT)，复数格式
返回值：
	无返回值
*************************************************/
void fpga_FFT2(cv::Mat srcImg, cv::Mat dstImg,Complex<double> *pOut)
{


	// 循环变量
	long		i;
	long		j;

	long		x;
	long		y;

	// FFT2的宽度和高度（2的整数次方）
	long w = 0;
	long h = 0;

	int		wp;
	int		hp;
	double dTemp;
	double dMax;
	double dMin;

	// 赋初值
	w = 1;
	h = 1;
	wp = 0;
	hp = 0;
	

	// 计算进行傅立叶变换的宽度和高度（2的整数次方）
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

	// 填充时域图像
	for (i = 0; i < h;i++)
	{
		for (j = 0; j < w;j++)
		{
						
			TD[i*h + j].re = srcImg.at<uchar>(i, j);
			

		}
	}
	
	for ( i = 0; i < h; i++)
	{
		// 对y方向进行快速傅立叶变换
		fpga_fft(&TD[w * i], &FD[w * i], wp);
	}

	// 保存变换结果使 X、Y 位置互换
	for ( i = 0; i < h; i++)
	{
		for ( j = 0; j < w; j++)
		{
			TD[i + h * j] = FD[j + w * i];
			
		}
	}

	for ( i = 0; i < w; i++)
	{
		// 对x方向进行快速傅立叶变换
		fpga_fft(&TD[i * h], &FD[i * h], hp);
	}


	// 保存变换结果，使 X、Y 位置互换
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
		{
			TD[i + h * j] = FD[j + w * i];

		}
	}


	dMax = 0; dMin = 0;
	//取最大值最小值
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
		{


			pOut[i*h + j] = TD[i*h + j];

			// 计算幅度谱
			dTemp = sqrt(TD[i*h + j].re * TD[i*h + j].re + TD[i*h + j].im * TD[i*h + j].im) / 100;
			
			// 对数变换
			dTemp = log(1 + dTemp);

			// 寻找最大和最小值
			dMax = max(dMax, dTemp);
			dMin = min(dMin, dTemp);
		}



	}

	//计算模 并平移图像
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
			//原始变换输出
			//dstImg.at<uchar>(i, j) = sqrt(TD[i*h + j].re * TD[i*h + j].re + TD[i*h + j].im * TD[i*h + j].im) / sqrt(h*w);// 
			//将变换后的原点移到中心
			//dstImg.at<uchar>(y, x) = sqrt(TD[i*h + j].re * TD[i*h + j].re + TD[i*h + j].im * TD[i*h + j].im) / sqrt(h*w);
			dTemp = sqrt(TD[i*h + j].re * TD[i*h + j].re + TD[i*h + j].im * TD[i*h + j].im) / 100;


			//printf("%f	", dTemp);
			dTemp =  log(1+ dTemp);
			//printf("%f  ", dTemp);

			// 改变动态范围并归一化到0~255
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
功能：
	二维快速傅里叶反变换
参数：
	Complex<double> *pInput
		输入图像指针，复数格式
	cv::Mat dstImg
		输出图像，cv::Mat 格式
返回值：
	无
**********************************************************/
void fpga_IFFT2(Complex<double> *pInput, cv::Mat dstImg)
{
	// 循环变量
	long		i;
	long		j;

	// IFFT2的宽度和高度（2的整数次方）
	long		w;
	long		h;

	int		wp;
	int		hp;
	double dTemp;
	double dMax;
	double dMin;

	// 赋初值
	w = 1;
	h = 1;
	wp = 0;
	hp = 0;

	// 计算进行反傅立叶变换的宽度和高度（2的整数次方）
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

	// 分配内存
	Complex<double> *TD = new Complex<double>[w * h];
	Complex<double> *FD = new Complex<double>[w * h];

	// 垂直方向
	for (i = 0; i < h; i++)
	{
		// 水平方向
		for (j = 0; j < w; j++)
		{
			// 给频域赋值
			FD[j + w * i] = pInput[j + w * i];
		}
	}

	for (i = 0; i < h; i++)
	{
		// 对y方向进行快速反傅立叶变换
		fpga_IFFT(&FD[w * i], &TD[w * i], wp);
	}

	// 保存变换结果
	// 垂直方向
	for (i = 0; i < h; i++)
	{
		// 水平方向
		for (j = 0; j < w; j++)
		{
			FD[i + h * j] = TD[j + w * i];
		}
	}

	for (i = 0; i < w; i++)
	{
		// 对x方向进行快速反傅立叶变换
		fpga_IFFT(&FD[i * h], &TD[i * h], hp);
	}



	dMax = 0; dMin = 0;



	//取最大值最小值
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
		{

			// 取实数部分
			dTemp = TD[i*h + j].re;
			// 寻找最大和最小值
			dMax = max(dMax, dTemp);
			dMin = min(dMin, dTemp);
		}



	}

	//计算模 并平移图像
	for (i = 0; i < h; i++)
	{
		for (j = 0; j < w; j++)
		{
			
			dTemp = TD[j*w + i].re/h*w;
			if (i== 10)
			{
				printf("%f	", dTemp);

			}

			// 改变动态范围并归一化到0~255
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