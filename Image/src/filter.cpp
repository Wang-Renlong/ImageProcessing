

#include "../include/filter.h"

#include "../base/pixel.h"
#include "../include/window.h"

//桶排序-私有函数
/*
@src 输入数据
@len 输入数据长度
*/
void inline filter::pix_sort(unsigned char* src, int len)
{
	unsigned char heap[256];
	int i, j, k;
	for (i = 0; i<256; i++)
		heap[i] = 0;
	for (i = 0; i<len; i++)
	{
		heap[src[i]]++;
	}
	k = 0;
	for (i = 0; i<256; i++)
	{
		for (j = 0; j<heap[i]; j++)
			src[k + j] = i;
		k += heap[i];
	}
}

void filter::midGRAY(Pixel* src, Pixel* dst, Window& wnd)
{
	int wnd_width, wnd_height, half_wnd_width, half_wnd_height;
	int width, height;
	int i, j, in_i, in_j;
	int pix_temp_i;
	unsigned int temp0;
	unsigned char *pix_temp = NULL;

	wnd_width = wnd.Width();
	wnd_height = wnd.Height();
	half_wnd_width = wnd_width / 2;
	half_wnd_height = wnd_height / 2;
	width = src->Width();
	height = src->Height();

	pix_temp = (unsigned char*)malloc(sizeof(unsigned char)*wnd_width*wnd_height);
	if ((!pix_temp))
	{
		printf("memory lack!\n");
		return;
	}

	dst->SetSize(width, height);

	//循环匹配
	//图像坐标扫描
	for (i = 0; i<height; i++)
	{
		for (j = 0; j<width; j++)
		{
			//降噪核匹配
			pix_temp_i = 0;
			for (in_i = 0 - half_wnd_height; in_i <= half_wnd_height; in_i++)
			{
				for (in_j = 0 - half_wnd_width; in_j <= half_wnd_width; in_j++)
				{
					//对没有越界的部分统计
					if (i + in_i >= 0 && i + in_i<height && j + in_j >= 0 && j + in_j<width)
					{
						//temp0 = (i+in_i)*width+j+in_j;
						pix_temp[pix_temp_i] = (*src)[(i + in_i)*width + j + in_j].g;
						pix_temp_i++;
					}
				}
			}
			//排序求中值
			pix_sort(pix_temp, pix_temp_i);
			temp0 = pix_temp[pix_temp_i / 2];
			(*dst)[i*width + j].b = temp0;
			(*dst)[i*width + j].g = temp0;
			(*dst)[i*width + j].r = temp0;
			(*dst)[i*width + j].a = 0;

		}//end for(j<width)
	}//end for(i<height)
	if (pix_temp)
		free(pix_temp);
}

void filter::mid(Pixel* src, Pixel* dst, Window& wnd)
{
	int wnd_width, wnd_height, half_wnd_width, half_wnd_height;
	int width, height;
	int i, j, in_i, in_j;
	int pix_temp_i;
	unsigned int temp0;
	unsigned char *pix_tempR = NULL, *pix_tempG = NULL, *pix_tempB = NULL;// = (unsigned char*)malloc(sizeof(unsigned char)*wnd_width*wnd_height);

	wnd_width = wnd.Width();
	wnd_height = wnd.Height();
	half_wnd_width = wnd_width / 2;
	half_wnd_height = wnd_height / 2;
	width = src->Width();
	height = src->Height();

	pix_tempR = (unsigned char*)malloc(sizeof(unsigned char)*wnd_width*wnd_height);
	pix_tempG = (unsigned char*)malloc(sizeof(unsigned char)*wnd_width*wnd_height);
	pix_tempB = (unsigned char*)malloc(sizeof(unsigned char)*wnd_width*wnd_height);
	if ((!pix_tempR) || (!pix_tempG) || (!pix_tempB))
	{
		if (pix_tempR)
			free(pix_tempR);
		if (pix_tempG)
			free(pix_tempG);
		if (pix_tempB)
			free(pix_tempB);
		printf("memory lack!\n");
		return;
	}

	dst->SetSize(width, height);

	//printf("start filting\n");
	//循环匹配
	//图像坐标扫描
	for (i = 0; i<height; i++)
	{
		for (j = 0; j<width; j++)
		{
			//降噪核匹配
			pix_temp_i = 0;
			for (in_i = 0 - half_wnd_height; in_i <= half_wnd_height; in_i++)
			{
				for (in_j = 0 - half_wnd_width; in_j <= half_wnd_width; in_j++)
				{
					//对没有越界的部分统计
					if (i + in_i >= 0 && i + in_i<height && j + in_j >= 0 && j + in_j<width)
					{
						temp0 = (i + in_i)*width + j + in_j;
						pix_tempB[pix_temp_i] = (*src)[temp0].b;
						pix_tempG[pix_temp_i] = (*src)[temp0].g;
						pix_tempR[pix_temp_i] = (*src)[temp0].r;
						pix_temp_i++;
					}
				}
			}
			//排序求中值
			pix_sort(pix_tempB, pix_temp_i);
			(*dst)[i*width + j].b = pix_tempB[pix_temp_i / 2];
			pix_sort(pix_tempG, pix_temp_i);
			(*dst)[i*width + j].g = pix_tempG[pix_temp_i / 2];
			pix_sort(pix_tempR, pix_temp_i);
			(*dst)[i*width + j].r = pix_tempR[pix_temp_i / 2];
			(*dst)[i*width + j].a = 0;

		}//end for(j<width)
	}//end for(i<height)
	if (pix_tempR)
		free(pix_tempR);
	if (pix_tempG)
		free(pix_tempG);
	if (pix_tempB)
		free(pix_tempB);
}

