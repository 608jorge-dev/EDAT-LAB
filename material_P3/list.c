/**
 * @file  list.c
 * @author Jorge Torrijos de la Cruz e Ivan Reyero Fernández
 * @date Marcg 2026
 * @mersion 1.0
 * @brief Library to manage list
 *
 * @details
 *
 * @see
 */
#include <string.h>
#include "list.h"

/* Node declaration goes here */
struct _Node
{
  void *info;
  struct _Node *next;
};

typedef struct _Node Node;

/* List declaration goes here */
struct _List
{
  Node *first; /* First node of the list*/
  Node *last;  /* Last node of the list*/
  int size;
};

/*****************************************/
Node *node_new()
{
  Node *new_node = NULL;

  new_node = (Node *)malloc(sizeof(Node));
  if (new_node == NULL)
  {
    return NULL;
  }

  new_node->info = NULL;
  new_node->next = NULL;

  return new_node;
}

Status list_set_size(List *pl, int amount)
{
  if (!pl || amount < 0)
  {
    return ERROR;
  }

  pl->size = amount;

  return OK;
}

/**************************************/
List *list_new()
{
  List *new_list = NULL;

  new_list = (List *)malloc(sizeof(List));
  if (!new_list)
  {
    return NULL;
  }

  new_list->first = NULL;
  new_list->last = NULL;
  new_list->size = 0;

  return new_list;
}

void list_free(List *pl)
{
  if (pl == NULL)
  {
    return;
  }

  while (list_isEmpty(pl) == FALSE)
  {
    list_popFront(pl);
  }

  free((void *)pl);
}

Bool list_isEmpty(const List *pl)
{
  if (pl == NULL)
  {
    return TRUE;
  }

  if (pl->first == NULL)
  {
    return TRUE;
  }

  return FALSE;
}

Status list_pushFront(List *pl, const void *e)
{
  Node *n = NULL;
  if ((pl == NULL) || (e == NULL))
  {
    return ERROR;
  }

  n = node_new();
  if (n == NULL)
  {
    return ERROR;
  }

  n->info = (void *)e;
  n->next = pl->first;
  pl->first = n;
  list_set_size(pl, list_size(pl) + 1);

  return OK;
}

Status list_pushBack(List *pl, const void *e)
{
  Node *n = NULL;
  if ((pl == NULL) || (e == NULL))
  {
    return ERROR;
  }

  n = node_new();
  if (n == NULL)
  {
    return ERROR;
  }
  n->info = (void *)e;

  if (list_isEmpty(pl) == TRUE)
  {
    pl->first = n;
    pl->last = n;
    return OK;
  }

  pl->last->next = n;
  pl->last = n;
  list_set_size(pl, list_size(pl) + 1);

  return OK;
}

void *list_popFront(List *pl)
{
  void *e = NULL;
  Node *n = NULL;

  if ((pl == NULL) || (list_isEmpty(pl) == TRUE))
  {
    return NULL;
  }

  n = pl->first;
  e = n->info;
  pl->first = n->next;

  list_set_size(pl, list_size(pl) - 1);
  free((void *)n);

  return e;
}

void *list_popBack(List *pl)
{
  void *e = NULL;
  Node *pn = NULL;
  if ((pl == NULL) || (list_isEmpty(pl) == TRUE))
  {
    return NULL;
  }
  if (pl->first->next == NULL)
  {
    e = pl->first->info;
    free((void *)pl->first);
    pl->first = NULL;
    return e;
  }

  pn = pl->first;
  while (pn->next->next != NULL)
  {
    pn = pn->next;
  }
  e = pn->next->info;
  free((void *)pn->next);
  pn->next = NULL;
  return e;
}

void *list_getFront(List *pl)
{
  if (!pl)
  {
    return NULL;
  }

  return pl->first;
}

void *list_getBack(List *pl)
{
  if (!pl)
  {
    return NULL;
  }

  return pl->last;
}

int list_size(const List *pl)
{
  if (!pl)
  {
    return -1;
  }

  return pl->size;
}

int list_print(FILE *fp, const List *pl, p_list_ele_print f)
{
  int sz;
  Node *e = NULL;

  if (!fp || !pl || !f)
  {
    return ERROR_PRINT;
  }

  sz = list_size(pl);
  fprintf(stdout, "%d\n", sz);
  if (sz == 0)
  {
    return ERROR_PRINT;
  }

  e = pl->first;

  while (e != NULL)
  {

    if (f(fp, e->info) == 0)
    {
      return ERROR_PRINT;
    }
    fprintf(fp, "\n");

    e = e->next;
  }

  return 0;
}