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
    int n, more_duration, min_duration;
    Radio *r = NULL;

    if (argc != 3)
    {
        printf("Usage: %s music_file min_duration\n", argv[0]);
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
    if (!songs)
    {
        mainCleanUp(EXIT_FAILURE, r, fIn);
    }
    n = radio_getNumberOfMusic(r);
    if (n <= 0)
    {
        mainCleanUp(EXIT_FAILURE, r, fIn);
    }

    t = loadUnbalancedTree(songs, n);
    if (!t)
    {
        mainCleanUp(EXIT_FAILURE, r, fIn);
    }

    min_duration = atoi(argv[2]);
    more_duration = tree_countLongSongs (t, min_duration);

    if (more_duration == -1) {
        mainCleanUp(EXIT_FAILURE, r, fIn);
    }

    fprintf(stdout, "Numero de canciones con duracion mayor a %d segundos: %d\n", min_duration, more_duration);

    tree_destroy(t);
    mainCleanUp(EXIT_SUCCESS, r, fIn);

    return 1;
}

/* P3. Tal y como está construido el árbol ¿es posible realizar una poda inteligente para optimizar el recorrido al filtrar por duración?
No, ya que el árbol se ordena según los ids, por lo que vas a tener que revisar todas y cada una de las canciones para comprobar su duración, 
y que se comparen. En el caso en que se ordenaran por duración, se podría, aunque no tendría sentido ordenarlo así, ya que las duraciones 
pueden coincidir, y no habría manera de decidir si el nodo va hacia la izquierda o derecha. 
*/