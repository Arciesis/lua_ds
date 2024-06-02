#include "lua.h"

static int newNode(lua_State* L);
static int insertEnd(lua_State* L);
static int findNode(lua_State* L);
static int removeNode(lua_State* L);
static int deleteList(lua_State* L);
