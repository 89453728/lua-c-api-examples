#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

int main(int argc, char** argv)
{
    lua_State* l;
    l = luaL_newstate();
    luaL_openlibs(l);
    
    if (l == NULL)
	return 2;

    if (argc < 2)
	return 3;

    /* luaL_loadstring(l,argv[1]); */
    /* lua_pcall(l,0,LUA_MULTRET,0); */
    luaL_dostring(l,argv[1]);
    /* printf("%s\n",luaL_checkstring(l,-1)); */
    lua_close(l);
    
    return 0;
}
    
