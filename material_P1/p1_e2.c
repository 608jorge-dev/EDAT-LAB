#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "radio.h"

int main () {
    Radio *r1=NULL;
    int i;
    long *array=NULL;
    //FILE *f;
    //char name[20];

    /*printf ("Escriba el nombre del archivo final:");
    scanf ("%s", name);
    if (!(fopen(name, "w"))){
        return -1;
    }*/
    
    //Radio initialization and music adition
    r1=radio_init();
    fprintf (stdout, "Inserting Paint It, Black... ");
    if (radio_newMusic(r1,"id:111 title:Paint it, black artist:The Rolling Stones duration:202")==ERROR){
        fprintf (stdout, "result...: 0");
    }
    else if (radio_newMusic(r1,"id:111 title:Paint it, black artist:The Rolling Stones duration:202")==OK){
        fprintf (stdout, "result...: 1");
    }
    fprintf (stdout, "\nInserting Every Breath You Take...");
    if (radio_newMusic(r1,"id:222 title:Every Breath you take artist:The Police duration:253")==ERROR){
        fprintf (stdout, "result...: 0");
    }
    else if (radio_newMusic(r1,"id:222 title:Every Breath you take artist:The Police duration:253")==OK) {
        fprintf (stdout, "result...: 1");
    }

    //Relation between 222->111
    fprintf (stdout, "\n\nInserting radio recommendation: 222->111...");
    if ((radio_newRelation(r1, 222, 111))== ERROR) {
        fprintf (stdout, "result...: 0");
    }
    else if ((radio_newRelation(r1, 222, 111))== OK) {
        fprintf (stdout, "result...: 1");
    }
    fprintf (stdout,"\n\n111 -> 222?");
    if (radio_relationExists(r1, 111, 222)==FALSE){
        fprintf(stdout, " No");
    }
    else if ((radio_relationExists(r1, 111, 111)==TRUE)){
        fprintf (stdout, " Yes");
    }
    fprintf (stdout,"\n222 -> 111?");
    if (radio_relationExists(r1, 222, 111)==FALSE){
        fprintf(stdout, " No");
    }
    else if ((radio_relationExists(r1, 222, 111)==TRUE)){
        fprintf (stdout, " Yes");
    }
    fprintf (stdout, "\nNumber of connections from 111: %d ", radio_getNumberOfRelations(r1));
    fprintf (stdout, "\nNumber of connections from 222: %d", radio_getNumberOfRelations(r1));;

    //Relations to Paint It, Black
    fprintf (stdout, "\n\nRadio recommendations from Paint it, Black: ");
    array=radio_getRelationsFromId(r1, 111);
    for (i=0;i<radio_getNumberOfMusic(r1); i++){
        fprintf (stdout, "%ld", array[i]);
    }

    //Print all radio (relations included)
    fprintf (stdout, "\n\nAll radio recommendations: \n");
    radio_print(stdout, r1);

    //free r1
    radio_free(r1);
    return 0;
}