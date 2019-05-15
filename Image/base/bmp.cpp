#include "bmp.h"

#include "..\stdafx.h"
#include "bitmap.h"
//��Visual Studio�������������ͷ�ļ���ɾ��stdafx.h
//#include "structs.h"
//#include <stdlib.h>


void saveDebug(PixelRGBA* pixel, unsigned int countp)
{
	FILE* fp = NULL;// = fopen("debug.dat", "wb");
	fopen_s(&fp, "debug.dat", "wb");
	fwrite(pixel, sizeof(PixelRGBA), countp, fp);
	fclose(fp);
}

Bmp::Bmp()
{
}

void Bmp::LoadBitMap(const char *file, Pixel* pixel)
{
	if (pixel == NULL)
		return;
	this->pixel = pixel;
	quad = NULL;
	//fp = fopen(file, "rb");
	fp = NULL;
	fopen_s(&fp, file, "rb");
	if (fp == NULL)
		return;
	//��ȡλͼ�ļ�ͷ�����ﲻ��ֱ�Ӷ��ṹ�壬�ṹ��ռ��16�ֽڣ�ʵ��ֻ��14�ֽ�
	fread(&fileheader.bfType, sizeof(UINT16_), 1, fp);
	fread(&fileheader.bfSize, sizeof(DWORD_), 1, fp);
	fread(&fileheader.bfReserved1, sizeof(UINT16_), 1, fp);
	fread(&fileheader.bfReserved2, sizeof(UINT16_), 1, fp);
	fread(&fileheader.bfOffBits, sizeof(DWORD_), 1, fp);
	//�����ļ�ͷ�ж��Ƿ���bmp��ʽ
	if (fileheader.bfType != 0x4D42)
	{
		fclose(fp);
		this->pixel = NULL;
		return;
	}
	//��ȡλͼ��Ϣͷ
	fread(&infoheader, sizeof(BITMAPINFOHEADER_), 1, fp);
	width = infoheader.biWidth;
	height = infoheader.biHeight;
	//λͼλ���жϣ��Դ��������ɫ���С
	if (infoheader.biBitCount == DOUBLE_COLOR)
		QUADlenth = 2;
	else if (infoheader.biBitCount == COLOR_16)
		QUADlenth = 16;
	else if (infoheader.biBitCount == COLOR_256)
		QUADlenth = 256;
	else if (infoheader.biBitCount >= COLOR_64K)
		QUADlenth = 0;
	//���ʵ��ʹ�õ���ɫ����ȱʡ����С�������ɫ����ȡʵ��ʹ����ɫ��������ɫ���С
	if (infoheader.biClrUsed != 0 && infoheader.biClrUsed < QUADlenth)
		QUADlenth = infoheader.biClrUsed;
	//��ɫ����ڣ�Ϊ��ɫ�������ڴ�
	if (QUADlenth != 0)
	{
		quad = (RGBQUAD_*)malloc(sizeof(RGBQUAD_)*QUADlenth);
		if (quad == NULL)
			return;
		//��ȡ��ɫ��
		fread(quad, sizeof(RGBQUAD_), QUADlenth, fp);
	}
	//λͼѹ����ʽ�ж�
	if (infoheader.biComression == BI_RGB)
		loadBI_RGB();
	else if (infoheader.biComression == BI_RLE4)
		loadBI_RLE4();
	else if (infoheader.biComression == BI_RLE8)
		loadBI_RLE8();

	fclose(fp);
	if (quad)
	    free(quad);
	quad = NULL;
	this->pixel = NULL;
}

