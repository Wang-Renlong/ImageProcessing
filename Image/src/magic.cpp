

#include "../include/magic.h"

#include "../base/pixel.h"

void magic::moveTo(Pixel* src, Pixel* dst, unsigned int src_x, unsigned int src_y, unsigned int dst_x, unsigned int dst_y,
        unsigned int w, unsigned int h, char flag)
{
	unsigned int i, j;
	unsigned int width, height;
	unsigned int src_width, src_height;
	unsigned int x_src_tmp, x_dst_tmp, y_src_tmp, y_dst_tmp;

	width = src->Width();
	height = src->Height();
	src_width = src->Width();
	src_height = src->Height();

	if (flag)
		dst->SetSize(width, height);
	else
	{
		width = dst->Width();
		height = dst->Height();
	}
	//计算移动区域的长宽
	//width = dst->Width; height = dst->Height;
	if (src_x + w > src->Width())
		w = src->Width() - src_x;
	if (dst_x + w > width)
		w = width - dst_x;

	if (src_y + h > src->Height())
		h = src->Height() - src_y;
	if (dst_y + h > height)
		h = height - dst_y;

	//printf("from:%d,%d %d %d\n",src_x,src_y,w,h);
	//printf("to:%d,%d %d %d\n",dst_x,dst_y,w,h);
	//起始y变量
	//y_src_tmp = src_y * src->Width();
	//y_dst_tmp = dst_y * dst->Width();
	y_src_tmp = src_y * src_width;
	y_dst_tmp = dst_y * width;
	for (i = 0; i < h; i++)
	{
		//起始x变量
		x_src_tmp = src_x;
		x_dst_tmp = dst_x;
		for (j = 0; j < w; j++)
		{
			(*dst)[y_dst_tmp + x_dst_tmp].b = (*src)[y_src_tmp + x_src_tmp].b;
			(*dst)[y_dst_tmp + x_dst_tmp].g = (*src)[y_src_tmp + x_src_tmp].g;
			(*dst)[y_dst_tmp + x_dst_tmp].r = (*src)[y_src_tmp + x_src_tmp].r;
			(*dst)[y_dst_tmp + x_dst_tmp].a = (*src)[y_src_tmp + x_src_tmp].a;

			x_src_tmp++;
			x_dst_tmp++;
		}
		//y_src_tmp += src->Width();
		//y_dst_tmp += dst->Width();
		y_src_tmp += src_width;
		y_dst_tmp += width;
	}
}

void magic::reSize_Upper(Pixel* src, Pixel* dst, int dst_width, int dst_height, char flag)
{
	int i, j;
	int si, sj;
	int src_width;//, src_height;
	float v_per, h_per;
	//float v_low, v_high, h_low, h_high;

	if (flag)
		dst->SetSize(dst_width, dst_height);
	//垂直, 水平缩放比例
	v_per = (float)(src->Width()) / dst_width;
	h_per = (float)(src->Height()) / dst_height;

	src_width = src->Width();
	//src_height = src->Height();

	for (i = 0; i < dst_height; i++)
	{
		si = i * h_per;
		for (j = 0; j < dst_width; j++)
		{
			sj = j * v_per;
			(*dst)[i*dst_width + j].b = (*src)[si*src_width + sj].b;
			(*dst)[i*dst_width + j].g = (*src)[si*src_width + sj].g;
			(*dst)[i*dst_width + j].r = (*src)[si*src_width + sj].r;
			(*dst)[i*dst_width + j].a = (*src)[si*src_width + sj].a;
		}
	}
}

