

#include "../include/img.h"

#include "../base/pixel.h"
#include <queue>
#include <vector>
#include <math.h>
#include "../base/point.h"
#include "../base/rect.h"
#include "../base/quadtree.h"
#include "../include/q_and_qu.h"


void img::copyRedChannel(Pixel* src, Pixel* dst)
{
	unsigned int i;
	unsigned int len = src->Width()*src->Height();
	dst->SetSize(src->Width(), src->Height());
	for (i = 0; i<len; i++)
	{
		(*dst)[i].r = (*src)[i].r;
		(*dst)[i].g = 0;
		(*dst)[i].b = 0;
		(*dst)[i].a = 0;
	}
}

void img::copyGreenChannel(Pixel* src, Pixel* dst)
{
	unsigned int i;
	unsigned int len = src->Width()*src->Height();
	dst->SetSize(src->Width(), src->Height());
	for (i = 0; i<len; i++)
	{
		(*dst)[i].r = 0;
		(*dst)[i].g = (*src)[i].g;
		(*dst)[i].b = 0;
		(*dst)[i].a = 0;
	}
}

void img::copyBlueChannel(Pixel* src, Pixel* dst)
{
	unsigned int i;
	unsigned int len = src->Width()*src->Height();
	dst->SetSize(src->Width(), src->Height());
	for (i = 0; i<len; i++)
	{
		(*dst)[i].r = 0;
		(*dst)[i].g = 0;
		(*dst)[i].b = (*src)[i].b;
		(*dst)[i].a = 0;
	}
}

void img::toGray(Pixel* src, Pixel* dst)
{
	unsigned int i, pix;
	unsigned int len = src->Width() * src->Height();
	dst->SetSize(src->Width(), src->Height());
	for (i = 0; i<len; i++)
	{
		//pix = pixel[i*width+j].r*0.299+pixel[i*width+j].g*0.587+pixel[i*width+j].b*0.114;
		pix = (*src)[i].r * 306 + (*src)[i].g * 601 + (*src)[i].b * 117;
		//pix = pix / 1024;
		pix = pix >> 10;
		(*dst)[i].r = pix;
		(*dst)[i].g = pix;
		(*dst)[i].b = pix;
		(*dst)[i].a = 0;
	}
}

void img::AntiColor(Pixel* src, Pixel* dst)
{
	unsigned int i;
	unsigned int len = src->Width() * src->Height();
	dst->SetSize(src->Width(), src->Height());
	for (i = 0; i<len; i++)
	{
		(*dst)[i].r = 255 - (*src)[i].r;
		(*dst)[i].g = 255 - (*src)[i].g;
		(*dst)[i].b = 255 - (*src)[i].b;
		(*dst)[i].a = 0;
	}
}

void img::equalization(Pixel* src, Pixel* dst)
{
	unsigned int i, j, sum;
	unsigned int len = src->Width()*src->Height();
	unsigned int counts[256];
	unsigned int s[256];
	//float temp;

	//初始化
	for (i = 0; i<255; i++)
		counts[i] = 0;
	//统计
	for (i = 0; i<len; i++)
	{
		counts[(*src)[i].g] ++;
	}
	//计算换算映射 s = (L-1){[0-r]Pr(w)dw
	sum = 0;
	for (i = 0; i<256; i++)
	{
		sum += counts[i];
		s[i] = (float)(sum) / len * 255;
	}
	//变换
	dst->SetSize(src->Width(), src->Height());
	for (i = 0; i<len; i++)
	{
		j = (*src)[i].g;
		(*dst)[i].g = s[j];
		(*dst)[i].b = s[j];
		(*dst)[i].r = s[j];
		(*dst)[i].a = 0;
	}
}

