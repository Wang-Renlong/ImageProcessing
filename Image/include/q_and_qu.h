#pragma once

#ifndef Q_AND_QU_H
#define Q_AND_QU_H

#include "../stdafx.h"
#include "../base/pixel.h"
#include "../base/rect.h"

namespace img{
    //用于无种子点划分d判定函数,输入为矩形的位置和大小, 输出值和给定的dt做比较,
    // <dt为true
    class QandQU{
    public:
        //单个区域的判定函数
        short Q(Pixel* src, Rect& r);
        //两个区域的判定函数
        short QU(Pixel* src, Rect& r1, Rect& r2);

    };

}

#endif // Q_AND_QU_H

/*


    short __Q(Pixel* src, Rect& r)
    {
        unsigned int tx, ty;
        unsigned int width = src->Width();
        //unsigned int height = src->Height();
        unsigned int sum = 0, colorSum = 0;
        unsigned char colorHigh = 0, colorLow = 255;
        sum = r.Width()*r.Height();
        for(ty = r.sy; ty < r.ey; ty++)
        {
            for(tx = r.sx; tx < r.ex; tx++)
            {
                colorSum += (*src)[ty*width+tx].b;
                //
                if((*src)[ty*width+tx].b > colorHigh)
                    colorHigh = (*src)[ty*width+tx].b;
                if((*src)[ty*width+tx].b < colorLow)
                    colorLow = (*src)[ty*width+tx].b;
            }
        }
        colorSum = colorSum / sum;
        //debug
        //printf("max=%d, min=%d, avg=%d\n", colorHigh, colorLow, colorSum);
        if(colorHigh - colorSum < 1 || colorSum - colorLow < 1)
            return 0;
        else
            return 10;
    }

    short __QU(Pixel* src, Rect& r1, Rect& r2)
    {
        unsigned int tx, ty;
        unsigned int width = src->Width();
        unsigned int sum1 = 0, colorSum1 = 0;
        unsigned int sum2 = 0, colorSum2 = 0;
        //unsigned char colorHigh = 0, colorLow = 255;

        sum1 = r1.Width()*r1.Height();
        sum2 = r2.Width()*r2.Height();
        //t1
        for(ty = r1.sy; ty < r1.ey; ty++)
        {
            for(tx = r1.sx; tx < r1.ex; tx++)
            {
                colorSum1 += (*src)[ty*width+tx].b;
                //
                //if((*src)[ty*width+tx].b > colorHigh)
                //    colorHigh = (*src)[ty*width+tx].b;
                //if((*src)[ty*width+tx].b < colorLow)
                //    colorLow = (*src)[ty*width+tx].b;
            }
        }
        //t2
        for(ty = r2.sy; ty < r2.ey; ty++)
        {
            for(tx = r2.sx; tx < r2.ex; tx++)
            {
                colorSum2 += (*src)[ty*width+tx].b;
                //
                //if((*src)[ty*width+tx].b > colorHigh)
                //    colorHigh = (*src)[ty*width+tx].b;
                //if((*src)[ty*width+tx].b < colorLow)
                //    colorLow = (*src)[ty*width+tx].b;
            }
        }
        //if(colorSum / sum < 60 && colorHigh - colorLow < 10)
        //    return 0;
        //else
        //    return 10;
        //return colorSum / sum;
        //colorSum = colorSum / sum;
        colorSum1 = colorSum1 / sum1;
        colorSum2 = colorSum2 / sum2;
        if(colorSum1 > colorSum2)
            colorSum1 -= colorSum2;
        else
            colorSum1 = colorSum2 - colorSum1;
        if(colorSum1 < 40)
            return 0;
        else
            return 10;
        //debug
        //printf("max=%d, min=%d, avg=%d\n", colorHigh, colorLow, colorSum);
        //if(colorHigh - colorSum < 8 || colorSum - colorLow < 8)
        //    return 0;
        //else
        //    return 10;

    }


*/