void magic::reSize_quadratic_linear(Pixel* src, Pixel* dst, unsigned int dst_width, unsigned int dst_height, char flag)
{
	unsigned int i, j;
	unsigned int si, sj;
	unsigned int src_width, src_height;
	unsigned int ah_tmp, aw_tmp, dh_tmp, dw_tmp;
	//unsigned int clrTempB, clrTempG, clrTempR;
	float v_per, h_per;
	float r, k;
	float a, b, c, d;//up_left, up_right, down_left, down_right

	if (flag)
		dst->SetSize(dst_width, dst_height);
	//垂直, 水平缩放比例
	v_per = (float)(src->Width()) / dst_width;
	h_per = (float)(src->Height()) / dst_height;

	src_width = src->Width();
	src_height = src->Height();

	for (i = 0; i < dst_height; i++)
	{
		//k: 距离上临近点的距离 si: 上临近点y坐标
		k = i * h_per;
		si = (int)k;
		k -= si;
		//y变量临时值, y*width偏移量
		ah_tmp = si*src_width;
		//越界处理
		if (si + 1 < src_height)
			dh_tmp = ah_tmp + src_width;
		else
			dh_tmp = ah_tmp;

		for (j = 0; j < dst_width; j++)
		{
			//r: 距离左临近点的距离 sj: 左临近点y坐标
			//sj = j * v_per;
			r = j * v_per;
			sj = (int)r;
			r -= sj;
			//x变量
			aw_tmp = sj;
			dw_tmp = aw_tmp + 1;
			//越界处理
			if (dw_tmp >= src_width)
				dw_tmp = aw_tmp;
			//四个临近点的权值
			b = r*k;
			a = k - b;
			c = b - k + 1 - r;
			d = r - b;

			(*dst)[i*dst_width + j].b = (*src)[ah_tmp + aw_tmp].b*a + (*src)[ah_tmp + dw_tmp].b*b +
				(*src)[dh_tmp + aw_tmp].b*c + (*src)[dh_tmp + dw_tmp].b*d;

			(*dst)[i*dst_width + j].g = (*src)[ah_tmp + aw_tmp].g*a + (*src)[ah_tmp + dw_tmp].g*b +
				(*src)[dh_tmp + aw_tmp].g*c + (*src)[dh_tmp + dw_tmp].g*d;

			(*dst)[i*dst_width + j].r = (*src)[ah_tmp + aw_tmp].r*a + (*src)[ah_tmp + dw_tmp].r*b +
				(*src)[dh_tmp + aw_tmp].r*c + (*src)[dh_tmp + dw_tmp].r*d;

			(*dst)[i*dst_width + j].a = (*src)[ah_tmp + aw_tmp].a*a + (*src)[ah_tmp + dw_tmp].a*b +
				(*src)[dh_tmp + aw_tmp].a*c + (*src)[dh_tmp + dw_tmp].a*d;

		}//end for(j < dst_width)
	}//end for(i < dst_height)
}

void magic::imageX(Pixel* src, Pixel* dst, char flag)
{
	unsigned int i, j;
	unsigned int width, height;
	unsigned int temp0, tempY, temp1, temp2;

	width = src->Width();
	height = src->Height();
	if (flag)
		dst->SetSize(width, height);

	temp0 = (height - 1) * width;
	tempY = 0;
	for (i = 0; i < height; i++)
	{
		temp1 = tempY; //目标点偏移量
		temp2 = temp0 - tempY; //原始点偏移量
		for (j = 0; j < width; j++)
		{
			//0.219s 0.141s 0.141s 0.141s(build & run)
			//(*dst)[(height-i-1)*width+j].b = (*src)[i*width+j].b;
			//(*dst)[(height-i-1)*width+j].g = (*src)[i*width+j].g;
			//(*dst)[(height-i-1)*width+j].r = (*src)[i*width+j].r;
			//(*dst)[(height-i-1)*width+j].a = (*src)[i*width+j].a;
			//0.141s 0.125s 0.250s 0.141s 0.156s 0.094s 0.094s 0.109s 0.125s(build & run)
			(*dst)[temp2].b = (*src)[temp1].b;
			(*dst)[temp2].g = (*src)[temp1].g;
			(*dst)[temp2].r = (*src)[temp1].r;
			(*dst)[temp2].a = (*src)[temp1].a;
			temp1++;
			temp2++;
		}
		tempY += width;
	}

}

void magic::imageY(Pixel* src, Pixel* dst, char flag)
{
	unsigned int i, j;
	unsigned int width, height;
	unsigned int temp0, tempY;//, temp1, temp2

	width = src->Width();
	height = src->Height();
	if (flag)
		dst->SetSize(width, height);

	tempY = 0;
	for (i = 0; i < height; i++)
	{
		temp0 = width - 1;
		for (j = 0; j < width; j++)
		{
			//0.117s 0.031s 0.031s(build & run, run)
			//(*dst)[i*width+width-j].b = (*src)[i*width+j].b;
			//(*dst)[i*width+width-j].g = (*src)[i*width+j].g;
			//(*dst)[i*width+width-j].r = (*src)[i*width+j].r;
			//(*dst)[i*width+width-j].a = (*src)[i*width+j].a;
			//0.234s 0.031s 0.031s(build & run, run)
			(*dst)[tempY + temp0].b = (*src)[tempY + j].b;
			(*dst)[tempY + temp0].g = (*src)[tempY + j].g;
			(*dst)[tempY + temp0].r = (*src)[tempY + j].r;
			(*dst)[tempY + temp0].a = (*src)[tempY + j].a;
			temp0--;
		}
		tempY += width;
	}

}

