/**
Mamy mini bazę studentów (tabelę z studentami, przedmiotami i ocenami)
Cel: obliczyć ranking.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _student {
    char imie[25];
    char nazwisko[50];
    char nr_albumu[10];
    char kod_przed[10];
    char nazwa_przed[255];
    float ocena;
    int ects;
} student, *pstudent;

int wczytaj(student dane[100], char *fnazwa) {
    FILE * fin = fopen(fnazwa, "r");
    int cnt, i;
    char bufor[1024];
    char *w;

    fgets(bufor, 1023, fin);
    sscanf(bufor, "%d", &cnt);

    for (i=0; i<cnt; i++) {
        fgets(bufor, 1023, fin);
        // printf("%s", bufor);
        w = strtok(bufor, "|");
        strncpy(dane[i].imie, w, 24);

        w = strtok(NULL, "|");
        strncpy(dane[i].nazwisko, w, 49);

        w = strtok(NULL, "|");
        strncpy(dane[i].nr_albumu, w, 9);

        w = strtok(NULL, "|");
        strncpy(dane[i].kod_przed, w, 9);

        w = strtok(NULL, "|");
        strncpy(dane[i].nazwa_przed, w, 254);

        w = strtok(NULL, "|");
        dane[i].ocena = atof(w);

        w = strtok(NULL, "|");
        dane[i].ects = atoi(w);
    }

    fclose(fin);
    return cnt;
}

void wypisz(student dane[100], int n) {
    int i;
    for (i=0; i<n;i++) {
        printf("{ Student: %s - %s %s, z przedmiotu: [%s] %s za ECTS: %d otrzymał %.1f\n",
            dane[i].nr_albumu, dane[i].imie, dane[i].nazwisko,
            dane[i].kod_przed, dane[i].nazwa_przed,
            dane[i].ects, dane[i].ocena
        );
    }
}

int znajdz(char *szukany_nr, char nr_albumow[100][10], int n) {
    int i;
    for (i=0; i<n; i++) {
        if (strcmp(szukany_nr, nr_albumow[i]) == 0)
            return i;
    }
    return -1;
}

int znajdz_studentow(char nr_albumow[100][10], student dane[100], int n) {
    int ile_znalazlem = 0;
    int i;

    for (i=0; i <n; i++) {
        if (znajdz(dane[i].nr_albumu, nr_albumow, ile_znalazlem ) == -1) {
            strncpy(nr_albumow[ile_znalazlem], dane[i].nr_albumu, 9);
            ile_znalazlem++;
        }
    }
    return ile_znalazlem;
}


void najlepszy_student(student dane[100], int ile_rekordow) {
    char nr_albumow[100][10];
    int ile_studentow;
    float sumy_wazonych_ocen[100];
    int sumy_ects[100];
    float srednie[100];
    int i;
    int pozycja;
    int najlepsza_pozycja;
    float najlepsza = 0.0f;

    ile_studentow = znajdz_studentow(nr_albumow, dane, ile_rekordow);

    for (i=0; i < ile_rekordow; i++) {
        pozycja = znajdz( dane[i].nr_albumu, nr_albumow, ile_studentow );
        // if (pozycje >= 0)
        sumy_wazonych_ocen[pozycja] += dane[i].ocena * dane[i].ects;
        sumy_ects[pozycja] += dane[i].ects;
    }

    for (i=0;i<ile_studentow; i++)
        printf("Student [%d]: %s - %f:%d - %f \n", i+1, nr_albumow[i],
        sumy_wazonych_ocen[i], sumy_ects[i], sumy_wazonych_ocen[i] / sumy_ects[i]);

    for (i=0; i < ile_studentow; i++) {
        if (najlepsza < sumy_wazonych_ocen[i] / sumy_ects[i]) {
            najlepsza = sumy_wazonych_ocen[i] / sumy_ects[i];
            najlepsza_pozycja = i;
        }
    }

    printf("Najlepszy student: \n");
    printf("Student [%d]: %s - %f \n",
        najlepsza_pozycja+1, nr_albumow[najlepsza_pozycja],
        sumy_wazonych_ocen[najlepsza_pozycja] / sumy_ects[najlepsza_pozycja]
    );

}


int znajdz_kod_przedmiotu(char *szukany_nr, char kody_przedmiotow[100][10], int n) {
    int i;
    for (i=0; i<n; i++) {
        if (strcmp(szukany_nr, kody_przedmiotow[i]) == 0)
            return i;
    }
    return -1;
}

int znajdz_przedmioty(char kody_przedmiotow[100][10], char nazwy_przedmiotow[100][255], student dane[100], int n) {
    int ile_znalazlem = 0;
    int i;

    for (i=0; i <n; i++) {
        if (znajdz_kod_przedmiotu(dane[i].kod_przed, kody_przedmiotow, ile_znalazlem ) == -1) {
            strncpy(kody_przedmiotow[ile_znalazlem], dane[i].kod_przed, 9);
            strncpy(nazwy_przedmiotow[ile_znalazlem], dane[i].nazwa_przed, 254);
            ile_znalazlem++;
        }
    }
    return ile_znalazlem;
}


void najtrudniejszy_przedmiot(student dane[100], int ile_rekordow) {
    char kody_przedmiotow[100][10];
    char nazwy_przedmiotow [100][255];
    int ile_przedmiotow;
    float sumy_ocen[100];
    int ile_ocen[100];
    float srednie[100];
    int i;
    int pozycja;
    int najlepsza_pozycja;
    float min = 10.0f;
    float max = 0.0f;

    int minidx = 0;
    int maxidx = 0;


    for (i=0; i<100; i++){
        ile_ocen [i] = 0;

    }

    ile_przedmiotow = znajdz_przedmioty(kody_przedmiotow, nazwy_przedmiotow ,dane, ile_rekordow);

    for (i=0; i < ile_rekordow; i++) {
        pozycja = znajdz_kod_przedmiotu( dane[i].kod_przed, kody_przedmiotow, ile_przedmiotow );
        sumy_ocen[pozycja] += dane[i].ocena;
        ile_ocen[pozycja] +=1;
        srednie[pozycja] = sumy_ocen[pozycja] / ile_ocen [pozycja];
    }

    for (i=0;i<ile_przedmiotow; i++)
        printf("Przedmiot [%s]: %f, %d %f \n", kody_przedmiotow[i], sumy_ocen[i], ile_ocen[i], srednie[i]);

    for (i=0; i<ile_przedmiotow; i++){
        if (srednie[i] < min){
            min = srednie[i];
            minidx = i;

        }

        if (srednie[i] > max){
            max = srednie [i];
            maxidx = i;

        }
    }


    printf("Najlepsza srednia: %s - %s: %f\n", kody_przedmiotow[maxidx], nazwy_przedmiotow[maxidx], srednie[maxidx]);
    printf("Najgorsza srednia: %s - %s: %f", kody_przedmiotow[minidx], nazwy_przedmiotow[minidx] ,srednie[minidx]);


    //printf("Najlepszy student: \n");
    //printf("Student [%d]: %s - %f \n",
    //    najlepsza_pozycja+1, nr_albumow[najlepsza_pozycja],
    //    sumy_wazonych_ocen[najlepsza_pozycja] / sumy_ects[najlepsza_pozycja]
   // );

}

int main(int argc, char ** argv) {
    student dane[100];
    int ile;
    // dane == &dane[0]
    ile = wczytaj(dane, argv[1]);
    wypisz(dane, ile);

    najtrudniejszy_przedmiot(dane, ile);

    return 0;
}
