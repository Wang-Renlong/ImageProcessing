#pragma once

#ifndef MAGIC_HPP
#define MAGIC_HPP

#include "../stdafx.h"

#include "../base/pixel.h"


namespace magic{
    //flag=0: ����ʼ��dst flag=1: ��ʼ��dst
    /* ͼ���ƶ�

     @src ����ͼ��
     @dst ���ͼ��
     @src_x ԭͼ�����ʼλ��X����, ����������λ��
     @src_y ԭͼ�����ʼλ��Y����, ����������λ��
     @dst_x ԭͼ��Xλ�ö�ӦĿ��ͼ���Xλ��, ����������λ��
     @dst_y ԭͼ��Yλ�ö�ӦĿ��ͼ���Xλ��, ����������λ��
     @w �ƶ�����Ŀ��, �����src_x
     @h �ƶ�����ĸ߶�, �����src_y
     @flag ��־λ, flag=1ʱ������dst�Ĵ�С����ʼ��
    */
	void moveTo(Pixel* src, Pixel* dst, unsigned int src_x, unsigned int src_y, unsigned int dst_x, unsigned int dst_y,
		unsigned int w, unsigned int h, char flag = 1);
	/*��ͼ������
    
    //����ȡ��
     @src ����ͼ��
     @dst ���ͼ��
     @dst_width ���ú�Ŀ��
     @dst_height ���ú�ĸ߶�
     @flag ��־λ, flag=1ʱ������dst�Ĵ�С����ʼ��
    */
	void reSize_Upper(Pixel* src, Pixel* dst, int dst_width, int dst_height, char flag = 1);
    //flag=0: ����ʼ��dst flag=1: ��ʼ��dst
	//�������� linear quadratic
	/*˫���Բ�ֵͼ������
    
     @src ����ͼ��
     @dst ���ͼ��
     @dst_width ���ú�Ŀ��
     @dst_height ���ú�ĸ߶�
     @flag ��־λ, flag=1ʱ������dst�Ĵ�С����ʼ��
    */
	void reSize_quadratic_linear(Pixel* src, Pixel* dst, unsigned int dst_width, unsigned int dst_height, char flag = 1);
	//flag=0: ����ʼ��dst flag=1: ��ʼ��dst
	/*X�᾵��
    
     @src ����ͼ��
     @dst ���ͼ��
     @flag ��־λ, flag=1ʱ������dst�Ĵ�С����ʼ��
    */
	void imageX(Pixel* src, Pixel* dst, char flag = 1);
	//flag=0: ����ʼ��dst flag=1: ��ʼ��dst
	/*Y�᾵��
    
     @src ����ͼ��
     @dst ���ͼ��
     @flag ��־λ, flag=1ʱ������dst�Ĵ�С����ʼ��
    */
	void imageY(Pixel* src, Pixel* dst, char flag = 1);
    //˽�к���, ��ȡ�ĸ��������ֵ
	inline long long max_in4(long long a, long long b, long long c, long long d);
	inline long long min_in4(long long a, long long b, long long c, long long d);
	/*��ת-����ת
    
     @src ����ͼ��
     @dst ���ͼ��
     @sinSi ��ת�Ƕ�sin
     @cosSi ��ת�Ƕ�cos, sin^2+cos^2����Ϊ1
     @flag ��־λ
     //flag=1: ����ԭͼƬ��������(���󻭲�) flag=2: �������߽�(ԭͼ��С) flag=0: �Զ����С(����ʼ��dst)
    */
	void rotateImg(Pixel* src, Pixel* dst, unsigned int ctr_x, unsigned int ctr_y, float sinSi, float cosSi, char flag = 1);
	/*��ת-�ٽ���ֵ
    
     @src ����ͼ��
     @dst ���ͼ��
     @sinSi ��ת�Ƕ�sin
     @cosSi ��ת�Ƕ�cos, sin^2+cos^2����Ϊ1
     @flag ��־λ
     //��ֹ��ת������ķ���ú��ȱ����, ���귴��ӳ��
     //flag=1: ����ԭͼƬ��������(���󻭲�) flag=2: �������߽�(ԭͼ��С) flag=0: �Զ����С(����ʼ��dst)
    */
	void rotateImgAdvanced(Pixel* src, Pixel* dst, unsigned int ctr_x, unsigned int ctr_y, float sinSi, float cosSi, char flag = 1);

	float sinSigma(float Si);

	float cosSigma(float Si);
	/*��ͼ
    
     @src ����ͼ��
     @pen ���ʹ켣, ������ɫֵΪ(255, 255, 255)���ǻ��ʵĹ켣��, ����ĵ�ᰴ��src�������
     @dst ���ͼ��
     @color ������ɫ
     @flag ��־λ, flag=1ʱ������dst�Ĵ�С����ʼ��
    */
	void paint(Pixel* src, Pixel* pen, Pixel* dst, PixelRGBA& color, char flag = 1);

}

#endif//MAGIC_HPP
