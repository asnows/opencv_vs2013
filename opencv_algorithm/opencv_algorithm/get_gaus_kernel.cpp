#include "include.h"
// 参考网址 https://blog.csdn.net/farmwang/article/details/74452750
//g(x,y) = (1/2*π²*σ) * e-(x²+y²)/2σ²
void get_gaus_kernel(uchar size, float sigma,float * kernel)
{
	float total_f = 0;
	float PI = 3.1415926;
	int center = size / 2;
	

	for ( int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			
			kernel[y*size + x] = (1 / (2 * PI*sigma*sigma))*exp(-(((x - center)*(x - center) + (y - center)*(y - center)) / (2 * sigma*sigma))) ;
			total_f += kernel[y*size + x];
			//printf("%f ,", kernel[y*size + x]);

		}
		//printf("\r\n");
		//printf("\r\n");
	}


	printf("-------------------\r\n");
	for (uchar y = 0; y < size; y++)
	{
		for (uchar x = 0; x < size; x++)
		{
			
			kernel[y*size + x] = kernel[y*size + x] / total_f;

			printf("%f ,", kernel[y*size + x] *1024);
		}
		printf("\r\n");
		printf("\r\n");
	}

	//printf("total_f = %f ,", total_f);






}


