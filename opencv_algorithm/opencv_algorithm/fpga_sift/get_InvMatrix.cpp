

#include"../include.h"
#define dType float
//LU ·Ö½âÇóÄæ¾ØÕó
void get_InvMatrix(cv::Mat src, cv::Mat Inv)
{

	int rows = src.rows;
	int cols = src.cols;

	cv::Mat L = cv::Mat::zeros(rows, cols,CV_32FC1);
	cv::Mat U = cv::Mat::zeros(rows, cols, CV_32FC1);
	cv::Mat L_inv = cv::Mat::zeros(rows, cols, CV_32FC1);// L Äæ¾ØÕó
	cv::Mat U_inv = cv::Mat::zeros(rows, cols, CV_32FC1);// UÄæ¾ØÕó





	//LU ·Ö½â
	//L21 = A21 / A11;
	//L31 = A31 / A11;
	//L32 = (A32A11 - A31A12) / (A22A11 - A21A12);

	//U22 = A22 - (A21 / A11)A12;
	//U23 = A23 - (A21 / A11)A13;
	//U33 = A33 - (A31 / A11)A13 - [(A32A11 - A31A12) / (A22A11 - A21A12)]*[(A23A11-A21A13)/A11]
	//https://blog.csdn.net/billbliss/article/details/78559289
	//https://wenku.baidu.com/view/7bc48b05a76e58fafab00352.html


	L.at<float>(0, 0) = 1;	
	L.at<float>(0, 1) = 0;	
	L.at<float>(0, 2) = 0;
	L.at<float>(1, 0) = src.at<float>(1, 0) / src.at<float>(0, 0);	
	L.at<float>(1, 1) = 1;	
	L.at<float>(1, 2) = 0;
	L.at<float>(2, 0) = src.at<float>(2, 0) / src.at<float>(0, 0);
	L.at<float>(2, 1) = (src.at<float>(2, 1)*src.at<float>(0, 0) - src.at<float>(2, 0)*src.at<float>(0, 1)) / (src.at<float>(1, 1)*src.at<float>(0, 0) - src.at<float>(1, 0)*src.at<float>(0, 1));
	L.at<float>(2, 2) = 1;




	U.at<float>(0, 0) = src.at<float>(0, 0);
	U.at<float>(0, 1) = src.at<float>(0, 1);
	U.at<float>(0, 2) = src.at<float>(0, 2);
	U.at<float>(1, 0) = 0;
	U.at<float>(1, 1) = src.at<float>(1, 1) - src.at<float>(1, 0)*src.at<float>(0, 1) / src.at<float>(0, 0);
	U.at<float>(1, 2) = src.at<float>(1, 2) - src.at<float>(1, 0)*src.at<float>(0, 2) / src.at<float>(0, 0);
	U.at<float>(2, 0) = 0;
	U.at<float>(2, 1) = 0;
	U.at<float>(2, 2) = src.at<float>(2, 2) - src.at<float>(2, 0)*src.at<float>(0, 2) / src.at<float>(0, 0) 
		- ((src.at<float>(2, 1)*src.at<float>(0, 0) - src.at<float>(2, 0)*src.at<float>(0, 1)) 
		 / (src.at<float>(1, 1)*src.at<float>(0, 0) - src.at<float>(1, 0)*src.at<float>(0, 1))
		 *((src.at<float>(1, 2)*src.at<float>(0, 0) - src.at<float>(1, 0)*src.at<float>(0, 2)) / src.at<float>(1, 0)*src.at<float>(0, 0)));




	printf("------src------- \r\n");
	for (uchar y = 0; y < 3; y++)
	{
		for (uchar x = 0; x < 3; x++)
		{
			printf("%f  ,", src.at<float>(y, x));
		}
		printf("\r\n");

	}


	printf("------L------- \r\n");
	for (uchar y = 0; y < 3;y++)
	{
		for (uchar x = 0; x < 3;x++)
		{
			printf("%f  ,", L.at<float>(y, x));
		}
		printf("\r\n");

	}

	printf("------U------- \r\n");
	for (uchar y = 0; y < 3; y++)
	{
		for (uchar x = 0; x < 3; x++)
		{
			printf("%f  ,", U.at<float>(y, x));
		}
		printf("\r\n");

	}


	//L Äæ¾ØÕó
	//L_inv00 = 1;
	//L_inv10 = -L10*L_inv00;L_inv11 = 1;
	//L_inv20 = -(L20*L_inv00 + L21*L_inv10);L_inv21 = -L21*L_inv11;L_inv22 = 1;

	L_inv.at<float>(0, 0) = 1;
	L_inv.at<float>(1, 0) = -(L.at<float>(1, 0) * L_inv.at<float>(0, 0));
	L_inv.at<float>(1, 1) = 1;
	L_inv.at<float>(2, 0) = -(L.at<float>(2, 0) * L_inv.at<float>(0, 0) + L.at<float>(2, 1) * L_inv.at<float>(1, 0));
	L_inv.at<float>(2, 1) = -(L.at<float>(2, 1) * L_inv.at<float>(1, 1));
	L_inv.at<float>(2, 2) = 1;


	//U Äæ¾ØÕó
	//U_inv00 = 1 / U00;	U_inv01 = -[(1 / U00)*U01*U_inv11];		U_inv02 = -[(1 / U00)*(U01*U_inv12 + U02*U_inv22)];
	//						U_inv11 = 1 / U11;						U_inv12 = -(1 / U11)*U12*U_inv22 ;
	//																U_inv22 = 1 / U22;

	U_inv.at<float>(0, 0) = 1 / U.at<float>(0, 0);
	U_inv.at<float>(1, 1) = 1 / U.at<float>(1, 1);
	U_inv.at<float>(2, 2) = 1 / U.at<float>(2, 2);

	U_inv.at<float>(0, 1) = -(1 / U.at<float>(0, 0))*(U.at<float>(0, 1) * U_inv.at<float>(1, 1));
	U_inv.at<float>(0, 2) = -(1 / U.at<float>(0, 0))*(U.at<float>(0, 1) * U_inv.at<float>(1, 2) + U.at<float>(0, 2) * U_inv.at<float>(2, 2));
	U_inv.at<float>(1, 2) = -(1 / U.at<float>(1, 1))*(U.at<float>(1, 2) * U_inv.at<float>(2, 2));



	printf("------L_inv------- \r\n");
	for (uchar y = 0; y < 3; y++)
	{
		for (uchar x = 0; x < 3; x++)
		{
			printf("%f  ,", L_inv.at<float>(y, x));
		}
		printf("\r\n");

	}

	printf("------U_inv------- \r\n");
	for (uchar y = 0; y < 3; y++)
	{
		for (uchar x = 0; x < 3; x++)
		{
			printf("%f  ,", U_inv.at<float>(y, x));
		}
		printf("\r\n");

	}

	// Çósrc µÄÄæ¾ØÕó
	Inv.at<float>(0, 0) = U_inv.at<float>(0, 0) + U_inv.at<float>(0, 1) * L_inv.at<float>(1, 0) + U_inv.at<float>(0, 2) * L_inv.at<float>(2, 0);
	Inv.at<float>(0, 1) = U_inv.at<float>(0, 1)  + U_inv.at<float>(0, 2) * L_inv.at<float>(2, 1);
	Inv.at<float>(0, 2) = U_inv.at<float>(0, 2) ;

	Inv.at<float>(1, 0) = U_inv.at<float>(1, 1) * L_inv.at<float>(1, 0) + U_inv.at<float>(1, 2) * L_inv.at<float>(2, 0);
	Inv.at<float>(1, 1) = U_inv.at<float>(1, 1) + U_inv.at<float>(1, 2) * L_inv.at<float>(2, 1);
	Inv.at<float>(1, 2) = U_inv.at<float>(1, 2) ;

	Inv.at<float>(2, 0) = U_inv.at<float>(2, 2) * L_inv.at<float>(2, 0);
	Inv.at<float>(2, 1) = U_inv.at<float>(2, 2) * L_inv.at<float>(2, 1);
	Inv.at<float>(2, 2) = U_inv.at<float>(2, 2) ;


	printf("------src_inv------- \r\n");
	for (uchar y = 0; y < 3; y++)
	{
		for (uchar x = 0; x < 3; x++)
		{
			printf("%f  ,", Inv.at<float>(y, x));
		}
		printf("\r\n");

	}




}


