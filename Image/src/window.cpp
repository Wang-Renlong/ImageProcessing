#include "../include/window.h"
#include "../stdafx.h"
//非Visual Studio引用请添加下面头文件并删除stdafx.h
//#include <stdlib.h>
//#include <math.h>

Window::Window(int w, int h, char has_kernel)
{
    width = w;
    height = h;
    kernel = NULL;
    if(has_kernel)
        kernel = (int*)malloc(sizeof(int)*w*h);
}

Window::~Window()
{
    if(kernel)
    {
        free(kernel);
        kernel = NULL;
    }
}

int Window::Width()
{
    return width;
}

int Window::Height()
{
    return height;
}

char Window::HaveKernel()
{
    if(kernel)
        return 1;
    else
        return 0;
}

int& Window::operator[](int i)
{
    return kernel[i];
}

int* Window::Kernel()
{
    return kernel;
}

Window* Window::GetPrewittWindow(char flag)
{
    Window *window = new Window(3, 3, 1);
    int* kk = window->Kernel();
    kk[4] = 0;
    if(flag == WINDOW_HORIZONTAL)
    {
        kk[0] = -1;
        kk[1] = 0;
        kk[2] = 1;
        kk[3] = -1;
        kk[5] = 1;
        kk[6] = -1;
        kk[7] = 0;
        kk[8] = 1;
    }
    else if(flag == WINDOW_VERTICAL)
    {
        kk[0] = -1;
        kk[1] = -1;
        kk[2] = -1;
        kk[3] = 0;
        kk[5] = 0;
        kk[6] = -1;
        kk[7] = -1;
        kk[8] = -1;
    }
    else if(flag == WINDOW_DIAGONAL_LEFT)
    {
        kk[0] = 0;
        kk[1] = 1;
        kk[2] = 1;
        kk[3] = -1;
        kk[5] = 1;
        kk[6] = -1;
        kk[7] = -1;
        kk[8] = 0;
    }
    else if(flag == WINDOW_DIAGONAL_RIGHT)
    {
        kk[0] = -1;
        kk[1] = -1;
        kk[2] = 0;
        kk[3] = -1;
        kk[5] = 1;
        kk[6] = 0;
        kk[7] = 1;
        kk[8] = 1;
    }
    return window;
}

Window* Window::GetSobelWindow(char flag)
{
    Window *window = new Window(3, 3, 1);
    int* kk = window->Kernel();
    kk[4] = 0;
    if(flag == WINDOW_HORIZONTAL)
    {
        kk[0] = -1;
        kk[1] = 0;
        kk[2] = 1;
        kk[3] = -2;
        kk[5] = 2;
        kk[6] = -1;
        kk[7] = 0;
        kk[8] = 1;
    }
    else if(flag == WINDOW_VERTICAL)
    {
        kk[0] = 1;
        kk[1] = 2;
        kk[2] = 1;
        kk[3] = 0;
        kk[5] = 0;
        kk[6] = -1;
        kk[7] = -2;
        kk[8] = -1;
    }
    else if(flag == WINDOW_DIAGONAL_LEFT)
    {
        kk[0] = 0;
        kk[1] = 1;
        kk[2] = 2;
        kk[3] = -1;
        kk[5] = 1;
        kk[6] = -2;
        kk[7] = -1;
        kk[8] = 0;
    }
    else if(flag == WINDOW_DIAGONAL_RIGHT)
    {
        kk[0] = -2;
        kk[1] = -1;
        kk[2] = 0;
        kk[3] = -1;
        kk[5] = 1;
        kk[6] = 0;
        kk[7] = 1;
        kk[8] = 2;
    }
    return window;
}

Window* Window::GetLoGWindow()
{
    Window *window = new Window(5, 5, 1);
    int* kk = window->Kernel();

    kk[0] = 0;
    kk[1] = 0;
    kk[2] = -1;
    kk[3] = 0;
    kk[4] = 0;

    kk[5] = 0;
    kk[6] = -1;
    kk[7] = -2;
    kk[8] = -1;
    kk[9] = 0;

    kk[10] = -1;
    kk[11] = -2;
    kk[12] = 16;
    kk[13] = -2;
    kk[14] = -1;

    kk[15] = 0;
    kk[16] = -1;
    kk[17] = -2;
    kk[18] = -1;
    kk[19] = 0;

    kk[20] = 0;
    kk[21] = 0;
    kk[22] = -1;
    kk[23] = 0;
    kk[24] = 0;

    return window;
}

Window* Window::GetGaussianWindow(unsigned int r, float d2)
{
    float dd2 = d2 * 2;
    float a = 1 / (dd2 * 3.14159); // e=2.71828
    float temp;
    int half_r = r / 2;
    int *kk;
    int t1, t2;

    dd2 = 1 / dd2;
    Window *window = new Window(r,r,1);
    kk = window->Kernel();

    t1 = 0;
    t2 = 0;
    for(int i = 0 - half_r; i <= half_r; i++)
    {
        t2 = 0;
        for(int j = 0 - half_r; j <= half_r; j++)
        {
            temp = 0 - (i*i + j*j);
            temp = temp * dd2;
            temp = a*pow((float)2.71828, (float)temp);
            kk[t1+t2] = temp*100000;
            t2++;
        }
        t1 += r;
    }
    return window;
}








