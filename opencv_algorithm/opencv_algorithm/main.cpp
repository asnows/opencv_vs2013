//#include<opencv2\opencv.hpp>
#include"include.h"
//using namespace cv;


#if 1
int main()
{


	file_read();
	//return 0;
	cv::Mat srcImg = cv::imread("sift1.jpg",0);//3_26_a.tif  top_640x480 ps_test,sift.jpg,luowei.jpg
	cv::Mat srcImg1 = cv::imread("sift2.jpg", 0);//3_26_a.tif  top_640x480 ps_test,sift.jpg,luowei.jpg
	cv::imshow("src", srcImg);
	cv::imwrite("srcImg.bmp", srcImg);
	printf("srcImg.rows = %d, srcImg.cols = %d,srcImg.channel = %d  \r\n", srcImg.rows, srcImg.cols, srcImg.channels());
	printf("srcImg.step = %d \r\n", srcImg.step);
	//main_tt(srcImg);
	//return 0;

	cv::Mat test(srcImg.rows, srcImg.cols, CV_32FC1);
	cv::GaussianBlur(srcImg, test, cv::Size(3, 3), 1.6, 1.6);

	cv::imshow("test", test);
	cv::imwrite("test.bmp", test);





//	fpga_module(srcImg1);

//    opencv_module(srcImg, srcImg1);

	cv::waitKey(0);


	return 0;

}
#endif

