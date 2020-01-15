#ifndef FPGA_MODULE_H
#define FPGA_MODULE_H
#include"include.h"
#include"fpga_sift\fpga_sift.h"
void fpga_module(cv::Mat srcImg);
void sobel_3x3(cv::Mat src, cv::Mat dst, uchar sel);
void sobel_5x5(cv::Mat srcImg, cv::Mat dstImg, uchar sel);
void sobel_7x7(cv::Mat srcImg, cv::Mat dstImg, uchar sel);
void laplacian_sharp(cv::Mat srcImg, cv::Mat dstImg);
void fpga_gaus3x3(cv::Mat srcImg, cv::Mat dstImg);
void fpga_gaus5x5(cv::Mat srcImg, cv::Mat dstImg);
void img_compare(cv::Mat srcImg1, cv::Mat srcImg2);
void unsharpMaking(cv::Mat srcImg, cv::Mat gaus, cv::Mat dstImg, uchar k);
void fpga_gamma(cv::Mat srcImg, cv::Mat dstImg, float gamma);
void localHist(cv::Mat srcImg, cv::Mat dstImg);
void localHist2(cv::Mat srcImg, cv::Mat dstImg);
void fpga_DFT(cv::Mat srcImg, cv::Mat dstImg);
void fpga_IDFT(cv::Mat srcImg, cv::Mat dstImg);
void fpga_FFT2(cv::Mat srcImg, cv::Mat dstImg, Complex<double> *pOut);
cv::Mat img_resize(cv::Mat srcImg);
void fpga_IFFT2(Complex<double> *pInput, cv::Mat dstImg);
void fpga_rgb2gray(cv::Mat srcImg, cv::Mat dstImg, uchar sel);
void fpga_canny(cv::Mat src, cv::Mat dst, uchar sel, uchar maxVal, uchar minVal);


#endif