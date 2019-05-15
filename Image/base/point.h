#ifndef POINT_H
#define POINT_H

class Point{
public:
    unsigned int x;
    unsigned int y;

    Point(unsigned int x, unsigned int y)
        :x(x),y(y) {}

    Point(const Point& arg1)
        :x(arg1.x),y(arg1.y) {}

    Point()
        :x(0),y(0) {}

    BOOL operator=(const Point& arg1)
    {
        x = arg1.x;
        y = arg1.y;
        return TRUE;
    }

    BOOL operator==(const Point& arg1)
    {
        if(arg1.x == x && arg1.x == x)
            return TRUE;
        else
            return FALSE;
    }

    BOOL operator!=(const Point& arg1)
    {
        if(arg1.x == x && arg1.x == x)
            return FALSE;
        else
            return TRUE;
    }

    Point operator+(const Point& arg1)
    {
        return Point(x+arg1.x, y+arg1.y);
    }

    Point operator-(const Point& arg1)
    {
        return Point(x-arg1.x, y-arg1.y);
    }

    Point operator*(const Point& arg1)
    {
        return Point(x*arg1.x, y*arg1.y);
    }

    Point operator/(const Point& arg1)
    {
        if(arg1.x && arg1.y)
            return Point(x-arg1.x, y-arg1.y);
        else
            return Point(0, 0);
    }

};

#endif // POINT_H
