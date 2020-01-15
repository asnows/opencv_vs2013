//		-1, 0, 1			-1,-2,-1
// GX = -2, 0, 2      GY =   0, 0, 0
//		-1, 0, 1			 1, 2, 1

//		   (x-1,y-1),( x, y-1),(x+1,y-1)
//kernel = (x-1,y  ),( x, y  ),(x+1,y  )
//		   (x-1,y+1),( x, y+1),(x+1,y+1)

#include"include.h"
//sel = 0£¬Ë«±ßÔµÊä³ö£¬
//sel = 1£¬µ«±ßÔµÊä³ö£¬
void sobel_3x3(cv::Mat src, cv::Mat dst, uchar sel)
{

	unsigned int rows = src.rows;
 	unsigned int cols = src.cols;
 	unsigned int x1,x2,y1,y2,Gout;
 	unsigned int x_abs,y_abs;


	

 	for(unsigned int y = 2; y< rows -1; y++)
 	{
		for (unsigned int x = 2; x < cols - 1; x++)
 		{
 			x1 = src.at<unsigned char>(y - 1,x - 1)
 			   + src.at<unsigned char>(y	,x - 1) * 2
			   + src.at<unsigned char>(y + 1,x - 1) ;

 			x2 = src.at<unsigned char>(y - 1,x + 1)
 			   + src.at<unsigned char>(y    ,x + 1) * 2
			   + src.at<unsigned char>(y + 1,x + 1) ;

 			y1 = src.at<unsigned char>(y - 1,x - 1)
 			   + src.at<unsigned char>(y - 1,x    ) * 2
			   + src.at<unsigned char>(y - 1,x + 1) ;

 			y2 = src.at<unsigned char>(y + 1,x - 1)
 			   + src.at<unsigned char>(y + 1,x    ) * 2
			   + src.at<unsigned char>(y + 1,x + 1) ;

 			if(x1 > x2)
 			{
				if (sel)
				{
					x_abs = 0;
				}
				else
				{
					x_abs = x1 - x2;
				}

				
 			}
 			else
 			{
 				x_abs = x2 - x1;
 			}

 			if(y1 > y2)
 			{
				if (sel)
				{
					y_abs = 0;
				}
				else
				{
					y_abs = y1 - y2;
				}
 			}
 			else
 			{
 				y_abs = y2 - y1;
 			}

 			Gout = x_abs + y_abs;
 			if(Gout > 255)
 			{
 				Gout = 255;
 			}

			dst.at<unsigned char>(y, x) = Gout;

 		}

 	}

}


unsigned int get_abs(unsigned int valu1, unsigned int valu2, uchar sel)
{
	unsigned int reval;

	if (valu1 > valu2)
	{
		if (sel)
		{
			reval = 0;
		}
		else
		{
			reval = valu1 - valu2;
		}
	}
	else
	{
		reval = valu2 - valu1;
	}


	return reval;


}




//		{ -1, -2, 0, 2, 1 },
//		{ -4, -8, 0, 8, 4 },   
//gx =	{ -6, -12,0, 12,6 },
//		{ -4, -8, 0, 8, 4 },
//		{ -1, -2, 0, 2, 1 }

//		{ -1, -4, -6, -4, -1 },
//		{ -2, -8, -12,-8, -2 },
//gy =	{  0,  0,  0,  0,  0 },
//		{  2,  8,  12, 8,  2 },
//		{  1,  4,  6,  4,  1 }


