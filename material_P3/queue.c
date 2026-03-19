#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "queue.h"


struct _Queue
{
    void *data [MAX_QUEUE];
    void **front;
    void **rear;
};

Queue *queue_new()  {
    Queue *new_queue = NULL;
    int i;
    new_queue = (Queue*) calloc (1, sizeof(Queue));
    if (!new_queue) {
        return NULL;
    }

    for (i=0; i<MAX_QUEUE; i++) {
        new_queue->data[i] = NULL;
    }

    new_queue->front = &new_queue->data[0];
    new_queue->rear = &new_queue->data[0];

    return new_queue;
}

void queue_free(Queue *q)   {
    q->front = NULL;
    q->rear = NULL;
    free (q);
}

Bool queue_isEmpty(const Queue *q) {
    if (!q) {
        return FALSE;
    } 

    if (q->front == q->rear)    {
        return TRUE;
    }
    
    return FALSE;
}

Status queue_push(Queue *q, void *ele) {
    if (!q || !ele) {
        return FALSE;
    } 
    
    q->rear = ele;
    q->rear = q->data + (q->rear+1 - q->data) % MAX_QUEUE;

    return OK;
}

void *queue_pop(Queue *q) {
    void *ele = NULL;
    if (!q) {
        return FALSE;
    } 
    
    ele = q->front;
    q->front = q->data + (q->front+1 - q->data) % MAX_QUEUE;

    return ele;
}

void *queue_getFront(const Queue *q) {
    if (!q) {
        return NULL;
    }

    return q->front;
}

void *queue_getBack(const Queue *q) {
    if (!q) {
        return NULL;
    }

    return q->rear;
}

size_t queue_size(const Queue *q) {
  if (!q) {
    return 0;
  }

  if (queue_isEmpty(q) == TRUE)     {
    return 0;
  }

  if (q->front < q->rear) {
    return (q->front - q->rear) % MAX_QUEUE;
  }

  return ((q->rear - q->front) % MAX_QUEUE);
}

int queue_print(FILE *fp, const Queue *q, p_queue_ele_print f) {
  void *e=NULL, *w=NULL;
  Queue *temp=NULL;
  int sz;

  if (!fp || !q || !f)  {
    return ERROR_PRINT;
  }

  temp = queue_new();
  if (!temp)  {
    return ERROR_PRINT;
  }
  sz = queue_size(q); 
  fprintf (fp, "SIZE: %d", sz); 

  /*while (queue_isEmpty(q) != TRUE){
    fprintf(fp, "\n");
    e = queue_pop((void*)q);
    if (!e) {
      return ERROR_PRINT;
    }
    if (f(fp, e) == 0)  {
      return ERROR_PRINT;
    }
    if (!queue_push(temp, e)) {
      return ERROR_PRINT;
    }
  }

  while (queue_isEmpty(temp)!= TRUE)  {
    w = (void*)queue_pop(temp);
    queue_push((void*)q,w);
  }*/

  queue_free(temp);
  return 0;
}
    
