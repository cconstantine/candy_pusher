#ifndef __CANDY_H__
#define __CANDY_H__

extern "C"{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "luna.h"

#include "LedMatrix.h"

class Candy {
  public:
    Candy(lua_State *L);

    int add_strip(lua_State *L);
	int get_width(lua_State *L);
	int get_height(lua_State *L);


    static const char className[];
    static const Luna<Candy>::RegType Register[];

    LedMatrix *matrix;
    static AbstractDriver *driver;
};

#endif