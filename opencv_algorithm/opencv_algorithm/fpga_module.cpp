#include"include.h"




void fpga_module(cv::Mat srcImg)
{

#ifdef SOBEL
	cv::Mat sobel3x3_fpga0(srcImg.rows,srcImg.cols,CV_8U);
	cv::Mat sobel3x3_fpga1(srcImg.rows, srcImg.cols, CV_8U);
	//cv::Mat sobel5x5_fpga0(srcImg.rows, srcImg.cols, CV_8U);
	//cv::Mat sobel5x5_fpga1(srcImg.rows, srcImg.cols, CV_8U);
	//cv::Mat sobel7x7_fpga0(srcImg.rows, srcImg.cols, CV_8U);
	//cv::Mat sobel7x7_fpga1(srcImg.rows, srcImg.cols, CV_8U);



	sobel_3x3(srcImg, sobel3x3_fpga0, 0);
	sobel_3x3(srcImg, sobel3x3_fpga1, 1);
	//sobel_5x5(srcImg, sobel5x5_fpga0, 0);
	//sobel_5x5(srcImg, sobel5x5_fpga1, 1);
	//sobel_5x5(srcImg, sobel7x7_fpga0, 0);
	//sobel_7x7(srcImg, sobel7x7_fpga1, 1);




	cv::imshow("sobel3x3_fpga0", sobel3x3_fpga0);
	cv::imshow("sobel3x3_fpga1", sobel3x3_fpga1);
	//cv::imshow("sobel5x5_fpga0", sobel5x5_fpga0);
	//cv::imshow("sobel5x5_fpga1", sobel5x5_fpga1);
	//cv::imshow("sobel7x7_fpga0", sobel7x7_fpga0);
	//cv::imshow("sobel7x7_fpga1", sobel7x7_fpga1);
	cv::imwrite("fpga_sobel3x3_0.bmp", sobel3x3_fpga0);
	cv::imwrite("fpga_sobel3x3_1.bmp", sobel3x3_fpga1);
#endif 

#ifdef Laplacian
	cv::Mat gaus3x3(srcImg.rows, srcImg.cols, CV_8U);
	cv::Mat gaus5x5(srcImg.rows, srcImg.cols, CV_8U);
	cv::Mat fpgaGaus3x3(srcImg.rows, srcImg.cols, CV_8U);
	cv::Mat fpgaGaus5x5(srcImg.rows, srcImg.cols, CV_8U);

	cv::Mat laplance_gaus3x3(srcImg.rows, srcImg.cols, CV_8U);
	cv::Mat laplance_gaus5x5(srcImg.rows, srcImg.cols, CV_8U);
	

	fpga_gaus3x3(srcImg, fpgaGaus3x3);
	fpga_gaus5x5(srcImg, fpgaGaus5x5);


//	cv::GaussianBlur(srcImg, gaus3x3, cv::Size(3, 3), 2, 2);
//	cv::GaussianBlur(srcImg, gaus5x5, cv::Size(5, 5), 0, 0);
	

	
	
	laplacian_sharp(fpgaGaus3x3, laplance_gaus3x3);
	laplacian_sharp(fpgaGaus5x5, laplance_gaus5x5);

	cv::imshow("fpgaGaus3x3", fpgaGaus3x3);
	cv::imshow("fpgaGaus5x5", fpgaGaus5x5);
	cv::imshow("gaus3x3", gaus3x3);
	cv::imshow("gaus5x5", gaus5x5);
	cv::imshow("laplance_gaus3x3", laplance_gaus3x3);
	cv::imshow("laplance_gaus5x5", laplance_gaus5x5);
	img_compare(gaus3x3, fpgaGaus3x3);
#endif	

#ifdef Unsharp
	cv::Mat unsharpFpgaGaus5x5(srcImg.rows, srcImg.cols, CV_8U);
	cv::Mat unsharpMakingK_1(srcImg.rows, srcImg.cols, CV_8U);
	cv::Mat unsharpMakingK_4_5(srcImg.rows, srcImg.cols, CV_8U);
	cv::Mat unsharpMakingK_8 (srcImg.rows, srcImg.cols, CV_8U);
	 
	fpga_gaus5x5(srcImg, unsharpFpgaGaus5x5);
	unsharpMaking(srcImg, unsharpFpgaGaus5x5, unsharpMakingK_1, 1);
	unsharpMaking(srcImg, unsharpFpgaGaus5x5, unsharpMakingK_4_5, 4.5);
	unsharpMaking(srcImg, unsharpFpgaGaus5x5, unsharpMakingK_8, 8);

	cv::imshow("unsharpMakingK_1", unsharpMakingK_1);
	cv::imshow("unsharpMakingK_4_5", unsharpMakingK_4_5);
	cv::imshow("unsharpMakingK_8", unsharpMakingK_8);
	

#endif

#ifdef Gamma
	cv::Mat gamma1(srcImg.rows, srcImg.cols, CV_8U);
	cv::Mat gamma2(srcImg.rows, srcImg.cols, CV_8U);
	fpga_gamma(srcImg, gamma1,0.4);
	fpga_gamma(srcImg, gamma2, 4);

	cv::imshow("gamma1", gamma1);
	cv::imshow("gamma2", gamma2);



#endif

#ifdef HIST
	cv::Mat hist(srcImg.rows, srcImg.cols, CV_8U);
	cv::Mat hist2(srcImg.rows, srcImg.cols, CV_8U);
	localHist(srcImg, hist);
	localHist2(srcImg, hist2);
	cv::imshow("hist", hist);
	cv::imshow("hist2", hist2);

	img_compare(hist, hist2);
#endif

#ifdef DFT
	///*
	

	
	cv::Mat src = img_resize(srcImg);

	cv::Mat dft(src.rows, src.cols, CV_8U);
	cv::Mat Idft(src.rows, src.cols, CV_8U);
	Complex<double> *fft_img = new Complex<double>[src.cols * src.rows];
	

	int a = clock();
	
	fpga_FFT2(src, dft, fft_img);
	int b = clock();
	fpga_IFFT2(fft_img, Idft);


	printf("b - a = %d \r\n",b-a);
	//fpga_IDFT(dft, Idft);
	cv::imshow("src", src);
	cv::imshow("dft", dft);
	cv::imshow("Idft", Idft);
	img_compare(dft, Idft);
	//*/
	//fpga_fft2();
#endif

#ifdef RGB2GRAY

	cv::Mat img1_rgb2gray(srcImg.rows, srcImg.cols,CV_8U);
	cv::Mat img2_rgb2gray(srcImg.rows, srcImg.cols, CV_8U);
	cv::Mat img3_rgb2gray(srcImg.rows, srcImg.cols, CV_8U);
	fpga_rgb2gray(srcImg, img1_rgb2gray,0);
	fpga_rgb2gray(srcImg, img2_rgb2gray, 1);
	fpga_rgb2gray(srcImg, img3_rgb2gray, 2);

	cv::imshow("img1_rgb2gray", img1_rgb2gray);
	cv::imshow("img2_rgb2gray", img2_rgb2gray);
	cv::imshow("img3_rgb2gray", img3_rgb2gray);
#endif

#ifdef CANNY
	cv::imshow("cannyImg2", srcImg);
	cv::Mat dstImg(srcImg.rows, srcImg.cols, CV_8U);
	fpga_canny(srcImg, dstImg, 0, 200, 150);
#endif


#ifdef SIFT


	fpga_sift(srcImg);





#endif

}


