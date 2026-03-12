  /**
 * @file  music.c
 * @author Profesores EDAT
 * @date February 2026
 * @mersion 1.0
 * @brief Library to manage ADT Music
 *
 * @details 
 * 
 * @see
 */

#include <string.h>
#include "music.h"

/* Music declaration goes here */
struct _Music {
  long id;
  char title[STR_LENGTH];
  char artist[STR_LENGTH];
  unsigned short duration;
  State state;
  int index;
};

/*----------------------------------------------------------------------------------------*/
/*
* Private function:
*/
Status music_setField (Music *m, char *key, char *value);

Status music_setField (Music *m, char *key, char *value) {
  if (!key || !value) return ERROR;

  if (strcmp(key, "id") == 0) {
    return music_setId(m, atol(value));
  } else if (strcmp(key, "title") == 0) {
    return music_setTitle(m, value);
  } else if (strcmp(key, "artist") == 0) {
    return music_setArtist(m, value);
  } else if (strcmp(key, "duration") == 0) {
    return music_setDuration(m, atol(value));
  } else if (strcmp(key, "state") == 0) {
    return music_setState(m, (State)atoi(value));
  }

  return ERROR;
}

/*----------------------------------------------------------------------------------------*/
Music *music_initFromString(char *descr) {
  Music *m;
  char *p;
  char *key_start;
  char *value_start;
  char *buffer;

  if (!descr) return NULL;

  buffer = strdup(descr);          /* copiar entrada */
  if (!buffer) return NULL;

  m = music_init();
  if (!m) {
    free(buffer);
    return NULL;
  }

  p = buffer;

  while (*p) {
    /* Skip whitespace */
    while (*p == ' ' || *p == '\t' || *p == '\n')
      p++;

    if (!*p) break;

    /* Parse key */
    key_start = p;
    while (*p && *p != ':')
      p++;

    if (!*p) break;
    *p++ = '\0';   /* terminate key */

    /* Expect opening quote */
    if (*p != '"') break;
    p++;

    /* Parse value */
    value_start = p;
    while (*p && *p != '"')
      p++;

    if (!*p) break;
    *p++ = '\0';   /* terminate value */

    music_setField(m, key_start, value_start);
  }

  free(buffer);
  return m;
}


/**  Remaining functions of music.h to be implemented here **/

Music* music_init (){
  Music *m = NULL;
  
  m = (Music*) calloc(1, sizeof(Music));

  if (m == NULL) {
    return NULL;
  }

  music_setId(m, ID_INIT);
  music_setDuration(m, DUR_INIT);
  music_setState(m, NOT_LISTENED);
  music_setTitle(m, "");
  music_setArtist(m, "");
  music_setIndex(m, 0);

  return m;
}

void music_free (void * m) {
  if (m) {
    free(m);
  }
}

long music_getId (const Music * m) {
  if (m == NULL){
    return NO_ID;
  }
  
  return m->id;
}

const char* music_getTitle (const Music * m){
  if (m == NULL){
    return NULL;
  }
  
  return m->title;
}

const char* music_getArtist (const Music * m){
  if (m == NULL){
    return NULL;
  }
  
  return m->artist;
}

unsigned short music_getDuration (const Music * m){
  if (m == NULL){
    return NO_DUR;
  }
  
  return m->duration;
}

State music_getState (const Music * m){
  if (m == NULL){
    return ERROR_MUSIC;
  }
  
  return m->state;
}

Status music_setId (Music *m, const long id){
  if (m == NULL || id < 0){
    return ERROR;
  }
  m->id= id;

  return OK;
}

int music_getIndex(const Music *m) {
  if (!m) return ERROR_INDEX;

  return m->index;
}

Status music_setTitle (Music * m, const char * title) {
  if (m == NULL || title == NULL || strlen(title) >= STR_LENGTH){
    return ERROR;
  }
  strcpy (m->title, title);

  return OK;
}

Status music_setArtist (Music * m, const char * artist) {
   if (m == NULL || artist == NULL || strlen(artist) >= STR_LENGTH){
    return ERROR;
  }
  strcpy (m->artist, artist);

  return OK;
}

Status music_setDuration (Music * m, const unsigned short duration) {
  if (m == NULL){
    return ERROR;
  }
  m->duration= duration;

  return OK;
}

Status music_setState (Music * m, const State state) {
  if (m == NULL || state < NOT_LISTENED || state > ERROR_MUSIC){
    return ERROR;
  }
  m->state= state;

  return OK;
}

Status music_setIndex(Music *m, int index) {
  if (!m) return ERROR;
  m->index = index;
  return OK;
}

int music_cmp (const void * m1, const void * m2){
  Music *one=NULL, *two=NULL;
  if (!m1 || !m2){
    return ERROR_CMP;
  }
  one = (Music*) m1;
  two = (Music*) m2;
  
  if (!one || !two){
    return ERROR_CMP;
  }

  if (music_getId(one) == music_getId(two)){
    if (strcmp(music_getTitle(one), music_getTitle(two))==0){
      return strcmp(music_getArtist(one), music_getArtist(two));
    }
    else{
      return strcmp(music_getTitle(one), music_getTitle(two));
    }
  }
  else{
    return DIF_CMP;
  }
}

void * music_copy (const void * src) {
  Music *orig = (Music*)src;
  Music *copy;

  if (!orig) return NULL;

  copy = music_init();

  if (!copy) return NULL;

  copy->id = music_getId(orig);
  strcpy(copy->title, music_getTitle(orig));
  strcpy(copy->artist, music_getArtist(orig));
  copy->duration = music_getDuration(orig);
  copy->state = music_getState(orig);
  copy->index = music_getIndex(orig);

  return copy;
}

int music_plain_print (FILE * pf, const void * m){
  Music *aux=NULL;
	int counter = 0;
  if (!pf || !m) return ERROR_PRINT;

  aux = (Music*) m;
  counter += fprintf(pf, "[%ld, ", aux->id);
  counter += fprintf(pf, "%s, ", aux->title);
	counter += fprintf(pf, "%s, ", aux->artist);
	counter += fprintf(pf, "%hu, ", aux->duration);
  counter += fprintf(pf, "%d]", aux->state);
  counter += fprintf(pf, "%d]", aux->index);
	
	return counter;
}

int music_formatted_print (FILE * pf, const void * m) {
	Music * aux;
	int counter = 0, minutes, sec;
	if (!pf || !m) return ERROR_PRINT;

	aux = (Music*) m;
	
	if (!aux->duration || aux->duration <= 0) return ERROR_PRINT;

	minutes = aux->duration / 60;
  sec = aux->duration % 60;
	
	counter = fprintf(pf, "\t ɴᴏᴡ ᴘʟᴀʏɪɴɢ: %s\n", aux->title);
	counter += fprintf(pf, "\t • Artist %s •\n", aux->artist);
	counter += fprintf(pf, "\t──────────⚪──────────\n");
	counter += fprintf(pf, "\t\t◄◄⠀▐▐ ⠀►►\n");
	counter += fprintf(pf, "\t 0:00 / %02d:%02d ───○ 🔊⠀\n\n", minutes, sec);
	
	return counter;
}



