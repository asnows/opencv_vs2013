#include"include.h"

/*****************************************************************
void fpga_canny(cv::Mat src, cv::Mat dst, uchar sel,uchar maxVal,uchar minVal)
���ܣ�
	Canny �㷨
������
	cv::Mat srcImg
		����ͼ���Ѿ�����˹����
	cv::Mat dstImg
		���ͼ��
	uchar sel
		sobel ���ͼ���Ե 1=��׼sobel��0=˫��Ե
	uchar maxVal
		�����ֵ
	uchar minVal
		��С��ֵ
����ֵ��
��
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
	unsigned char theta; // 0 = 0 �ȣ�1 = 45�ȣ�2 = 90�ȣ�3 = 135��
	unsigned char Gx_s;// Gx ���� 0= ���� 1= ���� 
	unsigned char Gy_s;// Gy ���� 0= ���� 1= ����
	unsigned char buff3x3[9];
	unsigned char value;

	//cv::Mat nonMaxImg = cv::Mat::zeros (src.rows, dst.cols, CV_16UC1);//��� nonMax
	cv::Mat nonMaxImg(src.rows, dst.cols, CV_16UC1);//��� nonMax
	cv::Mat sobelImg(src.rows, dst.cols, CV_16UC1);//��� sobel
	cv::Mat dirImg(src.rows, dst.cols, CV_8UC1);//����ݶȷ���


	cv::Mat sobelImg_show;
	cv::Mat nonMaxImg_show;
	 
	
	// sobel ���ݶ�
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

			// ���ݶȷ���
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


	//�Ǽ���ֵ����
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
	//����(˳��)˫��ֵ����
	cv::Mat hyst_seqImg(src.rows, dst.cols, CV_8UC1);//���˫��ֵ˳������ͼ
	value = maxVal;//�߽�ֵ

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
					nonMaxImg.at<unsigned short>(y, x) = 255;//��Ե�ӳ�

				}
				else
				{
					hyst_seqImg.at<uchar>(y, x) = 0;
					//nonMaxImg.at<unsigned short>(y, x) = 0;//��Ե�ض�
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



	//����(����)˫��ֵ����
	unsigned int rev_y = 0;
	unsigned int rev_x = 0;
	cv::Mat hyst_revImg(src.rows, dst.cols, CV_8UC1);//���˫��ֵ��������ͼ��

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
					nonMaxImg.at<unsigned short>(rev_y, rev_x) = 255;//��Ե�ӳ�

				}
				else
				{
					hyst_revImg.at<uchar>(rev_y, rev_x) = 0;
					//nonMaxImg.at<unsigned short>(rev_y, rev_x) = 0;//��Ե�ض�
				}


			}

		}

	}



	cv::imshow("hyst_revImg", hyst_revImg);
	cv::imwrite("hyst_revImg.bmp", hyst_revImg);


	//���ɱ�Եͼ�����
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

	//�ݹ鴦��
	//��Ե���, �������ŵİ취Ӧ����ջ�Ĳ�����ʵ�֡�����ֻ��Ϊ�˱������
	cv::Mat flgImg(src.rows, src.cols, CV_8UC1);//��ű�� 0=�����Ǳ�Ե��1=�����Ǳ�Ե��2=�Ǳ�Ե
	uchar *stack[65536];// ��� ��Ե��ĵ�ַ
	uchar **p_stack_top;
	uchar **p_stack_bottom;
	unsigned short *p_nonMax;//ָ��Ǽ���ֵ������ͼ��
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

			if (*(p_nonMax + y*cols + x) <= minVal)					// ��ǰ����С�ڼ���ֵ
			{
				*(p_flgImg + y*cols + x) = 0;						// ���Ǳ�Ե��
			}
			else if (*(p_nonMax + y*cols + x) > maxVal				// ��ǰ���ش��ڼ���ֵ
					&& (*(p_nonMax + (y - 1)*cols + x) <= maxVal)	//��һ�����ز��Ǳ�Ե��
					&& (*(p_nonMax + y*cols + x -1) <= maxVal)		// ǰһ�����ز��Ǳ�Ե��
					)	
			{
				
				*(p_flgImg + y*cols + x) = 2;						// ���Ϊ��Ե�㣨��㣩
				*p_stack_top = (p_flgImg + y*cols + x);				
				p_stack_top++;

			}
			else
			{
				*(p_flgImg + y*cols + x) = 1;						// �����Ǳ�Ե��
			}
	
		}

	}

	cv::imshow("flgImg", flgImg);

	//// ���±�ǣ��Կ����Ǳ�Ե�ĵ���д�����Ե׷�٣�
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

	////���ɱ�Եͼ��
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