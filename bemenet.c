//
// Created by Rakolcza Peter on 2019. 11. 16..
//
#include "bemenet.h"

/**Billentyűzet tömb annak az elemét 1-re változtatjuk, amelyik le lett nyomva; repeat legyen 0, nehogy feltorlódjon. */
void elengedve(SDL_KeyboardEvent *esemeny, Jatek* jatek) {
    if (esemeny->repeat == 0 && esemeny->keysym.scancode < 400) {
        jatek->billentyuzet[esemeny->keysym.scancode] = 0;
    }
}

/**Billentyűzet tömb annak az elemét 0-r változtatjuk, amelyik fel lett engedve; repeat legyen 0, nehogy feltorlódjon. */
void lenyomva(SDL_KeyboardEvent *esemeny, Jatek* jatek) {
    if (esemeny->repeat == 0 && esemeny->keysym.scancode < 400) {
        jatek->billentyuzet[esemeny->keysym.scancode] = 1;
    }
}

/**Egérgomb lenyomásának regisztrálása a gomb tömbbe. */
void gombFel(SDL_MouseButtonEvent *es, Jatek *jatek) {
    jatek->eger.gomb[es->button] = 0;
}

/**Egérgomb felengedésének regisztrálása a gomb tömbbe. */
void gombLe(SDL_MouseButtonEvent *es, Jatek *jatek) {
    jatek->eger.gomb[es->button] = 1;
}



