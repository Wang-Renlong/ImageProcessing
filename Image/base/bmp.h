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
	//����λͼ
	void LoadBitMap(const char *file, Pixel* pixel);
	//����Ϊ24λλͼ
	void SaveBitMap(const char *file, Pixel* pixel);
	//����Ϊ˫ɫλͼ
	void Save2Bit(const char *file, Pixel* pixel);
	//����Ϊ16ɫλͼ
	void Save16Bit(const char *file, Pixel* pixel);
	//����Ϊ256ɫλͼ
	void Save256Bit(const char *file, Pixel* pixel);
	//����Ϊ256ɫ�Ҷ�λͼ
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

��biBitCount=1ʱ��8������ռ1���ֽ�;
��biBitCount=4ʱ��2������ռ1���ֽ�;
��biBitCount=8ʱ��1������ռ1���ֽ�;
��biBitCount=24ʱ,1������ռ3���ֽ�;
Windows�涨һ��ɨ������ռ���ֽ���������4�ı���(����longΪ��λ),�������0��䣬
һ��ɨ������ռ���ֽ������㷽��:
DataSizePerLine= (biWidth* biBitCount+31)/8;
// һ��ɨ������ռ���ֽ���
DataSizePerLine= DataSizePerLine/4*4; // �ֽ���������4�ı���
λͼ���ݵĴ�С(��ѹ�������):
DataSize= DataSizePerLine* biHeight;

*/
