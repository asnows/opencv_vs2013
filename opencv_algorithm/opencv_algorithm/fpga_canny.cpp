#include"include.h"

/*****************************************************************
void fpga_canny(cv::Mat src, cv::Mat dst, uchar sel,uchar maxVal,uchar minVal)
功能：
	Canny 算法
参数：
	cv::Mat srcImg
		输入图像，已经过高斯处理
	cv::Mat dstImg
		输出图像
	uchar sel
		sobel 输出图像边缘 1=标准sobel，0=双边缘
	uchar maxVal
		最大阈值
	uchar minVal
		最小阈值
返回值：
无
****************************************************************/



void fpga_canny(cv::Mat src, cv::Mat dst, uchar sel, uchar maxVal, uchar minVal)
{

	unsigned int rows = src.rows;
	unsigned int cols = src.cols;
	unsigned int x1, x2, y1, y2, Gout;
	unsigned int x_abs, y_abs;
	unsigned int x_abs_dir, y_abs_dir;
	float tan_225 = 0.4142;
	float tan_675 = 2.4142;
	float tmp;
	unsigned char theta; // 0 = 0 度，1 = 45度，2 = 90度，3 = 135度
	unsigned char Gx_s;// Gx 符号 0= 正， 1= 负； 
	unsigned char Gy_s;// Gy 符号 0= 正， 1= 负；
	unsigned char buff3x3[9];
	unsigned char value;

	//cv::Mat nonMaxImg = cv::Mat::zeros (src.rows, dst.cols, CV_16UC1);//存放 nonMax
	cv::Mat nonMaxImg(src.rows, dst.cols, CV_16UC1);//存放 nonMax
	cv::Mat sobelImg(src.rows, dst.cols, CV_16UC1);//存放 sobel
	cv::Mat dirImg(src.rows, dst.cols, CV_8UC1);//存放梯度方向


	cv::Mat sobelImg_show;
	cv::Mat nonMaxImg_show;
	 
	
	// sobel 求梯度
	for (unsigned int y = 2; y< rows -1; y++)
	{

		for (unsigned int x = 2; x < cols -1 ; x++)
		{
			x1 = src.at<unsigned char>(y - 1, x - 1)
				+ src.at<unsigned char>(y, x - 1) * 2
				+ src.at<unsigned char>(y + 1, x - 1);

			x2 = src.at<unsigned char>(y - 1, x + 1)
				+ src.at<unsigned char>(y, x + 1) * 2
				+ src.at<unsigned char>(y + 1, x + 1);

			y1 = src.at<unsigned char>(y - 1, x - 1)
				+ src.at<unsigned char>(y - 1, x) * 2
				+ src.at<unsigned char>(y - 1, x + 1);

			y2 = src.at<unsigned char>(y + 1, x - 1)
				+ src.at<unsigned char>(y + 1, x) * 2
				+ src.at<unsigned char>(y + 1, x + 1);

			if (x1 > x2)
			{
				if (sel)
				{
					x_abs = 0;
				}
				else
				{
					x_abs = x1 - x2;
				}

				Gx_s = 1;
				x_abs_dir = x1 - x2;
				


			}
			else
			{
				x_abs = x2 - x1;

				Gx_s = 0;
				x_abs_dir = x2 - x1;
				
			}



			if (y1 > y2)
			{
				if (sel)
				{
					y_abs = 0;
				}
				else
				{
					y_abs = y1 - y2;
				}

				Gy_s = 1;
				y_abs_dir = y1 - y2;
			}
			else
			{
				y_abs = y2 - y1;

				Gy_s = 0;
				y_abs_dir = y2 - y1;
			}

			Gout = x_abs + y_abs;
			if (Gout > 255)
			{
				//Gout = 255;
			}


			sobelImg.at<unsigned short>(y, x) = Gout;

			// 求梯度方向
			tmp = (float)y_abs_dir / (float)x_abs_dir;

			if (tmp < tan_225)
			{
				theta = 0;
			}
			else if (tmp > tan_675)
			{
				theta = 2;
			}
			else
			{
				if (Gy_s == Gx_s)
				{
					theta = 1;
				}
				else
				{
					theta = 3;
				}

			}

			dirImg.at<unsigned char>(y, x) = theta;


		}

	}


	sobelImg.convertTo(nonMaxImg_show, CV_8UC1);
	cv::imshow("fpga_canny_sobel", sobelImg);
	cv::imwrite("fpga_canny_sobel.bmp", sobelImg);


	//非极大值抑制
	for (unsigned int y = 2; y< rows -1; y++)
	{
		for (unsigned int x = 2; x < cols -1; x++)
		{
			theta = dirImg.at<unsigned char>(y, x);

			switch (theta)
			{
			case 0:
				if ((sobelImg.at<unsigned short>(y, x - 1) < sobelImg.at<unsigned short>(y, x)) && (sobelImg.at<unsigned short>(y, x) >= sobelImg.at<unsigned short>(y, x + 1)))
				{
					nonMaxImg.at<unsigned short>(y, x) = sobelImg.at<unsigned short>(y, x);
					
				}
				else
				{
					nonMaxImg.at<unsigned short>(y, x) = 0;
					
				}
			
					
				break;
			case 3:

				if ((sobelImg.at<unsigned short>(y + 1, x - 1) < sobelImg.at<unsigned short>(y, x)) && (sobelImg.at<unsigned short>(y, x) > sobelImg.at<unsigned short>(y - 1, x + 1)))
				{
					nonMaxImg.at<unsigned short>(y, x) = sobelImg.at<unsigned short>(y, x);
				}
				else
				{
					nonMaxImg.at<unsigned short>(y, x) = 0;
				}


				break;
			case 2:
				if ((sobelImg.at<unsigned short>(y - 1, x) < sobelImg.at<unsigned short>(y, x)) && (sobelImg.at<unsigned short>(y, x) >= sobelImg.at<unsigned short>(y + 1, x)))
				{
					nonMaxImg.at<unsigned short>(y, x) = sobelImg.at<unsigned short>(y, x);
				}
				else
				{
					nonMaxImg.at<unsigned short>(y, x) = 0;
				}

				break;
			case 1:

				if ((sobelImg.at<unsigned short>(y - 1, x - 1) < sobelImg.at<unsigned short>(y, x)) && (sobelImg.at<unsigned short>(y, x) > sobelImg.at<unsigned short>(y + 1, x + 1)))
				{
					nonMaxImg.at<unsigned short>(y, x) = sobelImg.at<unsigned short>(y, x);
				}
				else
				{
					nonMaxImg.at<unsigned short>(y, x) = 0;
				}

				break;
			}
				 

		}

	}

#if 1
	unsigned int dis_y,dis_x;
	dis_y = 210;
	dis_x = 458;
	printf("-----------src------------\r\n");
	printf("%x,%x %x \r\n", src.at<uchar>(dis_y - 1, dis_x - 1), src.at<uchar>(dis_y - 1, dis_x), src.at<uchar>(dis_y - 1, dis_x + 1));
	printf("%x,%x %x \r\n", src.at<uchar>(dis_y, dis_x - 1), src.at<uchar>(dis_y, dis_x), src.at<uchar>(dis_y, dis_x + 1));
	printf("%x,%x %x \r\n", src.at<uchar>(dis_y + 1, dis_x - 1), src.at<uchar>(dis_y + 1, dis_x), src.at<uchar>(dis_y + 1, dis_x + 1));

	printf("-----------sobelImg------------\r\n");
	printf("%x,%x %x \r\n", sobelImg.at<unsigned short>(dis_y - 1, dis_x - 1), sobelImg.at<unsigned short>(dis_y - 1, dis_x), sobelImg.at<unsigned short>(dis_y - 1, dis_x + 1));
	printf("%x,%x %x \r\n", sobelImg.at<unsigned short>(dis_y    , dis_x - 1), sobelImg.at<unsigned short>(dis_y    , dis_x), sobelImg.at<unsigned short>(dis_y    , dis_x + 1));
	printf("%x,%x %x \r\n", sobelImg.at<unsigned short>(dis_y + 1, dis_x - 1), sobelImg.at<unsigned short>(dis_y + 1, dis_x), sobelImg.at<unsigned short>(dis_y + 1, dis_x + 1));
	
	printf("-----------dirImg------------\r\n");
	printf("%x,%x %x \r\n", dirImg.at<uchar>(dis_y - 1, dis_x - 1), dirImg.at<uchar>(dis_y - 1, dis_x), dirImg.at<uchar>(dis_y - 1, dis_x + 1));
	printf("%x,%x %x \r\n", dirImg.at<uchar>(dis_y, dis_x - 1), dirImg.at<uchar>(dis_y, dis_x), dirImg.at<uchar>(dis_y, dis_x + 1));
	printf("%x,%x %x \r\n", dirImg.at<uchar>(dis_y + 1, dis_x - 1), dirImg.at<uchar>(dis_y + 1, dis_x), dirImg.at<uchar>(dis_y + 1, dis_x + 1));

	printf("-----------nonMaxImg------------\r\n");
	printf("%x,%x %x \r\n", nonMaxImg.at<unsigned short>(dis_y - 1, dis_x - 1), nonMaxImg.at<unsigned short>(dis_y - 1, dis_x), nonMaxImg.at<unsigned short>(dis_y - 1, dis_x + 1));
	printf("%x,%x %x \r\n", nonMaxImg.at<unsigned short>(dis_y    , dis_x - 1), nonMaxImg.at<unsigned short>(dis_y    , dis_x), nonMaxImg.at<unsigned short>(dis_y    , dis_x + 1));
	printf("%x,%x %x \r\n", nonMaxImg.at<unsigned short>(dis_y + 1, dis_x - 1), nonMaxImg.at<unsigned short>(dis_y + 1, dis_x), nonMaxImg.at<unsigned short>(dis_y + 1, dis_x + 1));

#endif



	
	nonMaxImg.convertTo(nonMaxImg_show, CV_8UC1);
	cv::imshow("nonMaxImg", nonMaxImg_show);
	cv::imwrite("fpga_canny_nonMaxImg.bmp", nonMaxImg_show);

#if 1
	//正向(顺序)双阈值处理
	cv::Mat hyst_seqImg(src.rows, dst.cols, CV_8UC1);//存放双阈值顺序处理后的图
	value = maxVal;//边界值

	for (unsigned int y = 2; y< rows - 1; y++)
	{
		for (unsigned int x = 2; x < cols - 1; x++)
		{
			if (nonMaxImg.at<unsigned short>(y, x) > maxVal)
			{
				hyst_seqImg.at<uchar>(y, x) = 255;
				//nonMaxImg.at<unsigned short>(y, x) = 255;
			}
			else if (nonMaxImg.at<unsigned short>(y, x) <= minVal)
			{
				hyst_seqImg.at<uchar>(y, x) = 0;
				//nonMaxImg.at<unsigned short>(y, x) = 0;
			}
			else
			{



				if ((nonMaxImg.at<unsigned short>(y - 1, x - 1) > value) || (nonMaxImg.at<unsigned short>(y - 1, x) > value) || (nonMaxImg.at<unsigned short>(y - 1, x + 1) > value)
					|| (nonMaxImg.at<unsigned short>(y, x - 1) > value) || (nonMaxImg.at<unsigned short>(y, x + 1) > value)
					|| (nonMaxImg.at<unsigned short>(y + 1, x - 1) > value) || (nonMaxImg.at<unsigned short>(y + 1, x) > value) || (nonMaxImg.at<unsigned short>(y + 1, x + 1) > value))
				{
					hyst_seqImg.at<uchar>(y, x) = 255;
					nonMaxImg.at<unsigned short>(y, x) = 255;//边缘延长

				}
				else
				{
					hyst_seqImg.at<uchar>(y, x) = 0;
					//nonMaxImg.at<unsigned short>(y, x) = 0;//边缘截断
				}


			}

		}

	}


	cv::imshow("hyst_seqImg", hyst_seqImg);
	cv::imwrite("hyst_seqImg.bmp", hyst_seqImg);


	printf("-----------hyst_seqImg------------\r\n");
	printf("%x,%x %x \r\n", hyst_seqImg.at<uchar>(dis_y - 1, dis_x - 1), hyst_seqImg.at<uchar>(dis_y - 1, dis_x), hyst_seqImg.at<uchar>(dis_y - 1, dis_x + 1));
	printf("%x,%x %x \r\n", hyst_seqImg.at<uchar>(dis_y, dis_x - 1), hyst_seqImg.at<uchar>(dis_y, dis_x), hyst_seqImg.at<uchar>(dis_y, dis_x + 1));
	printf("%x,%x %x \r\n", hyst_seqImg.at<uchar>(dis_y + 1, dis_x - 1), hyst_seqImg.at<uchar>(dis_y + 1, dis_x), hyst_seqImg.at<uchar>(dis_y + 1, dis_x + 1));



	//反向(倒序)双阀值处理
	unsigned int rev_y = 0;
	unsigned int rev_x = 0;
	cv::Mat hyst_revImg(src.rows, dst.cols, CV_8UC1);//存放双阈值反向处理后的图像

	for (unsigned int y = 2; y< rows - 1; y++)
	{
		for (unsigned int x = 2; x < cols - 1; x++)
		{
			rev_y = rows - y;
			rev_x = cols - x;

			if (nonMaxImg.at<unsigned short>(rev_y, rev_x) > maxVal)
			{
				hyst_revImg.at<uchar>(rev_y, rev_x) = 255;

			}
			else if (nonMaxImg.at<unsigned short>(rev_y, rev_x) <= minVal)
			{
				hyst_revImg.at<uchar>(rev_y, rev_x) = 0;

			}
			else
			{


				if ((nonMaxImg.at<unsigned short>(rev_y - 1, rev_x - 1) > value) || (nonMaxImg.at<unsigned short>(rev_y - 1, rev_x) > value) || (nonMaxImg.at<unsigned short>(rev_y - 1, rev_x + 1) > value)
					|| (nonMaxImg.at<unsigned short>(rev_y, rev_x - 1) > value) || (nonMaxImg.at<unsigned short>(rev_y, rev_x + 1) > value)
					|| (nonMaxImg.at<unsigned short>(rev_y + 1, rev_x - 1) > value) || (nonMaxImg.at<unsigned short>(rev_y + 1, rev_x) > value) || (nonMaxImg.at<unsigned short>(rev_y + 1, rev_x + 1) > value))
				{
					hyst_revImg.at<uchar>(rev_y, rev_x) = 255;
					nonMaxImg.at<unsigned short>(rev_y, rev_x) = 255;//边缘延长

				}
				else
				{
					hyst_revImg.at<uchar>(rev_y, rev_x) = 0;
					//nonMaxImg.at<unsigned short>(rev_y, rev_x) = 0;//边缘截断
				}


			}

		}

	}



	cv::imshow("hyst_revImg", hyst_revImg);
	cv::imwrite("hyst_revImg.bmp", hyst_revImg);


	//生成边缘图像输出
	unsigned short dst_value;
	for (unsigned int y = 2; y< rows - 1; y++)
	{
		for (unsigned int x = 2; x < cols - 1; x++)
		{
			dst_value = hyst_seqImg.at<uchar>(y, x) + hyst_revImg.at<uchar>(y, x);

			if (dst_value > 255)
			{
				dst_value = 255;
			}

			dst.at<uchar>(y, x) = dst_value;

		}

	}

#else

	//递归处理
	//边缘标记, 这里最优的办法应该用栈的操作来实现。这里只是为了便于理解
	cv::Mat flgImg(src.rows, src.cols, CV_8UC1);//存放标记 0=不是是边缘，1=可能是边缘，2=是边缘
	uchar *stack[65536];// 存放 边缘点的地址
	uchar **p_stack_top;
	uchar **p_stack_bottom;
	unsigned short *p_nonMax;//指向非极大值处理后的图像
	uchar *p_flgImg;

	memset(&stack[0], 0,sizeof(stack));
	p_stack_top = &stack[0];
	p_stack_bottom = &stack[0];

	p_nonMax = (unsigned short*)nonMaxImg.data;
	p_flgImg = flgImg.data ;


	for (unsigned int y = 2; y< rows - 1; y++)
	{
		for (unsigned int x = 2; x < cols - 1; x++)
		{

			if (*(p_nonMax + y*cols + x) <= minVal)					// 当前像素小于极大值
			{
				*(p_flgImg + y*cols + x) = 0;						// 不是边缘点
			}
			else if (*(p_nonMax + y*cols + x) > maxVal				// 当前像素大于极大值
					&& (*(p_nonMax + (y - 1)*cols + x) <= maxVal)	//上一个像素不是边缘点
					&& (*(p_nonMax + y*cols + x -1) <= maxVal)		// 前一个像素不是边缘点
					)	
			{
				
				*(p_flgImg + y*cols + x) = 2;						// 标记为边缘点（起点）
				*p_stack_top = (p_flgImg + y*cols + x);				
				p_stack_top++;

			}
			else
			{
				*(p_flgImg + y*cols + x) = 1;						// 可能是边缘点
			}
	
		}

	}

	cv::imshow("flgImg", flgImg);

	//// 更新标记，对可能是边缘的点进行处理（边缘追踪）
	uchar  *p_tmp;
	while (p_stack_top - p_stack_bottom)
	{
		p_stack_top--;
		p_tmp = *p_stack_top;
		
		if (*(p_tmp - cols - 1) == 1)
		{
			*p_stack_top = p_tmp - cols - 1;
			*(p_tmp - cols - 1) = 2;
			p_stack_top++;
			
		}
		if (*(p_tmp - cols) == 1)
		{
			*p_stack_top = p_tmp - cols ;
			*(p_tmp - cols) = 2;
			p_stack_top++;

		}

		if (*(p_tmp - cols + 1) == 1)
		{
			*p_stack_top = p_tmp - cols + 1;
			*(p_tmp - cols + 1) = 2;
			p_stack_top++;

		}
		if (*(p_tmp - 1) == 1)
		{
			*p_stack_top = p_tmp  - 1;
			*(p_tmp - 1) = 2;
			p_stack_top++;
		}

		if (*(p_tmp + 1) == 1)
		{
			*p_stack_top = p_tmp + 1;
			*(p_tmp + 1 ) = 2;
			p_stack_top++;
		}
		if (*(p_tmp + cols - 1) == 1)
		{
			*p_stack_top = p_tmp + cols - 1;
			*(p_tmp + cols - 1) = 2;
			p_stack_top++;
		}
		if (*(p_tmp + cols) == 1)
		{
			*p_stack_top = p_tmp + cols ;
			*(p_tmp + cols) = 2;
			p_stack_top++;
		}
		if (*(p_tmp + cols + 1) == 1)
		{
			*p_stack_top = p_tmp + cols + 1;
			*(p_tmp + cols + 1) = 2;
			p_stack_top++;
		}


	}

	////生成边缘图像
	uchar *p_dstImg;
	p_dstImg = dst.data;
	for (unsigned int y = 2; y< rows - 1; y++)
	{
		for (unsigned int x = 2; x < cols - 1; x++)
		{

			if (*(p_flgImg + y*cols + x) == 2)
			{
				*(p_dstImg + y*cols + x) = 255;
			}
			else

			{
				*(p_dstImg + y*cols + x) = 0;
			}
		

		}

	}

#endif

	cv::imshow("fpga_canny_Dst", dst);
	cv::imwrite("fpga_canny_Dst.bmp", dst);



}