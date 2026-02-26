#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack.h"
#include "music.h"
#include "radio.h"

int show_player_menu(Stack *history);
int show_player_menu(Stack *history) {
    int option;
    Music *m = NULL;
	
	/* Obtenemos canción actual del top de la pila */
	m = (Music *)stack_top (history);
    if (m != NULL) {
		music_formatted_print(stdout, m);
    } else {
        printf("\nNo song currently playing.\n");
    }
	
	/* Imprimimos historial (pila) */
	printf("\nRecently Played:\n");
	stack_print(stdout, history, music_plain_print);
	
	/* Mostramos menu y esperamos selección */
    printf("\n1. Back to previous song\n");
    printf("2. Exit\n");
    printf("Choose an option: ");

    scanf("%d", &option);

    return option;
}

/* TODO MAIN FUNCTION */
int main (int argc, char **argv) {
    Radio *r1=NULL;
    FILE *fIn=fopen(argv[1], "r");
    Music *m=NULL;
    Stack *sl=NULL;
    int i, option;
    
    if (argc<2) {
        fprintf (stderr, "Error while reading %s file.\n", argv[0]);
        return -1;
    }
    
    if ((fIn == NULL)){
        fprintf (stderr, "Error opening file.\n");
        fclose(fIn);
        return -1;
    }
    r1=radio_init();
    if (r1==NULL)    {
        fprintf(stderr, "Error while initializing the radio.\n");
        fclose(fIn);
        return -1;
    }
    if (radio_readFromFile(fIn,r1)==ERROR)  {
        fprintf (stderr, "Error while reading the file.\n");
        radio_free(r1);
        fclose (fIn);
        return -1;
    }
    
    //Adding radio music to stack
    sl=stack_init();
    if (sl==NULL)    {
        fprintf (stderr, "Error while initializing the stack.\n");
        radio_free(r1);
        fclose (fIn);
        return -1;
    }
    for (i=0; i<radio_getNumberOfMusic(r1); i++)    {
        m=radio_getMusic(r1,i);
        if (m==NULL) {
            fprintf (stderr, "Error while getting the music strutcure.\n");
            radio_free(r1);
            fclose (fIn);
            stack_free(sl);
            return -1;
        }
        stack_push(sl, m);
    }

    do {
        option = show_player_menu(sl);

        if (option == 1) {
            stack_pop(sl);
        }
        
    } while (option != 2);



    //free r1, file and stack
    radio_free(r1);
    fclose (fIn);
    stack_free(sl);
}


