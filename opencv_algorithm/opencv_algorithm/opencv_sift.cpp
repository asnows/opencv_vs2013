#include"include.h"
#define KDTREE_BBF_MAX_NN_CHKS 200

/* threshold on squared ratio of distances between NN and 2nd NN */
#define NN_SQ_DIST_RATIO_THR 0.49





void find_sift_features(IplImage* img)
{
	struct feature* feat1;
	int num;

	num =sift_features(img, &feat1);
	draw_features(img, feat1, num);

	cvShowImage("features", img);
	printf("num = %d \r\n", num);




}

//void sift_match(IplImage* img1, IplImage* img2)
//{
//	struct feature* feat,* feat1, *feat2;
//	struct kd_node* kd_root;
//	struct feature** nbrs;
//	CvPoint pt1, pt2;
//
//	double d0, d1;
//	int n1, n2, k, i, m = 0;
//
//	IplImage* stacked = cvCreateImage(cvSize(MAX(img1->width, img2->width),
//		img1->height + img2->height),
//		IPL_DEPTH_8U, 3);
//	stacked = stack_imgs(img1, img2);
//
//	n1 = sift_features(img1, &feat1);
//	n2 = sift_features(img2, &feat2);
//
//	kd_root = kdtree_build(feat2, n2);
//
//	for (i = 0; i < n1; i++)
//	{
//		feat = feat1 + i;
//		k = kdtree_bbf_knn(kd_root, feat, 2, &nbrs, KDTREE_BBF_MAX_NN_CHKS);
//		if (k == 2)
//		{
//			d0 = descr_dist_sq(feat, nbrs[0]);
//			d1 = descr_dist_sq(feat, nbrs[1]);
//			if (d0 < d1 * NN_SQ_DIST_RATIO_THR)
//			{
//				pt1 = cvPoint(cvRound(feat->x), cvRound(feat->y));
//				pt2 = cvPoint(cvRound(nbrs[0]->x), cvRound(nbrs[0]->y));
//				pt2.y += img1->height;
//				cvLine(stacked, pt1, pt2, CV_RGB(255, 0, 255), 1, 8, 0);
//				m++;
//				feat1[i].fwd_match = nbrs[0];
//			}
//		}
//		free(nbrs);
//	}
//
//	cvShowImage("stacked", stacked);
//
//	cvReleaseImage(&stacked);
//	cvReleaseImage(&img1);
//	cvReleaseImage(&img2);
//	kdtree_release(kd_root);
//	free(feat1);
//	free(feat2);
//}

void opencv_sift(cv::Mat srcImg1, cv::Mat srcImg2)
{


	IplImage* img1 = &IplImage(srcImg1);
	IplImage* img2 = &IplImage(srcImg2);
	find_sift_features(img1);

	//sift_match(img1, img2);





}
