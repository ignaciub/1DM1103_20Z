#include "baza.h"

SBaza * wczytaj_baze(char *nazwa_pliku) {
    FILE *fin = fopen(nazwa_pliku, "r");
    if (fin == NULL) {
        printf("BŁĄD! Nie moge otworzyc pliku: %s.\n", nazwa_pliku);
        exit(-1);
    }

    SBaza *baza = (SBaza*) malloc( sizeof(SBaza) );

    char bufor[255];
    int n, i;
    char *s;

    //WCZYTYWANIE STUDENTOW

    Student *last_student = NULL;
    Student *glowa_student = NULL;
    fgets(bufor, 254, fin);
    sscanf(bufor, "%d", &n);

    for (i=0; i<n; i++) {
        Student *stud = (Student*) malloc(sizeof(Student));
        stud->nast = NULL;

        if (last_student == NULL)
            glowa_student = stud;
        else
            last_student->nast = stud;
        last_student = stud;

        fgets(bufor, 254, fin);
        s = strtok(bufor, ";");
        stud->imie = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(stud->imie, s);

        s = strtok(NULL, ";");
        stud->nazwisko = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(stud->nazwisko, s);

        s = strtok(NULL, ";");
        stud->nr_albumu = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(stud->nr_albumu, s);

        s = strtok(NULL, "\n");
        stud->email = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(stud->email, s);
    }

    baza->lista_studentow = glowa_student;

    // WCZYTYWANIE PRZEDMIOTOW

    Przedmiot *last_przedmiot = NULL;
    Przedmiot *glowa_przedmiot = NULL;
    fgets(bufor, 254, fin);
    sscanf(bufor, "%d", &n);

    for (i=0; i<n; i++) {
        Przedmiot *przed = (Przedmiot*) malloc(sizeof(Przedmiot));
        przed->nast = NULL;

        if (last_przedmiot == NULL)
            glowa_przedmiot = przed;
        else
            last_przedmiot->nast = przed;
        last_przedmiot = przed;

        fgets(bufor, 254, fin);
        s = strtok(bufor, ";");
        przed->id = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(przed->id, s);

        s = strtok(NULL, ";");
        przed->nazwa = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(przed->nazwa, s);

        s = strtok(NULL, "\n");
        przed->kod = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(przed->kod, s);
    }

    baza->lista_przedmiotow = glowa_przedmiot;

    //WCZYTYWANIE OCEN

    Ocena *last_ocena = NULL;
    Ocena *glowa_ocena = NULL;
    fgets(bufor, 254, fin);
    sscanf(bufor, "%d", &n);

    for (i=0; i<n; i++) {
        Ocena *oc = (Ocena*) malloc(sizeof(Ocena));
        oc->nast = NULL;

        if (last_ocena == NULL)
            glowa_ocena = oc;
        else
            last_ocena->nast = oc;
        last_ocena = oc;

        fgets(bufor, 254, fin);
        s = strtok(bufor, ";");
        oc->id_przedmiotu = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(oc->id_przedmiotu, s);

        s = strtok(NULL, ";");
        oc->nr_albumu = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(oc->nr_albumu, s);

        s = strtok(NULL, ";");
        oc->ocena = atof(s);

        s = strtok(NULL, "\n");
        oc->komentarz = (char*) malloc( sizeof(char) * (strlen(s) + 1));
        strcpy(oc->komentarz, s);
    }

    baza->lista_ocen = glowa_ocena;

    fclose(fin);
    return baza;
}

SBaza * zapisz_baze(char *nazwa_pliku, SBaza * baza) {
    FILE *fout = fopen(nazwa_pliku, "w");
    if (fout == NULL) {
        printf("BŁĄD! Nie moge otworzyc pliku: %s.\n", nazwa_pliku);
        exit(-1);
    }

    Student * stud = baza->lista_studentow;
    fprintf(fout, "%d\n", ile_studentow(baza));
    while (stud != NULL) {
        fprintf(fout, "%s;%s;%s;%s\n", stud->imie, stud->nazwisko, stud->nr_albumu, stud->email);
        stud = stud->nast;
    }

    Przedmiot * przed = baza->lista_przedmiotow;
    fprintf(fout, "%d\n", ile_przedmiotow(baza));
    while (przed != NULL) {
        fprintf(fout, "%s;%s;%s\n", przed->id, przed->nazwa, przed->kod);
        przed = przed->nast;
    }

    Ocena * oc = baza->lista_ocen;
    fprintf(fout, "%d\n", ile_ocen(baza));
    while (oc != NULL) {
        fprintf(fout, "%s;%s;%f;%s\n", oc->id_przedmiotu, oc->nr_albumu, oc->ocena, oc->komentarz);
        oc = oc->nast;
    }
    fclose(fout);
    return baza;
}