void Bmp::SaveBitMap(const char *file, Pixel* pixel)
{
	unsigned long stdWidth;
	//BYTE_ blank = 0;
	int i, j, k;
	BYTE_ *row;

    //pixel����
	if (pixel == NULL)
		return;
	this->pixel = pixel;

	//���óߴ�
	width = pixel->Width();
	height = pixel->Height();
	if (width*height == 0)
		return;

    //���ļ�
	//fp = fopen(file, "wb");
	fp = NULL;
	fopen_s(&fp, file, "wb");
	if (fp == NULL)
		return;

	//����ÿ�е��ֽ���
	stdWidth = width * 3;
	i = stdWidth % 4;
	if (i>0)
		stdWidth = stdWidth + 4 - i;
	//�����ļ�ͷ
	fileheader.bfType = 0x4D42;
	fileheader.bfSize = stdWidth*height + 54;
	fileheader.bfReserved1 = 0;
	fileheader.bfReserved2 = 0;
	fileheader.bfOffBits = 54;
	//����λͼ��Ϣͷ
	infoheader.biSize = 40;
	infoheader.biWidth = width;
	infoheader.biHeight = height;
	infoheader.biPlanes = 1;
	infoheader.biBitCount = 24;
	infoheader.biComression = 0;
	infoheader.biSizeImage = stdWidth*height;
	infoheader.biXPelsPerMeter = 96;
	infoheader.biYPelsPerMeter = 96;
	infoheader.biClrUsed = 0;
	infoheader.biClrImportant = 0;
	//д��ͷ����Ϣ
	fwrite(&fileheader.bfType, sizeof(UINT16_), 1, fp);
	fwrite(&fileheader.bfSize, sizeof(DWORD_), 1, fp);
	fwrite(&fileheader.bfReserved1, sizeof(UINT16_), 1, fp);
	fwrite(&fileheader.bfReserved2, sizeof(UINT16_), 1, fp);
	fwrite(&fileheader.bfOffBits, sizeof(DWORD_), 1, fp);
	fwrite(&infoheader, sizeof(BITMAPINFOHEADER_), 1, fp);

	//�л���
	row = (BYTE_*)malloc(sizeof(BYTE_)*stdWidth);
	//�����һ�п�ʼ����
	for (i = height - 1; i >= 0; i--)
	{
		k = 0;
		for (j = 0; j<width; j++)
		{
			row[k] = ((*pixel)[i*width + j].b);
			k++;
			row[k] = ((*pixel)[i*width + j].g);
			k++;
			row[k] = ((*pixel)[i*width + j].r);
			k++;
		}
		//j = j*3;
		//ʣ�ಿ�����0������4�ı���
		for (; k<stdWidth; k++)
		{
			row[k] = 0;
		}
		//д��һ��
		fwrite(row, sizeof(BYTE_)*stdWidth, 1, fp);
		//break;
	}
	free(row);
	fclose(fp);
	this->pixel = NULL;
}