inline long long magic::max_in4(long long a, long long b, long long c, long long d)
{
	long long mm = a;
	if (b > mm)
		mm = b;
	if (c > mm)
		mm = c;
	if (d > mm)
		mm = d;
	return mm;
}
inline long long magic::min_in4(long long a, long long b, long long c, long long d)
{
	long long mm = a;
	if (b < mm)
		mm = b;
	if (c < mm)
		mm = c;
	if (d < mm)
		mm = d;
	return mm;
}

void magic::rotateImg(Pixel* src, Pixel* dst, unsigned int ctr_x, unsigned int ctr_y, float sinSi, float cosSi, char flag)
{
	unsigned int i, j;
	unsigned int src_width, src_height;
	unsigned int dst_width, dst_height;
	long long ax, ay, bx, by, cx, cy, dx, dy;
	float ftemp0, toX, toY;

	src_width = src->Width();
	src_height = src->Height();
	//过滤非法的角度值
	ftemp0 = sinSi*sinSi + cosSi*cosSi;
	if (ftemp0 > 1.01 || ftemp0 < 0.99)
		return;

	// set dst size
	if (flag == 1)
	{
		//四角点的映射坐标
		//(0,0) ax
		//ftemp0 = (0 - ctr_x)*(0 - ctr_x) + (0 - ctr_y)*(0 - ctr_y);
		//ftemp0 = sqrt(ftemp0);
		toY = (float)0 - ctr_y; //sina = (0 - ctr_y) / ftemp0;
		toX = (float)0 - ctr_x; //cosa = (0 - ctr_x) / ftemp0;
		//ax = cosa*cosSi - sina*sinSi + ctr_x;
		//ax = ax*ftemp0;
		ax = toX*cosSi - toY*sinSi + ctr_x;
		//ay = sina*cosSi + cosa*sinSi + ctr_y;
		//ay = ay*ftemp;
		ay = toY*cosSi + toX*sinSi + ctr_y;

		//(0,end) bx
		//ftemp0 = (0 - ctr_x)*(0  - ctr_x) + (src_height - 1 - ctr_y)*(src_height - 1  - ctr_y);
		//ftemp0 = sqrt(ftemp0);
		toY = (float)src_height - 1 - ctr_y;
		toX = (float)0 - ctr_x;
		//bx = cosa*cosSi - sina*sinSi + ctr_x;
		bx = toX*cosSi - toY*sinSi + ctr_x;
		//by = sina*cosSi + cosa*sinSi + ctr_y;
		by = toY*cosSi + toX*sinSi + ctr_y;

		//(end,0) cx
		//ftemp0 = (src_width - 1 - ctr_x)*(src_width - 1  - ctr_x) + (0 - ctr_y)*(0  - ctr_y);
		//ftemp0 = sqrt(ftemp0);
		toY = (float)0 - ctr_y;
		toX = (float)src_width - 1 - ctr_x;
		//cx = cosa*cosSi - sina*sinSi + ctr_x;
		cx = toX*cosSi - toY*sinSi + ctr_x;
		//cy = sina*cosSi + cosa*sinSi + ctr_y;
		cy = toY*cosSi + toX*sinSi + ctr_y;

		//(end,end) dx
		//ftemp0 = (src_width - 1 - ctr_x)*(src_width - 1  - ctr_x) + (src_height - 1 - ctr_y)*(src_height - 1  - ctr_y);
		//ftemp0 = sqrt(ftemp0);
		toY = (float)src_height - 1 - ctr_y; //sina = (src_height - 1 - src_y) / ftemp0;
		toX = (float)src_width - 1 - ctr_x; //cosa = (src_width - 1  - src_x) / ftemp0;
		//dx = cosa*cosSi - sina*sinSi + ctr_x;
		//dx = dx*ftemp0;
		dx = toX*cosSi - toY*sinSi + ctr_x;
		//dy = sina*cosSi + cosa*sinSi +ctr_y;
		//dy = dy*ftemp;
		dy = toY*cosSi + toX*sinSi + ctr_y;

		//取焦点坐标最大值，用来决定目的图像的大小
		dst_width = max_in4(ax, bx, cx, dx) - min_in4(ax, bx, cx, dx);
		dst_height = max_in4(ay, by, cy, dy) - min_in4(ay, by, cy, dy);
		dst->SetSize(dst_width, dst_height);
		bx = dst_width / 2;
		by = dst_height / 2;
	}
	else if (flag == 2)
	{
		dst_width = src_width;
		dst_height = src_height;
		dst->SetSize(dst_width, dst_height);
		bx = ctr_x;
		by = ctr_y;
	}
	else
	{
		dst_width = dst->Width();
		dst_height = dst->Height();
		bx = ctr_x;
		by = ctr_y;
	}
	//printf("width:%d, height:%d\n", dst_width,dst_height);
	//printf("center:%lld, %lld\n",bx, by);
	//printf("(0,0)->");
	//start
	for (i = 0; i < src_height; i++)
	{
		toY = (float)i - ctr_y; //原始y坐标坐标转换
		for (j = 0; j < src_width; j++)
		{
			toX = (float)j - ctr_x; //原始x坐标坐标转换

			//if(i==0&&j==0)
			//    printf("(%f,%f)->(%f,%f)->", toX, toY, toX*cosSi - toY*sinSi, toY*cosSi + toX*sinSi);

			//ftemp0 = (j - src_x)*(j - src_x) + (i - src_y)*(i - src_y);
			//ftemp0 = cosa*cosa + sina*sina;
			//ftemp0 = sqrt(ftemp0);
			//ax = cosa*cosSi - sina*sinSi + src_x;
			//ay = sina*cosSi + cosa*sinSi + src_y;
			ax = toX*cosSi - toY*sinSi + bx; //目的x坐标
			ay = toY*cosSi + toX*sinSi + by; //目的y坐标

			//if(i==0&&j==0)
			//    printf("(%lld,%lld)\n", ax, ay);

			if (ax >= 0 && ax < dst_width && ay >= 0 && ay < dst_height)
			{
				(*dst)[ay*dst_width + ax].b = (*src)[i*src_width + j].b;
				(*dst)[ay*dst_width + ax].g = (*src)[i*src_width + j].g;
				(*dst)[ay*dst_width + ax].r = (*src)[i*src_width + j].r;
				(*dst)[ay*dst_width + ax].a = (*src)[i*src_width + j].a;
			}//end if()
		}//end for(j<src_width)
		//printf("line %d finished\n",i);
	}//end for(i<src_height)
}

