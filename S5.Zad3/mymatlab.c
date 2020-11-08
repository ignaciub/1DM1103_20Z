#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct Macierz {
    int r;
    int c;
    float tab[200][200];
};


void wczytaj(FILE * fin, struct Macierz *m) {
    int i,j;
    fscanf(fin, "%d", &(*m).r);
    fscanf(fin, "%d", &(*m).c);

    for (i=0; i < (*m).r; i++) {
        for (j=0; j < (*m).c; j++) {
            fscanf(fin, "%f", &(*m).tab[i][j]);
        }
    }
}


struct Macierz sum(struct Macierz m1, struct Macierz m2){
    int i,j;
    struct Macierz wynik;
    wynik.c = m1.c;
    wynik.r = m1.r;
    if (m1.r == m2.r && m1.c == m2.c){
        for (i=0; i < m1.r; i++) {
            for (j=0; j < m1.c; j++) {
                wynik.tab[i][j] = m1.tab[i][j] + m2.tab[i][j];
            }
        }
    }
    else
        printf("Macierze nie sa zgodne rozmiarowo\n");

    return wynik;
}

struct Macierz subtract(struct Macierz m1, struct Macierz m2){
    int i,j;
    struct Macierz wynik;
    wynik.c = m1.c;
    wynik.r = m1.r;
    if (m1.r == m2.r && m1.c == m2.c){
        for (i=0; i < m1.r; i++) {
            for (j=0; j < m1.c; j++) {
                wynik.tab[i][j] = m1.tab[i][j] - m2.tab[i][j];
            }
        }
    }
    else
        printf("Macierze nie sa zgodne rozmiarowo\n");

    return wynik;
}

struct Macierz prod(struct Macierz m1, struct Macierz m2){
    int k,i,j;
    struct Macierz wynik;
    wynik.c = m2.c;
    wynik.r = m1.r;
    if (m1.c == m2.r){
        for (i=0; i < wynik.r; i++) {
            for (j=0; j < wynik.c; j++)
            {
                wynik.tab[i][j] = 0.0;
                for (k=0; k<m1.c; k++){

                   wynik.tab[i][j] += m1.tab[i][k] * m2.tab[k][j];
                }

            }
        }
    }
    else
        printf("Macierze nie sa zgodne rozmiarowo\n");

    return wynik;
}

struct Macierz multiply(struct Macierz m1, float skalar){
    int i,j;
    struct Macierz wynik;
    wynik.c = m1.c;
    wynik.r = m1.r;
        for (i=0; i < m1.r; i++) {
            for (j=0; j < m1.c; j++) {
                wynik.tab[i][j] = m1.tab[i][j] * skalar;
            }
        }
    return wynik;
}

void wypisz(struct Macierz m) {
    int i, j;
    printf("[ ");
    for (i = 0; i < m.r; i++) {
        for (j=0; j < m.c; j++) {
            printf("%5.1f ", m.tab[i][j]);
        }
        if (i < (m.r-1))
            printf("\n  ");
    }
    printf("]\n");
}

float norm(struct Macierz m) {
    float s = 0;
    int i,j;

    for (i = 0; i < m.r; i++) {
        for (j=0; j < m.c; j++) {
            s += m.tab[i][j] * m.tab[i][j];
        }
    }
    return sqrt(s);
}


void wypiszDoPliku(FILE * fout, struct Macierz m) {
    int i, j;
    fprintf(fout, "%d\n%d\n", m.r, m.c);
    for (i = 0; i < m.r; i++) {
        for (j=0; j < m.c; j++) {
            fprintf(fout, "%f ", m.tab[i][j]);
        }

        if (i < (m.r-1))
            fprintf(fout, "\n");
    }
}

int main(int argc, char *argv[]) {
    struct Macierz mac1;
    struct Macierz mac2;
    struct Macierz mac3;
    if (strcmp (argv[1],"sum") == 0 ){
        FILE * fin1 = fopen(argv[2], "r");
        wczytaj(fin1, &mac1);
        FILE * fin2 = fopen(argv[3], "r");
        wczytaj(fin2, &mac2);
        mac3 = sum(mac1, mac2);
        if (argc<5){
            wypisz(mac3);
            }
        else {
            FILE * fout = fopen(argv[4], "w");
            wypiszDoPliku(fout, mac3);
        }
        fclose(fin1);
        fclose(fin2);
    }

    if (strcmp (argv[1],"subtract") == 0 ){
        FILE * fin1 = fopen(argv[2], "r");
        wczytaj(fin1, &mac1);
        FILE * fin2 = fopen(argv[3], "r");
        wczytaj(fin2, &mac2);
        mac3 = subtract(mac1, mac2);
        if (argc<5){
            wypisz(mac3);
            }
        else {
            FILE * fout = fopen(argv[4], "w");
            wypiszDoPliku(fout, mac3);
        }
        fclose(fin1);
        fclose(fin2);
    }

    if (strcmp (argv[1],"prod") == 0 ){
        FILE * fin1 = fopen(argv[2], "r");
        wczytaj(fin1, &mac1);
        FILE * fin2 = fopen(argv[3], "r");
        wczytaj(fin2, &mac2);
        mac3 = prod(mac1, mac2);
        if (argc<5){
            wypisz(mac3);
            }
        else {
            FILE * fout = fopen(argv[4], "w");
            wypiszDoPliku(fout, mac3);
        }
        fclose(fin1);
        fclose(fin2);
    }

    if (strcmp (argv[1],"multiply") == 0 ){
        FILE * fin1 = fopen(argv[2], "r");
        wczytaj(fin1, &mac1);
        float skalar = atof(argv[3]);
        mac3 = multiply(mac1, skalar);
        if (argc<5){
            wypisz(mac3);
            }
        else {
            FILE * fout = fopen(argv[4], "w");
            wypiszDoPliku(fout, mac3);
        }
        fclose(fin1);
    }

    if (strcmp (argv[1],"norm") == 0 ){
        FILE * fin1 = fopen(argv[2], "r");
        wczytaj(fin1, &mac1);
        float norma = norm(mac1);
        printf("%f", norma);

        fclose(fin1);
    }
    return 0;
}
