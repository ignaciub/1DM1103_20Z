#include "funkcje.h"

int main(int argc, char *argv[]) {
    int rozm1w=0;
    int rozm1k=0;
    int rozm2w=0;
    int rozm2k=0;
    int rozm3w=0;
    int rozm3k=0;
    int i;
    FILE * fin1;
    FILE * fin2;

    struct Macierz mac1;
    fin1 = fopen(argv[2], "r");
    fscanf(fin1, "%d", &rozm1w);
    fscanf(fin1, "%d", &rozm1k);
    mac1.r = rozm1w;
    mac1.c = rozm1k;

    struct Macierz mac2;
    if (strcmp (argv[1],"multiply") != 0 && strcmp (argv[1],"norm") != 0)
    {
        fin2 = fopen(argv[3], "r");
        fscanf(fin2, "%d", &rozm2w);
        fscanf(fin2, "%d", &rozm2k);
        mac2.r = rozm2w;
        mac2.c = rozm2k;
    }

    struct Macierz mac3;
    if (rozm1w > rozm2w)
        rozm3w = rozm1w;
    else
        rozm3w = rozm2w;
    if (rozm1k > rozm2k)
        rozm3k = rozm1k;
    else
        rozm3k = rozm2k;

    mac1.tab = malloc(sizeof(float*) * rozm1w);
    for (i=0;i<rozm1w;i++)
        mac1.tab[i] = malloc(sizeof(float) * rozm1k);
    mac2.tab = malloc(sizeof(float*) * rozm2w);
    for (i=0;i<rozm2w;i++)
        mac2.tab[i] = malloc(sizeof(float) * rozm2k);
    mac3.tab = malloc(sizeof(float*) * rozm3w);
    for (i=0;i<rozm3w;i++)
        mac3.tab[i] = malloc(sizeof(float) * rozm3k);

    if (strcmp (argv[1],"sum") == 0 ){
        wczytaj(fin1, &mac1);
        wczytaj(fin2, &mac2);
        mac3 = sum(mac1, mac2, &mac3);
        if (argc<5){
            wypisz(mac3);
            }
        else {
            FILE * fout = fopen(argv[4], "w");
            wypiszDoPliku(fout, mac3);
            fclose(fout);
        }
    }

    if (strcmp (argv[1],"subtract") == 0 ){
        wczytaj(fin1, &mac1);
        wczytaj(fin2, &mac2);
        mac3 = subtract(mac1, mac2, &mac3);
        if (argc<5){
            wypisz(mac3);
            }
        else {
            FILE * fout = fopen(argv[4], "w");
            wypiszDoPliku(fout, mac3);
            fclose(fout);
        }
    }

    if (strcmp (argv[1],"prod") == 0 ){
        wczytaj(fin1, &mac1);
        wczytaj(fin2, &mac2);
        mac3 = prod(mac1, mac2, &mac3);
        if (argc<5){
            wypisz(mac3);
            }
        else {
            FILE * fout = fopen(argv[4], "w");
            wypiszDoPliku(fout, mac3);
            fclose(fout);
        }
    }

    if (strcmp (argv[1],"multiply") == 0 ){
        wczytaj(fin1, &mac1);
        float skalar = atof(argv[3]);
        mac3 = multiply(mac1, skalar, &mac3);
        if (argc<5){
            wypisz(mac3);
        }
        else {
            FILE * fout = fopen(argv[4], "w");
            wypiszDoPliku(fout, mac3);
            fclose(fout);
        }
    }

    if (strcmp (argv[1],"norm") == 0 ){
        wczytaj(fin1, &mac1);
        float norma = norm(mac1);
        printf("%f", norma);
    }

    fclose(fin1);
    fclose(fin2);

    for(i = 0; i < rozm1w; i++) {
        free(mac1.tab[i]);
    }
    free(mac1.tab);
    mac1.tab = NULL;

    for(i = 0; i < rozm2w; i++) {
        free(mac2.tab[i]);
    }
    free(mac2.tab);
    mac2.tab = NULL;

    for(i = 0; i < rozm3w; i++) {
        free(mac3.tab[i]);
    }
    free(mac3.tab);
    mac3.tab = NULL;

    return 0;
}
