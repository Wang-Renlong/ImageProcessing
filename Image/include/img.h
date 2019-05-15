#pragma once

#ifndef IMG_HPP_INCLUDED
#define IMG_HPP_INCLUDED

#include "../stdafx.h"

#include "../base/pixel.h"
#include <queue>
#include <vector>
#include <math.h>
#include "../base/point.h"
#include "../base/rect.h"
#include "../base/quadtree.h"
#include "q_and_qu.h"
//#include "stastics.hpp"

namespace img{
	/*复制红色通道
    
     @src 输入图像
     @dst 输出图像
    */
	void copyRedChannel(Pixel* src, Pixel* dst);
	/*复制绿色通道
    
     @src 输入图像
     @dst 输出图像
    */
	void copyGreenChannel(Pixel* src, Pixel* dst);
	/*复制蓝色通道
    
     @src 输入图像
     @dst 输出图像
    */
	void copyBlueChannel(Pixel* src, Pixel* dst);
	/*灰度化
    
     @src 输入图像
     @dst 输出图像
    */
	void toGray(Pixel* src, Pixel* dst);
	/*反色
    
     @src 输入图像
     @dst 输出图像
    */
	void AntiColor(Pixel* src, Pixel* dst);
	/*直方图均衡化
    
     @src 输入图像
     @dst 输出图像
    */
	void equalization(Pixel* src, Pixel* dst);
	/*阈值分割-给定阈值
    
     @src 输入图像
     @dst 输出图像
     @t1 第一个阈值 小于第一阈值输出颜色#0
     @t2 第二个阈值 小于第二阈值但大于第一阈值输出颜色#127 大于第二阈值输出#255
     @flag 标志位, flag=1时会重置dst的大小并初始化
    */
	void divide(Pixel* src, Pixel* dst, short t1, short t2, char flag = 1);
	/*统计灰度直方的私有函数
    
     @src 输入图像
     @counts 存放统计结果的一维数组指针
     @counts_len counts数组的长度
    */
	void __countGray(Pixel* src, unsigned int* counts, unsigned int counts_len);
	/*阈值分割-迭代方法
    
     @src 输入图像
     @t 初始灰度颜色阈值
     @dt 判定结束迭代的最小阈值差值
     @return 分割的灰度颜色阈值
    */
	short t_devide_iterative(Pixel* src, short t, short dt);
	/*阈值分割-otsu方法
    
     @src 输入图像
     @return 分割的灰度颜色阈值
    */
	short t_devide_otsu(Pixel* src);
    //用于种子点增长的区域分割的私有比较函数
	unsigned char __diff(unsigned char color1, unsigned char color2);
	/*种子点增长的区域分割
    
     @src 输入图像
     @dst 输出图像
     @x 种子点x坐标
     @y 种子点y坐标
     @dt 判定是否输出的阈值,如果和种子点的像素差值<dt会被输出
     @flag 标志位, flag=1时会重置dst的大小并初始化
    */
	void devide_seed(Pixel* src, Pixel* dst, unsigned int x, unsigned int y, unsigned char dt, char flag = 1);
	/*无种子点增长, 分割算法
    
     @src 输入图像
     @dst 输出图像
     @dev 不为空指针则输出分割的结果, 即分割出的矩形
     @min_len 最小矩形的边长, 小于这个值的矩形不会被分割
     @dt 判定是否分割或合并的最小值, 用来和QandQU的返回值做比较, < dt为true
     @func 包含两个判定函数的对象, QandQU的对象或者其子类对象
     @flag 标志位, flag=1时会重置dst的大小并初始化
    */
    void devide_nonseed(Pixel* src, Pixel* dst, Pixel* dev, unsigned int min_len,
                        unsigned char dt, QandQU &func, char flag = 1);
	/*hough变换
    
     @src 输入图像
     @dst 输出图像
     @tcolor 需要检测的颜色, 即前景色
     @dt 判定是否输出的阈值, 计数值小于这个阈值的直线不会输出
     @flag 标志位, flag=1时会重置dst的大小并初始化
    */
	void hough_line(Pixel* src, Pixel* dst, unsigned char tcolor, unsigned short dt, char flag = 1);
	/*区域标记-序贯标记(针对黑白二值图像, 可以处理灰度差异明显的灰度图像)
    
     @src 输入图像
     @dst 输出图像
     @w 划分区域的最小色差
     @flag 标志位, flag=1时会重置dst的大小并初始化
    */
	void mark_sequential(Pixel* src, Pixel* dst, unsigned char w, char flag = 1);
    //序贯标记还可以有更优化的方法, 在第一次扫描时, 如果有临近的已标记区域,
    // 则给当前点设为所有临近区域的最小等价标记值
	/*轮廓提取(针对黑白二值图像)
    
     @src 输入图像
     @ocolor 前景色灰度值
     @dst 输出图像
     @flag 标志位, flag=1时会重置dst的大小并初始化
    */
	void contour_extraction(Pixel* src, Pixel* dst, unsigned char ocolor, char flag = 1);

}

#endif // IMG_HPP_INCLUDED
