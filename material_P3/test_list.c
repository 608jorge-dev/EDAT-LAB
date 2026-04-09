#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

#define MAX_TEST 8

/* ====== HELPERS ====== */
int int_print(FILE *fp, const void *a) {
    return fprintf(fp, "%d ", *(int*)a);
}

int *new_int(int v) {
    int *p = malloc(sizeof(int));
    assert(p != NULL);
    *p = v;
    return p;
}

void emptyList(List *l) {
	while(!list_isEmpty(l) ){
		free(list_popFront(l));
	}
}

/* ====== TESTS ====== */
/* Creación e inicialización */
void test_list_new() {
    List *l = list_new();
    assert(l != NULL);
    assert(list_isEmpty(l) == TRUE);
    assert(list_size(l) == 0);
    assert(list_getFront(l) == list_getBack(l));
    list_free(l);
}

/* Push básico */
void test_list_push_basic() {
    List *l = list_new();
    int *a = new_int(1);

    assert(list_pushBack(l, a) == OK);
    assert(list_isEmpty(l) == FALSE);
    assert(list_size(l) == 1);
    assert(*(int*)list_getFront(l) == 1);
    assert(*(int*)list_getBack(l) == 1);
	
	emptyList(l);
    list_free(l);
}

/* Push y Pop correcto */
void test_list_push_pop() {
    List *l = list_new();

    for (int i = 0; i < 5; i++) {
        assert(list_pushBack(l, new_int(i)) == OK);
    }

    for (int i = 0; i < 5; i++) {
        int *x = list_popFront(l);
        assert(x != NULL);
        assert(*x == i);
        free(x);
    }

    assert(list_isEmpty(l) == TRUE);
    list_free(l);
}

/* Pop en vacío */
void test_list_pop_empty() {
    List *l = list_new();

    assert(list_popFront(l) == NULL);
    assert(list_getFront(l) == list_getBack(l));

    list_free(l);
}

/* Llenado hasta capacidad (MAX_LIST -1) - No aplica a listas, pero test de push múltiple */
void test_list_multiple_push() {
    List *l = list_new();

    for (int i = 0; i < MAX_TEST; i++) {
        assert(list_pushBack(l, new_int(i)) == OK);
    }

    assert(list_size(l) == MAX_TEST);

	emptyList(l);
    list_free(l);
}

/* Front y Back correctos */
void test_front_back() {
    List *l = list_new();

    list_pushBack(l, new_int(10));
    list_pushBack(l, new_int(20));
    list_pushBack(l, new_int(30));

    assert(*(int*)list_getFront(l) == 10);
    assert(*(int*)list_getBack(l) == 30);

    int *x = list_popFront(l);
    free(x);

    assert(*(int*)list_getFront(l) == 20);

	emptyList(l);
    list_free(l);
}

/* Tamaño correcto en operaciones mixtas */
void test_size_consistency() {
    List *l = list_new();

    assert(list_size(l) == 0);

    list_pushBack(l, new_int(1));
    list_pushBack(l, new_int(2));
    assert(list_size(l) == 2);

    free(list_popFront(l));
    assert(list_size(l) == 1);

    free(list_popFront(l));
    assert(list_size(l) == 0);

	emptyList(l);
    list_free(l);
}

/* Robustez con NULL */
void test_null_cases() {
    assert(list_isEmpty(NULL) == TRUE);
    assert(list_size(NULL) == -1);
    assert(list_pushBack(NULL, NULL) == ERROR);
    assert(list_popFront(NULL) == NULL);
    assert(list_getFront(NULL) == NULL);
    assert(list_getBack(NULL) == NULL);
}

/* Print */
void test_list_print() {
    List *l = list_new();

    list_pushBack(l, new_int(1));
    list_pushBack(l, new_int(2));
    list_pushBack(l, new_int(3));

    int chars = list_print(stdout, l, int_print);
    assert(chars > 0);
	
	/* No se debe vaciar lista */
	assert(list_isEmpty(l) == FALSE);

    printf("\n");
	emptyList(l);
    list_free(l);
}

/* ====== MAIN ====== */
int main() {
    printf("Running tests...\n");

    test_list_new();
    test_list_push_basic();
    test_list_push_pop();
    test_list_pop_empty();
    test_list_multiple_push();
    test_front_back();
    test_size_consistency();
    test_null_cases();
    test_list_print();

    printf("All tests passed!\n");
    return 0;
}