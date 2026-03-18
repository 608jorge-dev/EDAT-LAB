#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "stack.h"

#define MAX_STACK 8

struct _Stack {
void *data[MAX_STACK ];
int top;
};

Stack *stack_init() {
  Stack *sl = NULL;
  int i;

  sl = (Stack *) malloc(sizeof(Stack));
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
  if ((s == NULL) || (ele == NULL) || (_stack_is_full(s) == TRUE)) {
    return ERROR;
  }

  s->top ++;
  s->data[s->top] = (void *)ele;

  return OK;
}

void *stack_pop(Stack *s)   {
  void *e = NULL;
  if ((s == NULL) || (stack_is_empty(s) == TRUE)) {
    return NULL;
  }

  e = s->data[s->top];
  s->data[s->top] = NULL;
  s->top --;

 return e;
}

void *stack_top(const Stack *s) {
  if ((s == NULL) || (stack_is_empty(s) == TRUE)) {
    return NULL;
 }

  return s->data[s->top];
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

size_t stack_size(const Stack *s)   {
  if ((s == NULL) || (stack_is_empty(s) == TRUE)) {
    return 0;
  }

  return s->top;
}

/**
 * @brief: Merges both stacks and unites them in a third stack
 *
 * @param sin1 first input stack
 * @param sin2 second input stack
 * @param sout  result stack
 * @return The function returns OK or ERROR
 **/
Status mergeStacksa(Stack *sin1, Stack *sin2, Stack *sout)
{
    void *e = NULL;
    Stack *ps = NULL;

    if (!sin1 || !sin2 || !sout)
    {
        return ERROR;
    }

    while (stack_isEmpty(sin1) == FALSE && stack_isEmpty(sin2) == FALSE)
    {
        if (stack_top(sin1) > stack_top(sin2))
        {
            if (!(e = stack_pop(sin1)))
            {
                return ERROR;
            }
        }
        else
        {
            if (!(e = stack_pop(sin2)))
            {
                return ERROR;
            }
        }

        if (stack_push(sout, e) == ERROR)
        {
            return ERROR;
        }
    }

    if (stack_isEmpty(sin1) == TRUE)
    {
        ps = sin2;
    }
    else
    {
        ps = sin1;
    }

    while (stack_isEmpty(ps) == FALSE)
    {
        if (!(e = stack_pop(ps)))
        {
            return ERROR;
        }

        if (stack_push(sout, e) == ERROR)
        {
            return ERROR;
        }
    }

    return OK;
}

/* Merges both stacks and unites them in a third stack*/
Status mergeStacksb(Stack *sin1, Stack *sin2, Stack *sout, P_stack_ele_cmp f)
{
    void *e = NULL;
    Stack *ps = NULL;

    if (!sin1 || !sin2 || !sout)
    {
        return ERROR;
    }

    while (stack_isEmpty(sin1) == FALSE && stack_isEmpty(sin2) == FALSE)
    {
        if (f(stack_top(sin1), stack_top(sin2)) == 0)
        {
            if (!(e = stack_pop(sin1)))
            {
                return ERROR;
            }
        }
        else if (f(stack_top(sin1), stack_top(sin2)) == 1)
        {
            if (!(e = stack_pop(sin1)))
            {
                return ERROR;
            }
        }
        else if (f(stack_top(sin1), stack_top(sin2)) == -1)
        {
            if (!(e = stack_pop(sin2)))
            {
                return ERROR;
            }
        }

        if (stack_push(sout, e) == ERROR)
        {
            return ERROR;
        }
    }

    if (stack_isEmpty(sin1) == TRUE)
    {
        ps = sin2;
    }
    else
    {
        ps = sin1;
    }

    while (stack_isEmpty(ps) == FALSE)
    {
        if (!(e = stack_pop(ps)))
        {
            return ERROR;
        }

        if (stack_push(sout, e) == ERROR)
        {
            return ERROR;
        }
    }

    return OK;
}

int stack_print(FILE *fp, const Stack *s, P_stack_ele_print f)  {
  int i;  
  if (!fp || !s || !f)  {
    return 0;
  }

  fprintf (fp, "Stack:");   
  while (s->top != 0)  {
    if (!f(fp, stack_pop(s)))   {
        return -1;
    }
  }
}

