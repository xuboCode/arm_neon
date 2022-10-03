#include <opencv2/opencv.hpp>
#include <arm_neon.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
using namespace cv;

int main( )
{
    Mat src = imread("../ggray.png", cv::IMREAD_UNCHANGED);
    size_t src_w, src_h;

    uchar* src_data = src.data;
    src_w = src.cols;
    src_h = src.rows;
    uchar **gbild = (uchar**)malloc(sizeof(char *) * src_h);	//定义二维数据
	for(int i = 0 ; i < src_h ; i++)
	{
		gbild[i] = src_data + i * src_w; 
	}

	//二维数组的使用
	uchar *gbild_out_ = (uchar*)malloc(sizeof(uchar) * (src_w * src_h + 16)); //a[5 + 列数 * 6]
	uchar **gbild_out = (uchar**)malloc(sizeof(uchar * ) * src_h);
	for(int i = 0 ; i < src_w ; i++)
	{
		gbild_out[i] = gbild_out_ + i * src_w;		//gbild_out[1][3]
	}


	uint8x16_t regin, mitt;	//定义NEON向量
	float16x8_t;

	for(int i = 0 ; i < src_h ; i++)
	{
		for(int ii = 0 ; ii < src_w ; ii += 16)
		{
			regin = vld1q_u8(&gbild[i][ii]);	//数据读取

			// mitt = vdupq_n_u8(50);
			// regin = vqsubq_u8(regin, mitt);
			
			vst1q_u8(&gbild_out[i][ii], regin);	//数据回写
		}
	}
    Mat dst(src.size(), src.type());
    dst.data = gbild_out_;
	imwrite("dst.png", dst);
	free(gbild);
	free(gbild_out_);
	free(gbild_out);

    return 0;
}