#ifndef FPGA_SIFT_H
#define FPGA_SIFT_H
#include"../include.h"


void fpga_sift(cv::Mat srcImg);

struct layers_def
{
	cv::Mat layersImg[6];

};

struct octvs_def
{
	layers_def octvsImg[5];

};

void get_hessian_3D(struct octvs_def srcImg, int octv, int intvl, int r, int c, cv::Mat hessian_3D);
void get_extrPoint(struct octvs_def srcImg, int octv, int intvl, struct octvs_def dstImg, struct octvs_def dstImg2);
void remove_edgeByHessian(cv::Mat srcImg, int r, int c, int curv_thr, cv::Mat dstImg);
void get_InvMatrix(cv::Mat src, cv::Mat InvMaxtrix);

#endif