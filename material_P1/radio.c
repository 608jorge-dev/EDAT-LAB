#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "radio.h"

struct _Radio {
  Music *songs[MAX_MSC];
  Bool relations [MAX_MSC][MAX_MSC];
  int num_music;
  int num_relations;
};

/*----------------------------------------------------------------------------------------*/
/*
Private function:
*/

/**
 * @brief Finds the position of a music in the radio by its ID.
 *
 * Searches sequentially through the array of musics stored in the radio
 * to locate the music with the specified ID.
 *
 * @param r Pointer to the radio.
 * @param id ID of the music to be searched.
 *
 * @return The position of the music in the radio if found, -1 otherwise.
 */
int radio_musicPosition(const Radio *r, long id);

int radio_musicPosition(const Radio *r, long id) {
  int i;

  if (!r || id<0){ return NO_MUSICPOSITION;}

  for (i = 0; i < r->num_music; i++) {
    if (music_getId(r->songs[i]) == id)
      return i;
  }

  return NO_MUSICPOSITION;
}

/*----------------------------------------------------------------------------------------*/

Radio *radio_init() {
  Radio *r = NULL;
  int i, j;
  
  r = (Radio*) calloc(1, sizeof(Radio));
  if (r == NULL) {
    return NULL;
  }

  for (i=0; i<MAX_MSC; i++) {
    r->songs[i]=music_init();
  }
  r->num_music = 0;
  r->num_relations = 0;

  for (i = 0; i < MAX_MSC; i++) {
    r->songs[i] = NULL;
      for (j = 0; j < MAX_MSC; j++) {
        r->relations[i][j] = FALSE;
      }
  }

  return r;
}

void radio_free(Radio *r) {
  int i;

  if (r) {
    for (i = 0; i < r->num_music; i++) {
    music_free(r->songs[i]);
    }
  
    free(r);
  }
}

Status radio_newMusic(Radio *r, char *desc) {
  Music *m=NULL;
  long id;

  if (!r || !desc) return ERROR;

  m = music_initFromString(desc);
  if (!m) return ERROR;

  id = music_getId(m);

  if (radio_contains(r, id) == TRUE){
    music_free(m);
    return OK;
  }

  if (r->num_music >= MAX_MSC) {
    music_free(m);
    return ERROR;
  }

  r->songs[r->num_music] = m;
  r->num_music++;

  return OK;
}

Status radio_newRelation(Radio *r, long orig, long dest) {
  int i, j;

  if (!r || orig<0 || dest<0) return ERROR;

  i = radio_musicPosition(r, orig);
  j = radio_musicPosition(r, dest);

  if (i == NO_MUSICPOSITION || j == NO_MUSICPOSITION) return ERROR;

  if (radio_relationExists(r, orig, dest) == TRUE) {
    return OK; 
  }
  
  r->relations[i][j] = TRUE;
  r->num_relations++;

  return OK;
}

Bool radio_contains(const Radio *r, long id) {
  int i;

  if (!r || id<0) return FALSE;

  for (i = 0; i < r->num_music; i++) {
    if (music_getId(r->songs[i]) == id)
      return TRUE;
  }

  return FALSE;
}

int radio_getNumberOfMusic(const Radio *r) {
  if (!r) return NO_NUMMUSIC;

  return r->num_music;
}

int radio_getNumberOfRelations(const Radio *r) {
  if (!r) return NO_RELATIONS;

  return r->num_relations;
}

//*******************************************************//
Bool radio_relationExists(const Radio *r, long orig, long dest) {
  if (!r || orig<0 || dest<0) {
    return FALSE;
  }
  if ((radio_contains(r,orig)==FALSE)||(radio_contains(r,dest)==FALSE)) {
    return FALSE;
  }

  if ((r->relations[radio_musicPosition(r,orig)][radio_musicPosition(r,dest)])==TRUE) {
    return TRUE;
  }

  return FALSE;
}

int radio_getNumberOfRelationsFromId(const Radio *r, long id) {
  int i,rel=0;
  if (!r || id<0) {
    return NO_RELATIONS;
  }

  for (i=0; i<(radio_getNumberOfMusic(r)); i++) {
      if ((radio_relationExists(r,id,music_getId(r->songs[i])))==TRUE)  {
        rel++;
      }
    
  }
  return rel;
}

long *radio_getRelationsFromId(const Radio *r, long id) {
  long *array=NULL;
  int i,j=0,size;
  if (!r || id<0) {
    return NULL;
  }

  size=radio_getNumberOfRelationsFromId(r,id);
  if (size==0) {
    return NULL;
  }
  
  array=(long*)calloc(size,sizeof(long));
  if (array==NULL) {
    return ERROR;
  }

  for (i=0; i<(radio_getNumberOfMusic(r)); i++)  {
    if ((radio_relationExists(r, id, music_getId(r->songs[i])))==TRUE){
      array[j]=music_getId(r->songs[i]);
      j++;
    }
  }
  return array;
}

int radio_print (FILE *pf, const Radio *r) {
  int i,j;
  long *ar=NULL;
  if (!pf || !r) {
    return NO_PRINT;
  }

  for (i=0; i<(radio_getNumberOfMusic(r)); i++)  {
    music_plain_print(pf,r->songs[i]);
    fprintf (pf, ":");
    ar=radio_getRelationsFromId(r, music_getId(r->songs[i]));
    for (j=0; j<(radio_getNumberOfMusic(r)); j++)  {
      music_plain_print(pf,r->songs[radio_musicPosition(r, ar[j])]);
    }
    fprintf (pf, "\n");
  }
  return OK;
}

/*Status radio_readFromFile (FILE *fin, Radio *r) {

}*/