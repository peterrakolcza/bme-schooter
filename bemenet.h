//
// Created by Rakolcza Peter on 2019. 11. 16..
//

#ifndef BME_SCHOOTER_BEMENET_H
#define BME_SCHOOTER_BEMENET_H

#include "kozos.h"

void elengedve(SDL_KeyboardEvent *esemeny, Jatek* jatek);
void lenyomva(SDL_KeyboardEvent *esemeny, Jatek* jatek);
void gombFel(SDL_MouseButtonEvent *es, Jatek *jatek);
void gombLe(SDL_MouseButtonEvent *es, Jatek *jatek);

#endif //BME_SCHOOTER_BEMENET_H
