#include "oo_ll.h"

#include <stdio.h>
#include <stdlib.h>

#include "lauxlib.h"
#include "lua.h"
#include "lua_list.h"

/** create a new instance for the lua's linked list.
 *
 * @param L The lua_Stack on which it has been called.
 *
 * @return the number of arguments returned.
 */
static int new_object(lua_State* L) {
    int type = lua_type(L, 1);

    // Creation of the table for set it as a metatable.
    const char* key = "__index";
    lua_newtable(L);
    void* head_node = lua_newuserdata(L, sizeof(ONode_t));
    lua_setfield(L, -2, key);

    // create the metatable on self in orer to create the new lua object.
    lua_pushlightuserdata(L, &head_node);
    lua_setmetatable(L, -1);


    ONode_t* head = (ONode_t*)head_node;
    head->value = lua_touserdata(L, -1);
    head->next = NULL;

    // handle each acceptable type and throw error if it's not a good one.
    switch (type) {
        case LUA_TBOOLEAN:
            lua_newuserdata(L, sizeof(int));
            head->type = bool;
            break;
        case LUA_TNUMBER:
            lua_newuserdata(L, sizeof(lua_Number));
            head->type = number;
            break;
        case LUA_TSTRING:
            lua_newuserdata(L, sizeof(const char*));
            head->type = str;
            break;
        case LUA_TLIGHTUSERDATA:
            lua_newuserdata(L, sizeof(const void*));
            head->type = ludata;
            break;
        case LUA_TFUNCTION:
            lua_newuserdata(L, sizeof(const void*));
            head->type = fn;
            break;
        case LUA_TTABLE:
            lua_newuserdata(L, sizeof(const void*));
            head->type = table;
            break;
        case LUA_TUSERDATA:
            lua_newuserdata(L, sizeof(const void*));
            head->type = udata;
            break;
        default:
            luaL_error(L, "You must pass a valid argument to this function");
            return 0;
            break;
    }
    
    return 1;
}

/** Helper function that prints the actual stack into stdout.
 *
 * @param L the lua Stack
 */
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

/**
 * Lua's lib related
 */
static const struct luaL_Reg linkedlist[] = {{"new", new_object}, {NULL, NULL}};

int luaopen_libluall(lua_State* L) {
    luaL_register(L, "libluall", linkedlist);
    return 1;
}
