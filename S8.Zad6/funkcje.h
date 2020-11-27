#ifndef funkcje_h
#define funkcje_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct Macierz {
    int r;
    int c;
    float** tab;
};

void wczytaj(FILE * fin, struct Macierz *m);
struct Macierz sum(struct Macierz m1, struct Macierz m2, struct Macierz *wynik);
struct Macierz subtract(struct Macierz m1, struct Macierz m2, struct Macierz *wynik);
struct Macierz prod(struct Macierz m1, struct Macierz m2, struct Macierz *wynik);
struct Macierz multiply(struct Macierz m1, float skalar, struct Macierz *wynik);
struct Macierz subtract(struct Macierz m1, struct Macierz m2, struct Macierz *wynik);
struct Macierz prod(struct Macierz m1, struct Macierz m2, struct Macierz *wynik);
struct Macierz multiply(struct Macierz m1, float skalar, struct Macierz *wynik);
void wypisz(struct Macierz m);
float norm(struct Macierz m);
void wypiszDoPliku(FILE * fout, struct Macierz m);
void wypisz(struct Macierz m);

#endif