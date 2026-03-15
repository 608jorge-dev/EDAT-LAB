#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack.h"
#include "music.h"
#include "radio.h"

/**
* @brief: Makes a search from the origin music to the final music of a radio using the
* depth-first search algorithm through an ADT Stack
*
* The function prints each visited music while traversing the radio
*
* @param r, Pointer to radio
* @param from_id, id of the origin Music
* @param to_id, id of the destination Music
* @return The function returns OK or ERROR
**/
Status radio_depthSearch (Radio *r, long from_id, long to_id);

int main(int argc, char **argv)
{
    Radio *r1 = NULL;
    FILE *fIn;
    long from_id, to_id;

    if (argc < 4)
    {
        fprintf(stderr, "Usage: %s <file> <from_id> <to_id>\n", argv[0]);
        return -1;
    }

    from_id = strtol(argv[2], NULL, 10);
    to_id = strtol(argv[3], NULL, 10);

    if (from_id < 0 || to_id < 0)
    {
        fprintf(stderr, "Error while reading argument ids.\n");
        return -1;
    }

    fIn = fopen(argv[1], "r");

    if (fIn == NULL)
    {
        fprintf(stderr, "Error opening file.\n");
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

    fprintf(stderr, "Radio:\n");
    radio_print(stdout, r1);

    /* Using DFS Algorithm */
    if (radio_depthSearch(r1, from_id, to_id) == ERROR) {
        fprintf(stderr, "Error while using the DFS algorithm.\n");
        radio_free(r1);
        fclose(fIn);
        return -1;
    }

    /* Free memory */
    radio_free(r1);
    fclose(fIn);

    return 0;
}

Status radio_depthSearch (Radio *r, long from_id, long to_id) {
  Music *m = NULL;
  Stack *sl = NULL;
  Music *recommended = NULL;
  int i, num;

  if (!r) return ERROR;

  if (radio_contains(r, from_id) == FALSE || radio_contains(r, to_id) == FALSE) {
    return ERROR;
  }
    
  fprintf (stdout, "\nFrom music with id: %ld\n", from_id);
  fprintf (stdout, "To music with id: %ld\n", to_id);
  fprintf (stdout, "Music exploration path: \n");

  sl = stack_init();

  if (!sl) return ERROR;

  num = radio_getNumberOfMusic(r);

  /* Inicializar estados */
  for (i = 0; i < num; i++) {
    music_setState(radio_getMusic(r, i), NOT_LISTENED);
  }

  m = radio_getMusic(r, radio_musicPosition(r, from_id));

  music_setState(m, LISTENED);
  stack_push(sl, m);

  while (stack_isEmpty(sl) == FALSE) {
    m = stack_pop(sl);
    music_plain_print(stdout, m);
    fprintf(stdout, "\n");

    if (music_getId(m) == to_id) {
        stack_free(sl);
        return OK;
    }

    for (i = 0; i < num; i++) {
        recommended = radio_getMusic(r, i);

        if (radio_relationExists(r, music_getId(m), music_getId(recommended)) && music_getState(recommended) == NOT_LISTENED) {
            music_setState(recommended, LISTENED);
            stack_push(sl, recommended);
        }
    }
  }

  stack_free(sl);
  return OK;
}