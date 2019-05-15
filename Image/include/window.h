#pragma once

#ifndef WINDOW_H
#define WINDOW_H

#define WINDOW_VERTICAL      0
#define WINDOW_HORIZONTAL    1
#define WINDOW_DIAGONAL_LEFT 2
#define WINDOW_DIAGONAL_RIGHT 3

class Window{
private:
    int* kernel;
    int width;
    int height;
public:

    Window(int w, int h, char have_kernel);
    ~Window();
    int Width();
    int Height();
    char HaveKernel();
    int& operator[](int i);
    int* Kernel();
    static Window* GetPrewittWindow(char flag);
    static Window* GetSobelWindow(char flag);
    static Window* GetLoGWindow();
    static Window* GetGaussianWindow(unsigned int r, float d2);

};

#endif // WINDOW_H
