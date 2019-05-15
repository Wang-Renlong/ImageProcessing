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
    UINT16_ bfType; //位图文件类型
    DWORD_ bfSize;  //位图文件大小，字节
    UINT16_ bfReserved1; //保留字
    UINT16_ bfReserved2; //保留字
    DWORD_ bfOffBits;  //位图数据相对于位图的起始位置
}BITMAPFILEHEADER_;

typedef struct tagBITMAPINFOHEADER_{
    DWORD_ biSize;//本结构占用字节数
    LONG_ biWidth;//位图宽度
    LONG_ biHeight;//位图高度
    WORD_ biPlanes;//目标设备级别
    WORD_ biBitCount;//每个像素所需位数1 双色,4 16色,8 256色,24 真彩色
    DWORD_ biComression;//压缩类型0 不压缩,1 BI_RLE8压缩, 2 BI_RLE4压缩
    DWORD_ biSizeImage;//位图大小，字节
    LONG_ biXPelsPerMeter;//位图垂直分辨率
    LONG_ biYPelsPerMeter;//位图水平分辨率
    DWORD_ biClrUsed;//位图实际使用的颜色表颜色数
    DWORD_ biClrImportant;//位图显示过程中重要的颜色数
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
说明图像数据的压缩类型，取值范围为：
0         BI_RGB 不压缩（最常用）
1         BI_RLE8 8比特游程编码（BLE），只用于8位位图
2         BI_RLE4 4比特游程编码（BLE），只用于4位位图
3         BI_BITFIELDS比特域（BLE），只用于16/32位位图
*/
