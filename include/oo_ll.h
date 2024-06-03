#include "lua.h"
#include "lauxlib.h"

typedef struct ONode {
    void* value;
    struct ONode* next;
} ONode_t;

void print_stack(lua_State* L);
static int new_object(lua_State* L);
