#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int wczytaj_macierz (FILE *fin, float tablica [][100]){
int wlasciwie_zinterpretowane
int wiersze = 0;
int kolumny = 0;
float liczba;

if ((wlasciwie_zinterpretowane = fscanf(fin, %d, %d, &wiersze, &kolumny)) != 2){

    printf("Rozmiar macierzy nie jest liczbą całkowitą"
           "Liczba prawidłowo zinterpretowanych argumentów: %d \n" wlasciwie_zinterpretowane);
           exit (-1)
}

for (int i=0; i<wiersze; i++){
    for (int j=0; j< kolumny; j++){
        if (fscanf(fin, "%f", &liczba) != 1){
            printf("%d. Liczba w %d wierszu nie jest liczbą zmiennoprzecinkową.\n", j+1, i+1 );
            exit (-2);

        }
        tablica [i][j] = liczba;
    }
}

return wiersze;

}



void iloczyn(float macierz [][100], float wektor [][100], int wiersze_m, int wiersze_w){
    float suma=0;
    printf("[");
    int j=0;
    for(int i=0; i<wiersze_m; i++){
        for (int k=0; i<wiersze_w; k++){
            suma = suma + (macierz[i][k]*wektor[k][j]);
        }

        printf("%f", suma);
        suma=0;
    }
    printf("]\n")

}


int main(int argc, char *argv[])
{
    FILE *plikm;
    FILE *plikw;
    
    float wektor [100][100];
    float macierz [100][100];
     int wiersze_m;
     int wiersze_w;
     
     plikm = fopen( argv[1], "r");
     plikw = fopen (argv[2], "r");
    
    wiersze_m wczytaj_macierz(plikm,macierz);
    wiersze_w wczytaj_macierz(plikw,wektor);
    
    printf("%d", wiersze_m);
    iloczyn(macierz,wektor,wiersze_m,);
    
    return 0;
}