void img::divide(Pixel* src, Pixel* dst, short t1, short t2, char flag)
{
	unsigned int i, j, width, height, temp;
	width = src->Width();
	height = src->Height();

	if (t1 > 255 || t2 > 255 || (width&height) == 0)
		return;

	if (flag)
		dst->SetSize(width, height);

	temp = 0;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (t2 >= 0 && (*src)[temp + j].g > t2)
			{
				(*dst)[temp + j].b = 255;
				(*dst)[temp + j].g = 255;
				(*dst)[temp + j].r = 255;
				//(*dst)[temp+j].a = 255;
			}
			else if (t1 >= 0 && (*src)[temp + j].g > t1)
			{
				(*dst)[temp + j].b = 127;
				(*dst)[temp + j].g = 127;
				(*dst)[temp + j].r = 127;
				//(*dst)[temp+j].a = 255;
			}
			else
			{
				(*dst)[temp + j].b = 0;
				(*dst)[temp + j].g = 0;
				(*dst)[temp + j].r = 0;
				//(*dst)[temp+j].a = 255;
			}
		}
		temp += width;
	}//end for
}//end func

void img::__countGray(Pixel* src, unsigned int* counts, unsigned int counts_len)
{
	unsigned int i;
	unsigned int len = src->Width()*src->Height();

	if (counts_len > 256)
		counts_len = 256;

	if (len <= 0)
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

short img::t_devide_iterative(Pixel* src, short t, short dt)
{
	unsigned int width, height;
	unsigned int grayCount[256];
	unsigned int colorSum, pixSum;
	short ct, pt;
	short i, avg1, avg2;

	width = src->Width();
	height = src->Height();
	//sum = width * height;

	if (t < 0 || t > 255 || dt < 0 || dt > 254 || (width&height) == 0)
		return 0;

	__countGray(src, grayCount, 256);

	ct = t;
	pt = 0;
	avg1 = dt + 2;
	while (avg1 > dt)
	{
		colorSum = 0;
		pixSum = 0;
		for (i = 0; i <= ct; i++)
		{
			pixSum += grayCount[i];
			colorSum += grayCount[i] * i;
		}
		if (pixSum)
			avg1 = colorSum / pixSum;
		else
			avg1 = 0;
		pixSum = 0;
		colorSum = 0;
		for (; i < 256; i++)
		{
			pixSum += grayCount[i];
			colorSum += grayCount[i] * i;
		}
		if (pixSum)
			avg2 = colorSum / pixSum;
		else
			avg2 = 0;
		pt = ct;
		ct = (avg1 + avg2) / 2;
		//printf("avg1 = %d, avg2 = %d\n", avg1, avg2);
		if (ct > pt)
			avg1 = ct - pt;
		else
			avg1 = pt - ct;
	}//end while
	//printf("T=%d\n", pt);
	//divide(src, dst, -1, pt, flag);
	return pt;
}//end func

short img::t_devide_otsu(Pixel* src)
{
	unsigned int width, height;
	unsigned int grayCount[256];
	unsigned int p1ks[256], mk[256];
	float p1k, p2k, si2[256];
	double sum;
	short t, tc;
	unsigned int mg, m2k;

	unsigned int i;

	width = src->Width();
	height = src->Height();
	sum = width * height;

	if ((width&height) == 0)
		return 0;

	__countGray(src, grayCount, 256);

	for (i = 0; i < 256; i++)
	{
		p1ks[i] = 0;
		mk[i] = 0;
		si2[i] = 0;
	}

	p1ks[0] = grayCount[0];
	mk[0] = 0;
	for (i = 1; i < 256; i++)
	{
		p1ks[i] = p1ks[i - 1] + grayCount[i];
		mk[i] = mk[i - 1] + grayCount[i] * i;
	}

	mg = mk[255] / p1ks[255];
	t = 0;
	tc = 0;
	for (i = 0; i < 256; i++)
	{
		m2k = mk[255] - mk[i];
		//p2k = (p1ks[255]-p1ks[i]);
		if (p1ks[i])
			mk[i] = mk[i] / p1ks[i];
		else
			mk[i] = 0;
		p1k = p1ks[i] / sum;
		if (p1k != 1 && p1k != 0)
			si2[i] = (mg*p1k - mk[i]) * (mg*p1k - mk[i]) / (p1k - p1k*p1k);
		else if (p1k == 1)
			si2[i] = (mk[i] - mg)*(mk[i] - mg);
		else
		{
			p2k = (p1ks[255] - p1ks[i]);
			m2k = m2k / p2k;
			p2k = p2k / sum;
			si2[i] = (m2k - mg)*(m2k - mg);
		}
		//si2[i] = mg*p1k-mk[i];
		//si2[i] = si2[i]*si2[i];
		//si2[i] = si2[i] / (p1k-p1k*p1k);

		if (si2[i] > si2[t])
		{
			tc = 1;
			t = i;
		}
		else if (si2[i] == si2[t])
		{
			t += i;
			tc++;
		}
	}
	return t / tc;
}

unsigned char img::__diff(unsigned char color1, unsigned char color2)
{
	if (color1 > color2)
		return color1 - color2;
	else
		return color2 - color1;
}

void img::devide_seed(Pixel* src, Pixel* dst, unsigned int x, unsigned int y, unsigned char dt, char flag)
{
	unsigned int width, height;
	//unsigned int i, j, temp;
	//char tag;
	Point cPoint, tPoint;
	std::queue<Point> pointQue;//种子点队列

	width = src->Width();
	height = src->Height();

	if (!(width & height))
		return;

	if (flag)
	{
		dst->SetSize(width, height);
		dst->Fill(0, 0, 0, 0);
	}
	//添加种子点, 进行广度优先遍历
	pointQue.push(Point(x, y));
	(*dst)[y*width + x].b = 255;
	(*dst)[y*width + x].g = 255;
	(*dst)[y*width + x].r = 255;
	while (!pointQue.empty())
	{
		cPoint = pointQue.front();
		pointQue.pop();
		//left
		if (cPoint.x > 0 && (*dst)[cPoint.y*width + cPoint.x - 1].b < 255 &&
			__diff((*src)[cPoint.y*width + cPoint.x].b, (*src)[cPoint.y*width + cPoint.x - 1].b) <= dt)
		{
			tPoint.x = cPoint.x - 1;
			tPoint.y = cPoint.y;
			pointQue.push(tPoint);

			(*dst)[tPoint.y*width + tPoint.x].b = 255;
			(*dst)[tPoint.y*width + tPoint.x].g = 255;
			(*dst)[tPoint.y*width + tPoint.x].r = 255;
		}
		//top
		if (cPoint.y > 0 && (*dst)[cPoint.y*width + cPoint.x - width].b < 255 &&
			__diff((*src)[cPoint.y*width + cPoint.x].b, (*src)[cPoint.y*width + cPoint.x - width].b) <= dt)
		{
			tPoint.x = cPoint.x;
			tPoint.y = cPoint.y - 1;
			pointQue.push(tPoint);

			(*dst)[tPoint.y*width + tPoint.x].b = 255;
			(*dst)[tPoint.y*width + tPoint.x].g = 255;
			(*dst)[tPoint.y*width + tPoint.x].r = 255;
		}
		//right
		if (cPoint.x + 1 < width && (*dst)[cPoint.y*width + cPoint.x + 1].b < 255 &&
			__diff((*src)[cPoint.y*width + cPoint.x].b, (*src)[cPoint.y*width + cPoint.x + 1].b) <= dt)
		{
			tPoint.x = cPoint.x + 1;
			tPoint.y = cPoint.y;
			pointQue.push(tPoint);

			(*dst)[tPoint.y*width + tPoint.x].b = 255;
			(*dst)[tPoint.y*width + tPoint.x].g = 255;
			(*dst)[tPoint.y*width + tPoint.x].r = 255;
		}
		//down
		if (cPoint.y + 1 < height && (*dst)[cPoint.y*width + cPoint.x + width].b < 255 &&
			__diff((*src)[cPoint.y*width + cPoint.x].b, (*src)[cPoint.y*width + cPoint.x + width].b) <= dt)
		{
			tPoint.x = cPoint.x;
			tPoint.y = cPoint.y + 1;
			pointQue.push(tPoint);

			(*dst)[tPoint.y*width + tPoint.x].b = 255;
			(*dst)[tPoint.y*width + tPoint.x].g = 255;
			(*dst)[tPoint.y*width + tPoint.x].r = 255;
		}
		//break;
	}//end while
}//end func

void img::devide_nonseed(Pixel* src, Pixel* dst, Pixel* dev, unsigned int min_len,
	unsigned char dt, QandQU &func, char flag)
{
	unsigned int width = src->Width();
	unsigned int height = src->Height();
	std::queue<unsigned int> indexQue;
	std::vector<unsigned int> indexVec((width / min_len + 1)*(height / min_len + 1));//叶子节点下标数组
	unsigned int tree_max, vec_max, near_max, nearSum, temp, t1, t2, t3, t4;

	near_max = ((width / 2) / min_len) + ((height / 2) / min_len);
	std::vector<unsigned int> nearIndex(near_max);//临近节点缓存
	unsigned char colort, tag;
	//short q1, q2;
	short q2;
	Rect c_rect, t_rect;

	if (!(width & height))
		return;

	tree_max = width > height ? width : height;
	tree_max = tree_max / min_len;
	if (tree_max <= 16)
	{
		tree_max = (unsigned int)pow(4.0, tree_max) / 3;
	}
	else //防溢出, 总数最多不能超过..., 否则内存过大
	{
		printf("ERROR: img::devide_nonseed: memory lack\n\tchange to up 30000000");
		tree_max = 30000000;
	}
	/*
	//防溢出, 总数最多不能超过..., 否则内存过大
	if (tree_max > 30000000)
	{
		//return;
		tree_max = 30000000;
	}
	tree_max = 30000000;
	*/
	Quadtree<Rect> tree(tree_max);
	//printf("img::devide_nonseed: tree_max=%d\n", tree_max);
	//初始化输出
	if (flag)
	{
		dst->SetSize(width, height);
		//dst->Fill(255, 255, 255, 0);
	}
	//分割
	//总尺寸大小的矩形作为根节点入队列
	c_rect.sx = 0;
	c_rect.sy = 0;
	c_rect.ex = width;
	c_rect.ey = height;
	c_rect.color = 0;//初始化颜色
	tree.add(0, 1, c_rect);//加入四叉树
	indexQue.push(0);//入队列
	while (!indexQue.empty())
	{
		temp = indexQue.front();
		indexQue.pop();
		c_rect = tree.getById(temp);
		//Q(Rect) == false
		if (temp != NULL_NODE && c_rect.Width() > min_len && c_rect.Height() > min_len &&
			func.Q(src, c_rect) > dt)
			//__Q(src, c_rect) > dt)
			//__Q(src, c_rect.sx, c_rect.sy, c_rect.ex, c_rect.ey) > dt)
		{
			//block 1
			t_rect.sx = c_rect.sx;
			t_rect.sy = c_rect.sy;
			t_rect.ex = c_rect.sx + c_rect.Width() / 2;
			t_rect.ey = c_rect.sy + c_rect.Height() / 2;
			t_rect.color = 0;
			indexQue.push(tree.add(temp, 1, t_rect));
			//block2
			t_rect.sx = c_rect.sx + c_rect.Width() / 2;
			t_rect.sy = c_rect.sy;
			t_rect.ex = c_rect.ex;
			t_rect.ey = c_rect.sy + c_rect.Height() / 2;
			t_rect.color = 0;
			indexQue.push(tree.add(temp, 2, t_rect));
			//block 3
			t_rect.sx = c_rect.sx;
			t_rect.sy = c_rect.sy + c_rect.Height() / 2;
			t_rect.ex = c_rect.sx + c_rect.Width() / 2;
			t_rect.ey = c_rect.ey;
			t_rect.color = 0;
			indexQue.push(tree.add(temp, 3, t_rect));
			//block 4
			t_rect.sx = c_rect.sx + c_rect.Width() / 2;
			t_rect.sy = c_rect.sy + c_rect.Height() / 2;
			t_rect.ex = c_rect.ex;
			t_rect.ey = c_rect.ey;
			t_rect.color = 0;
			indexQue.push(tree.add(temp, 4, t_rect));
		}//end if
	}//end while

	//绘制矩形
	if (dev != NULL)
	{
		dev->SetSize(width, height);
		dev->Fill(0, 0, 0, 0);

		for (t1 = 0; t1 < tree.sum(); t1++)
		{
			t_rect = tree.getById(t1);
			//水平边界
			t4 = t_rect.ey - 1;
			for (t2 = t_rect.sx; t2 < t_rect.ex; t2++)
			{
				(*dev)[t_rect.sy*width + t2].b = 255;
				(*dev)[t_rect.sy*width + t2].g = 255;
				(*dev)[t_rect.sy*width + t2].r = 255;
				//下边界
				//(*dst)[t4*width+t2].b = 255;
				//(*dst)[t4*width+t2].g = 255;
				//(*dst)[t4*width+t2].r = 255;
			}
			//垂直边界
			t4 = t_rect.ex - 1;
			for (t2 = t_rect.sy; t2 < t_rect.ey; t2++)
			{
				(*dev)[t2*width + t_rect.sx].b = 255;
				(*dev)[t2*width + t_rect.sx].g = 255;
				(*dev)[t2*width + t_rect.sx].r = 255;
				//右边界
				//(*dst)[t2*width+t4].b = 255;
				//(*dst)[t2*width+t4].g = 255;
				//(*dst)[t2*width+t4].r = 255;
			}
		}//end for tree.sum()
		//绘制最外层缺少的边框
		t4 = height*width - width;
		for (t2 = 0; t2 < width; t2++)
		{
			(*dev)[t4 + t2].b = 255;
			(*dev)[t4 + t2].g = 255;
			(*dev)[t4 + t2].r = 255;
		}
		t4 = width - 1;
		for (t2 = 0; t2 < height; t2++)
		{
			(*dev)[t2*width + t4].b = 255;
			(*dev)[t2*width + t4].g = 255;
			(*dev)[t2*width + t4].r = 255;
		}
	}//end if(dev != NULL)

	//区域合并
	//获取所有叶子节点
	t1 = tree.sum();
	vec_max = 0;
	for (temp = 0; temp < t1; temp++)
	{
		if (tree.isLeaf(temp))
		{
			indexVec[vec_max] = temp;
			vec_max++;
		}
	}

	//合并
	//printf("searching...\n");
	colort = 1;
	for (t1 = 0; t1 < vec_max; t1++)
	{
		c_rect = tree.getById(indexVec.at(t1));

		nearSum = 0;
		//q1 = __Q(src, c_rect);
		for (t2 = 0; t2 < vec_max; t2++)
		{
			if (t1 != t2)
			{
				tag = 0;
				t_rect = tree.getById(indexVec.at(t2));
				//判断是否临近
				if (c_rect.sy == t_rect.ey && (c_rect.sx == t_rect.sx || c_rect.ex == t_rect.ex))//up of c_rect
				{
					tag = 1;
				}
				else if (t_rect.sy == c_rect.ey && (t_rect.sx == c_rect.sx || t_rect.ex == c_rect.ex))//down of c_rect
				{
					tag = 2;
				}
				else if (c_rect.ex == t_rect.sx && (c_rect.sy == t_rect.sy || c_rect.ey == t_rect.ey))//right of c_rect
				{
					tag = 3;
				}
				else if (c_rect.sx == t_rect.ex && (c_rect.sy == t_rect.sy || c_rect.ey == t_rect.ey))//left of c_rect
				{
					tag = 4;
				}

				if (tag > 0)
				{
					//判断是否满足合并条件
					q2 = func.QU(src, c_rect, t_rect);
					if (q2 <= dt)
					{
						nearIndex[nearSum] = indexVec[t2];
						nearSum++;
					}
				}
			}//end if t1 != t2
		}//end for t2
		//get near color
		tag = 0;
		for (t2 = 0; t2 < nearSum; t2++)
		{
			if (tree.getById(nearIndex[t2]).color != 0)
			{
				tag = tree.getById(nearIndex[t2]).color;
				break;
			}
		}
		//new color
		if (tag == 0)
		{
			tag = colort;
			colort++;
		}
		//上色
		tree.getPtrById(indexVec[t1])->color = tag;
		for (t2 = 0; t2 < nearSum; t2++)
		{
			tree.getPtrById(nearIndex[t2])->color = tag;
		}
	}//end for t1

	//output
	//printf("output...\n");
	colort--;
	for (t1 = 0; t1 < vec_max; t1++)
	{
		c_rect = tree.getById(indexVec.at(t1));
		tag = c_rect.color*(256 / colort);
		for (t2 = c_rect.sy; t2 < c_rect.ey; t2++)
		{
			for (t3 = c_rect.sx; t3 < c_rect.ex; t3++)
			{
				(*dst)[t2*width + t3].b = tag;
				(*dst)[t2*width + t3].g = tag;
				(*dst)[t2*width + t3].r = tag;
			}//end for t3 < c_rect.ex
		}//end for t2 < c_erct.ey
	}//end for t1 <vec_max
}//end func

void img::hough_line(Pixel* src, Pixel* dst, unsigned char tcolor, unsigned short dt, char flag)
{
	unsigned int width, height;
	unsigned int si, ro, ro_max;
	unsigned int i, j;
	double a, b;

	unsigned short *hough = NULL;
	double si_v[180][2];

	width = src->Width();
	height = src->Height();

	if (!(width & height))
		return;

	ro_max = width*width + height*height;
	ro_max = sqrt(ro_max) + 1;
	printf("ro_max=%d\n", ro_max);
	hough = (unsigned short*)malloc(sizeof(short)*ro_max * 180);
	if (hough == NULL)
		return;
	//init
	j = ro_max * 180;
	for (i = 0; i < j; i++)
		hough[i] = 0;
	for (i = 0; i < 180; i++)
	{
		si_v[i][0] = sin(3.1415927*i / 180);
		si_v[i][1] = cos(3.1415927*i / 180);
	}

	if (flag)
	{
		dst->SetSize(width, height);
		dst->Fill(0, 0, 0, 0);
	}
	//printf("scan\n");
	//扫描
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if ((*src)[i*width + j].b > tcolor)
			{   //计数所有可能的直线
				for (si = 0; si < 180; si++)
				{
					//ro = x*cos(si) + y*sin(si)
					ro = i*si_v[si][0] + j*si_v[si][1];
					//hough[ro][si]
					if (ro < ro_max && hough[ro * 180 + si] < 0x7FFF)
						hough[ro * 180 + si]++;
				}//end for si < 180
			}//end if tcolor
		}//end for j
	}//end for i
	//printf("draw\n");
	//输出直线
	for (ro = 0; ro < ro_max; ro++)
	{
		for (si = 0; si < 180; si++)
		{   //大于阈值, 输出
			if (hough[ro * 180 + si] >= dt)
			{   //垂直直线, 不存在斜率
				if (si_v[si][0] < 0.00001)
				{
					if (ro < width)
					{
						//x = ro / cos(si), cos(si) = 1, x = ro
						j = 0;//j = i*width;
						for (i = 0; i < height; i++)
						{
							(*dst)[j + ro].b = 255;
							(*dst)[j + ro].g = 255;
							(*dst)[j + ro].r = 255;
							j += width;
						}//end for
					}//end if
				}
				else
				{
					//计算直线参数
					//y = (ro - x*cos(si))/sin(si)
					a = ro / si_v[si][0];
					b = si_v[si][1] / si_v[si][0];
					//输出
					for (j = 0; j < width; j++)
					{
						i = a - b*j;
						if (i < height && i >= 0)
						{
							(*dst)[i*width + j].b = 255;
							(*dst)[i*width + j].g = 255;
							(*dst)[i*width + j].r = 255;
						}//end if
					}//end for j
				}//end if...else
			}//end if hough >= dt
		}//end for si
	}//end for ro
	free(hough);
	//printf("finish\n");
}//end func

