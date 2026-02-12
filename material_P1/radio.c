#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "radio.h"

#define MAX_MSC 4096

struct _Radio {
    Music *songs[MAX_MSC];
    Bool relations [MAX_MSC][MAX_MSC];
    int num_music;
    int num_relations;
};


Radio *radio_init() {
    Radio *r = NULL;
  
    r = (Radio*) calloc(1, sizeof(Radio));

    if (r == NULL) {
        return NULL;
    }

    r->num_music=FALSE;
    r->num_relations=FALSE;

    return r;
}

void radio_free(Radio *r) {
  if (r) {
    free(r);
  }
}

Status radio_newMusic(Radio *r, char *desc) {
    
}