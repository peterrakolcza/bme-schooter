//
// Created by Rakolcza Peter on 2019. 11. 29..
//

#ifndef BME_SCHOOTER_EREDMENYEK_H
#define BME_SCHOOTER_EREDMENYEK_H

#include "kozos.h"

void beolvasas(Eredmenyek tomb[]);
void kiiras(Eredmenyek tomb[]);
void feluliras(Eredmenyek tomb[], int pontszam, char nev[], int i, int index);
void szovegBeirasa(Jatek *jatek, bool *vege);

#endif //BME_SCHOOTER_EREDMENYEK_H