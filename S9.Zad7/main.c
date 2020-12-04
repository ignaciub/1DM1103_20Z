#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "baza.h"

int main(int argc, char ** argv) {
    SBaza *baza;
    baza = wczytaj_baze(argv[1]);

    if (strcmp("list_students", argv[2]) == 0) {
        listuj_studentow(baza);
    } else if (strcmp("list_przedmioty", argv[2]) == 0) {
        listuj_przedmioty(baza);
    } else if (strcmp("list_oceny", argv[2]) == 0) {
        listuj_oceny(baza);
    } else if (strcmp("add_student", argv[2]) == 0) {
        dodaj_studenta(baza, argv[3], argv[4], argv[5], argv[6]);
    } else if (strcmp("add_course", argv[2]) == 0) {
        dodaj_przedmiot(baza, argv[3], argv[4], argv[5]);
    } else if (strcmp("set_grade", argv[2]) == 0) {
        dodaj_ocene(baza, argv[3], argv[4], atof(argv[5]), argv[6]);
        //listuj_oceny(baza);
    } else if (strcmp("student_average", argv[2]) == 0) {
        printf ("srednia tego studenta to: %f\n", srednia_studenta(baza, argv[3]));
    } else if (strcmp("course_average", argv[2]) == 0) {
        printf ("srednia tego przedmiotu to: %f\n", srednia_przedmiotu(baza, argv[3]));
    } else if (strcmp("course_grades", argv[2]) == 0) {
        printf ("ilosc ocen z tego przedmiotu to: %d\n", liczba_ocen(baza, argv[3]));
    } else if (strcmp("count_students", argv[2]) == 0) {
        printf("Liczba studentow: %d\n", ile_studentow(baza));
    }


    zapisz_baze(argv[1], baza);
    zwolnij(baza);
    return 0;
}