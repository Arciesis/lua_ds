#include "oo_ll.h"

#include <lua.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lauxlib.h"
#include "lua.h"

static const struct luaL_Reg libluall_met[] = {{"find", find_node},
                                               {NULL, NULL}};

/** create a new instance for the lua's linked list.
 *
 * @param L The lua_Stack on which it has been called.
 *
 * @return the number of arguments returned.
 */
static int new_object(lua_State* L) {
    int type = lua_type(L, 1);
    ONode* head = malloc(sizeof(ONode));
    int bool_udata;
    lua_Number number_udata;
    const char* str_udata;
    void* fn_udata;
    void* table_udata;

    switch (type) {
        case LUA_TBOOLEAN:
            head->flag = tbool;
            bool_udata = lua_toboolean(L, 1);
            lua_pop(L, 1);
            lua_pushlightuserdata(L, &bool_udata);
            break;
        case LUA_TNUMBER:
            head->flag = tnumber;
            number_udata = lua_tonumber(L, 1);
            lua_pop(L, 1);
            lua_pushlightuserdata(L, &number_udata);
            break;
        case LUA_TSTRING:
            head->flag = tstr;
            str_udata = lua_tostring(L, 1);
            lua_pop(L, 1);
            lua_pushlightuserdata(L, &str_udata);
            break;
        case LUA_TFUNCTION:
            head->flag = tfn;
            fn_udata = lua_touserdata(L, 1);
            lua_pop(L, 1);
            lua_pushlightuserdata(L, &fn_udata);
            break;
        case LUA_TTABLE:
            head->flag = ttable;
            table_udata = lua_touserdata(L, 1);
            lua_pop(L, 1);
            lua_pushlightuserdata(L, &table_udata);
            break;
        default:
            luaL_error(L, "You must pass a valid argument to this function");
            return 0;
            break;
    }

    // TODO: need a better handling of that thing
    if (lua_gettop(L) != 1 || lua_type(L, 1) != LUA_TLIGHTUSERDATA) {
        printf("ERROR !!!");
    } else {
        printf("type: %s\n", lua_typename(L, lua_type(L, 1)));
    }

    head->value = lua_touserdata(L, 1);
    lua_pop(L, 1);
    head->next = NULL;
    /* lua_pushlightuserdata(L, (void*)head); */
    lua_pushlightuserdata(L, (void*)head);  // stack: ludata

    char meta_uid[100];
    const char* basename = "libluall_mt";
    snprintf(meta_uid, 100ul, "%s %p", basename, (void*)head);

    luaL_newmetatable(L, meta_uid);  // stack: ludata, meta{}
    lua_pushvalue(L, -1);            // stack: ludata, meta{}, meta{}

    // Set the __index field to the methods table
    luaL_register(L, NULL, libluall_met);  // stack: ludata, meta{}, meta{}
    lua_setfield(L, -2, "__index");  // mt.__index = mt => stack: ludata, meta{}

    // Set the metatable on the userdata
    lua_setmetatable(L, 1);  // stack: ludata

    return 1;  // i.e: head
}

static int find_node(lua_State* L) {
    print_stack(L);

    // stack should be => udata, value
    if (!lua_isuserdata(L, 1)) {
        lua_pop(L, 2);
        luaL_error(L, "That should not happen, I don't understand...");
        return 0;
    }

    ONode* head = (ONode*)lua_touserdata(L, 1);

    //TODO: implement this
    switch (head->flag) {
        case tbool:
            findbool((int*)head->value);
            break;
        case tnumber:
            findnum((lua_Number*)head->value);
            break;
        case tstr:
            findstr((const char*)head->value);
            break;
        case ttable:
            findtable(head->value);
            break;
        case tfn:
            findfn(head->value);
        default:
            luaL_error(L, "don't know yet");
            break;
    }

    /*HasType* types = malloc(sizeof(HasType));*/
    /*types->isfn = 0;*/
    /*types->istable = 0;*/
    /*types->isstring = 0;*/
    /*types->isluaNumber = 0;*/
    /*types->isbool = 0;*/
    /**/
    /*switch (lua_type(L, -1)) {*/
    /*    case LUA_TBOOLEAN:*/
    /*        types->isbool = 1;*/
    /*        break;*/
    /*    case LUA_TNUMBER:*/
    /*        types->isluaNumber = 1;*/
    /*        break;*/
    /*    case LUA_TSTRING:*/
    /*        types->isstring = 1;*/
    /*        break;*/
    /*    case LUA_TTABLE:*/
    /*        types->istable = 1;*/
    /*        break;*/
    /*    case LUA_TFUNCTION:*/
    /*        types->isfn =1;*/
    /*    default:*/
    /*        luaL_error(L, "don't know yet");*/
    /*        break;*/
    /*}*/

    /* if (lua_pcall(L, 1, 1, 0)) { */
    /* luaL_error(L, lua_tostring(L, -1)); */
    /* return 0; */
    /* } */
    /* print_stack(L); */
    /* return 1; */

    // lua_Number val_to_find = lua_tonumber(L, 2);

    /*ONode_t* head = (ONode_t*)head_udata;*/
    /*int node_type = head->type;*/
    /*switch (node_type) {*/
    /*    case number:*/
    /*        break;*/
    /*}*/
    /**/
    /*ONode_t* current = head;*/
    /*while (current != NULL) {*/
    /*    if (current->value == &val_to_find) {*/
    /*        lua_pushlightuserdata(L, (void*)current);*/
    /*        return 1;*/
    /*    } else {*/
    /*        current = current->next;*/
    /*    }*/
    /*}*/
    /**/

    /*free(types);*/
    return 1;
}

/** Helper function that prints the actual stack into stdout.
 *
 * @param L the lua Stack
 */
void print_stack(lua_State* L) {
    int top = lua_gettop(L);  // Get the number of elements on the stack
    printf("Stack size: %i\n", top);

    printf("{\n");
    for (int i = 1; i <= top; i++) {  // Iterate over each element
        printf("\t[%i => %s]\n", i, lua_typename(L, lua_type(L, i)));
    }
    printf("}\n");
}

/**
 * Lua's lib related
 */
static const struct luaL_Reg linkedlist[] = {{"new", new_object}, {NULL, NULL}};

int luaopen_libluall(lua_State* L) {
    luaL_register(L, "libluall", linkedlist);
    return 1;
}
