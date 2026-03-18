#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "stack.h"

#define INIT_CAPACITY 2 // init stack capacity
#define FCT_CAPACITY 2 // multiply the stack capacity

struct _Stack {
void **item;    /*!<Static array of elements*/
int top;        /*!<index of the top element in the stack*/
int capacity;   /*!<xcapacity of the stack*/
};

Stack *stack_init() {
  Stack *sl = NULL;
  int i;

  sl = (Stack *) calloc(1,sizeof(Stack));
  if (sl == NULL) {
    return NULL;
  }

  sl->item = calloc(INIT_CAPACITY, sizeof(void*));
  for (i = 0; i < INIT_CAPACITY; i++) {
    sl->item[i] = NULL;
  }
  sl->top = -1;
  sl->capacity = INIT_CAPACITY;

  return sl;
}

void stack_free(Stack *s)   { 
  free (s->item);
  free((void *)s); 
}

Status stack_set_capacity (Stack *s, int value)  {
  if (!s) {
    return ERROR;
  }

  s->capacity=value;
  return OK;
}

int stack_get_capacity (Stack *s) {
  return s->capacity;
}

Status stack_get_morememory(Stack *s) {
  void **sl = NULL;

  if (!s) { 
    return ERROR;
  }

  sl = (void **) realloc(s->item, (s->capacity * FCT_CAPACITY) * sizeof(void *));
  
  if (!sl)  { 
    return ERROR; 
  }

  s->item = sl;
  s->capacity = s->capacity * FCT_CAPACITY;
  
  return OK;
}

Status stack_push(Stack *s, const void *ele)    {
  if ((s == NULL) || (ele == NULL))  {
    return ERROR;
  }

  if (stack_isFull(s) == TRUE) {
    if (stack_get_morememory(s) == ERROR) {
      return ERROR;
    }
  }

  s->top ++;
  s->item[s->top] = (void *)ele;
  

  return OK;
}

void *stack_pop(Stack *s)   {
  void *e = NULL;
  if ((s == NULL) || (stack_isEmpty(s) == TRUE)) {
    return NULL;
  }

  e = s->item[s->top];
  s->item[s->top] = NULL;
  s->top --;

 return e;
}

void *stack_top(const Stack *s) {
  if ((s == NULL) || (stack_isEmpty(s) == TRUE)) {
    return NULL;
  }

  return s->item[s->top];
}

Bool stack_isEmpty(const Stack *s)  {
  if (s == NULL) {
    return TRUE;
  }
  if (s ->top == -1) {
    return TRUE;
 }

  return FALSE;
}

Bool stack_isFull(const Stack *s)  {
  if (s == NULL) {
    return TRUE;
  }
  if ((s->top+1) == s->capacity) {
    return TRUE;
  }

  return FALSE;
}

size_t stack_size(const Stack *s)   {
  int num;
  if ((s == NULL) || (stack_isEmpty(s) == TRUE)) {
    return 0;
  }

  num = s->top+1;
  return num;
}

int stack_print(FILE *fp, const Stack *s, P_stack_ele_print f)  {
  int sz;
  void *e=NULL, *w=NULL;
  Stack *temp=NULL;
  if (!fp || !s || !f)  {
    return ERROR_PRINT;
  }

  temp = stack_init();
  if (!temp)  {
    return ERROR_PRINT;
  }
  sz=stack_size(s);
  fprintf (fp, "Stack:\n");   
  fprintf (fp, "\tNumber of elements: %d\n", sz); 

  while (stack_isEmpty(s) != TRUE){
    fprintf(fp, "\n");
    e=stack_pop((void*)s);
    if (!e) {
      return ERROR_PRINT;
    }
    if (f(fp, e) == 0)  {
      return ERROR_PRINT;
    }
    if (!stack_push(temp, e)) {
      return ERROR_PRINT;
    }
  }

  while (stack_isEmpty(temp)!= TRUE)  {
    w=(void*)stack_pop(temp);
    stack_push((void*)s,w);
  }

  stack_free(temp);
  return 0;
}

