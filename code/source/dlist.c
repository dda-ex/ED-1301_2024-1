/*
    dlist.c
*/
#include <stdlib.h>
#include <string.h>

#include "dlist.h"

/*
    Initialize the dlist
*/
void dlist_init (DList *list, void (*destroy)(void *data)) {
    list->size = 0;
    list->destroy = destroy;
    list->head = NULL;
    list->tail = NULL;

    return;    
}

/*
    Destroying the dlist
*/
void dlist_destroy (DList *list) {
    void *data;

    while (dlist_size(list) > 0) {
        if (dlist_remove(list, dlist_tail(list), (void **)&data) == 0 && list->destroy != NULL) {
            list->destroy(data);
        }
    }    
    memset(list, 0, sizeof(DList));
    return;
}

/*
    Insert next node at the dlist
*/
int dlist_ins_next (DList *list, DListNode *node, const void *data ) {
    DListNode    *new_node;

    // Do not allow a NULL node unless the list is empty
    if (node == NULL && dlist_size(list) != 0)
        return -1;

    if ((new_node = (DListNode *)malloc(sizeof(DListNode))) == NULL)
        return -1;

    new_node->data = (void *)data;

    // The list is empty?, insert at the head
    if (dlist_size(list) == 0){
        list->head = new_node;
        list->head->prev = NULL;
        list->head->next = NULL;
        list->tail = new_node;
        
    } else {
        // Insert at the middle or end of the dlist (tail)
        new_node->next = node->next;
        new_node->prev = node;

        // Is the last node?
        if (node->next == NULL)
            list->tail = new_node; // yes
        else
            node->next->prev = new_node; // no

        node->next = new_node;
    }

    list->size++;

    return 0;
}

/*
    Insert next node at the List
*/
int dlist_ins_prev (DList *list, DListNode *node, const void *data ) {
    DListNode    *new_node;

    // Do not allow a NULL node unless the list is empty
    if (node == NULL && dlist_size(list) != 0)
        return -1;

    if ((new_node = (DListNode *)malloc(sizeof(DListNode))) == NULL)
        return -1;

    new_node->data = (void *)data;

    // The list is empty?, insert at the head
    if (dlist_size(list) == 0){
        list->head = new_node;
        list->head->prev = NULL;
        list->head->next = NULL;
        list->tail = new_node;
        
    } else {
    // Insert at the middle or end of the dlist (head)
        new_node->next = node;
        new_node->prev = node->prev;

        // Is the first node?
        if (node->prev == NULL)
            list->head = new_node; // yes
        else
            node->prev->next = new_node; // no

        node->prev = new_node;
    }

    list->size++;

    return 0;
}

/*
    Remove node at the List
*/
int dlist_remove (DList *list, DListNode *node, void **data) {

    // Check if is not empty the list
    if (node == NULL && dlist_size(list) == 0)
        return -1;
    
    *data = node->data;

    // The node to remove is at the head of the dlist
    if (node == list->head) {
        list->head = node->next;

        // Is the lastest node?
        if (list->head == NULL)
            list->tail = NULL; // yes, there's not any node
        else 
            node->next->prev = NULL; // no, there are one o more nodes

    } else {
        node->prev->next = node->next; 

        // Is the lastest node?
        if (node->next == NULL) 
            list->tail = node->prev; // yes
        else
            node->next->prev = node->prev; // no
    }

    free(node);
    list->size--;

    return 0;
}
