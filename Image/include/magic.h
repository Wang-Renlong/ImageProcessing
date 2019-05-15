#pragma once

#ifndef MAGIC_HPP
#define MAGIC_HPP

#include "../stdafx.h"

#include "../base/pixel.h"


namespace magic{
    //flag=0: 不初始化dst flag=1: 初始化dst
    /* 图像移动

     @src 输入图像
     @dst 输出图像
     @src_x 原图像的起始位置X坐标, 可以是任意位置
     @src_y 原图像的起始位置Y坐标, 可以是任意位置
     @dst_x 原图像X位置对应目标图像的X位置, 可以是任意位置
     @dst_y 原图像Y位置对应目标图像的X位置, 可以是任意位置
     @w 移动区域的宽度, 相对于src_x
     @h 移动区域的高度, 相对于src_y
     @flag 标志位, flag=1时会重置dst的大小并初始化
    */
	void moveTo(Pixel* src, Pixel* dst, unsigned int src_x, unsigned int src_y, unsigned int dst_x, unsigned int dst_y,
		unsigned int w, unsigned int h, char flag = 1);
	/*简单图像缩放
    
    //向下取整
     @src 输入图像
     @dst 输出图像
     @dst_width 重置后的宽度
     @dst_height 重置后的高度
     @flag 标志位, flag=1时会重置dst的大小并初始化
    */
	void reSize_Upper(Pixel* src, Pixel* dst, int dst_width, int dst_height, char flag = 1);
    //flag=0: 不初始化dst flag=1: 初始化dst
	//二次线性 linear quadratic
	/*双线性插值图像缩放
    
     @src 输入图像
     @dst 输出图像
     @dst_width 重置后的宽度
     @dst_height 重置后的高度
     @flag 标志位, flag=1时会重置dst的大小并初始化
    */
	void reSize_quadratic_linear(Pixel* src, Pixel* dst, unsigned int dst_width, unsigned int dst_height, char flag = 1);
	//flag=0: 不初始化dst flag=1: 初始化dst
	/*X轴镜像
    
     @src 输入图像
     @dst 输出图像
     @flag 标志位, flag=1时会重置dst的大小并初始化
    */
	void imageX(Pixel* src, Pixel* dst, char flag = 1);
	//flag=0: 不初始化dst flag=1: 初始化dst
	/*Y轴镜像
    
     @src 输入图像
     @dst 输出图像
     @flag 标志位, flag=1时会重置dst的大小并初始化
    */
	void imageY(Pixel* src, Pixel* dst, char flag = 1);
    //私有函数, 获取四个数的最大值
	inline long long max_in4(long long a, long long b, long long c, long long d);
	inline long long min_in4(long long a, long long b, long long c, long long d);
	/*旋转-简单旋转
    
     @src 输入图像
     @dst 输出图像
     @sinSi 旋转角度sin
     @cosSi 旋转角度cos, sin^2+cos^2必须为1
     @flag 标志位
     //flag=1: 保留原图片所有像素(扩大画布) flag=2: 不保留边角(原图大小) flag=0: 自定义大小(不初始化dst)
    */
	void rotateImg(Pixel* src, Pixel* dst, unsigned int ctr_x, unsigned int ctr_y, float sinSi, float cosSi, char flag = 1);
	/*旋转-临近插值
    
     @src 输入图像
     @dst 输出图像
     @sinSi 旋转角度sin
     @cosSi 旋转角度cos, sin^2+cos^2必须为1
     @flag 标志位
     //防止旋转后产生的蜂窝煤空缺像素, 坐标反向映射
     //flag=1: 保留原图片所有像素(扩大画布) flag=2: 不保留边角(原图大小) flag=0: 自定义大小(不初始化dst)
    */
	void rotateImgAdvanced(Pixel* src, Pixel* dst, unsigned int ctr_x, unsigned int ctr_y, float sinSi, float cosSi, char flag = 1);

	float sinSigma(float Si);

	float cosSigma(float Si);
	/*绘图
    
     @src 输入图像
     @pen 画笔轨迹, 其中颜色值为(255, 255, 255)的是画笔的轨迹点, 其余的点会按照src内容输出
     @dst 输出图像
     @color 画笔颜色
     @flag 标志位, flag=1时会重置dst的大小并初始化
    */
	void paint(Pixel* src, Pixel* pen, Pixel* dst, PixelRGBA& color, char flag = 1);

}

#endif//MAGIC_HPP
