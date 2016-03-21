#include "LedMatrix.h"
#include <iostream>

extern "C"{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "luna.h"

class Candy {
  public:
    Candy(lua_State *L) {
      const char * hostname = luaL_checkstring(L, 1);
      printf("-- Pushing to: '%s'\n", hostname);

      matrix = new LedMatrix(hostname);

      LedMatrix::matrices.push_back(matrix);
     }

    int add_strip(lua_State *L) {
      int x, y;

      luaL_checktype(L, 2, LUA_TTABLE);
      lua_getfield(L, 2, "x");
      lua_getfield(L, 2, "y");
      x = luaL_checknumber(L, -2);
      y = luaL_checknumber(L, -1);
      lua_pop(L, 2);
      Point start = Point(x, y);

      luaL_checktype(L, 3, LUA_TTABLE);
      lua_getfield(L, 3, "x");
      lua_getfield(L, 3, "y");
      x = luaL_checknumber(L, -2);
      y = luaL_checknumber(L, -1);
      lua_pop(L, 2);
      Point end = Point(x, y);

      int count = luaL_checknumber(L, 4);

      printf("--- Adding %d LEDS from (%d, %d) to (%d, %d)\n",
        count,
        start.x, start.y,
        end.x, end.y);

      matrix->add_strip(start, end, count);
      lua_pushnumber(L, 123); // return value
      return 1; // number of return values
    }

    ~Candy() {  }

    static const char className[];
    static const Luna<Candy>::RegType Register[];

    LedMatrix *matrix;
};

const char Candy::className[] = "Candy";
const Luna<Candy>::RegType Candy::Register[] = {
  { "add_strip", &Candy::add_strip },
  { 0, 0 }
};

void LedMatrix::load_lua(const char* filename) {
  lua_State *L = luaL_newstate();
  luaL_requiref(L, "io", luaopen_io, 1);
  luaL_requiref(L, "math", luaopen_math, 1);

  Luna<Candy>::Register(L);

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
std::vector<LedMatrix*> LedMatrix::matrices;
