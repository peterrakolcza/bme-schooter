//
// Created by Rakolcza Peter on 2019. 11. 29..
//

#include "eredmenyek.h"

void beolvasas(Eredmenyek tomb[]) {

    FILE *f;
    f = fopen("legjobberedmenyek.txt", "r");

    if (f != NULL) {
        char sor[51];
        int pont;
        char line[60];
        int i = 0;
        while (fgets(line, sizeof(line), f)) {
            sscanf(line, "%s %d", sor, &pont);
            strcpy(tomb[i].nev, sor);
            tomb[i].pontSzam = pont;
            i++;
        }

        if (i < 10) {
            for (int j = i; j < 10; ++j) {
                tomb[j].nev[0] = '\0';
                tomb[j].pontSzam = 0;
            }
        }

        fclose(f);
    }
    else {
        for (int j = 0; j < 10; ++j) {
            tomb[j].nev[0] = '\0';
            tomb[j].pontSzam = 0;
        }
    }
}

void kiiras(Eredmenyek tomb[]) {

    FILE *f;
    f = fopen("legjobberedmenyek.txt", "w+");

    if (f != NULL) {
        int i = 0;
        while (tomb[i].nev[0] != '\0') {
            fprintf(f, "%s %d", tomb[i].nev, tomb[i].pontSzam);
            fprintf(f,"\n");
            i++;
        }

        fclose(f);
    }
    else {
        f = fopen("legjobberedmenyek.txt", "w");

        int i = 0;
        while (tomb[i].nev[0] != '\0') {
            fprintf(f, "%s %d", tomb[i].nev, tomb[i].pontSzam);
            i++;
        }

        fclose(f);
    }
}

bool televanE(Eredmenyek tomb[]) {
    for (int i = 0; i < 10; ++i) {
        if (tomb[i].nev[0] == '\0')
            return false;
    }
    return true;
}

void feluliras(Eredmenyek tomb[], int pontszam, char nev[]) {
    int index = 0;

    if (pontszam == 0)
        return;

    int i = 0;
    while (tomb[i].nev[0] != '\0' && i < 10) {
        if (pontszam > tomb[i].pontSzam)
            index = i;
        i++;
    }

    if (i == 10)
        return;

    if (tomb[i].nev[0] == '\0') {
        strcpy(tomb[i].nev, nev);
        tomb[i].pontSzam = pontszam;
    }
}