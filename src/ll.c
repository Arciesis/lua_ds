#include "ll.h"

#include <stdlib.h>

Node_t* create_node(double value) {
    Node_t* node = malloc(sizeof(Node_t));
    node->value = value;
    node->next = NULL;
    return node;
}

void insert_end_by_node(Node_t** head, Node_t* node) {
    if (*head == NULL) {
        *head = node;
        return;
    }
    Node_t* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = node;
}

Node_t* insert_end_by_value(Node_t** head, double value) {
    Node_t* node = create_node(value);
    if (*head == NULL) {
        *head = node;
        return node;
    }
    Node_t* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = node;
    return node;
}

Node_t* find_node(Node_t* head, double value) {
    Node_t* current = head;
    while (current != NULL) {
        if (current->value == value) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

Node_t* remove_node(double value, Node_t* head) {
    Node_t* current = head;
    Node_t* previous = NULL;
    while (current != NULL) {
        if (current->value == value) {
            if (previous == NULL) {
                head = current->next;
            } else {
                previous->next = current->next;
            }
            return current;
        }
        previous = current;
        current = current->next;
    }
    return NULL;
}

void delete_list(Node_t* head) {
    Node_t* current = head;
    while (current != NULL) {
        Node_t* previous = current;
        current = current->next;
        free(previous);
    }
}
