#ifndef IMG_RECT_H
#define IMG_RECT_H

namespace img{

    class Rect{
    public:
        unsigned int sx;
        unsigned int sy;
        unsigned int ex;
        unsigned int ey;
        unsigned int color;

        Rect(unsigned int sx, unsigned int sy, unsigned int ex, unsigned int ey)
            :sx(sx), sy(sy), ex(ex), ey(ey){}

        Rect(const Rect& arg1)
            :sx(arg1.sx), sy(arg1.sy), ex(arg1.ex), ey(arg1.ey), color(arg1.color){};

        Rect(){};

        bool operator=(const Rect& arg1)
        {
            sx = arg1.sx;
            sy = arg1.sy;
            ex = arg1.ex;
            ey = arg1.ey;
            color = arg1.color;
            return true;
        }

        Rect operator+(const Rect& arg1)
        {
            unsigned int a,b,c,d;
            a = sx < arg1.sx ? sx : arg1.sx;
            b = sy < arg1.sy ? sy : arg1.sy;
            c = ex > arg1.ex ? ex : arg1.ex;
            d = ey > arg1.ey ? ey : arg1.ey;
            return Rect(a, b, c, d);
        }

        unsigned int Width()
        {
            if(ex > sx)
                return ex-sx;
            else
                return 0;
        }

        unsigned int Height()
        {
            if(ey > sy)
                return ey-sy;
            else
                return 0;
        }

    };

}

#endif // IMG_RECT_H
