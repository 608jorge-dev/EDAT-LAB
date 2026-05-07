#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bstree.h"
#include "radio.h"
#include "types.h"

int mainCleanUp(int ret_value, Radio *r, FILE *pf, BSTree *t, List *l)
{
    radio_free(r);
    fclose(pf);
    tree_destroy(t);
    list_free(l);
    exit(ret_value);
}

BSTree *loadUnbalancedTree(Music **data, int n)
{
    BSTree *t;
    Music *m;
    int i;

    if (!data || (n <= 0))
    {
        return NULL;
    }

    if (!(t = tree_init(music_plain_print, music_cmp)))
    {
        return NULL;
    }

    for (i = 0; i < n; i++)
    {
        m = data[i];
        if (tree_insert(t, m) == ERROR)
        {
            fprintf(stdout, "Music ");
            music_plain_print(stdout, m);
            fprintf(stdout, " not inserted!\n");
        }
    }

    return t;
}

int main(int argc, char const *argv[])
{
    FILE *fIn = NULL;
    BSTree *t = NULL;
    Music **songs = NULL, *m1 = NULL, *m2 = NULL;
    long min, max;
    int n;
    Radio *r = NULL;
    List *l = NULL;

    if (argc != 4)
    {
        printf("Usage: %s music_file first_id second_id\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    fIn = fopen(argv[1], "r");
    if (!fIn)
    {
        return (EXIT_FAILURE);
    }

    min = atoi(argv[2]);
    min = atoi(argv[2]);
    max = atoi(argv[3]);
    max = atoi(argv[3]);

    r = radio_init();
    if (!r)
    {
        mainCleanUp(EXIT_SUCCESS, r, fIn, t, l);
    }

    if (radio_readFromFile(fIn, r) == ERROR)
    {
        fprintf(stdout, "Not file or File format incorrect\n");
        mainCleanUp(EXIT_SUCCESS, r, fIn, t, l);
    }

    songs = radio_getSongs(r);
    if (!songs)
    {
        mainCleanUp(EXIT_SUCCESS, r, fIn, t, l);
    }
    n = radio_getNumberOfMusic(r);
    if (n <= 0)
    {
        mainCleanUp(EXIT_SUCCESS, r, fIn, t, l);
    }

    fprintf(stdout, "Lista de canciones desde id %ld hasta id %ld\n", min, max);
    t = loadUnbalancedTree(songs, n);
    if (!t)
    {
        mainCleanUp(EXIT_SUCCESS, r, fIn, t, l);
    }

    m1 = songs[radio_musicPosition(r, min)];
    m2 = songs[radio_musicPosition(r, max)];

    l = tree_rangeSearch(t, m1, m2);
    if (!l)
    {
        mainCleanUp(EXIT_SUCCESS, r, fIn, t, l);
    }
    if (list_print(stdout, l, music_plain_print) == 0)
    {
        mainCleanUp(EXIT_SUCCESS, r, fIn, t, l);
    }

    mainCleanUp(EXIT_SUCCESS, r, fIn, t, l);
    return 0;
}

/* P2 ¿qué características observas en la lista resultante?, ¿a qué se debe?*/
/* La característica más notoria de la lista es que se encuentra ordenada en orden ascendente debido a que la función de búsqueda del árbol recorre el árbol en inorden
y la función recursiva de búsqueda usa la funcion list_pushback para insertar los nodos que va encontrando, lo que produce una lista organizada en orden (debido a la función de búsqueda)
y en orden ascendente (debido a la función recursiva de búsqueda)*/