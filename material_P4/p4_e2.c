#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bstree.h"
#include "radio.h"
#include "types.h"

int mainCleanUp(int ret_value, Radio *r, FILE *pf)
{
    radio_free(r);
    fclose(pf);
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
    Music **songs = NULL;
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

    r = radio_init();
    if (!r)
    {
        mainCleanUp(EXIT_FAILURE, r, fIn);
    }

    if (radio_readFromFile(fIn, r) == ERROR)
    {
        fprintf(stdout, "Not file or File format incorrect\n");
        mainCleanUp(EXIT_FAILURE, r, fIn);
    }

    songs = radio_getSongs(r);
    if (songs)
    {
        mainCleanUp(EXIT_FAILURE, r, fIn);
    }
    n = radio_getNumberOfMusic(r);
    if (n <= 0)
    {
        mainCleanUp(EXIT_FAILURE, r, fIn);
    }

    min = atoi(argv[2]);
    max = atoi(argv[3]);
    fprintf(stdout, "Lista de canciones desde id %ld hasta id %ld\n", min, max);
    t = loadUnbalancedTree(songs, n);
    if (!t)
    {
        mainCleanUp(EXIT_FAILURE, r, fIn);
    }

    l = tree_rangeSearch(t, (void *)min, (void *)max);
    if (!l)
    {
        mainCleanUp(EXIT_FAILURE, r, fIn);
    }
    if (list_print(stdout, l, music_plain_print) == 0)
    {
        mainCleanUp(EXIT_FAILURE, r, fIn);
    }

    return 1;
}

/* P2 ¿qué características observas en la lista resultante?, ¿a qué se debe?*/