#include "oo_ll.h"

#include <stdio.h>
#include <stdlib.h>

#include "lauxlib.h"
#include "lua.h"
#include "lua_list.h"

static int new_object(lua_State* L) {
    int type = lua_type(L, 1);
    void* udata;

    switch (type) {
        case LUA_TSTRING:
            udata = lua_newuserdata(L, sizeof(const char*));
            break;
        case LUA_TBOOLEAN:
            udata = lua_newuserdata(L, sizeof(int));
            break;
        case LUA_TNUMBER:
            udata = lua_newuserdata(L, sizeof(lua_Number));
            break;
        case LUA_TLIGHTUSERDATA:
            udata = lua_newuserdata(L, sizeof(const void*));
            break;
        case LUA_TFUNCTION:
            udata = lua_newuserdata(L, sizeof(const void*));
            break;
        case LUA_TTABLE:
            udata = lua_newuserdata(L, sizeof(const void*));
            break;
        case LUA_TUSERDATA:
            udata = lua_newuserdata(L, sizeof(const void*));
            break;
        default:
            luaL_error(L, "You must pass a valid argument to this function");
            return 0;
            break;
    }

    const char* key = "__index";
    lua_newtable(L);
    void* head_node = lua_newuserdata(L, sizeof(ONode_t));
    lua_setfield(L, -2, key);

    lua_pushlightuserdata(L, &head_node);
    lua_setmetatable(L, -1);

    return 1;
}

void print_stack(lua_State* L) {
    int top = lua_gettop(L);  // Get the number of elements on the stack
    printf("Stack size: %d\n", top);

    for (int i = 1; i <= top; i++) {  // Iterate over each element
        int t = lua_type(L, i);
        switch (t) {
            case LUA_TSTRING:
                printf("String: %s\n", lua_tostring(L, i));
                break;
            case LUA_TBOOLEAN:
                printf("Boolean: %s\n", lua_toboolean(L, i) ? "true" : "false");
                break;
            case LUA_TNUMBER:
                printf("Number: %g\n", lua_tonumber(L, i));
                break;
            case LUA_TLIGHTUSERDATA:
                printf("Lightuserdata: %p\n", lua_touserdata(L, i));
                break;
            default:
                printf("%s\n", lua_typename(L, t));
                break;
        }
    }
}

static const struct luaL_Reg linkedlist[] = {{"new", new_object}, {NULL, NULL}};

int luaopen_libluall(lua_State* L) {
    luaL_register(L, "libluall", linkedlist);
    return 1;
}
