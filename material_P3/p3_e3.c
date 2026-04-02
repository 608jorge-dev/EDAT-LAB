#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"
#include "music.h"
#include "radio.h"

int main(int argc, char **argv)
{
    Radio *r1 = NULL;
    FILE *fIn = fopen(argv[1], "r");
    Music *m = NULL;
    List *ls = NULL;
    int i, num, half;

    if (argc < 2)
    {
        fprintf(stderr, "Error while reading %s file.\n", argv[0]);
        fclose(fIn);
        return -1;
    }

    if ((fIn == NULL))
    {
        fprintf(stderr, "Error opening file.\n");
        fclose(fIn);
        return -1;
    }

    r1 = radio_init();
    if (r1 == NULL)
    {
        fprintf(stderr, "Error while initializing the radio.\n");
        fclose(fIn);
        return -1;
    }
    if (radio_readFromFile(fIn, r1) == ERROR)
    {
        fprintf(stderr, "Error while reading the file.\n");
        radio_free(r1);
        fclose(fIn);
        return -1;
    }

    /*Adding radio music to list*/
    ls = list_new();
    if (!ls)
    {
        fprintf(stderr, "Error while initializing the List.\n");
        radio_free(r1);
        fclose(fIn);
        return -1;
    }

    num = radio_getNumberOfMusic(r1);

    for (i = 0; i < num; i++)
    {
        m = radio_getMusic(r1, i);
        if (m == NULL)
        {
            fprintf(stderr, "Error while getting the music structure.\n");
            list_free(ls);
            radio_free(r1);
            fclose(fIn);
            return -1;
        }

        if (i % 2 == 0)
        {
            if (list_pushBack(ls, m) == ERROR)
            {
                fprintf(stderr, "Error inserting at back.\n");
                list_free(ls);
                radio_free(r1);
                fclose(fIn);
                return -1;
            }
        }
        else 
        {
            if (list_pushFront(ls, m) == ERROR)
            {
                fprintf(stderr, "Error inserting at front.\n");
                list_free(ls);
                radio_free(r1);
                fclose(fIn);
                return -1;
            }
        }
    }

    list_print(stdout, ls, music_plain_print);

    /*Revoming radio music to list*/
    half = num / 2;

    fprintf(stdout, "\nFinished inserting. Now we extract from the beginning:\n");
    for (i = 0; i < half; i++)
    {
        m = list_popFront(ls);
        if (!m)
        {
            fprintf(stderr, "Error popping from front.\n");
            list_free(ls);
            radio_free(r1);
            fclose(fIn);
            return -1;
        }

        music_plain_print(stdout, m);
        fprintf(stdout, "\n");
    }

    fprintf(stdout, "\n\nNow we extract from the end:\n");
    while (list_isEmpty(ls) == FALSE)
    {
        m = list_popBack(ls);
        if (!m)
        {
            fprintf(stderr, "Error popping from back.\n");
            list_free(ls);
            radio_free(r1);
            fclose(fIn);
            return -1;
        }

        music_plain_print(stdout, m);
        fprintf(stdout, "\n");
    }

    /*free r1, file and list*/
    list_free(ls);
    radio_free(r1);
    fclose(fIn);

    return 0;
}