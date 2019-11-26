//
// Created by Rakolcza Peter on 2019. 11. 25..
//

#include "jatekmenet.h"

float szog(int x1, int y1, int x2, int y2) {
    float angle = -90 + atan2(y1 - y2, x1 - x2) * (180 / PI);
    return angle >= 0 ? angle : 360 + angle;
}

void jatekFrissites(Peldany *jatekos, Jatek *jatek) {
    jatekosFrissites(jatekos, jatek);
    peldanyFrissites(jatekos);
}

void peldanyFrissites(Peldany *jatekos) {
    Peldany *p;

    for (p = jatekos ; p != NULL ; p = p->kov)
    {
        p->x += p->dx;
        p->y += p->dy;

        if (p == jatekos)
        {
            p->x = MIN(MAX(p->x, p->w / 2), SCREEN_WIDTH - p->w / 2);
            p->y = MIN(MAX(p->y, p->h / 2), SCREEN_HEIGHT - p->h / 2);
        }
    }
}

void jatekosFrissites(Peldany *jatekos, Jatek *jatek, Palya *palya) {
    jatekos->dx = 0; //reset
    jatekos->dy = 0;

    if (jatek->billentyuzet[SDL_SCANCODE_W]) {
        jatekos->dy = -5;
    }

    if (jatek->billentyuzet[SDL_SCANCODE_S]) {
        jatekos->dy = 5;
    }

    if (jatek->billentyuzet[SDL_SCANCODE_A]) {
        jatekos->dx = -5;
    }

    if (jatek->billentyuzet[SDL_SCANCODE_D]) {
        jatekos->dx = 5;
    }

    jatekos->szog = szog(jatekos->x, jatekos->y, jatek->eger.x, jatek->eger.y);

    if (jatekos->ujratoltIdo == 0 && palya->tolteny[jatekos->fegyver] > 0 && jatek->eger.gomb[SDL_BUTTON_LEFT]) {
        loves();

        palya->tolteny[jatekos->fegyver]--;
    }

    if (jatek->eger.gorgo < 0) {
        if (--jatekos->fegyver < WPN_PISTOL) {
            jatekos->fegyver = WPN_MAX - 1;
        }

        jatek->eger.gorgo = 0;
    }

    if (jatek->eger.gorgo > 0) {
        if (++jatekos->fegyver >= WPN_MAX) {
            jatekos->fegyver = WPN_PISTOL;
        }

        jatek->eger.gorgo = 0;
    }

    if (jatek->eger.gomb[SDL_BUTTON_RIGHT]) {
        if (jatekos->fegyver == WPN_PISTOL && palya->tolteny[WPN_PISTOL] == 0) {
            palya->tolteny[WPN_PISTOL] = 12;
        }

        jatek->eger.gomb[SDL_BUTTON_RIGHT] = 0;
    }
}
