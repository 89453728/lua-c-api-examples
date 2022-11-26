#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


int main()
{
    lua_State* l;
    l = luaL_newstate();
    luaL_openlibs(l);

    printf("lua abs index od -1: %d\n",lua_absindex(l,-1));
    printf("lua abs index of 0: %d\n",lua_absindex(l,0));

    lua_pushnumber(l,3.31f);
    lua_pushnumber(l,3.54f);
    lua_arith(l,LUA_OPPOW);
    printf("value of exponentiation: %.4f\n",(double)lua_tonumber(l,-1));
    printf("size of the stack: %d\n",lua_gettop(l));

    lua_pushfstring(l,"hello %f",lua_tonumber(l,-1));
    printf("string: %s\n",lua_tostring(l,-1));

    luaL_Buffer b;
    luaL_buffinitsize(l,&b,(size_t)12);
    luaL_addlstring(&b,"Hello, World\n",12);
    luaL_pushresultsize(&b,(size_t)12);

    printf("%s!\n",lua_tostring(l,-1));

    luaL_checkstack(l,200,"stack is full\n");

    size_t sz;
    const char* value = luaL_checklstring(l,-1,&sz);
    // by 2 because is a utf character encoding
    printf("string value: %s\nWith size: %d\n", (sz == 0)? "" : value,(int)sz/2);
    luaL_dofile(l,"./hello.lua");
    lua_getglobal(l,"fmt");
    const char* s = luaL_checkstring(l,-1);
    printf("value: %s\n",(s == NULL)? "none" : s);
    printf("[C] len: %d\n", (int)luaL_len(l,-1));
    printf("[C] gsub: %s\n", luaL_gsub(l,lua_tostring(l,-1),"lua","luna"));
    
    lua_close(l);
    return 0;
}


static void* l_alloc(void* ud,void* ptr,size_t osize, size_t nsize)
{
    (void)ud;
    (void)osize;
    if(nsize == 0){
	free(ptr);
	return NULL;
    } else
	return realloc(ptr,nsize);
}

