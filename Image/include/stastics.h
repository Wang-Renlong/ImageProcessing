/* 直方图和统计相关
*  Author: Wang RenLong
*  All rights reserved
*/
#pragma once

#ifndef STASTICS_HPP
#define STASTICS_HPP

#include "../stdafx.h"

#include "../base/pixel.h"


namespace stastics{
	/*直方图
     //必须输入灰度图像
     @src 输入图像
     @grap 输出图像, 即输出的直方图
    */
	void countGray(Pixel* src, Pixel* grap);
	/*直方图-带标记值
     //必须输入灰度图像
    
     @src 输入图像
     @grap 输出图像, 即输出的直方图
     @t1 第一阈值, 颜色为R^200, 如不需要请置-1
     @t2 第一阈值, 颜色为G^200, 如不需要请置-1
    */
	void countGrayWinthT(Pixel* src, Pixel* grap, short t1, short t2);
	/*灰度直方统计
     //必须输入灰度图像
    
     @src 输入图像
     @counts 输出的统计结果数组
     @counts_len counts数组长度
    */
	void countGray(Pixel* src, unsigned int* counts, unsigned int counts_len);


} // namespace end

#endif //STASTICS_HPP