void img::mark_sequential(Pixel* src, Pixel* dst, unsigned char w, char flag)
{
	unsigned int width, height;
	unsigned int marks_len, i, j, k;
	unsigned char marks[10240][2];//等价表规则: marks[][0]<marks[][1], 只能将较大标记值等价为较小标记值
	unsigned char ucolor, colors[4], c_count, c_temp, c_temp2;

	width = src->Width();
	height = src->Height();
	if (!(width & height))
		return;
	if (flag)
	{
		dst->SetSize(width, height);
		dst->Fill(0, 0, 0, 0);
	}
	//第一次扫描, 标记相同的区域
	ucolor = 1;
	marks_len = 0;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if ((*dst)[i*width + j].b == 0)
			{
				//初始化四个方向的标记统计
				colors[0] = 0;
				colors[1] = 0;
				colors[2] = 0;
				colors[3] = 0;
				//left 只有临近区域和该区域属于同一区域时才统计其标记, 否则统计为未标记
				if (j > 0)
				{
					c_temp = (*src)[i*width + j].b > (*src)[i*width + j - 1].b ?
						(*src)[i*width + j].b - (*src)[i*width + j - 1].b : (*src)[i*width + j - 1].b - (*src)[i*width + j].b;
					if (c_temp <= w)
						colors[0] = (*dst)[i*width + j - 1].b;
					//left-top
					if (i > 0)
					{
						c_temp = (*src)[i*width + j].b > (*src)[i*width + j - width - 1].b ?
							(*src)[i*width + j].b - (*src)[i*width + j - width - 1].b : (*src)[i*width + j - width - 1].b - (*src)[i*width + j].b;
						if (c_temp <= w)
							colors[1] = (*dst)[i*width + j - width - 1].b;
					}
				}//end if j > 0
				//top
				if (i > 0)
				{
					c_temp = (*src)[i*width + j].b > (*src)[i*width + j - width].b ?
						(*src)[i*width + j].b - (*src)[i*width + j - width].b : (*src)[i*width + j - width].b - (*src)[i*width + j].b;
					if (c_temp <= w)
						colors[2] = (*dst)[i*width + j - width].b;
					//top-right
					if (j < width - 1)
					{
						c_temp = (*src)[i*width + j].b >(*src)[i*width + j - width + 1].b ?
							(*src)[i*width + j].b - (*src)[i*width + j - width + 1].b : (*src)[i*width + j - width + 1].b - (*src)[i*width + j].b;
						if (c_temp <= w)
							colors[3] = (*dst)[i*width + j - width + 1].b;
					}
				}//end if i > 0
				//统计已标记的邻近区域数量, 寻找最小标记值
				c_count = 0;
				c_temp = 255;//min
				for (k = 0; k < 4; k++)
				{
					if (colors[k] > 0)
					{
						c_count++;
						if (colors[k] < c_temp)
							c_temp = colors[k];
					}
				}
				//new color 临近区域没有标记
				if (c_count == 0)
				{
					(*dst)[i*width + j].b = ucolor;
					ucolor++;
				}
				//有标记区域
				else if (c_count >= 1)
				{
					//set color with min将最小标记值给目标区域
					(*dst)[i*width + j].b = c_temp;
					/*需要加入等价表的第一种情况
					* case: X-background, C-current, O-the same field with different marks
					* X X O
					* O C
					*/
					c_temp2 = colors[3] > colors[0] ? colors[3] : colors[0];//max
					c_temp = colors[3] > colors[0] ? colors[0] : colors[3];//min
					if (c_temp2 != c_temp && colors[0] > 0 && colors[3] > 0)
					{
						//add equal mark
						//查找表中是否含有相同的等价标记
						for (k = 0; k < marks_len; k++)
						{
							if (marks[k][0] == c_temp && marks[k][1] == c_temp2)
								break;
						}
						if (k >= marks_len)//no same equal不含相同的等价标记
						{
							//查找较小值的更小等价值
							for (k = 0; k < marks_len; k++)
							{
								if (marks[k][1] == c_temp)
									break;
							}
							//存在更小等价值, 换为更小的等价值
							if (k < marks_len)
								c_temp = marks[k][0];
							//添加等价标记
							if (marks_len < 10240)
							{
								marks[marks_len][0] = c_temp;
								marks[marks_len][1] = c_temp2;
								marks_len++;
							}
						}
					}//end if c_temp2 != c_temp
					/*需要加入等价表的第二种情况
					* case: X-background, C-current, O-the same field with different marks
					* O X O
					* X C
					*/
					c_temp2 = colors[3] > colors[1] ? colors[3] : colors[1];//max
					c_temp = colors[3] > colors[1] ? colors[1] : colors[3];//min
					if (c_temp2 != c_temp && colors[1] > 0 && colors[3] > 0)
					{
						//add equal mark
						//查找表中是否含有相同的等价标记
						for (k = 0; k < marks_len; k++)
						{
							if (marks[k][0] == c_temp && marks[k][1] == c_temp2)
								break;
						}
						if (k >= marks_len)//no same equal不含相同的等价标记
						{   //查找较小值的更小等价值
							for (k = 0; k < marks_len; k++)
							{
								if (marks[k][1] == c_temp)
									break;
							}
							//存在更小等价值, 换为更小的等价值
							if (k < marks_len)
								c_temp = marks[k][0];
							//添加等价标记
							if (marks_len < 10240)
							{
								marks[marks_len][0] = c_temp;
								marks[marks_len][1] = c_temp2;
								marks_len++;
							}
						}
					}//end if c_temp2 != c_temp
				}//end if c_count >= 1
			}//end if (*dst)[i*width+j].b
		}//end for j <width
	}//end for i<height
	/*printf("----mark----\n");
	for(k = 0; k < marks_len; k++)
	printf("%4d -> %4d\n", marks[k][1], marks[k][0]);
	printf("------------\nmarks_len=%d\n", marks_len);
	*/
	/*printf("----mark----\n");
	for(k = 0; k < marks_len; k++)
	printf("%4d -> %4d\n", marks[k][1], marks[k][0]);
	printf("------------\nmarks_len=%d\n", marks_len);
	*/
	//twice
	c_count = 255 / (ucolor - 1);
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			//从等价表中查找最小的等价标记
			c_temp = (*dst)[i*width + j].b;
			for (k = 0; k < marks_len; k++)
			{
				if (c_temp == marks[k][1] && marks[k][0] < c_temp)
				{
					c_temp = marks[k][0];
					//break;
				}
			}//end for k < marks_len
			//计算标记值对应的颜色, 输出
			c_temp = c_temp * c_count;
			(*dst)[i*width + j].b = c_temp;
			(*dst)[i*width + j].g = c_temp;
			(*dst)[i*width + j].r = c_temp;
		}//end for j < width
	}//end for i < height

}//end func

