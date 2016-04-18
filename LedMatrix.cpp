#include <iostream>

#include "LedMatrix.h"
#include "candy.h"



void LedMatrix::load_lua(const char* filename, AbstractDriver *driver) {
  lua_State *L = luaL_newstate();
  luaL_requiref(L, "base", luaopen_base, 1);
  luaL_requiref(L, "io", luaopen_io, 1);
  luaL_requiref(L, "math", luaopen_math, 1);

  Luna<Candy>::Register(L);

  Candy::driver = driver;
  int s = luaL_loadfile(L, filename);

  if ( s==0 ) {
    printf("- Loading file: %s\n", filename);

    // execute Lua program
    s = lua_pcall(L, 0, LUA_MULTRET, 0);
  }

  if ( s!=0 ) {
    std::cerr << "-- " << lua_tostring(L, -1) << std::endl;
    lua_pop(L, 1); // remove error message
  }
  std::cerr << std::endl;

  lua_close(L);

  for(std::vector<LedMatrix*>::iterator mx = LedMatrix::matrices.begin(); mx != LedMatrix::matrices.end();++mx) {
    LedMatrix *matrix = *mx;
    matrix->finalize();
  }
}


LedMatrix::LedMatrix(const char * hostname) {
  opc_client.resolve(hostname);

}


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

void LedMatrix::finalize() {
  int frameBytes = leds.size() * 3;
  frameBuffer.resize(sizeof(OPCClient::Header) + frameBytes);

  OPCClient::Header::view(frameBuffer).init(0, opc_client.SET_PIXEL_COLORS, frameBytes);
}

std::vector<LedMatrix*> LedMatrix::matrices;
