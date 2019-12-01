//
// Created by Rakolcza Peter on 2019. 11. 29..
//

#include "eredmenyek.h"

void beolvasas(Eredmenyek tomb[]) {

    FILE *f;
    f = fopen("legjobberedmenyek.txt", "r");

    if (f != NULL) {
        char sor[42];
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
        while (tomb[i].nev[0] != '\0' && i < 10) {
            fprintf(f, "%s %d", tomb[i].nev, tomb[i].pontSzam);
            fprintf(f,"\n");
            i++;
        }

        fclose(f);
    }
    else {
        f = fopen("legjobberedmenyek.txt", "w");

        int i = 0;
        while (tomb[i].nev[0] != '\0' && i < 10) {
            fprintf(f, "%s %d", tomb[i].nev, tomb[i].pontSzam);
            i++;
        }

        fclose(f);
    }
}

void feluliras(Eredmenyek tomb[], int pontszam, char nev[], int i, int index) {
    if (index == -1 && tomb[i].nev[0] == '\0') {
        strcpy(tomb[i].nev, nev);
        tomb[i].pontSzam = pontszam;
    }
    else {
        for (int j = 8; j >= index; j--) {
            tomb[j+1] = tomb[j];
        }

        strcpy(tomb[index].nev, nev);
        tomb[index].pontSzam = pontszam;
    }
}

void szovegBeirasa(Jatek *jatek, bool *vege) {
    int hossz = strlen(jatek->beSzoveg);

    for (int i = 0 ; i < strlen(jatek->beSzoveg) ; i++)
    {
        jatek->beSzoveg[i] = toupper(jatek->beSzoveg[i]);
    }

    if (hossz > 0 && jatek->billentyuzet[SDL_SCANCODE_BACKSPACE])
    {
        jatek->beSzoveg[--hossz] = '\0';

        jatek->billentyuzet[SDL_SCANCODE_BACKSPACE] = 0;
    }

    if (jatek->billentyuzet[SDL_SCANCODE_RETURN] && strlen(jatek->beSzoveg) != 0) {
        *vege = true;
    }
}