void filter::avg(Pixel* src, Pixel* dst, Window& wnd)
{
	int wnd_width, wnd_height, half_wnd_width, half_wnd_height;
	int width, height;
	int i, j, in_i, in_j, a, b;
	unsigned int temp0;
	unsigned int pix_tempR, pix_tempG, pix_tempB;
	int *kernel, kernel_sum, kernel_len;

	wnd_width = wnd.Width();
	wnd_height = wnd.Height();
	half_wnd_width = wnd_width / 2;
	half_wnd_height = wnd_height / 2;
	width = src->Width();
	height = src->Height();
	kernel = wnd.Kernel();
	kernel_len = wnd_width*wnd_height;
	kernel_sum = 0;
	for (i = 0; i<kernel_len; i++)
		kernel_sum += kernel[i];

	dst->SetSize(width, height);
	//坐标临时变量, 用于计算核坐标时快速计算
	temp0 = half_wnd_height*wnd_width + half_wnd_width;

	//循环匹配
	//图像坐标扫描
	for (i = 0; i<height; i++)
	{
		for (j = 0; j<width; j++)
		{
			//降噪核匹配
			pix_tempR = 0;
			pix_tempG = 0;
			pix_tempB = 0;
			for (in_i = 0 - half_wnd_height; in_i <= half_wnd_height; in_i++)
			{
				for (in_j = 0 - half_wnd_width; in_j <= half_wnd_width; in_j++)
				{
					//处理x越界
					if (i + in_i<0)
						a = 0;
					else if (i + in_i >= height)
						a = height - 1;
					else
						a = i + in_i;
					//处理y越界
					if (j + in_j<0)
						b = 0;
					else if (j + in_j >= width)
						b = width - 1;
					else
						b = j + in_j;

					pix_tempB += (*src)[a*width + b].b*kernel[in_i*wnd_width + in_j + temp0];
					pix_tempG += (*src)[a*width + b].g*kernel[in_i*wnd_width + in_j + temp0];
					pix_tempR += (*src)[a*width + b].r*kernel[in_i*wnd_width + in_j + temp0];

				}
			}
			//求均值
			(*dst)[i*width + j].b = pix_tempB / kernel_sum;
			(*dst)[i*width + j].g = pix_tempG / kernel_sum;
			(*dst)[i*width + j].r = pix_tempR / kernel_sum;
			(*dst)[i*width + j].a = 0;

		}//end for(j<width)
	}//end for(i<height)
}
//重载
void filter::avg(Pixel* src, Pixel* dst, Window* wnd)
{
	int wnd_width, wnd_height, half_wnd_width, half_wnd_height;
	int width, height;
	int i, j, in_i, in_j, a, b;
	unsigned int temp0, kernel_sum;
	unsigned int pix_tempR, pix_tempG, pix_tempB;
	int *kernel, kernel_len;

	wnd_width = wnd->Width();
	wnd_height = wnd->Height();
	half_wnd_width = wnd_width / 2;
	half_wnd_height = wnd_height / 2;
	width = src->Width();
	height = src->Height();
	kernel = wnd->Kernel();
	kernel_len = wnd_width*wnd_height;
	kernel_sum = 0;
	for (i = 0; i<kernel_len; i++)
		kernel_sum += kernel[i];

	dst->SetSize(width, height);
	//坐标临时变量, 用于计算核坐标时快速计算
	temp0 = half_wnd_height*wnd_width + half_wnd_width;

	//循环匹配
	//图像坐标扫描
	for (i = 0; i<height; i++)
	{
		for (j = 0; j<width; j++)
		{
			//降噪核匹配
			pix_tempR = 0;
			pix_tempG = 0;
			pix_tempB = 0;
			for (in_i = 0 - half_wnd_height; in_i <= half_wnd_height; in_i++)
			{
				for (in_j = 0 - half_wnd_width; in_j <= half_wnd_width; in_j++)
				{
					//处理x越界
					if (i + in_i<0)
						a = 0;
					else if (i + in_i >= height)
						a = height - 1;
					else
						a = i + in_i;
					//处理y越界
					if (j + in_j<0)
						b = 0;
					else if (j + in_j >= width)
						b = width - 1;
					else
						b = j + in_j;

					pix_tempB += (*src)[a*width + b].b*kernel[in_i*wnd_width + in_j + temp0];
					pix_tempG += (*src)[a*width + b].g*kernel[in_i*wnd_width + in_j + temp0];
					pix_tempR += (*src)[a*width + b].r*kernel[in_i*wnd_width + in_j + temp0];

				}
			}
			//求均值
			(*dst)[i*width + j].b = pix_tempB / kernel_sum;
			(*dst)[i*width + j].g = pix_tempG / kernel_sum;
			(*dst)[i*width + j].r = pix_tempR / kernel_sum;
			(*dst)[i*width + j].a = 0;

		}//end for(j<width)
	}//end for(i<height)
}

