/*
* BMP format picture lib
* Author: Wang Ren Long
* All rights reserved.
*/
#ifndef IMAGE_H
#define IMAGE_H

#include "bitmap.h"
#include "pixel.h"
#include <stdio.h>

class Bmp{

public:
	Pixel* pixel;
private:
	RGBQUAD_* quid;
	FILE* fp;
	BITMAPFILEHEADER_ fileheader;
	BITMAPINFOHEADER_ infoheader;
	RGBQUAD_ *quad;
	unsigned int QUADlenth;
	unsigned width;
	unsigned height;

public:
	Bmp();
	//载入位图
	void LoadBitMap(const char *file, Pixel* pixel);
	//保存为24位位图
	void SaveBitMap(const char *file, Pixel* pixel);
	//保存为双色位图
	void Save2Bit(const char *file, Pixel* pixel);
	//保存为16色位图
	void Save16Bit(const char *file, Pixel* pixel);
	//保存为256色位图
	void Save256Bit(const char *file, Pixel* pixel);
	//保存为256色灰度位图
	void Save256GRAY(const char *file, Pixel* pixel, char isGray = 0);

	~Bmp();

private:
	void loadBI_RGB();
	void loadBI_RLE8();
	void loadBI_RLE4();
	void loadDOUBLE_COLOR(BYTE_* row, UINT_ lenth, UINT_ col);
	void loadCOLOR_16(BYTE_* row, UINT_ lenth, UINT_ col);
	void loadCOLOR_256(BYTE_* row, UINT_ lenth, UINT_ col);
	void loadTRUE_COLOR(BYTE_* row, UINT_ lenth, UINT_ col);



};

#endif // IMAGE_H

/*

当biBitCount=1时，8个像素占1个字节;
当biBitCount=4时，2个像素占1个字节;
当biBitCount=8时，1个像素占1个字节;
当biBitCount=24时,1个像素占3个字节;
Windows规定一个扫描行所占的字节数必须是4的倍数(即以long为单位),不足的以0填充，
一个扫描行所占的字节数计算方法:
DataSizePerLine= (biWidth* biBitCount+31)/8;
// 一个扫描行所占的字节数
DataSizePerLine= DataSizePerLine/4*4; // 字节数必须是4的倍数
位图数据的大小(不压缩情况下):
DataSize= DataSizePerLine* biHeight;

*/
