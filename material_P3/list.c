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
struct _Node {
  void  *info;
  struct _Node *next;
};

typedef struct _Node Node;

/* List declaration goes here */
struct _List {
  Node  *first; /* First node of the list*/
  Node *last;   /* Last node of the list*/
  int size;
};

List *list_new() {
  List *new_list = NULL;
  int i;
  new_list = (List *)calloc(1, sizeof(List));
  if (!new_list)
  {
    return NULL;
  }


  return new_list;
}

Bool list_isEmpty(const List *pl);
Status list_pushFront(List *pl, const void *e);
Status list_pushBack(List *pl, const void *e);
void *list_popFront(List *pl);
void *list_popBack(List *pl);
void *list_getFront(List *pl);
void *list_getBack(List *pl);
void list_free(List *pl);
int list_size(const List *pl);
int list_print(FILE *fp, const List *pl, p_list_ele_print f);