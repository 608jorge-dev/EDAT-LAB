#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "music.h"

int main () {
    Music *m1=NULL, *m2=NULL;
    //FILE *f;
    //char name[20];

    /*printf ("Escriba el nombre del archivo final:");
    scanf ("%s", name);
    if (!(fopen(name, "w"))){
        return -1;
    }*/

    //set m1
    m1=music_init();
    music_setId(m1, 10);
    music_setTitle(m1, "Blinding Lights");
    music_setArtist(m1, "The Weeknd");
    music_setDuration(m1, 200);

    //set m2
    m2=music_init();
    music_setId(m2, 20);
    music_setTitle(m2, "Bohemian Rhapsody");
    music_setArtist(m2, "Queen");
    music_setDuration(m2, 355);

    //print m1 y m2
    music_formatted_print(stdout, m1);
    music_formatted_print(stdout, m2);
    printf ("\n");
    fprintf (stdout, "\nEquals? ");
    if (music_cmp(m1,m2)==0)   {
        fprintf (stdout, "Yes");
    } 
    else {
        fprintf (stdout, "No");
    }
    printf ("\nMusic 2 title: %s", music_getTitle(m2));

    //set m3
    Music *m3=NULL;
    m3=music_copy(m1);
    
    //print m3
    fprintf (stdout,"\nMusic 3 id: %ld\n", music_getId(m3));
    music_formatted_print(stdout, m1);
    music_formatted_print(stdout, m3);
    fprintf (stdout, "\nEquals? ");
    if (music_cmp(m1,m3)==0)   {
        fprintf (stdout, "Yes");
    } 
    else {
        fprintf (stdout, "No");
    }

    fprintf (stdout,"\n");

    //free m1, m2, m3
    music_free(m1);
    music_free(m2);
    music_free(m3);
    return 0;
}