#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

#include <stdio.h>

typedef struct Complex {
    lua_Number real;
    lua_Number imag;
} Complex;

static inline Complex l_getComplex(lua_State* l,const int idx)
{
    luaL_checktype(l,idx,LUA_TTABLE);
    lua_getfield(l,idx,"real");
    lua_getfield(l,idx,"imag");

    luaL_checktype(l,-1,LUA_TNUMBER);
    luaL_checktype(l,-2,LUA_TNUMBER);
    
    const double real = lua_tonumber(l,-2);
    const double imag = lua_tonumber(l,-1);
    const Complex c = {real,imag};
    
    return c;
}

static int l_subComplex(lua_State* l)
{
    const Complex c = l_getComplex(l,1);
    const Complex d = l_getComplex(l,2);
    const Complex e = (Complex) {
	c.real - d.real,
	c.imag - d.imag};
     
    lua_createtable(l,0,2);
    lua_pushnumber(l,e.real);
    lua_setfield(l,-2,"real"); // set field removes the last value in stack for you
    lua_pushnumber(l,e.imag);
    lua_setfield(l,-2,"imag");
    return 1;  
}

static int l_sumComplex(lua_State* l)
{
    const Complex c = l_getComplex(l,1);
    const Complex d = l_getComplex(l,2);
    const Complex e = (Complex) {
	c.real + d.real,
	c.imag + d.imag};
     
    lua_createtable(l,0,2);
    lua_pushnumber(l,e.real);
    lua_setfield(l,-2,"real");
    lua_pushnumber(l,e.imag);
    lua_setfield(l,-2,"imag");
    return 1;
}


LUALIB_API int l_loadcomplex(lua_State* l)
{
    const struct luaL_Reg funcs[] = {
	{"csum",l_sumComplex},
	{"csub",l_subComplex},
	{NULL,NULL}};
    luaL_newlib(l,funcs);
    return 1;
}
