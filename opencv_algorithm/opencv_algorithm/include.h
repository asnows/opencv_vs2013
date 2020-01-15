#ifndef INCLUDE_H
#define INCLUDE_H
#include<opencv2\opencv.hpp>
#include<stdio.h>
#include<complex.h>
#include<time.h>
#include"string.h"
using namespace cv;
#define INPUT_IMG "E:\WorkSpace\images\1.bmp"

// head file decleared
#include"opencv_module.h"
#include"fpga_module.h"
#include"fpga_sift\fpga_sift.h"
#include"sift\sift.h"
int main_tt(cv::Mat srcImg);




//#define SOBEL
//#define Laplacian
//#define Unsharp
//#define Gamma
//#define HIST
//#define DFT
//#define RGB2GRAY
//#define CANNY
#define SIFT

// function decleared 
void sobel_3x3(cv::Mat src, cv::Mat dst, uchar sel);
void file_read();
void get_gaus_kernel(uchar size, float sigma, float * kernel);
void write_imgData(std::string FileName, char * p_src, int size);





#endif