void filter::simple(Pixel* src, Pixel* dst, Window* wnd)
{
	int wnd_width, wnd_height, half_wnd_width, half_wnd_height;
	int width, height;
	int i, j, in_i, in_j, a, b;
	unsigned int temp0;
	int pix_tempR, pix_tempG, pix_tempB;
	int *kernel;//, kernel_sum, kernel_len;

	wnd_width = wnd->Width();
	wnd_height = wnd->Height();
	half_wnd_width = wnd_width / 2;
	half_wnd_height = wnd_height / 2;
	width = src->Width();
	height = src->Height();
	kernel = wnd->Kernel();

	dst->SetSize(width, height);
	//坐标临时变量, 用于计算核坐标时快速计算
	temp0 = half_wnd_height*wnd_width + half_wnd_width;

	//循环匹配
	//图像坐标扫描
	for (i = 0; i<height; i++)
	{
		for (j = 0; j<width; j++)
		{
			pix_tempR = 0;
			pix_tempG = 0;
			pix_tempB = 0;
			for (in_i = 0 - half_wnd_height; in_i <= half_wnd_height; in_i++)
			{
				for (in_j = 0 - half_wnd_width; in_j <= half_wnd_width; in_j++)
				{
					//处理x越界
					if (i + in_i<0)
						a = 0;
					else if (i + in_i >= height)
						a = height - 1;
					else
						a = i + in_i;
					//处理y越界
					if (j + in_j<0)
						b = 0;
					else if (j + in_j >= width)
						b = width - 1;
					else
						b = j + in_j;

					pix_tempB += (*src)[a*width + b].b*kernel[in_i*wnd_width + in_j + temp0];
					pix_tempG += (*src)[a*width + b].g*kernel[in_i*wnd_width + in_j + temp0];
					pix_tempR += (*src)[a*width + b].r*kernel[in_i*wnd_width + in_j + temp0];

				}
			}
			if (pix_tempB < 0)
				pix_tempB = 0;
			if (pix_tempG < 0)
				pix_tempG = 0;
			if (pix_tempR < 0)
				pix_tempR = 0;

			(*dst)[i*width + j].b = pix_tempB % 256;
			(*dst)[i*width + j].g = pix_tempG % 256;
			(*dst)[i*width + j].r = pix_tempR % 256;
			(*dst)[i*width + j].a = 0;

		}//end for(j<width)
	}//end for(i<height)
}