void sobel_5x5(cv::Mat srcImg, cv::Mat dstImg,uchar sel)
{
	unsigned int rows = srcImg.rows;
	unsigned int cols = srcImg.cols;

	unsigned int x1_0, x1_1, x2_0, x2_1, x4_0, x4_1, x6_0, x6_1, x8_0, x8_1, x12_0, x12_1;
	unsigned int y1_0, y1_1, y2_0, y2_1, y4_0, y4_1, y6_0, y6_1, y8_0, y8_1, y12_0, y12_1;
	unsigned int x1_abs,x2_abs,x4_abs, x6_abs, x8_abs, x12_abs;
	unsigned int y1_abs, y2_abs, y4_abs, y6_abs, y8_abs, y12_abs;
	unsigned int Gx,Gy,Gout;


	for (unsigned int y = 3; y < rows - 3; y++)
	{
		for (unsigned int x = 3; x < cols - 3; x++)
		{

			x1_0 = srcImg.at<unsigned char>(y - 2, x - 2)
				 + srcImg.at<unsigned char>(y + 2, x - 2);
			x1_1 = srcImg.at<unsigned char>(y - 2, x + 2)
				 + srcImg.at<unsigned char>(y + 2, x + 2);

			x2_0 = srcImg.at<unsigned char>(y - 2, x - 1) * 2
				 + srcImg.at<unsigned char>(y + 2, x - 1) * 2;
			x2_1 = srcImg.at<unsigned char>(y - 2, x + 1) * 2
				 + srcImg.at<unsigned char>(y + 2, x + 1) * 2;

			x4_0 = srcImg.at<unsigned char>(y - 1, x - 2) * 4
				 + srcImg.at<unsigned char>(y + 1, x - 2) * 4;
			x4_1 = srcImg.at<unsigned char>(y - 1, x + 2) * 4
				 + srcImg.at<unsigned char>(y + 1, x + 2) * 4;

			x6_0 = srcImg.at<unsigned char>(y    , x - 2) * 6;
			x6_1 = srcImg.at<unsigned char>(y    , x + 2) * 6;

			x8_0 = srcImg.at<unsigned char>(y - 1, x - 1) * 8
				 + srcImg.at<unsigned char>(y + 1, x - 1) * 8;
			x8_1 = srcImg.at<unsigned char>(y - 1, x + 1) * 8
				 + srcImg.at<unsigned char>(y + 1, x + 1) * 8;

			x12_0 = srcImg.at<unsigned char>(y	 , x - 1) * 12;
			x12_1 = srcImg.at<unsigned char>(y   , x + 1) * 12;

			// 
			y1_0 = srcImg.at<unsigned char>(y - 2, x - 2)
				 + srcImg.at<unsigned char>(y - 2, x + 2);
			y1_1 = srcImg.at<unsigned char>(y + 2, x - 2)
				 + srcImg.at<unsigned char>(y + 2, x + 2);

			y2_0 = srcImg.at<unsigned char>(y - 1, x - 2) * 2
				 + srcImg.at<unsigned char>(y - 1, x + 2) * 2;
			y2_1 = srcImg.at<unsigned char>(y + 1, x - 2) * 2
				 + srcImg.at<unsigned char>(y + 1, x + 2) * 2;

			y4_0 = srcImg.at<unsigned char>(y - 2, x - 1) * 4
				 + srcImg.at<unsigned char>(y - 2, x + 1) * 4;
			y4_1 = srcImg.at<unsigned char>(y + 2, x - 1) * 4
				 + srcImg.at<unsigned char>(y + 2, x + 1) * 4;

			y6_0 = srcImg.at<unsigned char>(y - 2, x) * 6;
			y6_1 = srcImg.at<unsigned char>(y + 2, x) * 6;

			y8_0 = srcImg.at<unsigned char>(y - 1, x - 1) * 8
				 + srcImg.at<unsigned char>(y - 1, x + 1) * 8;
			y8_1 = srcImg.at<unsigned char>(y + 1, x - 1) * 8
				 + srcImg.at<unsigned char>(y + 1, x + 1) * 8;

			y12_0 = srcImg.at<unsigned char>(y - 1, x) * 12;
			y12_1 = srcImg.at<unsigned char>(y + 1, x) * 12;


			x1_abs = get_abs(x1_0, x1_1,sel);
			x2_abs = get_abs(x2_0, x2_1, sel);
			x4_abs = get_abs(x4_0, x4_1, sel);
			x6_abs = get_abs(x6_0, x6_1, sel);
			x8_abs = get_abs(x8_0, x8_1, sel);
			x12_abs = get_abs(x12_0, x12_1, sel);


			y1_abs = get_abs(y1_0, y1_1, sel);
			y2_abs = get_abs(y2_0, y2_1, sel);
			y4_abs = get_abs(y4_0, y4_1, sel);
			y6_abs = get_abs(y6_0, y6_1, sel);
			y8_abs = get_abs(y8_0, y8_1, sel);
			y12_abs = get_abs(y12_0, y12_1, sel);


			Gx = x1_abs + x2_abs + x4_abs + x6_abs + x8_abs + x12_abs;
			Gy = y1_abs + y2_abs + y4_abs + y6_abs + y8_abs + y12_abs;

			Gout = Gx + Gy;

			if (Gout > 255)
			{
				Gout = 255;
			}

			dstImg.at<unsigned char>(y, x) = Gout;


		}
	}
}




