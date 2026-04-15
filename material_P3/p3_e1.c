#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "queue.h"
#include "music.h"
#include "radio.h"

int now_playing_menu(Queue *q);
int now_playing_menu(Queue *q)
{
    int option;
    Music *m = NULL;

    /* Obtenemos canción actual del top de la cola */
    m = (Music *)queue_getFront(q);
    if (m != NULL)
    {
        music_formatted_print(stdout, m);
    }
    else
    {
        printf("\nNo song currently playing.\n");
    }

    /* Imprimimos historial (cola) */
    printf("\nUncoming:\n");
    queue_print(stdout, q, music_plain_print);

    /* Mostramos menu y esperamos selección */
    printf("\n1. Next song\n");
    printf("2. Exit\n");
    printf("Choose an option: ");

    scanf("%d", &option);

    return option;
}

/* TODO MAIN FUNCTION */
int main(int argc, char **argv)
{
    Radio *r1 = NULL;
    FILE *fIn = fopen(argv[1], "r");
    Music *m = NULL;
    Queue *qu = NULL;
    int i, option = 0;

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

    /*Adding radio music to queue*/
    qu = queue_new();
    if (qu == NULL)
    {
        fprintf(stderr, "Error while initializing the queue.\n");
        radio_free(r1);
        fclose(fIn);
        return -1;
    }
    for (i = 0; i < radio_getNumberOfMusic(r1); i++)
    {
        m = radio_getMusic(r1, i);
        if (m == NULL)
        {
            fprintf(stderr, "Error while getting the music structure.\n");
            radio_free(r1);
            fclose(fIn);
            queue_free(qu);
            return -1;
        }
        queue_push(qu, m);
    }

    do
    {
        option = now_playing_menu(qu);
        if (option == 1)
        {
            queue_pop(qu);
        }

    } while (option != 2);

    /*free r1, file and queue*/
    radio_free(r1);
    fclose(fIn);
    queue_free(qu);

    return 0;
}
