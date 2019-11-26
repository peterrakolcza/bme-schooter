//
// Created by Rakolcza Peter on 2019. 11. 25..
//

#include "jatekmenet.h"

void jatekFrissites(Palya *palya, Peldany *jatekos, Jatek *jatek) {
    jatekosFrissites(jatekos, jatek);
    peldanyFrissites(palya, jatekos);
}

void peldanyFrissites(Palya *palya, Peldany *jatekos) {
    Peldany *p;

    for (p = palya->elem.kov ; p != NULL ; p = p->kov)
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

void jatekosFrissites(Peldany *jatekos, Jatek *jatek) {
    jatekos->dx *= 0.85;
    jatekos->dy *= 0.85;

    if (jatek->billentyuzet[SDL_SCANCODE_W])
    {
        jatekos->dy = -6;
    }

    if (jatek->billentyuzet[SDL_SCANCODE_S])
    {
        jatekos->dy = 6;
    }

    if (jatek->billentyuzet[SDL_SCANCODE_A])
    {
        jatekos->dx = -6;
    }

    if (jatek->billentyuzet[SDL_SCANCODE_D])
    {
        jatekos->dx = 6;
    }

    jatekos->szog = szog(jatekos->x, jatekos->y, jatek->eger.x, jatek->eger.y);
}
