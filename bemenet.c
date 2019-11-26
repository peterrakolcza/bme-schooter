//
// Created by Rakolcza Peter on 2019. 11. 16..
//
#include "bemenet.h"

void elengedve(SDL_KeyboardEvent *esemeny, Jatek* jatek) {
    if (esemeny->repeat == 0 && esemeny->keysym.scancode < MAX_KEYBOARD_KEYS) {
        jatek->billentyuzet[esemeny->keysym.scancode] = 0;
    }
}

void lenyomva(SDL_KeyboardEvent *esemeny, Jatek* jatek) {
    if (esemeny->repeat == 0 && esemeny->keysym.scancode < MAX_KEYBOARD_KEYS) {
        jatek->billentyuzet[esemeny->keysym.scancode] = 1;
    }
}



