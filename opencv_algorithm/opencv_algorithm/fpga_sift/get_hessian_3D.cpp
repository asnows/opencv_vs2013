//#include"fpga_sift.h"

/*
Computes the 3D Hessian matrix for a pixel in the DoG scale space pyramid.

@param dog_pyr DoG scale space pyramid
@param octv pixel's octave in dog_pyr
@param intvl pixel's interval in octv
@param r pixel's image row
@param c pixel's image col

@return Returns the Hessian matrix (below) for pixel I as a CvMat*

/ Ixx  Ixy  Ixs \ <BR>
| Ixy  Iyy  Iys | <BR>
\ Ixs  Iys  Iss /
*/

#include"../include.h"
void get_hessian_3D(struct octvs_def srcImg, int octv, int intvl, int r, int c , cv::Mat hessian_3D)
{
	float  v, dxx, dyy, dss, dxy, dxs, dys;

	v = srcImg.octvsImg[octv].layersImg[intvl].at<float>(r,c);

	dxx = srcImg.octvsImg[octv].layersImg[intvl].at<float>(r, c + 1) 
		+ srcImg.octvsImg[octv].layersImg[intvl].at<float>(r, c - 1)
		- 2 * v;

	dyy = srcImg.octvsImg[octv].layersImg[intvl].at<float>(r + 1, c) 
		+ srcImg.octvsImg[octv].layersImg[intvl].at<float>(r - 1, c)
		- 2 * v;

	dss = srcImg.octvsImg[octv].layersImg[intvl + 1].at<float>(r, c) 
		+ srcImg.octvsImg[octv].layersImg[intvl - 1].at<float>(r, c)
		- 2 * v;

	dxy = (srcImg.octvsImg[octv].layersImg[intvl].at<float>(r + 1, c + 1)
		- srcImg.octvsImg[octv].layersImg[intvl].at<float>(r + 1, c - 1)
		- srcImg.octvsImg[octv].layersImg[intvl].at<float>(r - 1, c + 1)
		+ srcImg.octvsImg[octv].layersImg[intvl].at<float>(r - 1, c - 1)) / 4.0;

	dxs = (srcImg.octvsImg[octv].layersImg[intvl + 1].at<float>(r, c + 1)
		- srcImg.octvsImg[octv].layersImg[intvl + 1].at<float>(r, c - 1)
		- srcImg.octvsImg[octv].layersImg[intvl - 1].at<float>(r, c + 1)
		+ srcImg.octvsImg[octv].layersImg[intvl - 1].at<float>(r, c - 1)) / 4.0;

	dys = (srcImg.octvsImg[octv].layersImg[intvl + 1].at<float>(r + 1, c)
		- srcImg.octvsImg[octv].layersImg[intvl + 1].at<float>(r-1, c)
		- srcImg.octvsImg[octv].layersImg[intvl - 1].at<float>(r+1, c)
		+ srcImg.octvsImg[octv].layersImg[intvl - 1].at<float>(r-1, c)) / 4.0;

	hessian_3D.at<float>(0, 0) = dxx; hessian_3D.at<float>(0, 1) = dxy; hessian_3D.at<float>(0, 2) = dxs;
	hessian_3D.at<float>(1, 0) = dxy; hessian_3D.at<float>(1, 1) = dyy; hessian_3D.at<float>(1, 2) = dys;
	hessian_3D.at<float>(2, 0) = dxs; hessian_3D.at<float>(2, 1) = dys; hessian_3D.at<float>(2, 2) = dss;

	//printf("------get_hessian_3D------ \r\n");
	//for (uchar i = 0; i < 3;i++)
	//{
	//	
	//	for (uchar j = 0; j < 3;j++)
	//	{
	//		printf("%f	,", hessian_3D.at<float>(i, j));
	//	}
	//	printf("\r\n");
	//}
	//printf("------------------------- \r\n");




}