void sobel_7x7(cv::Mat srcImg,cv::Mat dstImg,uchar sel)
{
	unsigned int rows = srcImg.rows;
	unsigned int cols = srcImg.cols;

	unsigned int x1_0, x1_1, x4_0, x4_1, x5_0, x5_1, x6_0, x6_1, x15_0, x15_1, x20_0, x20_1, 
				 x24_0, x24_1, x30_0, x30_1, x60_0, x60_1, x75_0, x75_1, x80_0, x80_1, x100_0, x100_1;
	unsigned int y1_0, y1_1, y4_0, y4_1, y5_0, y5_1, y6_0, y6_1, y15_0, y15_1, y20_0, y20_1,
				 y24_0, y24_1, y30_0, y30_1, y60_0, y60_1, y75_0, y75_1, y80_0, y80_1, y100_0, y100_1;


	unsigned int x1_abs, x4_abs, x5_abs, x6_abs, x15_abs, x20_abs, x24_abs, x30_abs, x60_abs, x75_abs, x80_abs, x100_abs;
	unsigned int y1_abs, y4_abs, y5_abs, y6_abs, y15_abs, y20_abs, y24_abs, y30_abs, y60_abs, y75_abs, y80_abs, y100_abs;

	unsigned int Gx, Gy, Gout;




	for (unsigned int y = 4; y < rows - 4; y++)
	{
		for (unsigned int x = 4; x < cols - 4; x++)
		{
			//x
			x1_0 = srcImg.at<unsigned char>(y - 3, x - 3)
				 + srcImg.at<unsigned char>(y + 3, x - 3);
			x1_1 = srcImg.at<unsigned char>(y - 3, x + 3)
				+ srcImg.at<unsigned char>(y + 3, x + 3);

			x4_0 = srcImg.at<unsigned char>(y - 3, x - 2) * 4
				 + srcImg.at<unsigned char>(y + 3, x - 2) * 4; 
			x4_1 = srcImg.at<unsigned char>(y - 3, x + 2) * 4
				 + srcImg.at<unsigned char>(y + 3, x + 2) * 4;

			x5_0 = srcImg.at<unsigned char>(y - 3, x - 1) * 5
				 + srcImg.at<unsigned char>(y + 3, x - 1) * 5;
			x5_1 = srcImg.at<unsigned char>(y - 3, x + 1) * 5
				 + srcImg.at<unsigned char>(y + 3, x + 1) * 5;

			x6_0 = srcImg.at<unsigned char>(y - 2, x - 3) * 6
				 + srcImg.at<unsigned char>(y + 2, x - 3) * 6;
			x6_1 = srcImg.at<unsigned char>(y - 2, x + 3) * 6
				 + srcImg.at<unsigned char>(y + 2, x + 3) * 6;

			x15_0 = srcImg.at<unsigned char>(y - 1, x - 3) * 15
				  + srcImg.at<unsigned char>(y + 1, x - 3) * 15;
			x15_1 = srcImg.at<unsigned char>(y - 1, x + 3) * 15
				  + srcImg.at<unsigned char>(y + 1, x + 3) * 15;

			x20_0 = srcImg.at<unsigned char>(y, x - 3) * 20;
			x20_1 = srcImg.at<unsigned char>(y, x + 3) * 20;

			x24_0 = srcImg.at<unsigned char>(y - 2, x - 2) * 24
				  + srcImg.at<unsigned char>(y + 2, x - 2) * 24;
			x24_1 = srcImg.at<unsigned char>(y - 2, x + 2) * 24
				  + srcImg.at<unsigned char>(y + 2, x + 2) * 24;

			x30_0 = srcImg.at<unsigned char>(y - 2, x - 1) * 30
				  + srcImg.at<unsigned char>(y + 2, x - 1) * 30;
			x30_1 = srcImg.at<unsigned char>(y - 2, x + 1) * 30
				  + srcImg.at<unsigned char>(y + 2, x + 1) * 30;

			x60_0 = srcImg.at<unsigned char>(y - 1, x - 2) * 60
				  + srcImg.at<unsigned char>(y + 1, x - 2) * 60;
			x60_1 = srcImg.at<unsigned char>(y - 1, x + 2) * 60
				  + srcImg.at<unsigned char>(y + 1, x + 2) * 60;

			x75_0 = srcImg.at<unsigned char>(y - 1, x - 1) * 75
				  + srcImg.at<unsigned char>(y + 1, x - 1) * 75;
			x75_1 = srcImg.at<unsigned char>(y - 1, x + 1) * 75
				  + srcImg.at<unsigned char>(y + 1, x + 1) * 75;

			x80_0 = srcImg.at<unsigned char>(y, x - 2) * 80;
			x80_1 = srcImg.at<unsigned char>(y, x + 2) * 80;

			x100_0 = srcImg.at<unsigned char>(y, x - 1) * 100;
			x100_1 = srcImg.at<unsigned char>(y, x + 1) * 100;


			//y

			y1_0 = srcImg.at<unsigned char>(y - 3, x - 3)
				 + srcImg.at<unsigned char>(y - 3, x + 3);
			y1_1 = srcImg.at<unsigned char>(y + 3, x - 3)
				 + srcImg.at<unsigned char>(y + 3, x + 3);

			y4_0 = srcImg.at<unsigned char>(y - 2, x - 3) * 4
				 + srcImg.at<unsigned char>(y - 2, x + 3) * 4;
			y4_1 = srcImg.at<unsigned char>(y + 2, x - 3) * 4
				 + srcImg.at<unsigned char>(y + 2, x + 3) * 4;

			y5_0 = srcImg.at<unsigned char>(y - 1, x - 3) * 5
				 + srcImg.at<unsigned char>(y - 1, x + 3) * 5;
			y5_1 = srcImg.at<unsigned char>(y + 1, x - 3) * 5
				 + srcImg.at<unsigned char>(y + 1, x + 3) * 5;

			y6_0 = srcImg.at<unsigned char>(y - 3, x - 2) * 6
				 + srcImg.at<unsigned char>(y - 3, x + 2) * 6;
			y6_1 = srcImg.at<unsigned char>(y + 3, x - 2) * 6
				 + srcImg.at<unsigned char>(y + 3, x + 2) * 6;

			y15_0 = srcImg.at<unsigned char>(y - 3, x - 1) * 15
				  + srcImg.at<unsigned char>(y - 3, x + 1) * 15;
			y15_1 = srcImg.at<unsigned char>(y + 3, x - 1) * 15
				  + srcImg.at<unsigned char>(y + 3, x + 1) * 15;

			y20_0 = srcImg.at<unsigned char>(y - 3, x) * 20;
			y20_1 = srcImg.at<unsigned char>(y + 3, x) * 20;

			y24_0 = srcImg.at<unsigned char>(y - 2, x - 2) * 24
				  + srcImg.at<unsigned char>(y - 2, x + 2) * 24;
			y24_1 = srcImg.at<unsigned char>(y + 2, x - 2) * 24
				  + srcImg.at<unsigned char>(y + 2, x + 2) * 24;

			y30_0 = srcImg.at<unsigned char>(y - 1, x - 2) * 30
				  + srcImg.at<unsigned char>(y - 1, x + 2) * 30;
			y30_1 = srcImg.at<unsigned char>(y + 1, x - 2) * 30
				  + srcImg.at<unsigned char>(y + 1, x + 2) * 30;

			y60_0 = srcImg.at<unsigned char>(y - 2, x - 1) * 60
				  + srcImg.at<unsigned char>(y - 2, x + 1) * 60;
			y60_1 = srcImg.at<unsigned char>(y + 2, x - 1) * 60
				  + srcImg.at<unsigned char>(y + 2, x + 1) * 60;

			y75_0 = srcImg.at<unsigned char>(y - 1, x - 1) * 75
				  + srcImg.at<unsigned char>(y - 1, x + 1) * 75;
			y75_1 = srcImg.at<unsigned char>(y + 1, x - 1) * 75
				  + srcImg.at<unsigned char>(y + 1, x + 1) * 75;

			y80_0 = srcImg.at<unsigned char>(y - 2, x) * 80;
			y80_1 = srcImg.at<unsigned char>(y + 2, x) * 80;

			y100_0 = srcImg.at<unsigned char>(y - 1, x) * 100;
			y100_1 = srcImg.at<unsigned char>(y + 1, x) * 100;


			x1_abs = get_abs(x1_0, x1_1, sel);
			x4_abs = get_abs(x4_0, x4_1, sel);
			x5_abs = get_abs(x5_0, x5_1, sel);
			x6_abs = get_abs(x6_0, x6_1, sel);
			x15_abs = get_abs(x15_0, x15_1, sel);
			x20_abs = get_abs(x20_0, x20_1, sel);
			x24_abs = get_abs(x24_0, x24_1, sel);
			x30_abs = get_abs(x30_0, x30_1, sel);
			x60_abs = get_abs(x60_0, x60_1, sel);
			x75_abs = get_abs(x75_0, x75_1, sel);
			x80_abs = get_abs(x80_0, x80_1, sel);
			x100_abs = get_abs(x100_0, x100_1, sel);


			y1_abs = get_abs(y1_0, y1_1, sel);
			y4_abs = get_abs(y4_0, y4_1, sel);
			y5_abs = get_abs(y5_0, y5_1, sel);
			y6_abs = get_abs(y6_0, y6_1, sel);
			y15_abs = get_abs(y15_0, y15_1, sel);
			y20_abs = get_abs(y20_0, y20_1, sel);
			y24_abs = get_abs(y24_0, y24_1, sel);
			y30_abs = get_abs(y30_0, y30_1, sel);
			y60_abs = get_abs(y60_0, y60_1, sel);
			y75_abs = get_abs(y75_0, y75_1, sel);
			y80_abs = get_abs(y80_0, y80_1, sel);
			y100_abs = get_abs(y100_0, y100_1, sel);

			Gx = x1_abs + x4_abs + x5_abs + x6_abs + x15_abs + x20_abs 
			  + x24_abs + x30_abs + x60_abs + x75_abs + x80_abs + x100_abs;

			Gy = y1_abs + y4_abs + y5_abs + y6_abs + y15_abs + y20_abs
				+ y24_abs + y30_abs + y60_abs + y75_abs + y80_abs + y100_abs;

			Gout = Gx + Gy;

			if (Gout > 255)
			{
				Gout = 255;
			}

			dstImg.at<unsigned char>(y, x) = Gout;



		}
	
	
	
	
	}



}