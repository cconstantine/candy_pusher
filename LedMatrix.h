#ifndef LEDMATRIX_H
#define LEDMATRIX_H

#include <vector>

class Point
{
public:
  Point(int x, int y) : x(x), y(y) {}

  int x, y;
};

class LedMatrix
{
public:
    virtual ~LedMatrix()  {}

    void add_strip(Point start, Point end, unsigned int length);


    // Hold the Position of our Capture points
    std::vector <Point> leds;
};


#endif // LEDMATRIX_H