void Bmp::Save2Bit(const char *file, Pixel* pixel)
{
	unsigned long stdWidth;
	//BYTE_ blank = 0;
	int i, j, k, clen;
	BYTE_ *row;

    //pixel����
	if (pixel == NULL)
		return;
	this->pixel = pixel;

	//���óߴ�
	width = pixel->Width();
	height = pixel->Height();
	if (width*height == 0)
		return;

    //���ļ�
	//fp = fopen(file, "wb");
	fp = NULL;
	fopen_s(&fp, file, "wb");
	if (fp == NULL)
		return;

	//����ÿ�е��ֽ���
	stdWidth = int(width / 8);
	if (width % 8>0)
		stdWidth++;
	i = stdWidth % 4;
	if (i>0)
		stdWidth = stdWidth + 4 - i;
	//�����ļ�ͷ
	fileheader.bfType = 0x4D42;
	fileheader.bfSize = stdWidth*height + 54 + sizeof(RGBQUAD_)* 2;
	fileheader.bfReserved1 = 0;
	fileheader.bfReserved2 = 0;
	fileheader.bfOffBits = 54 + sizeof(RGBQUAD_)* 2;
	//����λͼ��Ϣͷ
	infoheader.biSize = 40;
	infoheader.biWidth = width;
	infoheader.biHeight = height;
	infoheader.biPlanes = 1;
	infoheader.biBitCount = 1;
	infoheader.biComression = 0;
	infoheader.biSizeImage = stdWidth*height;
	infoheader.biXPelsPerMeter = 96;
	infoheader.biYPelsPerMeter = 96;
	infoheader.biClrUsed = 2; // ?
	infoheader.biClrImportant = 0;
	//д��
	fwrite(&fileheader.bfType, sizeof(UINT16_), 1, fp);
	fwrite(&fileheader.bfSize, sizeof(DWORD_), 1, fp);
	fwrite(&fileheader.bfReserved1, sizeof(UINT16_), 1, fp);
	fwrite(&fileheader.bfReserved2, sizeof(UINT16_), 1, fp);
	fwrite(&fileheader.bfOffBits, sizeof(DWORD_), 1, fp);
	fwrite(&infoheader, sizeof(BITMAPINFOHEADER_), 1, fp);
	//��ɫ��
	quad = (RGBQUAD_*)malloc(sizeof(RGBQUAD_)* 2);
	if (quad == NULL)
		return;
	//��
	quad[0].rgbBlue = 0;
	quad[0].rgbGreen = 0;
	quad[0].rgbRed = 0;
	quad[0].rgbReserved = 0;
	//��
	quad[1].rgbBlue = 255;
	quad[1].rgbGreen = 255;
	quad[1].rgbRed = 255;
	quad[1].rgbReserved = 0;

	fwrite(quad, sizeof(RGBQUAD_)* 2, 1, fp);

	row = (BYTE_*)malloc(sizeof(BYTE_)*stdWidth);

	//clen=0;
	for (i = height - 1; i >= 0; i--)
	{
		clen = 0;
		for (j = 0; j<stdWidth; j++)
		{
			//˫ɫͼ8������ռ��һ���ֽ�
			row[j] = 0;
			for (k = 0; k<8 && clen + k<width; k++)
			{
				row[j] = row[j] << 1;
				if ((*pixel)[i*width + clen + k].r>127 && (*pixel)[i*width + clen + k].g>127 && (*pixel)[i*width + clen + k].b>127)
					row[j] += 1;
				else
					row[j] += 0;
				//һ�н�β����8��������
				if (clen + k + 1 == width)
				{
					row[j] = row[j] << (7 - k);
					//row[j] = row[j] << 7 - k;
				}
			}
			clen += 8;
		}
		fwrite(row, sizeof(BYTE_)*stdWidth, 1, fp);
		//break;
	}
	free(row);
	free(quad);
	quad = NULL;
	this->pixel = NULL;
	fclose(fp);
}

void Bmp::Save16Bit(const char *file, Pixel* pixel)
{

}

void Bmp::Save256Bit(const char *file, Pixel* pixel)
{

}

