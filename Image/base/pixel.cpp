#include "pixel.h"

#include "..\stdafx.h"
//非Visual Studio引用请添加下面头文件并删除stdafx.h
//#include <stdlib.h>
//#include <stdio.h>


Pixel::Pixel()
{
	width = 0;
	height = 0;
	pixel = NULL;
}

Pixel::Pixel(unsigned int width, unsigned int height)
{
	this->width = width;
	this->height = height;
	pixel = (PixelRGBA*)malloc(sizeof(PixelRGBA)*width*height);
}

Pixel::~Pixel()
{
	if (pixel)
		free(pixel);
	pixel = NULL;
	width = 0;
	height = 0;
}

void Pixel::SetSize(unsigned int width, unsigned int height)
{
	if (width && height)
	{
		if (pixel)
			free(pixel);
		this->width = width;
		this->height = height;
		pixel = (PixelRGBA*)malloc(sizeof(PixelRGBA)*width*height);
	}
}

void Pixel::Fill(unsigned char color_b, unsigned char color_g, unsigned char color_r, unsigned char color_a)
{
    unsigned int len = width*height;
    unsigned int i;
    for(i = 0; i < len; i++)
    {
        pixel[i].b = color_b;
        pixel[i].g = color_g;
        pixel[i].r = color_r;
        pixel[i].a = color_a;
    }
}

unsigned int Pixel::Width()
{
	return width;
}
unsigned int Pixel::Height()
{
	return height;
}

PixelRGBA& Pixel::operator[](unsigned int i)
{
	return pixel[i];
}

PixelRGBA& Pixel::At(unsigned int x, unsigned int y)
{
	return pixel[y*width + x];
}

void Pixel::ToGray()
{
	unsigned int i, j;
	unsigned int pix;

	for (i = 0; i<height; i++)
	{
		for (j = 0; j<width; j++)
		{
			//pix = pixel[i*width+j].r*0.299+pixel[i*width+j].g*0.587+pixel[i*width+j].b*0.114;
			pix = pixel[i*width + j].r * 306 + pixel[i*width + j].g * 601 + pixel[i*width + j].b * 117;
			//pix = pix / 1024;
			pix = pix >> 10;
			pixel[i*width + j].r = pix;
			pixel[i*width + j].g = pix;
			pixel[i*width + j].b = pix;
		}
	}
}
/*
void Pixel::Print()
{
	int i, j;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			printf("%d-%d-%d ", pixel[i*width + j].r, pixel[i*width + j].g, pixel[i*width + j].b);
		}
		printf("\n");
	}
}
*/
