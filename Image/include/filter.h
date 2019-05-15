#pragma once

#ifndef FILTER_HPP
#define FILTER_HPP

#include "../stdafx.h"

#include "../base/pixel.h"
#include "window.h"

namespace filter{
    //Ͱ����-˽�к���
    /*
     @src ��������
     @len �������ݳ���
    */
	void inline pix_sort(unsigned char* src, int len);
	/*�Ҷ�ͼ��ֵ�˲�
    
     @src ����ͼ��
     @dst ���ͼ��
     @wnd �˲�����
    */
	void midGRAY(Pixel* src, Pixel* dst, Window& wnd);
	/*��ֵ�˲�
    
     @src ����ͼ��
     @dst ���ͼ��
     @wnd �˲�����
    */
	void mid(Pixel* src, Pixel* dst, Window& wnd);
	/*��ֵ�˲�
    
     @src ����ͼ��
     @dst ���ͼ��
     @wnd �˲�����, ���������λ�õ�Ȩֵ, ��kernel
    */
	void avg(Pixel* src, Pixel* dst, Window& wnd);
	void avg(Pixel* src, Pixel* dst, Window* wnd);
	/*���˲� ֻ���ݴ��ڶ�ͼƬ���򵥵ľ��
    
     @src ����ͼ��
     @dst ���ͼ��
     @wnd �˲�����, ���������λ�õ�Ȩֵ, ��kernel
    */
	void simple(Pixel* src, Pixel* dst, Window* wnd);
	/*���ؼ��, ֧��LoG���˲��ں�
    
     @src ����ͼ��
     @dst ���ͼ��
     @wnd �˲�����, ���������λ�õ�Ȩֵ, ��kernel
    */
	void edge_detection(Pixel* src, Pixel* dst, Window* wnd);
	/*Canny���ؼ��
    
     @src ����ͼ��
     @dst ���ͼ��
     @low ��ͨ��ֵ
     @high ��ͨ��ֵ
    */
	void edge_detection_canny(Pixel* src, Pixel* dst, unsigned short low, unsigned short high);

}


#endif // FILTER_HPP
