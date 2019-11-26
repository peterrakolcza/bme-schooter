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

void iranyitas(Jatek *jatek) {
    SDL_Event esemeny;

    while (SDL_PollEvent(&esemeny)) {
        switch (esemeny.type)
        {
            case SDL_QUIT:
                exit(0);
                break;

            case SDL_KEYDOWN:
                lenyomva(&esemeny.key, jatek);
                break;

            case SDL_KEYUP:
                elengedve(&esemeny.key, jatek);
                break;

            default:
                break;
        }
    }

    SDL_GetMouseState(&jatek->eger.x, &jatek->eger.y);
    //printf("%d %d", jatek->eger.x, jatek->eger.y);
}