void img::contour_extraction(Pixel* src, Pixel* dst, unsigned char ocolor, char flag)
{
	unsigned int width, height;
	unsigned int i, j, near_field_count;

	width = src->Width();
	height = src->Height();
	if (!(width & height))
		return;
	if (flag)
	{
		dst->SetSize(width, height);
		dst->Fill(0, 0, 0, 0);
	}

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			//背景点设为黑色
			if ((*src)[i*width + j].b != ocolor)
			{
				(*dst)[i*width + j].b = 0;
				(*dst)[i*width + j].g = 0;
				(*dst)[i*width + j].r = 0;
			}
			else//统计8个临近像素
			{
				near_field_count = 0;
				//top 3 pixel
				if (i > 0)
				{
					if ((*src)[i*width + j - width].b == ocolor)
						near_field_count++;
					if (j > 0 && (*src)[i*width + j - width - 1].b == ocolor)
						near_field_count++;
					if (j + 1 < width && (*src)[i*width + j - width + 1].b == ocolor)
						near_field_count++;
				}
				//bottom 3 pixel
				if (i + 1 < height)
				{
					if ((*src)[i*width + j + width].b == ocolor)
						near_field_count++;
					if (j > 0 && (*src)[i*width + j + width - 1].b == ocolor)
						near_field_count++;
					if (j + 1 < width && (*src)[i*width + j + width + 1].b == ocolor)
						near_field_count++;
				}
				//left 1 pixel
				if (j > 0 && (*src)[i*width + j - 1].b == ocolor)
					near_field_count++;
				//right 1 pixel
				if (j + 1 < width && (*src)[i*width + j + 1].b == ocolor)
					near_field_count++;

				//judge
				//8个像素都是前景色时, 将当前像素设为0
				if (near_field_count == 8)
				{
					(*dst)[i*width + j].b = 0;
					(*dst)[i*width + j].g = 0;
					(*dst)[i*width + j].r = 0;
				}
				else
				{
					(*dst)[i*width + j].b = 255;
					(*dst)[i*width + j].g = 255;
					(*dst)[i*width + j].r = 255;
				}
			}//end if (*src)[i*width+j].b != ocolor else ...
		}//end for j < width
	}//end for i <height

}//end func