void filter::edge_detection(Pixel* src, Pixel* dst, Window* wnd)
{
	int wnd_width, wnd_height, half_wnd_width, half_wnd_height;
	int width, height;
	int i, j, in_i, in_j, a, b;
	unsigned int temp0;
	int pix_temp;
	int *kernel;// , kernel_len;

	wnd_width = wnd->Width();
	wnd_height = wnd->Height();
	half_wnd_width = wnd_width / 2;
	half_wnd_height = wnd_height / 2;
	width = src->Width();
	height = src->Height();
	kernel = wnd->Kernel();
	//kernel_len = wnd_width*wnd_height;

	dst->SetSize(width, height);
	//坐标临时变量, 用于计算核坐标时快速计算
	temp0 = half_wnd_height*wnd_width + half_wnd_width;

	//循环匹配
	//图像坐标扫描
	for (i = 0; i<height; i++)
	{
		for (j = 0; j<width; j++)
		{
			//核匹配
			pix_temp = 0;
			for (in_i = 0 - half_wnd_height; in_i <= half_wnd_height; in_i++)
			{
				for (in_j = 0 - half_wnd_width; in_j <= half_wnd_width; in_j++)
				{
					//处理x越界
					if (i + in_i<0)
						a = 0;
					else if (i + in_i >= height)
						a = height - 1;
					else
						a = i + in_i;
					//处理y越界
					if (j + in_j<0)
						b = 0;
					else if (j + in_j >= width)
						b = width - 1;
					else
						b = j + in_j;

					pix_temp += (*src)[a*width + b].g*kernel[in_i*wnd_width + in_j + temp0];

				}
			}
			//
			//pix_temp += 128;
			if (pix_temp < 0)
				pix_temp = 0;
			pix_temp = pix_temp % 256;

			(*dst)[i*width + j].b = pix_temp; //pix_tempB % 256
			(*dst)[i*width + j].g = pix_temp; //pix_tempG % 256
			(*dst)[i*width + j].r = pix_temp; //pix_tempR % 256
			(*dst)[i*width + j].a = 0;

		}//end for(j<width)
	}//end for(i<height)
}

