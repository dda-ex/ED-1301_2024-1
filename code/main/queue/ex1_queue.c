#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "queue.h"

/*
    Print queue
*/
static void print_queue(const Queue *queue) {
    ListNode *node;
    int *data, size, i;

    fprintf(stdout, "Queue size is %d\n", size = queue_size(queue));

    i = 0;
    node = list_head(queue);

    while (i < size) {
       data = list_data(node);
       fprintf(stdout, "queue[%03d]=%03d, %p -> %p\n", i, *data, node, node->next);
       node = list_next(node);
       i++;
    }
    return;
}

// Main program
int main(int argc, char const *argv[]) {
    Queue queue;
    int *data, i;

    // Initialize the queue
    queue_init(&queue, free);

    fprintf(stdout, "\nEnqueuing 10 elements\n");

    for (i = 10; i < 20; i++) {

        if ((data = (int *)malloc(sizeof(int))) == NULL)
            return 1;

            *data = i + 1;

        if (queue_enqueue(&queue, data) != 0)
            return 1;
    }
    print_queue(&queue);

    fprintf(stdout, "\nDequeuing 3 elements\n");
    for (i = 0; i < 3; i++) {
        if(queue_dequeue(&queue, (void **)&data) == 0)
            free(data);
        else
            return 1;
    }
    print_queue(&queue);

    fprintf(stdout, "\nEnqueuing 001 and 998\n");
    if ((data = (int *)malloc(sizeof(int))) == NULL)
        return 1;
   *data = 1;
    if (queue_enqueue(&queue, data) != 0)
        return 1;

    if ((data = (int *)malloc(sizeof(int))) == NULL)
        return 1;
    *data = 998;
    if (queue_enqueue(&queue, data) != 0)
        return 1;
    
    print_queue(&queue);

    if ((data = queue_peek(&queue)) != NULL)
        fprintf(stdout, "\nPeeking at the head element [value]=%03d\n", *data);
    else
        fprintf(stdout, "\nPeeking at the head element [value]=NULL\n");
    print_queue(&queue);

    fprintf(stdout, "Dequeuing all elements\n");
    while (queue_size(&queue) > 0) {
        if (queue_dequeue(&queue, (void **)&data) == 0)
            free(data);
    }
    if ((data = queue_peek(&queue)) != NULL)
        fprintf(stdout, "\nPeeking at an empty [value]=%03d\n", *data);
    else
        fprintf(stdout, "\nPeeking at an empty [value]=NULL\n");
    print_queue(&queue);

    fprintf(stdout, "\nDestroying the queue\n");
    queue_destroy(&queue);
    return 0;
}