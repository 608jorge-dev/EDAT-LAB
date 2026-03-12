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
    FILE *fIn = fopen(argv[1], "r");
    Stack *sl = NULL;
    long from_id, to_id;

    if (argc < 4)
    {
        fprintf(stderr, "Usage: %s <file> <from_id> <to_id>\n", argv[0]);
        return -1;
    }

    from_id = strtol(argv[2], NULL, 10);
    to_id   = strtol(argv[3], NULL, 10);

    if (from_id < 0 || to_id < 0)
    {
        fprintf(stderr, "Error while reading argument ids.\n");
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
    radio_print(stdout, r1);

    //Using DFS Algorithm
    if (radio_depthSearch (r1, from_id, to_id) == ERROR)  {
        fprintf(stderr, "Error while using the DFS algorithm.\n");
        radio_free(r1);
        fclose(fIn);
        stack_free(sl);
        return -1;
    }

    // free r1, file and stack
    radio_free(r1);
    fclose(fIn);
    stack_free(sl);
    return 1;
}

Status radio_depthSearch (Radio *r, long from_id, long to_id) {
  Music *mo = NULL;
  Music *mf = NULL;
  Status st;
  Stack *sl = NULL;
  int i, from, to;

  if (!r || from_id == NO_ID || to_id == NO_ID) {
    return ERROR;
  }

  from = radio_musicPosition(r, from_id)-1;
  to = radio_musicPosition(r, to_id)-1;
  mo = radio_getMusic(r, from);
  mf = radio_getMusic(r, to);

  fprintf (stdout, "\nFrom music with id: %ld\n", from_id);
  fprintf (stdout, "To music with id: %ld\n", to_id);
  fprintf (stdout, "Music exploration path: \n");

  if (music_setState (mo, NOT_LISTENED) == ERROR || music_setState (mf, NOT_LISTENED) == ERROR) {
    return ERROR;
  }

  st = OK;
  sl = stack_init();

  if (music_setState (mo, LISTENED) == ERROR || stack_push (sl, mo) == ERROR ) {
    return ERROR;
  }

  while (stack_isEmpty(sl) == FALSE && st == OK)    
  {
    mo = stack_pop(sl);
    music_plain_print(stdout, mo);
    fprintf (stdout, "\n");
    
    if (music_cmp(mo, mf) == 0)   {
        st = ERROR;
    } 
    
    else {
        for (i=from; i<to; i++)   {
            if (radio_relationExists(r, music_getId(mo), music_getId(radio_getMusic(r, i))) == TRUE && (music_getState(radio_getMusic(r, i)) == NOT_LISTENED)) {
                music_setState (radio_getMusic(r, i), LISTENED);
                stack_push (sl, radio_getMusic(r, i));
            }
        }
    }
  }
  
  stack_free(sl);
  return st;
}