void Bmp::Save256GRAY(const char *file, Pixel* pixel, char isGray)
{
	unsigned long stdWidth;
	//BYTE_ blank = 0;
	int i, j;
	unsigned int gray;
	BYTE_ *row;

	//fp = fopen(file, "wb");
	fp = NULL;
	fopen_s(&fp, file, "wb");
	if (fp == NULL)
		return;
	if (pixel == NULL)
		return;
	this->pixel = pixel;
	//���óߴ�
	width = pixel->Width();
	height = pixel->Height();
	if (width*height == 0)
		return;

	//����ÿ�е��ֽ���
    stdWidth = width % 4;
    if (stdWidth>0)
        stdWidth = width + 4 - stdWidth;
    else
        stdWidth = width;

	//�����ļ�ͷ
	fileheader.bfType = 0x4D42;
	fileheader.bfSize = stdWidth*height + 54 + sizeof(RGBQUAD_)*256;
	fileheader.bfReserved1 = 0;
	fileheader.bfReserved2 = 0;
	fileheader.bfOffBits = 54 + sizeof(RGBQUAD_)*256;
	//����λͼ��Ϣͷ
	infoheader.biSize = 40;
	infoheader.biWidth = width;
	infoheader.biHeight = height;
	infoheader.biPlanes = 1;
	infoheader.biBitCount = 8;
	infoheader.biComression = 0;
	infoheader.biSizeImage = stdWidth*height;
	infoheader.biXPelsPerMeter = 96;
	infoheader.biYPelsPerMeter = 96;
	infoheader.biClrUsed = 256; // ?
	infoheader.biClrImportant = 0;
	//д��
	fwrite(&fileheader.bfType, sizeof(UINT16_), 1, fp);
	fwrite(&fileheader.bfSize, sizeof(DWORD_), 1, fp);
	fwrite(&fileheader.bfReserved1, sizeof(UINT16_), 1, fp);
	fwrite(&fileheader.bfReserved2, sizeof(UINT16_), 1, fp);
	fwrite(&fileheader.bfOffBits, sizeof(DWORD_), 1, fp);
	fwrite(&infoheader, sizeof(BITMAPINFOHEADER_), 1, fp);
	//��ɫ��
	quad = (RGBQUAD_*)malloc(sizeof(RGBQUAD_)* 256);
	if (quad == NULL)
		return;
	//���ɵ�ɫ������
	for(i=0;i<256;i++)
    {
        quad[i].rgbBlue = i;
        quad[i].rgbGreen = i;
        quad[i].rgbRed = i;
        quad[i].rgbReserved = 0;
    }

	fwrite(quad, sizeof(RGBQUAD_)* 256, 1, fp);

	row = (BYTE_*)malloc(sizeof(BYTE_)*stdWidth);
	if(row == NULL)
    {
        free(quad);
        return;
    }

	for (i = height - 1; i >= 0; i--)
	{
		for (j = 0; j<width; j++)
		{
		    if(isGray)
                row[j] = (*pixel)[i*width+j].g;
            else
            {
		        gray = (*pixel)[i*width+j].r * 306 + (*pixel)[i*width+j].g * 601 + (*pixel)[i*width+j].b * 117;
			    row[j] = gray >> 10;
            }
		}
		for(;j<stdWidth;j++)
            row[j] = 0;
		fwrite(row, sizeof(BYTE_)*stdWidth, 1, fp);
		//break;
	}
	free(row);
	free(quad);
	quad = NULL;
	this->pixel = NULL;
	fclose(fp);
}

Bmp::~Bmp()
{
}

void Bmp::loadBI_RGB()
{
	unsigned int i;
	//unsigned long sumBit;
	BYTE_* row;
	unsigned long stdWidth;

	//����ÿ�е��ֽ���
	if (infoheader.biBitCount == DOUBLE_COLOR) //˫ɫͼ
	{
		stdWidth = int(width / 8);
		if (width % 8>0)
			stdWidth++;
		i = stdWidth % 4;
		if (i>0)
			stdWidth = stdWidth + 4 - i;

	}
	else if (infoheader.biBitCount == COLOR_16) //4λͼ
	{
		stdWidth = int(width / 2);
		if (width % 2>0)
			stdWidth++;
		i = stdWidth % 4;
		if (i>0)
			stdWidth = stdWidth + 4 - i;
	}
	else if (infoheader.biBitCount == COLOR_256) //8λͼ
	{
		stdWidth = width % 4;
		if (stdWidth>0)
			stdWidth = width + 4 - stdWidth;
	}
	else if (infoheader.biBitCount == TRUE_COLOR) //���ɫ
	{
		stdWidth = width * 3;
		i = stdWidth % 4;
		if (i>0)
			stdWidth = stdWidth + 4 - i;
	}
	//��ʼ������
	//sumBit = width*height;
	//�����л���ռ�
	row = (BYTE_*)malloc(sizeof(BYTE_)*stdWidth);
	//����ͼ��洢�ռ�
	//pixel = (PixelRGBA*)malloc(sizeof(PixelRGBA)*sumBit);
	pixel->SetSize(width, height);

	fseek(fp, fileheader.bfOffBits, SEEK_SET);
	//��ȡ, �ж�ȡ
	for (i = 0; i<height&&!feof(fp); i++)
	{
		//cout<<"loading line "<<height-i-1<<"... ";
		fread(row, sizeof(BYTE_)*stdWidth, 1, fp);
		//cout<<"line "<<height-i-1<<"readed. ";
		if (infoheader.biBitCount == DOUBLE_COLOR)
			loadDOUBLE_COLOR(row, stdWidth, height - i - 1);
		else if (infoheader.biBitCount == COLOR_16)
			loadCOLOR_16(row, stdWidth, height - i - 1);
		else if (infoheader.biBitCount == COLOR_256)
			loadCOLOR_256(row, stdWidth, height - i - 1);
		else if (infoheader.biBitCount == TRUE_COLOR)
			loadTRUE_COLOR(row, width * 3, height - i - 1);
	}
	free(row);

}

