#include "candy.h"

AbstractDriver *Candy::driver = NULL;

Candy::Candy(lua_State *L) {
  const char * hostname = luaL_checkstring(L, 1);
  printf("-- Pushing to: '%s'\n", hostname);

  matrix = new LedMatrix(hostname);
  LedMatrix::matrices.push_back(matrix);
}

int Candy::add_strip(lua_State *L) {
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

int Candy::get_width(lua_State *L) {
  lua_pushnumber(L, driver->getWidth()); // return value
  return 1; // number of return values
}

int Candy::get_height(lua_State *L) {
  lua_pushnumber(L, driver->getHeight()); // return value
  return 1; // number of return values
}


const char Candy::className[] = "Candy";
const Luna<Candy>::RegType Candy::Register[] = {
  { "add_strip", &Candy::add_strip },
  { "get_width", &Candy::get_width },
  { "get_height", &Candy::get_height },
  { 0, 0 }
};
