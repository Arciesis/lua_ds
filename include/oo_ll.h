#include "lauxlib.h"
#include "lua.h"

typedef enum TypeFlag {
    tstr = LUA_TSTRING,
    tbool = LUA_TBOOLEAN,
    tnumber = LUA_TNUMBER,
    ttable = LUA_TTABLE,
    tfn = LUA_TFUNCTION,
} TypeFlag;

/**
 * Generic Node struct
 */
typedef struct ONode {
    void* value;
    TypeFlag flag;
    struct ONode_t* next;
} ONode;

/* typedef struct HasType { */
    /* int isstring; */
    /* int isluaNumber; */
    /* int isbool; */
    /* int istable; */
    /* int isfn; */
/* } HasType; */

void print_stack(lua_State* L);
static int new_object(lua_State* L);
static int find_node(lua_State* L);
