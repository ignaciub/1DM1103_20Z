#include "funkcje.h"

void wczytaj(FILE * fin, struct Macierz *m) {
    int i,j;
    for (i=0; i < (*m).r; i++) {
        for (j=0; j < (*m).c; j++) {
            fscanf(fin, "%f", &(*m).tab[i][j]);
        }
    }
}


struct Macierz sum(struct Macierz m1, struct Macierz m2, struct Macierz *wynik){
    int i,j;
    wynik->c = m1.c;
    wynik->r = m1.r;
    if (m1.r == m2.r && m1.c == m2.c){
        for (i=0; i < m1.r; i++) {
            for (j=0; j < m1.c; j++) {
                wynik->tab[i][j] = m1.tab[i][j] + m2.tab[i][j];
            }
        }
    }
    else
        printf("Macierze nie sa zgodne rozmiarowo\n");

    return *wynik;
}

struct Macierz subtract(struct Macierz m1, struct Macierz m2, struct Macierz *wynik){
    int i,j;
    wynik->c = m1.c;
    wynik->r = m1.r;
    if (m1.r == m2.r && m1.c == m2.c){
        for (i=0; i < m1.r; i++) {
            for (j=0; j < m1.c; j++) {
                wynik->tab[i][j] = m1.tab[i][j] - m2.tab[i][j];
            }
        }
    }
    else
        printf("Macierze nie sa zgodne rozmiarowo\n");

    return *wynik;
}

struct Macierz prod(struct Macierz m1, struct Macierz m2, struct Macierz *wynik){
    int k,i,j;
    wynik->c = m2.c;
    wynik->r = m1.r;
    if (m1.c == m2.r){
        for (i=0; i < wynik->r; i++) {
            for (j=0; j < wynik->c; j++)
            {
                wynik->tab[i][j] = 0.0;
                for (k=0; k<m1.c; k++){
                   wynik->tab[i][j] += m1.tab[i][k] * m2.tab[k][j];
                }

            }
        }
    }
    else
        printf("Macierze nie sa zgodne rozmiarowo\n");

    return *wynik;
}

struct Macierz multiply(struct Macierz m1, float skalar, struct Macierz *wynik){
    int i,j;
    wynik->c = m1.c;
    wynik->r = m1.r;
        for (i=0; i < m1.r; i++) {
            for (j=0; j < m1.c; j++) {
                wynik->tab[i][j] = m1.tab[i][j] * skalar;
            }
        }
    return *wynik;
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