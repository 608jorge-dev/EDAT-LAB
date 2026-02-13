#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "radio.h"

#define MAX_MSC 4096
#define NO_MUSICPOSITION -1
#define NO_NUMMUSIC -1
#define NO_RELATIONS -1

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

  if (!r) return NO_MUSICPOSITION;

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
  Music *m;
  long id;

  if (!r || !desc) return ERROR;

  m = music_initFromString(desc);
  if (!m) return ERROR;

  id = music_getId(m);

  if (radio_musicPosition(r, id) != NO_MUSICPOSITION) {
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

  if (!r) return ERROR;

  i = radio_musicPosition(r, orig);
  j = radio_musicPosition(r, dest);

  if (i == -1 || j == -1) return ERROR;

  if (r->relations[i][j] == TRUE) 
    return OK; //preguntar a la profe que deberia devolver, si OK o ERROR

  r->relations[i][j] = TRUE;
  r->num_relations++;
  

  return OK;
}

Bool radio_contains(const Radio *r, long id) {
  int i;

  if (!r) return FALSE;

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

Bool radio_relationExists(const Radio *r, long orig, long dest) {

}

int radio_getNumberOfRelationsFromId(const Radio *r, long id) {

}

long *radio_getRelationsFromId(const Radio *r, long id) {

}

int radio_print (FILE *pf, const Radio *r) {

}