void Bmp::loadBI_RLE4()
{

}

void Bmp::loadBI_RLE8()
{

}
//�н���: ˫ɫ
void Bmp::loadDOUBLE_COLOR(BYTE_* row, UINT_ lenth, UINT_ col)
{
	BYTE_ brow = 0;
	BYTE_ cell;
	int i, j, k;
	int line;
	line = col*width;

	i = 0;
	for (k = 0; k<width; k = k + 8)
	{
		cell = row[i];
		for (j = 0; j<8; j++)
		{
			if (k + j >= width)
				break;
			brow = cell / 128;
			cell = cell << 1;
			(*pixel)[line + k + j].b = quad[brow].rgbBlue;
			(*pixel)[line + k + j].g = quad[brow].rgbGreen;
			(*pixel)[line + k + j].r = quad[brow].rgbRed;
			(*pixel)[line + k + j].a = 0;

		}
		i++;
	}
}
//�н���: 16ɫ
void Bmp::loadCOLOR_16(BYTE_* row, UINT_ lenth, UINT_ col)
{
	BYTE_ hcell;
	BYTE_ lcell;
	int i, k;
	int line = width*col;
	i = 0;
	for (k = 0; k<width; k = k + 2)
	{
		hcell = row[i] / 16;
		lcell = row[i] % 16;

		(*pixel)[line + k].b = quad[hcell].rgbBlue;
		(*pixel)[line + k].g = quad[hcell].rgbGreen;
		(*pixel)[line + k].r = quad[hcell].rgbRed;
		(*pixel)[line + k].a = 0;

		if (k + 1<width)
		{
			(*pixel)[line + k + 1].b = quad[lcell].rgbBlue;
			(*pixel)[line + k + 1].g = quad[lcell].rgbGreen;
			(*pixel)[line + k + 1].r = quad[lcell].rgbRed;
			(*pixel)[line + k + 1].a = 0;
		}

		i++;
	}
}
//�н���: 256ɫ
void Bmp::loadCOLOR_256(BYTE_* row, UINT_ lenth, UINT_ col)
{
	int i;
	int line = width*col;
	for (i = 0; i<width; i++)
	{
		(*pixel)[line + i].b = quad[row[i]].rgbBlue;
		(*pixel)[line + i].g = quad[row[i]].rgbGreen;
		(*pixel)[line + i].r = quad[row[i]].rgbRed;
		(*pixel)[line + i].a = 0;
	}
}
//�н���: ���ɫ
void Bmp::loadTRUE_COLOR(BYTE_* row, UINT_ lenth, UINT_ col)
{
	unsigned int i = 0, j = 0, line = 0;
	line = col*width;
	for (i = 0; i<lenth; i = i + 3)
	{
		(*pixel)[line + j].b = row[i];
		(*pixel)[line + j].g = row[i + 1];
		(*pixel)[line + j].r = row[i + 2];
		(*pixel)[line + j].a = 0;

		j++;
	}
}



