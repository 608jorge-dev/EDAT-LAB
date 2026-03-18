#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "stack.h"

#define MAX_STACK 20

struct _Stack {
void *data[MAX_STACK ];
int top;
};

Stack *stack_init() {
  Stack *sl = NULL;
  int i;

  sl = (Stack *) calloc(1,sizeof(Stack));
  if (sl == NULL) {
    return NULL;
  }

  for (i = 0; i < MAX_STACK; i++) {
    sl->data[i] = NULL;
  }
  sl->top = 0;

  return sl;
}

void stack_free(Stack *s)   { 
  free((void *)s); 
}

Status stack_push(Stack *s, const void *ele)    {
  if ((s == NULL) || (ele == NULL) || (s->top+1 == MAX_STACK)) {
    return ERROR;
  }

  s->top ++;
  s->data[s->top] = (void *)ele;
 
  return OK;
}

void *stack_pop(Stack *s)   {
  void *e = NULL;
  if ((s == NULL) || (stack_isEmpty(s) == TRUE)) {
    return NULL;
  }

  e = s->data[s->top];
  s->data[s->top] = NULL;
  s->top --;

 return e;
}

void *stack_top(const Stack *s) {
  if ((s == NULL) || (stack_isEmpty(s) == TRUE)) {
    return NULL;
  }

  return s->data[s->top];
}

Bool stack_isEmpty(const Stack *s)  {
  if (s == NULL) {
    return TRUE;
  }
  if (s ->top == 0) {
    return TRUE;
 }

  return FALSE;
}

size_t stack_size(const Stack *s)   {
  if ((s == NULL) || (stack_isEmpty(s) == TRUE)) {
    return 0;
  }

  return s->top;
}

int stack_print(FILE *fp, const Stack *s, P_stack_ele_print f)  {
  int i,sz;
  void *e=NULL, *w=NULL;
  Stack *temp=NULL;
  if (!fp || !s || !f)  {
    return 0;
  }

  temp = stack_init();
  if (!temp)  {
    return -1;
  }
  fprintf (fp, "Stack:\n");   
  fprintf (fp, "\tNumber of elements: %ld\n", stack_size(s)); 
  sz=stack_size(s);
  for (i=0; i<sz; i++){
    fprintf(fp, "\n");
    e=stack_pop((void*)s);
    f(fp, e);
    stack_push(temp, e);
  }

  while (stack_isEmpty(temp)!= TRUE)  {
    w=(void*)stack_pop(temp);
    stack_push((void*)s,w);
  }
  stack_free(temp);
  return 0;
}

