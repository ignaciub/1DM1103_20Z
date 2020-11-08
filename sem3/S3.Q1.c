#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[]){

float x,y;

scanf ("%s", &x);


x = atof(argv[1]);


y = x*x;

printf ("Wartość %f do kwadratu to %f.\n", x, y );


    return 0;
}
