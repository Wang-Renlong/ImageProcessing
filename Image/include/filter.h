#pragma once

#ifndef FILTER_HPP
#define FILTER_HPP

#include "../stdafx.h"

#include "../base/pixel.h"
#include "window.h"

namespace filter{
    //桶排序-私有函数
    /*
     @src 输入数据
     @len 输入数据长度
    */
	void inline pix_sort(unsigned char* src, int len);
	/*灰度图中值滤波
    
     @src 输入图像
     @dst 输出图像
     @wnd 滤波窗口
    */
	void midGRAY(Pixel* src, Pixel* dst, Window& wnd);
	/*中值滤波
    
     @src 输入图像
     @dst 输出图像
     @wnd 滤波窗口
    */
	void mid(Pixel* src, Pixel* dst, Window& wnd);
	/*均值滤波
    
     @src 输入图像
     @dst 输出图像
     @wnd 滤波窗口, 需包含各个位置的权值, 即kernel
    */
	void avg(Pixel* src, Pixel* dst, Window& wnd);
	void avg(Pixel* src, Pixel* dst, Window* wnd);
	/*简单滤波 只根据窗口对图片做简单的卷积
    
     @src 输入图像
     @dst 输出图像
     @wnd 滤波窗口, 需包含各个位置的权值, 即kernel
    */
	void simple(Pixel* src, Pixel* dst, Window* wnd);
	/*边沿检测, 支持LoG等滤波内核
    
     @src 输入图像
     @dst 输出图像
     @wnd 滤波窗口, 需包含各个位置的权值, 即kernel
    */
	void edge_detection(Pixel* src, Pixel* dst, Window* wnd);
	/*Canny边沿检测
    
     @src 输入图像
     @dst 输出图像
     @low 低通阈值
     @high 高通阈值
    */
	void edge_detection_canny(Pixel* src, Pixel* dst, unsigned short low, unsigned short high);

}


#endif // FILTER_HPP
