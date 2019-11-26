//
// Created by Rakolcza Peter on 2019. 11. 16..
//
#include "bemenet.h"

//bill array annak az elemét 1-re változtatjuk, repeat legyen 0, nehogy feltorlódjon
void elengedve(SDL_KeyboardEvent *esemeny, Jatek* jatek) {
    if (esemeny->repeat == 0 && esemeny->keysym.scancode < 400) {
        jatek->billentyuzet[esemeny->keysym.scancode] = 0;
    }
}

void lenyomva(SDL_KeyboardEvent *esemeny, Jatek* jatek) {
    if (esemeny->repeat == 0 && esemeny->keysym.scancode < 400) {
        jatek->billentyuzet[esemeny->keysym.scancode] = 1;
    }
}

//6gomb közül beallitjuk a mouse eventet
void gombFel(SDL_MouseButtonEvent *es, Jatek *jatek) {
    jatek->eger.gomb[es->button] = 0;
}

void gombLe(SDL_MouseButtonEvent *es, Jatek *jatek) {
    jatek->eger.gomb[es->button] = 1;
}



