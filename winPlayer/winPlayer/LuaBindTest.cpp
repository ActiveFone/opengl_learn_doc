#include "LuaBindTest.h"
//#include <iostream>
#include <sstream>
#include <iostream>
#include "lua.hpp"

using namespace std;

static void stackDump(lua_State* L) {
	cout << "\nbegin dump lua stack" << endl;
	int i = 0;
	int top = lua_gettop(L);
	for (i = 1; i <= top; ++i) {
		int t = lua_type(L, i);
		switch (t) {
		case LUA_TSTRING:
		{
			printf("'%s' ", lua_tostring(L, i));
		}
		break;
		case LUA_TBOOLEAN:
		{
			printf(lua_toboolean(L, i) ? "true " : "false ");
		}break;
		case LUA_TNUMBER:
		{
			printf("%g ", lua_tonumber(L, i));
		}
		break;
		default:
		{
			printf("%s ", lua_typename(L, t));
		}
		break;
		}
	}
	cout << "\nend dump lua stack" << endl;
}

int foo(lua_State *L)
{
	int n = lua_tonumber(L, 1);

	lua_pushnumber(L, n + 1);

	return 1;
}

void LuaBindTest::showTest(GLFWwindow *window)
{
	std::cout << "Hello World!\n";

	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	lua_register(L, "foo", foo);

	if (luaL_dofile(L, "res/script/test.lua"))
	{
		luaL_error(L, "cannot dofile main.lua");
	}

	/*lua_getglobal(L, "myStr");

	string str = lua_tostring(L, -1);

	cout << "str = " << str.c_str() << endl;

	lua_getglobal(L, "myTable");

	lua_getfield(L, -1, "name");

	str = lua_tostring(L, -1);

	cout << "tablename = " << str.c_str() << endl;

	lua_getglobal(L, "funAdd");
	lua_pushnumber(L, 10);
	lua_pushnumber(L, 20);*/

	/*int ret = lua_pcall(L, 2, 1, 0);

	int addNum = lua_tonumber(L, -1);

	cout << "add result is:" << addNum << endl;

	str = lua_tostring(L, -2);

	cout << "next = " << str.c_str() << endl;*/

	cout << "=============================" << endl;

	//stackDump(L);

	lua_close(L);
}