int ile_studentow(SBaza *baza) {
    int n = 0;
    Student * stud = baza->lista_studentow;
    while (stud != NULL) {
        n++;
        stud = stud->nast;
    }
    return n;
}

int ile_przedmiotow(SBaza *baza) {
    int n = 0;
    Przedmiot * przed = baza->lista_przedmiotow;
    while (przed != NULL) {
        n++;
        przed = przed->nast;
    }
    return n;
}

int ile_ocen(SBaza *baza) {
    int n = 0;
    Ocena * oc = baza->lista_ocen;
    while (oc != NULL) {
        n++;
        oc = oc->nast;
    }
    return n;
}

void listuj_studentow(SBaza *baza) {
    Student * stud = baza->lista_studentow;
    while (stud != NULL) {
        printf("%s %s %s %s\n", stud->imie, stud->nazwisko, stud->nr_albumu, stud->email);
        stud = stud->nast;
    }
}

void listuj_przedmioty(SBaza *baza) {
    Przedmiot * przed = baza->lista_przedmiotow;
    while (przed != NULL) {
        printf("%s %s %s\n", przed->id, przed->nazwa, przed->kod);
        przed = przed->nast;
    }
}

void listuj_oceny(SBaza *baza) {
    Ocena * oc = baza->lista_ocen;
    while (oc != NULL) {
        printf("%s %s %f %s\n", oc->id_przedmiotu, oc->nr_albumu, oc->ocena, oc->komentarz);
        oc = oc->nast;
    }
}

Student* ostatni_student(SBaza * baza)
{
    Student * stud = baza->lista_studentow;
    while (stud->nast != NULL) {
        stud = stud->nast;
    }
    return stud;
}

Przedmiot* ostatni_przedmiot(SBaza * baza)
{
    Przedmiot * stud = baza->lista_przedmiotow;
    while (stud->nast != NULL) {
        stud = stud->nast;
    }
    return stud;
}

Ocena* ostatnia_ocena(SBaza * baza)
{
    Ocena * stud = baza->lista_ocen;
    while (stud->nast != NULL) {
        stud = stud->nast;
    }
    return stud;
}

void dodaj_studenta(SBaza *baza, char* imie, char* nazwisko, char* nr_albumu, char* email)
{
    Student *stud = (Student*) malloc(sizeof(Student));
    Student *last_student = ostatni_student(baza);
    stud->nast = NULL;

    if (ile_studentow(baza) == 0)
        baza->lista_studentow = stud;
    else
        last_student->nast = stud;


    stud->imie = (char*) malloc( sizeof(char) * (strlen(imie) + 1));
    stud->nazwisko = (char*) malloc( sizeof(char) * (strlen(nazwisko) + 1));
    stud->nr_albumu = (char*) malloc( sizeof(char) * (strlen(nr_albumu) + 1));
    stud->email = (char*) malloc( sizeof(char) * (strlen(email) + 1));

    strcpy(stud->imie, imie);
    strcpy(stud->nazwisko, nazwisko);
    strcpy(stud->nr_albumu, nr_albumu);
    strcpy(stud->email, email);
}

