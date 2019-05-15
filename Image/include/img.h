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
	/*���ƺ�ɫͨ��
    
     @src ����ͼ��
     @dst ���ͼ��
    */
	void copyRedChannel(Pixel* src, Pixel* dst);
	/*������ɫͨ��
    
     @src ����ͼ��
     @dst ���ͼ��
    */
	void copyGreenChannel(Pixel* src, Pixel* dst);
	/*������ɫͨ��
    
     @src ����ͼ��
     @dst ���ͼ��
    */
	void copyBlueChannel(Pixel* src, Pixel* dst);
	/*�ҶȻ�
    
     @src ����ͼ��
     @dst ���ͼ��
    */
	void toGray(Pixel* src, Pixel* dst);
	/*��ɫ
    
     @src ����ͼ��
     @dst ���ͼ��
    */
	void AntiColor(Pixel* src, Pixel* dst);
	/*ֱ��ͼ���⻯
    
     @src ����ͼ��
     @dst ���ͼ��
    */
	void equalization(Pixel* src, Pixel* dst);
	/*��ֵ�ָ�-������ֵ
    
     @src ����ͼ��
     @dst ���ͼ��
     @t1 ��һ����ֵ С�ڵ�һ��ֵ�����ɫ#0
     @t2 �ڶ�����ֵ С�ڵڶ���ֵ�����ڵ�һ��ֵ�����ɫ#127 ���ڵڶ���ֵ���#255
     @flag ��־λ, flag=1ʱ������dst�Ĵ�С����ʼ��
    */
	void divide(Pixel* src, Pixel* dst, short t1, short t2, char flag = 1);
	/*ͳ�ƻҶ�ֱ����˽�к���
    
     @src ����ͼ��
     @counts ���ͳ�ƽ����һά����ָ��
     @counts_len counts����ĳ���
    */
	void __countGray(Pixel* src, unsigned int* counts, unsigned int counts_len);
	/*��ֵ�ָ�-��������
    
     @src ����ͼ��
     @t ��ʼ�Ҷ���ɫ��ֵ
     @dt �ж�������������С��ֵ��ֵ
     @return �ָ�ĻҶ���ɫ��ֵ
    */
	short t_devide_iterative(Pixel* src, short t, short dt);
	/*��ֵ�ָ�-otsu����
    
     @src ����ͼ��
     @return �ָ�ĻҶ���ɫ��ֵ
    */
	short t_devide_otsu(Pixel* src);
    //�������ӵ�����������ָ��˽�бȽϺ���
	unsigned char __diff(unsigned char color1, unsigned char color2);
	/*���ӵ�����������ָ�
    
     @src ����ͼ��
     @dst ���ͼ��
     @x ���ӵ�x����
     @y ���ӵ�y����
     @dt �ж��Ƿ��������ֵ,��������ӵ�����ز�ֵ<dt�ᱻ���
     @flag ��־λ, flag=1ʱ������dst�Ĵ�С����ʼ��
    */
	void devide_seed(Pixel* src, Pixel* dst, unsigned int x, unsigned int y, unsigned char dt, char flag = 1);
	/*�����ӵ�����, �ָ��㷨
    
     @src ����ͼ��
     @dst ���ͼ��
     @dev ��Ϊ��ָ��������ָ�Ľ��, ���ָ���ľ���
     @min_len ��С���εı߳�, С�����ֵ�ľ��β��ᱻ�ָ�
     @dt �ж��Ƿ�ָ��ϲ�����Сֵ, ������QandQU�ķ���ֵ���Ƚ�, < dtΪtrue
     @func ���������ж������Ķ���, QandQU�Ķ���������������
     @flag ��־λ, flag=1ʱ������dst�Ĵ�С����ʼ��
    */
    void devide_nonseed(Pixel* src, Pixel* dst, Pixel* dev, unsigned int min_len,
                        unsigned char dt, QandQU &func, char flag = 1);
	/*hough�任
    
     @src ����ͼ��
     @dst ���ͼ��
     @tcolor ��Ҫ������ɫ, ��ǰ��ɫ
     @dt �ж��Ƿ��������ֵ, ����ֵС�������ֵ��ֱ�߲������
     @flag ��־λ, flag=1ʱ������dst�Ĵ�С����ʼ��
    */
	void hough_line(Pixel* src, Pixel* dst, unsigned char tcolor, unsigned short dt, char flag = 1);
	/*������-�����(��Ժڰ׶�ֵͼ��, ���Դ���ҶȲ������ԵĻҶ�ͼ��)
    
     @src ����ͼ��
     @dst ���ͼ��
     @w �����������Сɫ��
     @flag ��־λ, flag=1ʱ������dst�Ĵ�С����ʼ��
    */
	void mark_sequential(Pixel* src, Pixel* dst, unsigned char w, char flag = 1);
    //����ǻ������и��Ż��ķ���, �ڵ�һ��ɨ��ʱ, ������ٽ����ѱ������,
    // �����ǰ����Ϊ�����ٽ��������С�ȼ۱��ֵ
	/*������ȡ(��Ժڰ׶�ֵͼ��)
    
     @src ����ͼ��
     @ocolor ǰ��ɫ�Ҷ�ֵ
     @dst ���ͼ��
     @flag ��־λ, flag=1ʱ������dst�Ĵ�С����ʼ��
    */
	void contour_extraction(Pixel* src, Pixel* dst, unsigned char ocolor, char flag = 1);

}

#endif // IMG_HPP_INCLUDED
