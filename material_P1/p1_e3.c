#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "radio.h"

int main () {
    Radio *r1=NULL;
    FILE *fIn=fopen("radio1.txt", "r");
    
    if ((fIn == NULL)){
        fprintf (stdout, "Error opening file.");
        return -1;
    }
    r1=radio_init();
    if (radio_readFromFile(fIn,r1)== OK) {
        fprintf (stdout, "Radio recommendations: \n");
        radio_print(stdout,r1);
    }
    else {
        fprintf (stdout, "Error reading the file.");
    }
    
}
