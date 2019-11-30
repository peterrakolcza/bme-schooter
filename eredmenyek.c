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
        int i = 0;
        while (fscanf(f, "%s %d", sor, &pont) != EOF) {
            strcpy(tomb[i].nev, sor);
            tomb[i].pontSzam = pont;
        }

        fclose(f);
    }
}