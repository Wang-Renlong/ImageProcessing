/*
* C++ Pixel Basic Class
* Author: Wang Ren Long
* All rights reserved.
*/
#pragma once
#ifndef PIXEL_H
#define PIXEL_H


typedef struct PixelRGBA{
	unsigned char b;
	unsigned char g;
	unsigned char r;
	unsigned char a;
}PixelRGBA;

class Pixel
{
private:
	unsigned int width;
	unsigned int height;
	PixelRGBA *pixel;

public:
	Pixel();
	Pixel(unsigned int width, unsigned int height);
	~Pixel();
	void SetSize(unsigned int width, unsigned int height);//���óߴ���������ͼ������
	void Fill(unsigned char color_b, unsigned char color_g, unsigned char color_r, unsigned char color_a);
	unsigned int Width();
	unsigned int Height();
	PixelRGBA& operator[](unsigned int i);
	PixelRGBA& At(unsigned int i, unsigned int j);
	//ת��Ϊ�Ҷ�ͼ��
	void ToGray();

	//void Print();
};

#endif
