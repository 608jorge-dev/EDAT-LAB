/**
 * @file  queue.c
 * @author Jorge Torrijos de la Cruz e Ivan Reyero Fernández
 * @date March 2026
 * @mersion 1.0
 * @brief Library to manage queue
 *
 * @details 
 * 
 * @see
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "queue.h"

struct _Queue
{
  void *data[MAX_QUEUE];
  void **front;
  void **rear;
};

Queue *queue_new()
{
  Queue *new_queue = NULL;
  int i;
  new_queue = (Queue *)calloc(1, sizeof(Queue));
  if (!new_queue)
  {
    return NULL;
  }

  for (i = 0; i < MAX_QUEUE; i++)
  {
    new_queue->data[i] = NULL;
  }

  new_queue->front = &(new_queue->data[0]);
  new_queue->rear = &(new_queue->data[0]);

  return new_queue;
}

void queue_free(Queue *pq) { free((void *)pq); }

Bool queue_isEmpty(const Queue *q)
{
  if (!q)
  {
    return FALSE;
  }

  if (q->front == q->rear)
  {
    return TRUE;
  }

  return FALSE;
}

Bool queue_isFull(const Queue *pq)
{
  if (pq == NULL)
  {
    return TRUE;
  }
  if ((pq->rear + 1 - pq->front) % MAX_QUEUE == 0)
  {
    return TRUE;
  }
  return FALSE;
}

Status queue_push(Queue *q, void *ele)
{
  if (!q || !ele /*|| queue_isFull(q) == TRUE*/)
  {
    return FALSE;
  }

  *(q->rear) = (void *)ele;
  q->rear = q->data + (q->rear + 1 - q->data) % MAX_QUEUE;

  return OK;
}

void *queue_pop(Queue *q)
{
  void *ele = NULL;
  if (!q || queue_isEmpty(q) == TRUE )
  {
    return FALSE;
  }

  
  ele = *(q->front);
  *(q->front) = NULL;
  q->front = q->data + (q->front + 1 - q->data) % MAX_QUEUE;

  return ele;
}

void *queue_getFront(const Queue *q)
{
  if (!q)
  {
    return NULL;
  }

  return *(q->front);
}

void *queue_getBack(const Queue *q)
{
  void **last_elem;
  if ((q == NULL) || (queue_isEmpty(q) == TRUE))
  {
    return NULL;
  }
  if (q->rear == q->data)
  {
    last_elem = ((Queue *)q)->data + MAX_QUEUE - 1;
  }
  else
  {
    last_elem = q->rear - 1;
  }
  return *last_elem;
}

size_t queue_size(const Queue *q)
{
  if (!q) {
    return 0;
  }

  if (queue_isEmpty(q) == TRUE)  {
    return 0;
  }

  if (q->front > (q->rear)) {
    return (q->front - q->rear) % MAX_QUEUE;
  }
  
 return (((q->rear) - q->front) % MAX_QUEUE);
}

int queue_print(FILE *fp, const Queue *q, p_queue_ele_print f)
{
  int i, sz, initial, current;

  if (!fp || !q || !f)
  {
    return ERROR_PRINT;
  }

  sz = queue_size(q);
  fprintf (stdout, "%d\n", sz);
  if (sz == 0)
  {
    return ERROR_PRINT;
  }

  initial = q->front - (void **)q->data;
  
  for (i = 0; i < sz; i++)
  {
    current = (initial + i) % MAX_QUEUE;
   
    if (f(fp, q->data[current]) == 0)
    {
      return ERROR_PRINT;
    }
    fprintf(fp, "\n");
  }

  return 0;
}
