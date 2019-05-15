#ifndef BITMAP_H
#define BITMAP_H

#define DOUBLE_COLOR 1
#define COLOR_16     4
#define COLOR_256    8
#define COLOR_64K    16
#define TRUE_COLOR   24
#define TRUE_COLORA  32

#define QUID2   2
#define QUID16  16
#define QUID256 256

#define BI_RGB    0
#define BI_RLE8   1
#define BI_RLE4   2

typedef unsigned char BYTE_;
typedef unsigned int UINT_;
typedef unsigned short UINT16_;
typedef unsigned int UINT32_; //unsigned long ?
typedef unsigned long long UINT64_;
typedef long LONG_;
typedef unsigned long DWORD_;
typedef unsigned short WORD_;


typedef struct tagRGBQUAD_{
    BYTE_ rgbBlue;
    BYTE_ rgbGreen;
    BYTE_ rgbRed;
    BYTE_ rgbReserved;
}RGBQUAD_;

typedef struct tagBITMAPFILEHEADER_{
    UINT16_ bfType; //λͼ�ļ�����
    DWORD_ bfSize;  //λͼ�ļ���С���ֽ�
    UINT16_ bfReserved1; //������
    UINT16_ bfReserved2; //������
    DWORD_ bfOffBits;  //λͼ���������λͼ����ʼλ��
}BITMAPFILEHEADER_;

typedef struct tagBITMAPINFOHEADER_{
    DWORD_ biSize;//���ṹռ���ֽ���
    LONG_ biWidth;//λͼ���
    LONG_ biHeight;//λͼ�߶�
    WORD_ biPlanes;//Ŀ���豸����
    WORD_ biBitCount;//ÿ����������λ��1 ˫ɫ,4 16ɫ,8 256ɫ,24 ���ɫ
    DWORD_ biComression;//ѹ������0 ��ѹ��,1 BI_RLE8ѹ��, 2 BI_RLE4ѹ��
    DWORD_ biSizeImage;//λͼ��С���ֽ�
    LONG_ biXPelsPerMeter;//λͼ��ֱ�ֱ���
    LONG_ biYPelsPerMeter;//λͼˮƽ�ֱ���
    DWORD_ biClrUsed;//λͼʵ��ʹ�õ���ɫ����ɫ��
    DWORD_ biClrImportant;//λͼ��ʾ��������Ҫ����ɫ��
}BITMAPINFOHEADER_;
/*
typedef struct PixelRGBA{
    BYTE b;
    BYTE g;
    BYTE r;
    BYTE a;
}PixelRGBA;
*/
#endif // BITMAP_H

/*
˵��ͼ�����ݵ�ѹ�����ͣ�ȡֵ��ΧΪ��
0         BI_RGB ��ѹ������ã�
1         BI_RLE8 8�����γ̱��루BLE����ֻ����8λλͼ
2         BI_RLE4 4�����γ̱��루BLE����ֻ����4λλͼ
3         BI_BITFIELDS������BLE����ֻ����16/32λλͼ
*/
