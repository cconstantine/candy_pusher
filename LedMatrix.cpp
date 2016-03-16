#include "LedMatrix.h"

void LedMatrix::add_strip(Point start, Point end, unsigned int length)
{
    float width = end.x - start.x;
    float height = end.y - start.y;

    float deltaX = width / length;
    float deltaY = height / length;

    for (unsigned int i = 0; i < length; i++)
    {
        leds.push_back(Point(start.x + i*deltaX,start.y + i*deltaY));
    }

}
