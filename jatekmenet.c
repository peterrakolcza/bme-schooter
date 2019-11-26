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

void jatekosFrissites(Peldany *jatekos, Jatek *jatek) {
    jatekos->dx *= 0.7;
    jatekos->dy *= 0.7;

    if (jatek->billentyuzet[SDL_SCANCODE_W])
    {
        jatekos->dy = -5;
    }

    if (jatek->billentyuzet[SDL_SCANCODE_S])
    {
        jatekos->dy = 5;
    }

    if (jatek->billentyuzet[SDL_SCANCODE_A])
    {
        jatekos->dx = -5;
    }

    if (jatek->billentyuzet[SDL_SCANCODE_D])
    {
        jatekos->dx = 5;
    }

    jatekos->szog = szog(jatekos->x, jatekos->y, jatek->eger.x, jatek->eger.y);
}
