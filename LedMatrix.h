#ifndef LEDMATRIX_H
#define LEDMATRIX_H

#include <vector>

#include "opc_client.h"

class Point
{
public:
  Point(int x, int y) : x(x), y(y) {}

  int x, y;
};

class LedMatrix
{
public:
	LedMatrix(const char * hostname);
    virtual ~LedMatrix()  {}

    void add_strip(Point start, Point end, unsigned int length);

    // Hold the Position of our Capture points
    std::vector <Point> leds;
	OPCClient opc_client;

    static void load_lua(const char* filename);
    static std::vector<LedMatrix*> matrices;
};


#endif // LEDMATRIX_H
