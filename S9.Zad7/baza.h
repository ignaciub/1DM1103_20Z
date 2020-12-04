#ifndef _BAZA_H
#define _BAZA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Student {
    char * imie;
    char * nazwisko;
    char * nr_albumu;
    char * email;

    struct _Student *nast;
} Student;

 typedef struct _Przedmiot {
     char * id;
     char * nazwa;
     char * kod;

     struct _Przedmiot *nast;
 } Przedmiot;

 typedef struct _Ocena {
     char * id_przedmiotu;
     char * nr_albumu;
     float ocena;
     char * komentarz;

     struct _Ocena *nast;
 } Ocena;


typedef struct _SBaza {
    Student *lista_studentow; /* Glowa listy! */
    Przedmiot *lista_przedmiotow;
    Ocena *lista_ocen;
} SBaza;

SBaza * wczytaj_baze(char *nazwa_pliku);
SBaza * zapisz_baze(char *nazwa_pliku, SBaza * baza);
int ile_studentow(SBaza *baza);
int ile_przedmiotow(SBaza *baza);
int ile_ocen(SBaza *baza);
void listuj_studentow(SBaza *baza);
void listuj_przedmioty(SBaza *baza);
void listuj_oceny(SBaza *baza);
Student* ostatni_student(SBaza * baza);
Przedmiot* ostatni_przedmiot(SBaza * baza);
Ocena* ostatnia_ocena(SBaza * baza);
void dodaj_studenta(SBaza *baza, char* imie, char* nazwisko, char* nr_albumu, char* email);
void dodaj_przedmiot(SBaza *baza, char* id, char* nazwa, char* kod);
void dodaj_ocene(SBaza *baza, char* id_przedmiotu, char* nr_albumu, float ocena, char* komentarz);
float srednia_studenta (SBaza* baza, char* nr_indeksu);
float srednia_przedmiotu (SBaza* baza, char* nr_przedmiotu);
int liczba_ocen (SBaza* baza, char* nr_przedmiotu);
void zwolnij_student(Student *s);
void zwolnij_przedmiot(Przedmiot *p);
void zwolnij_ocene(Ocena *o);
void zwolnij_liste_studentow(Student *s);
void zwolnij_liste_przedmiotow(Przedmiot *p);
void zwolnij_liste_ocen(Ocena *o);
void zwolnij(SBaza *baza);

#endif
