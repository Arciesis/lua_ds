#include "main.h"

#include <stdlib.h>
#include <stdio.h>

#include "ll.h"

int main() {
    Node_t* head = create_node(3.6);
    Node_t* node = create_node(1.2);

    insert_end_by_node(&head, node);
    insert_end_by_value(&head, 2.3);

    while (head != NULL) {
        printf("%f\n", head->value);
        head = head->next;
    }

    delete_list(head);



    /* lua_State* L = luaL_newstate(); */

    return 0;
}


