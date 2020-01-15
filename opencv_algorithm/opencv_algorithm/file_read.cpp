#include"include.h"
//using namespace cv;


void file_read()
{
	FILE *fp = NULL;
	FILE *fp_wr = NULL;

	const int size = 307200;
	char buff1[size];

	char *p_src;
	char *p_dst;

	int ret;

	fp = fopen("srcImg_640x480.bin", "r");
	fp_wr = fopen("srcImg_640x480.txt", "w");

	fread(buff1, 1, size, (FILE*)fp);
	p_src = buff1;


	for (int i = 0, j = 0; i < size; i++, j++)
	{
		fprintf(fp_wr, "%x\n", *p_src);
		p_src++;
	}


	fclose(fp_wr);
	fclose(fp);

}


void write_imgData(std::string FileName,char * p_src, int size)
{


	FILE *fp_wr = NULL;
	const char *str = FileName.c_str();

	fp_wr = fopen(str, "w");

	fwrite(p_src, 1, size, fp_wr);

	fclose(fp_wr);


}
