
#include "../include/stastics.h"
#include "../base/pixel.h"

void stastics::countGray(Pixel* src, Pixel* grap)
{
	unsigned int i, j;
	unsigned int lineLen, index, maxCount;
	unsigned int len = src->Width()*src->Height();
	unsigned int counts[256];

	if (len == 0)
		return;

	//初始化
	for (i = 0; i<256; i++)
		counts[i] = 0;
	//统计
	for (i = 0; i<len; i++)
	{
		counts[(*src)[i].g] ++;
	}

	//取最大值作为绘图基准
	maxCount = counts[0];
	for (i = 1; i<256; i++)
	{
		if (counts[i]>maxCount)
			maxCount = counts[i];
	}

	//绘制直方图
	grap->SetSize(256, 100);

	for (i = 0; i<256; i++)
	{
		lineLen = (counts[i] * 100) / maxCount;
		//printf("%d: %d/%d  %.4f%%\n",i,counts[i], len, temp);
		index = 25344; //256*99
		for (j = 0; j<100 && j<lineLen; j++)
		{
			(*grap)[i + index].b = 0;//(*grap)[i+j*256].b = 0;
			(*grap)[i + index].g = 0;//(*grap)[i+j*256].g = 0;
			(*grap)[i + index].r = 0;//(*grap)[i+j*256].r = 0;
			(*grap)[i + index].a = 0;//(*grap)[i+j*256].a = 0;
			index -= 256;
		}
		for (; j<100; j++)
		{
			(*grap)[i + index].b = 255;//(*grap)[i+j*256].b = 255;
			(*grap)[i + index].g = 255;//(*grap)[i+j*256].g = 255;
			(*grap)[i + index].r = 255;//(*grap)[i+j*256].r = 255;
			(*grap)[i + index].a = 0;  //(*grap)[i+j*256].a = 0;
			index -= 256;
		}
	}// for end
}// countGray end

void stastics::countGrayWinthT(Pixel* src, Pixel* grap, short t1, short t2)
{
	unsigned int i, j;
	unsigned int lineLen, index, maxCount;
	unsigned int len = src->Width()*src->Height();
	unsigned int counts[256];

	if (t1 > 255 || t2 > 255 || len == 0)
		return;

	//初始化
	for (i = 0; i<256; i++)
		counts[i] = 0;
	//统计
	for (i = 0; i<len; i++)
	{
		counts[(*src)[i].g] ++;
	}

	//取最大值作为绘图基准
	maxCount = counts[0];
	for (i = 1; i<256; i++)
	{
		if (counts[i]>maxCount)
			maxCount = counts[i];
	}

	//绘制直方图
	grap->SetSize(256, 100);

	for (i = 0; i<256; i++)
	{
		lineLen = (counts[i] * 100) / maxCount;
		//printf("%d: %d/%d  %.4f%%\n",i,counts[i], len, temp);
		index = 25344; //256*99
		for (j = 0; j<100 && j<lineLen; j++)
		{
			(*grap)[i + index].b = 0;//(*grap)[i+j*256].b = 0;
			(*grap)[i + index].g = 0;//(*grap)[i+j*256].g = 0;
			(*grap)[i + index].r = 0;//(*grap)[i+j*256].r = 0;
			(*grap)[i + index].a = 0;//(*grap)[i+j*256].a = 0;
			index -= 256;
		}
		for (; j<100; j++)
		{
			(*grap)[i + index].b = 255;//(*grap)[i+j*256].b = 255;
			(*grap)[i + index].g = 255;//(*grap)[i+j*256].g = 255;
			(*grap)[i + index].r = 255;//(*grap)[i+j*256].r = 255;
			(*grap)[i + index].a = 0;  //(*grap)[i+j*256].a = 0;
			index -= 256;
		}
	}// for end
	index = t1;
	j = t2;
	for (i = 0; i < 100; i++)
	{
		//(*grap)[i+index].b = (*grap)[i+index].b;
		//(*grap)[i+index].g = (*grap)[i+index].g;
		if (t1 >= 0)
			(*grap)[index].r = (*grap)[index].r ^ 200;
		//(*grap)[i+index].a = 0;
		if (t2 >= 0)
			(*grap)[j].g = (*grap)[j].g ^ 200;
		index += 256;
		j += 256;
	}
}// countGray end

void stastics::countGray(Pixel* src, unsigned int* counts, unsigned int counts_len)
{
	unsigned int i;
	unsigned int len = src->Width()*src->Height();

	if (counts_len > 256)
		counts_len = 256;

	if (len == 0)
		return;

	//初始化
	for (i = 0; i<counts_len; i++)
		counts[i] = 0;
	//统计
	for (i = 0; i<len; i++)
	{
		if ((*src)[i].g < counts_len)
			counts[(*src)[i].g] ++;
	}
}// countGray end