/**
 * @file  queuelist.c
 * @author Jorge Torrijos de la Cruz e Ivan Reyero Fernández
 * @date March 2026
 * @mersion 1.0
 * @brief Library to manage queue with a list
 *
 * @details
 *
 * @see
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "list.h"
#include "queue.h"

struct _Queue
{
    List *pl;
};

/**********************************/
Bool queue_isFull(const Queue *q)
{
    if (q == NULL)
    {
        return TRUE;
    }
    return FALSE;
}
/******************************/
Queue *queue_new()
{
    Queue *pq = NULL;
    pq = (Queue *)malloc(sizeof(Queue));
    if (pq == NULL)
    {
        return NULL;
    }

    pq->pl = list_new();
    if (pq->pl == NULL)
    {
        free(pq);
        return NULL;
    }

    return pq;
}

void queue_free(Queue *q)
{
    if (q != NULL)
    {
        list_free(q->pl);
        free(q);
    }
}

Bool queue_isEmpty(const Queue *q)
{
    if (!q)
    {
        return FALSE;
    }

    return list_isEmpty(q->pl);
}

void *queue_pop(Queue *q)
{
    if (!q)
    {
        return NULL;
    }

    return list_popFront(q->pl);
}

Status queue_push(Queue *q, void *ele)
{
    if (!q || !ele)
    {
        return ERROR;
    }

    return list_pushBack(q->pl, ele);
}

void *queue_getFront(const Queue *q)    {
    if (!q) {
        return 0;
    }

    return list_getFront(q->pl);
}

void *queue_getBack(const Queue *q) {
    if (!q) {
        return 0;
    }

    return list_getBack(q->pl);
}

size_t queue_size(const Queue *q)   {
    if (!q) {
        return 0;
    }

    if (queue_isEmpty(q) == TRUE)  {
        return 0;
    }

    return list_size(q->pl);
}

int queue_print(FILE *fp, const Queue *q, p_queue_ele_print f)  {
    if (!q) {
        return 0;
    } 

    return list_print(fp, q->pl, f);
}