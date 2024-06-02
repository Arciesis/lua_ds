#include <stdio.h>
#include "ll.h"
#include "lua.h"
#include "lauxlib.h"

/* static Node_t* head = NULL; */

static int newNode(lua_State* L) {
    double value = luaL_checknumber(L, 1);
    Node_t* node = create_node(value);
    lua_pushlightuserdata(L, node);
    return 1;
}

static int insertEnd(lua_State* L) {
    Node_t* head = (Node_t*)lua_touserdata(L, 1);
    double value = luaL_checknumber(L, 2);

    Node_t* node = insert_end_by_value(&head, value);

    lua_pushlightuserdata(L, node);
    return 1;
}

static int findNode(lua_State* L) {
    Node_t* head = (Node_t*)lua_touserdata(L, 1);
    if (head == NULL) {
        luaL_error(L, "Don't know but there is an error");
    }

    double value = luaL_checknumber(L, 2);

    Node_t* found = find_node(head, value);

    if (found == NULL) {
        lua_pushnil(L);
    } else {
        lua_pushnumber(L, found->value);
    }
    return 1;
}

static int removeNode(lua_State* L) {
    Node_t* head = (Node_t*)lua_touserdata(L, 1);
    double value = luaL_checknumber(L, 1);

    Node_t* removed = remove_node(value, head);

    if (removed == NULL) {
        lua_pushnil(L);
    } else {
        lua_pushlightuserdata(L, removed);
    }

    return 1;
}

static int deleteList(lua_State* L) {
    Node_t* head = (Node_t*)lua_touserdata(L, 1);
    delete_list(head);

    return 0;
}


static const struct luaL_Reg linkedlist [] = {
    {"new", newNode},
    {"insert", insertEnd},
    {"find", findNode},
    {"remove", removeNode},
    {"deleteList", deleteList},
    {NULL, NULL}
};

int luaopen_linkedlist(lua_State* L) {
    luaL_register(L, "linkedlist", linkedlist);
    return 1;
}
