#include "lua.h"
#include "lauxlib.h"

typedef enum Accepted_type {
    str = LUA_TSTRING,
    bool = LUA_TBOOLEAN,
    number = LUA_TNUMBER,
    udata = LUA_TUSERDATA,
    table = LUA_TTABLE,
    fn = LUA_TFUNCTION,
    ludata = LUA_TLIGHTUSERDATA,
} Accepted_type;

typedef struct {
    Accepted_type type;
    void* value;
    struct ONode* next;
} ONode_t;

void print_stack(lua_State* L);
static int new_object(lua_State* L);