void magic::rotateImgAdvanced(Pixel* src, Pixel* dst, unsigned int ctr_x, unsigned int ctr_y, float sinSi, float cosSi, char flag)
{
	unsigned int i, j;
	unsigned int src_width, src_height;
	unsigned int dst_width, dst_height;
	long long ax, ay, bx, by, cx, cy, dx, dy;
	float ftemp0, toX, toY;

	src_width = src->Width();
	src_height = src->Height();

	ftemp0 = sinSi*sinSi + cosSi*cosSi;
	if (ftemp0 > 1.01 || ftemp0 < 0.99)
		return;

	// set dst size
	if (flag == 1)
	{
		//四个角点目的坐标
		//(0,0) ax
		//ftemp0 = (0 - ctr_x)*(0 - ctr_x) + (0 - ctr_y)*(0 - ctr_y);
		//ftemp0 = sqrt(ftemp0);
		toY = (float)0 - ctr_y; //sina = (0 - ctr_y) / ftemp0;
		toX = (float)0 - ctr_x; //cosa = (0 - ctr_x) / ftemp0;
		//ax = cosa*cosSi - sina*sinSi + ctr_x;
		//ax = ax*ftemp0;
		ax = toX*cosSi - toY*sinSi + ctr_x;
		//ay = sina*cosSi + cosa*sinSi + ctr_y;
		//ay = ay*ftemp;
		ay = toY*cosSi + toX*sinSi + ctr_y;

		//(0,end) bx
		//ftemp0 = (0 - ctr_x)*(0  - ctr_x) + (src_height - 1 - ctr_y)*(src_height - 1  - ctr_y);
		//ftemp0 = sqrt(ftemp0);
		toY = (float)src_height - 1 - ctr_y;
		toX = (float)0 - ctr_x;
		//bx = cosa*cosSi - sina*sinSi + ctr_x;
		bx = toX*cosSi - toY*sinSi + ctr_x;
		//by = sina*cosSi + cosa*sinSi + ctr_y;
		by = toY*cosSi + toX*sinSi + ctr_y;

		//(end,0) cx
		//ftemp0 = (src_width - 1 - ctr_x)*(src_width - 1  - ctr_x) + (0 - ctr_y)*(0  - ctr_y);
		//ftemp0 = sqrt(ftemp0);
		toY = (float)0 - ctr_y;
		toX = (float)src_width - 1 - ctr_x;
		//cx = cosa*cosSi - sina*sinSi + ctr_x;
		cx = toX*cosSi - toY*sinSi + ctr_x;
		//cy = sina*cosSi + cosa*sinSi + ctr_y;
		cy = toY*cosSi + toX*sinSi + ctr_y;

		//(end,end) dx
		//ftemp0 = (src_width - 1 - ctr_x)*(src_width - 1  - ctr_x) + (src_height - 1 - ctr_y)*(src_height - 1  - ctr_y);
		//ftemp0 = sqrt(ftemp0);
		toY = (float)src_height - 1 - ctr_y; //sina = (src_height - 1 - src_y) / ftemp0;
		toX = (float)src_width - 1 - ctr_x; //cosa = (src_width - 1  - src_x) / ftemp0;
		//dx = cosa*cosSi - sina*sinSi + ctr_x;
		//dx = dx*ftemp0;
		dx = toX*cosSi - toY*sinSi + ctr_x;
		//dy = sina*cosSi + cosa*sinSi +ctr_y;
		//dy = dy*ftemp;
		dy = toY*cosSi + toX*sinSi + ctr_y;

		//根据四个角点的目的坐标确定目的图像的尺寸
		dst_width = max_in4(ax, bx, cx, dx) - min_in4(ax, bx, cx, dx);
		dst_height = max_in4(ay, by, cy, dy) - min_in4(ay, by, cy, dy);
		dst->SetSize(dst_width, dst_height);
		bx = dst_width / 2;
		by = dst_height / 2;
	}
	else if (flag == 2)
	{
		dst_width = src_width;
		dst_height = src_height;
		dst->SetSize(dst_width, dst_height);
		bx = ctr_x;
		by = ctr_y;
	}
	else
	{
		dst_width = dst->Width();
		dst_height = dst->Height();
		bx = ctr_x;
		by = ctr_y;
	}
	//printf("width:%d, height:%d\n", dst_width,dst_height);
	//printf("center:%lld, %lld\n",bx, by);
	//printf("(0,0)->");
	//start
	for (i = 0; i < dst_height; i++)
	{
		toY = (float)i - by; //y坐标转换
		for (j = 0; j < dst_width; j++)
		{
			toX = (float)j - bx; //x坐标转换

			//if(i==0&&j==0)
			//    printf("(%f,%f)->(%f,%f)->", toX, toY, toX*cosSi - toY*sinSi, toY*cosSi + toX*sinSi);

			//ftemp0 = (j - src_x)*(j - src_x) + (i - src_y)*(i - src_y);
			//ftemp0 = cosa*cosa + sina*sina;
			//ftemp0 = sqrt(ftemp0);
			//ax = cosa*cosSi - sina*sinSi + src_x;
			//ay = sina*cosSi + cosa*sinSi + src_y;
			ax = toX*cosSi + toY*sinSi + ctr_x; //计算原始x坐标
			ay = toY*cosSi - toX*sinSi + ctr_y; //计算原始y坐标

			//if(i==0&&j==0)
			//    printf("(%lld,%lld)\n", ax, ay);

			if (ax >= 0 && ax < src_width && ay >= 0 && ay < src_height)
			{
				(*dst)[i*dst_width + j].b = (*src)[ay*src_width + ax].b;
				(*dst)[i*dst_width + j].g = (*src)[ay*src_width + ax].g;
				(*dst)[i*dst_width + j].r = (*src)[ay*src_width + ax].r;
				(*dst)[i*dst_width + j].a = (*src)[ay*src_width + ax].a;
			}//end if()
		}//end for(j<src_width)
		//printf("line %d finished\n",i);
	}//end for(i<src_height)
}

float magic::sinSigma(float Si)
{
	return (float)sin(Si);
}

float magic::cosSigma(float Si)
{
	return (float)cos(Si);
}

void magic::paint(Pixel* src, Pixel* pen, Pixel* dst, PixelRGBA& color, char flag)
{
	unsigned int width, height;
	unsigned int i, j;

	width = src->Width();
	height = src->Height();
	if (flag)
		dst->SetSize(width, height);

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if ((*pen)[i*width + j].b == 255)
			{
				(*dst)[i*width + j].b = color.b;
				(*dst)[i*width + j].g = color.g;
				(*dst)[i*width + j].r = color.r;
			}
			else
			{
				(*dst)[i*width + j].b = (*src)[i*width + j].b;
				(*dst)[i*width + j].g = (*src)[i*width + j].g;
				(*dst)[i*width + j].r = (*src)[i*width + j].r;
			}
		}
	}
}