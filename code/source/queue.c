/*
    queue.c
*/
#include <stdlib.h>

#include "list.h"
#include "queue.h"

/*
    Enqueue
*/
int queue_enqueue (Queue *queue, const void *data) {

    return list_ins_next(queue, list_tail(queue), data);
}

/*
    Dequeue
*/
int queue_dequeue (Queue *queue, void **data) {
    
    return list_rem_next(queue, NULL, data);
}
