#include "include.h"



void opencvDispMutPic(struct octvs_def oct, uchar group, uchar layer,std::string disName)
{

	uchar *p_src;
	uchar *p_dst;

	int rows = 0;
	int cols = 0;
	int col = 0;
	int row = 0;


	for (uchar i = 0; i < layer;i++)
	{
		cols += oct.octvsImg[0].layersImg[i].cols;
		cols += 4;

	}
	

	for (uchar i = 0; i < group; i++)
	{
		rows += oct.octvsImg[i].layersImg[0].rows;
		rows += 4;
	}

	//cv::Mat dispImg(rows, cols, oct.octvsImg[0].layersImg[0].type);
	cv::Mat dispImg = cv::Mat(rows, cols, CV_8UC1);
	p_dst = dispImg.data;
	
	for (uchar i = 0; i < group;i++)
	{
		
		for (int k = 0; k < oct.octvsImg[i].layersImg[0].rows;k++)
		{

			
			for (uchar j = 0; j < layer;j++)
			{
				
				col   = oct.octvsImg[i].layersImg[j].cols;
				p_src = oct.octvsImg[i].layersImg[j].data ;
				p_src += k*col;

				memcpy(p_dst, p_src, col);

				p_dst += oct.octvsImg[0].layersImg[0].cols ;
				p_dst += 4;

			}
		}

		p_dst += cols*4;
	}

	cv::imshow(disName, dispImg);



}

void opencvWriteMutPic(struct octvs_def oct, uchar group, uchar layer, std::string disName)
{
	std::string  string;
	std::string  str1;
	std::string  str2;

	std::stringstream stream;



	for (uchar o = 0; o < group; o++)
	{
		

		for (uchar i = 0; i < layer; i++)
		{

			char buf[1024];
			sprintf_s(buf, "_%d_%d.bmp",o, i);

			string = disName + buf;
			cv::imwrite(string, oct.octvsImg[o].layersImg[i]);
		}

	}




}