#ifndef OPENCV_MODULE_H
#define OPENCV_MODULE_H

#include"include.h"
#include"./sift/sift.h"
#include "./sift/imgfeatures.h"
#include"./sift/utils.h"
#include"./sift/kdtree.h"
#include"./sift/minpq.h"
#include"./sift/xform.h"



void opencv_module(cv::Mat srcImg, cv::Mat srcImg1);
void sobel_opencv(cv::Mat srcImg);
void opencv_sobel3x3(cv::Mat srcImg, cv::Mat dstImg);
void opencv_sobel5x5(cv::Mat srcImg);
void opencv_sobel7x7(cv::Mat srcImg);
void opencv_laplacian(cv::Mat srcImg);
void opencv_sobleSharp(cv::Mat srcImg, cv::Mat sobelImg);
void opencv_sift(cv::Mat srcImg1, cv::Mat srcImg2);
int siftfeat(IplImage* img);
int match(IplImage* img1, IplImage* img2);
void opencvDispMutPic(struct octvs_def oct, uchar group, uchar layer, std::string disName);
void opencvWriteMutPic(struct octvs_def oct, uchar group, uchar layer, std::string disName);
void draw_feat(cv::Mat srcImg, cv::Mat srcfeat);

#endif