void dodaj_przedmiot(SBaza *baza, char* id, char* nazwa, char* kod)
{
    Przedmiot *stud = (Przedmiot*) malloc(sizeof(Przedmiot));
    Przedmiot *last_student = ostatni_przedmiot(baza);
    stud->nast = NULL;

    if (ile_przedmiotow(baza) == 0)
        baza->lista_przedmiotow = stud;
    else
        last_student->nast = stud;


    stud->id = (char*) malloc( sizeof(char) * (strlen(id) + 1));
    stud->nazwa = (char*) malloc( sizeof(char) * (strlen(nazwa) + 1));
    stud->kod = (char*) malloc( sizeof(char) * (strlen(kod) + 1));

    strcpy(stud->id, id);
    strcpy(stud->nazwa, nazwa);
    strcpy(stud->kod, kod);
}

void dodaj_ocene(SBaza *baza, char* id_przedmiotu, char* nr_albumu, float ocena, char* komentarz)
{
    Ocena *stud = (Ocena*) malloc(sizeof(Ocena));
    Ocena *last_student = ostatnia_ocena(baza);
    stud->nast = NULL;
    printf ("0");
    if (ile_ocen(baza) == 0)
        baza->lista_ocen = stud;
    else
        last_student->nast = stud;

    printf ("1");
    stud->id_przedmiotu = (char*) malloc( sizeof(char) * (strlen(id_przedmiotu) + 1));
    stud->nr_albumu = (char*) malloc( sizeof(char) * (strlen(nr_albumu) + 1));
    stud->komentarz = (char*) malloc( sizeof(char) * (strlen(komentarz) + 1));
    printf ("2");
    strcpy(stud->id_przedmiotu, id_przedmiotu);
    strcpy(stud->nr_albumu, nr_albumu);
    strcpy(stud->komentarz, komentarz);
    printf ("3");
    stud->ocena = ocena;
    printf ("4");
}

float srednia_studenta (SBaza* baza, char* nr_indeksu)
{
    Ocena * oc = baza->lista_ocen;
    float suma = 0.0;
    int ile_ocen = 0;
    while (oc != NULL) {
        if (strcmp(oc->nr_albumu, nr_indeksu) == 0)
        {
            suma = suma + oc->ocena;
            ile_ocen++;
        }

        oc = oc->nast;
    }
    return suma/ile_ocen;
}

float srednia_przedmiotu (SBaza* baza, char* nr_przedmiotu)
{
    Ocena * oc = baza->lista_ocen;
    float suma = 0.0;
    int ile_ocen = 0;
    while (oc != NULL) {
        if (strcmp(oc->id_przedmiotu, nr_przedmiotu) == 0)
        {
            suma = suma + oc->ocena;
            ile_ocen++;
        }

        oc = oc->nast;
    }
    return suma/ile_ocen;
}

int liczba_ocen (SBaza* baza, char* nr_przedmiotu)
{
    Ocena * oc = baza->lista_ocen;
    int ile_ocen = 0;
    while (oc != NULL) {
        if (strcmp(oc->id_przedmiotu, nr_przedmiotu) == 0)
        {
            ile_ocen++;
        }

        oc = oc->nast;
    }
    return ile_ocen;
}

void zwolnij_student(Student *s) {
    free(s->imie);
    free(s->nazwisko);
    free(s->nr_albumu);
    free(s->email);
    free(s);
}

void zwolnij_przedmiot(Przedmiot *p) {
    free(p->id);
    free(p->nazwa);
    free(p->kod);
    free(p);
}

void zwolnij_ocene(Ocena *o) {
    free(o->id_przedmiotu);
    free(o->nr_albumu);
    free(o->komentarz);
    free(o);
}

void zwolnij_liste_studentow(Student *s) {
    Student *n;
    while (s != NULL) {
        n = s->nast;
        zwolnij_student(s);
        s = n;
    }
}

void zwolnij_liste_przedmiotow(Przedmiot *p) {
    Przedmiot *n;
    while (p != NULL) {
        n = p->nast;
        zwolnij_przedmiot(p);
        p = n;
    }
}

void zwolnij_liste_ocen(Ocena *o) {
    Ocena *n;
    while (o != NULL) {
        n = o->nast;
        zwolnij_przedmiot(o);
        o = n;
    }
}


void zwolnij(SBaza *baza) {
    zwolnij_liste_studentow(baza->lista_studentow);
    zwolnij_liste_przedmiotow(baza->lista_przedmiotow);
    zwolnij_liste_ocen(baza->lista_ocen);
    free(baza);
}
