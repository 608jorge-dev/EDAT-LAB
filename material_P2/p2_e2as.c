#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack.h"
#include "music.h"
#include "radio.h"

/**
 * @brief: Merges both stacks and unites them in a third stack
 *
 * @param sin1 first input stack
 * @param sin2 second input stack
 * @param sout  result stack
 * @return The function returns OK or ERROR
 **/
Status mergeStacks(Stack *sin1, Stack *sin2, Stack *sout);

void freeall(Radio *r1, Radio *r2, Stack *s1, Stack *s2, FILE *f1, FILE *f2);

int main(int argc, char **argv)
{
    Radio *r1 = NULL, *r2 = NULL;
    FILE *fIn1 = fopen(argv[1], "r"), *fIn2 = fopen(argv[2], "r");
    Music *m = NULL;
    Stack *sl1 = NULL, *sl2 = NULL, *sl3 = NULL;
    int i;

    /*Control de erores de argumentos al compilar*/
    if (argc < 3)
    {
        fprintf(stderr, "Error while reading %s file.\n", argv[0]);
        return -1;
    }

    /*Apertura y lectura de el primer file*/
    if ((fIn1 == NULL))
    {
        fprintf(stderr, "Error opening file 1.\n");
        return -1;
    }
    r1 = radio_init();
    if (r1 == NULL)
    {
        fprintf(stderr, "Error while initializing the radio1.\n");
        fclose(fIn1);
        return -1;
    }
    if (radio_readFromFile(fIn1, r1) == ERROR)
    {
        fprintf(stderr, "Error while reading the file1.\n");
        radio_free(r1);
        fclose(fIn1);
        return -1;
    }

    // Adding radio1 music to stack1
    sl1 = stack_init();
    if (sl1 == NULL)
    {
        fprintf(stderr, "Error while initializing the stack1.\n");
        radio_free(r1);
        fclose(fIn1);
        return -1;
    }
    for (i = 0; i < radio_getNumberOfMusic(r1); i++)
    {
        m = radio_getMusic(r1, i);
        if (m == NULL)
        {
            fprintf(stderr, "Error while getting the music structure.\n");
            radio_free(r1);
            fclose(fIn1);
            stack_free(sl1);
            return -1;
        }
        stack_push(sl1, m);
    }

    /*Apertura y lectura de el segundo file*/
    if ((fIn2 == NULL))
    {
        fprintf(stderr, "Error opening file 2.\n");
        radio_free(r1);
        fclose(fIn1);
        stack_free(sl1);
        return -1;
    }
    r2 = radio_init();
    if (r2 == NULL)
    {
        fprintf(stderr, "Error while initializing the radio2.\n");
        fclose(fIn2);
        radio_free(r1);
        fclose(fIn1);
        stack_free(sl1);
        return -1;
    }
    if (radio_readFromFile(fIn2, r2) == ERROR)
    {
        fprintf(stderr, "Error while reading the file2.\n");
        radio_free(r2);
        fclose(fIn2);
        radio_free(r1);
        fclose(fIn1);
        stack_free(sl1);
        return -1;
    }

    // Adding radio music to stack
    sl2 = stack_init();
    if (sl2 == NULL)
    {
        fprintf(stderr, "Error while initializing the stack2.\n");
        radio_free(r2);
        fclose(fIn2);
        radio_free(r1);
        fclose(fIn1);
        stack_free(sl1);
        return -1;
    }
    for (i = 0; i < radio_getNumberOfMusic(r2); i++)
    {
        m = radio_getMusic(r2, i);
        if (m == NULL)
        {
            fprintf(stderr, "Error while getting the music structure.\n");
            freeall(r1, r2, sl1, sl2, fIn1, fIn2);
            return -1;
        }
        stack_push(sl2, m);
    }

    /* Inicialización de r3, mergestacks y print de s3*/
    sl3 = stack_init();
    if (sl3 == NULL)
    {
        fprintf(stderr, "Error while initializing the stack3.\n");
        freeall(r1, r2, sl1, sl2, fIn1, fIn2);
        return -1;
    }
    fprintf(stdout, "\nPlaylist 0:\n");
    if (stack_print(stdout, sl1, music_plain_print) < 0)
    {
        fprintf(stderr, "Error while printing the stack1.\n");
        freeall(r1, r2, sl1, sl2, fIn1, fIn2);
        stack_free(sl3);
        return -1;
    }
    fprintf(stdout, "\nPlaylist 1:\n");
    if (stack_print(stdout, sl2, music_plain_print) < 0)
    {
        fprintf(stderr, "Error while printing the stack2.\n");
        freeall(r1, r2, sl1, sl2, fIn1, fIn2);
        stack_free(sl3);
        return -1;
    }
    if (mergeStacks(sl1, sl2, sl3) == ERROR)
    {
        fprintf(stderr, "Error while merging stacks.\n");
        freeall(r1, r2, sl1, sl2, fIn1, fIn2);
        stack_free(sl3);
        return -1;
    }
    fprintf(stdout, "\nPlaylist combined:\n");
    if (stack_print(stdout, sl3, music_plain_print) < 0)
    {
        fprintf(stderr, "Error while printing the stack3.\n");
        freeall(r1, r2, sl1, sl2, fIn1, fIn2);
        stack_free(sl3);
        return -1;
    }

    // free radios, files and stacks
    freeall(r1, r2, sl1, sl2, fIn1, fIn2);
    stack_free(sl3);
}

/**
 * @brief: Merges both stacks and unites them in a third stack
 *
 * @param sin1 first input stack
 * @param sin2 second input stack
 * @param sout  result stack
 * @return The function returns OK or ERROR
 **/
Status mergeStacks(Stack *sin1, Stack *sin2, Stack *sout)
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

/* Free both radios, both stacks and both files*/
void freeall(Radio *r1, Radio *r2, Stack *s1, Stack *s2, FILE *f1, FILE *f2)
{
    radio_free(r1);
    radio_free(r2);
    stack_free(s1);
    stack_free(s2);
    fclose(f1);
    fclose(f2);
}