void filter::edge_detection_canny(Pixel* src, Pixel* dst, unsigned short low, unsigned short high)
{
	int i, j, wi, wj, a, b;
	unsigned int width, height;
	Window *windowV, *windowH;
	int *kernelV, *kernelH, pix_tempH, pix_tempV, temp0;
	short *m = NULL; //梯度 注意最大范围32767, 设定窗口时需考虑
	float *md = NULL;//梯度方向
	int wnd_width, wnd_height, half_wnd_width, half_wnd_height;
	//梯度统计var
	//unsigned int m_count[65536] = {0};
	//unsigned int m_sum = 0;
	//short mhigh, mlow;
	//初始化
	//要求两个窗口尺寸相同
	//windowV = Window::GetPrewittWindow(WINDOW_VERTICAL);
	//windowH = Window::GetPrewittWindow(WINDOW_HORIZONTAL);
	windowV = Window::GetSobelWindow(WINDOW_VERTICAL);
	windowH = Window::GetSobelWindow(WINDOW_HORIZONTAL);
	kernelV = windowV->Kernel();
	kernelH = windowH->Kernel();
	wnd_width = windowV->Width();
	wnd_height = windowV->Width();
	half_wnd_width = wnd_width / 2;
	half_wnd_height = wnd_height / 2;
	width = src->Width();
	height = src->Height();
	m = (short*)malloc(sizeof(short)*width*height);
	md = (float*)malloc(sizeof(float)*width*height);
	if (m == NULL || md == NULL)
	{
		if (m)
			free(m);
		if (md)
			free(md);
		delete windowH;
		delete windowV;
		return;
	}

	dst->SetSize(width, height);
	//梯度计算
	temp0 = half_wnd_height * wnd_width + half_wnd_width;
	for (i = 0; i < height; i++)
	{
		//printf("calc m,line; %d\n", i);
		for (j = 0; j < width; j++)
		{
			pix_tempH = 0;
			pix_tempV = 0;
			for (wi = 0 - half_wnd_height; wi <= half_wnd_height; wi++)
			{
				for (wj = 0 - half_wnd_width; wj <= half_wnd_width; wj++)
				{
					//处理x越界
					if (i + wi < 0)
						a = 0;
					else if (i + wi >= height)
						a = height - 1;
					else
						a = i + wi;
					//处理y越界
					if (j + wj < 0)
						b = 0;
					else if (j + wj >= width)
						b = width - 1;
					else
						b = j + wj;
					pix_tempH += (*src)[a*width + b].g * kernelH[wi*wnd_width + wj + temp0];
					pix_tempV += (*src)[a*width + b].g * kernelV[wi*wnd_width + wj + temp0];
				}//end for(wj)
			}//end for(wi)
			m[i*width + j] = sqrt(double(pix_tempH*pix_tempH + pix_tempV*pix_tempV));
			if (pix_tempH)
				md[i*width + j] = ((float)pix_tempV) / pix_tempH;
			else
				md[i*width + j] = ((float)pix_tempV) * 1000;
			/*if(m[i*width+j]+100 > 255)
			{
			(*dst)[i*width+j].b = 255;
			(*dst)[i*width+j].g = 255;
			(*dst)[i*width+j].r = 255;
			}
			else
			{
			(*dst)[i*width+j].b = m[i*width+j]+100;
			(*dst)[i*width+j].g = m[i*width+j]+100;
			(*dst)[i*width+j].r = m[i*width+j]+100;
			}*/

		}//end for(i)
	}//end for(j)
	//非极大值抑制
	//int temp1,temp2;
	short m_temp1, m_temp2;
	float md_temp;
	// int wi, wj;
	for (i = 0; i < height; i++)
	{
		//printf("filt,line; %d\n", i);
		for (j = 0; j < width; j++)
		{
			//梯度小于0, 不是边缘点
			if (m[i*width + j] <= 0)
			{
				(*dst)[i*width + j].b = 0;
				(*dst)[i*width + j].g = 0;
				(*dst)[i*width + j].r = 0;
				(*dst)[i*width + j].a = 0;
			}
			else
			{
				if (md[i*width + j] > 1)// 2
				{
					//
					md_temp = 1 / md[i*width + j];
					if (j + 1 < width && i > 0)
						m_temp1 = m[i*width + j - width] * (1 - md_temp) + m[i*width + j - width + 1] * md_temp;
					else
						m_temp1 = 0;
					if (j > 0 && i + 1 < height)
						m_temp2 = m[i*width + j + width] * (1 - md_temp) + m[i*width + j + width - 1] * md_temp;
					else
						m_temp2 = 0;
				}
				else if (md[i*width + j] == 1)//1-2
				{
					//
					if (j + 1 < width && i > 0)
						m_temp1 = m[i*width + j - width + j];
					else
						m_temp1 = 0;
					if (j > 0 && i + 1 < height)
						m_temp2 = m[i*width + j + width - j];
					else
						m_temp2 = 0;
				}
				else if (md[i*width + j] < 1 && md[i*width + j] > 0)//1
				{
					//
					if (j + 1 < width && i > 0)
						m_temp1 = m[i*width + j + 1] * (1 - md[i*width + j]) + m[i*width + j + 1 - width] * md[i*width + j];
					else
						m_temp1 = 0;
					if (j > 0 && i + 1 < height)
						m_temp2 = m[i*width + j - 1] * (1 - md[i*width + j]) + m[i*width + j - 1 + width] * md[i*width + j];
					else
						m_temp2 = 0;
				}
				else if (md[i*width + j] == 0)//0-1
				{
					//
					if (j + 1 < width)
						m_temp1 = m[i*width + j + 1];
					else
						m_temp1 = 0;
					if (j > 0)
						m_temp2 = m[i*width + j - 1];
					else
						m_temp2 = 0;
				}
				else if (md[i*width + j] < 0 && md[i*width + j] > -1)//4
				{
					//
					md_temp = 0 - md[i*width + j];
					if (j > 0 && i > 0)
						m_temp1 = m[i*width + j - 1] * (1 - md_temp) + m[i*width + j - 1 - width] * md_temp;
					else
						m_temp1 = 0;
					if (j + 1 < width && i + 1 < height)
						m_temp2 = m[i*width + j + 1] * (1 - md_temp) + m[i*width + j + 1 + width] * md_temp;
					else
						m_temp2 = 0;
				}
				else if (md[i*width + j] == -1)//3-4
				{
					//
					md_temp = 0 - md[i*width + j];
					if (j > 0 && i > 0)
						m_temp1 = m[i*width + j - 1 - width];
					else
						m_temp1 = 0;
					if (j + 1 < width && i + 1 < height)
						m_temp2 = m[i*width + j + 1 + width];
					else
						m_temp2 = 0;
				}
				else//else if(md[i*width+j] < -1)
				{
					//
					md_temp = 1 / (0 - md[i*width + j]);
					if (j > 0 && i > 0)
						m_temp1 = m[i*width + j - width] * (1 - md_temp) + m[i*width + j - width - 1] * md_temp;
					else
						m_temp1 = 0;
					if (j + 1 < width && i + 1 < height)
						m_temp2 = m[i*width + j + 1] * (1 - md_temp) + m[i*width + j + 1 + width] * md_temp;
					else
						m_temp2 = 0;
				}
				//judge
				//
				if (m[i*width + j] > m_temp1 && m[i*width + j] > m_temp2)
				{
					(*dst)[i*width + j].b = 255;//m[i*width+j]%256;
					(*dst)[i*width + j].g = 255;//m[i*width+j]%256;
					(*dst)[i*width + j].r = 255;//m[i*width+j]%256;
					(*dst)[i*width + j].a = 0;
					/*//梯度统计
					m_temp1 = m[i*width+j];
					if(m_temp1 > 0)
					{
					m_sum++;
					m_count[m_temp1]++;
					}*/
				}
				else
				{
					(*dst)[i*width + j].b = 0;
					(*dst)[i*width + j].g = 0;
					(*dst)[i*width + j].r = 0;
					(*dst)[i*width + j].a = 0;
				}
			}//else
		}//end for(j)
	}//end for(i)
	//阈值选取
	// unsigned int m_count[32768] = {0};
	//阈值调整
	/*
	if(low > 100)
	low = 30;
	if(high > 100)
	high = 70;
	if(high == 0)
	high = 70;*/
	if (low > high)
		low = high / 2;
	/*
	wi = m_sum * low / 100;
	wj = m_sum * high / 100;
	temp0 = 0;
	mlow= 0;
	for(i = 0; i < 65536; i++)
	{
	temp0 += m_count[i];
	if(temp0 >= wi)
	{
	mlow = i;
	break;
	}
	}
	mhigh = mlow + 1;
	for(; i < 65536; i++)
	{
	temp0 += m_count[i];
	if(temp0 >= wj)
	{
	mhigh = i;
	break;
	}
	}*/
	printf("low: %d, high: %d\n", low, high);
	//边缘输出
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if ((*dst)[i*width + j].b > 0)
			{
				if (m[i*width + j] < low)
				{
					(*dst)[i*width + j].b = 0;
					(*dst)[i*width + j].g = 0;
					(*dst)[i*width + j].r = 0;
				}
				else if (m[i*width + j] < high)
				{
					wi = 0;
					if (i > 0)
					{
						if (j > 0 && m[i*width + j - 1 - width] >= high)
							wi = 1;
						else if (m[i*width + j - width] >= high)
							wi = 1;
						else if (j + 1 < width && m[i*width + j + 1 - width] >= high)
							wi = 1;
					}
					else if (i + 1 < height)
					{
						if (j > 0 && m[i*width + j - 1 + width] >= high)
							wi = 1;
						else if (m[i*width + j + width] >= high)
							wi = 1;
						else if (j + 1 < width && m[i*width + j + 1 + width] >= high)
							wi = 1;
					}
					else
					{
						if (j > 0 && m[i*width + j - 1] >= high)
							wi = 1;
						else if (j + 1 < width && m[i*width + j + 1] >= high)
							wi = 1;
					}
					if (wi == 0)
					{
						(*dst)[i*width + j].b = 0;
						(*dst)[i*width + j].g = 0;
						(*dst)[i*width + j].r = 0;
					}
				}//end else if
			}//end if(.b>0)
		}//end for(j)
	}//end for (i)

	//清内存
	free(m);
	free(md);
	delete windowH;
	delete windowV;
}


