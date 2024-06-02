
typedef struct Node {
     double value;
    struct Node* next;
} Node_t;


Node_t* create_node(double value);
Node_t* insert_end_by_value(Node_t** head, double value);
void insert_end_by_node(Node_t** head, Node_t* node);
Node_t* find_node(Node_t* head, double value);
Node_t* remove_node(double value, Node_t* head);
void delete_list(Node_t* head);
