//
// Created by Rakolcza Peter on 2019. 11. 25..
//

#include "jatekmenet.h"

float szog(int x1, int y1, int x2, int y2) {
    float angle = -90 + atan2(y1 - y2, x1 - x2) * (180 / PI);
    return angle >= 0 ? angle : 360 + angle;
}

void calcSlope(int x1, int y1, int x2, int y2, float *dx, float *dy)
{
    int steps = MAX(abs(x1 - x2), abs(y1 - y2));

    if (steps == 0) {
        *dx = *dy = 0;
        return;
    }

    *dx = (x1 - x2);
    *dx /= steps;

    *dy = (y1 - y2);
    *dy /= steps;
}




static void loves(Peldany *jatekos, SDL_Texture *texture, Lovedek **lovedek) {
    Lovedek *l;

    l = malloc(sizeof(Lovedek));
    memset(l, 0, sizeof(Lovedek));
    (*lovedek) = l;
    l->kov = NULL;

    l->x = jatekos->x;
    l->y = jatekos->y;
    l->texture = texture;
    l->elet = 60 * 2;
    l->szog = jatekos->szog;

    //calcSlope(app.mouse.x, app.mouse.y, l->x, l->y, &l->dx, &l->dy);

    l->dx *= 16;
    l->dy *= 16;

    if (jatekos->fegyver == GepFegyver)
        jatekos->ujratoltIdo = 4;
    else jatekos->ujratoltIdo = 16;
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

void jatekosFrissites(Peldany *jatekos, Jatek *jatek, Palya *palya, SDL_Texture *texture, Lovedek **lovedek) {
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
        loves(jatekos, texture, lovedek);

        palya->tolteny[jatekos->fegyver]--;
    }

    if (jatek->eger.gorgo < 0) {
        jatekos->fegyver = Pisztoly;

        jatek->eger.gorgo = 0;
    }

    if (jatek->eger.gorgo > 0) {
        jatekos->fegyver = GepFegyver;

        jatek->eger.gorgo = 0;
    }

    if (jatek->eger.gomb[SDL_BUTTON_RIGHT]) {
        if (jatekos->fegyver == Pisztoly && palya->tolteny[Pisztoly] == 0) {
            palya->tolteny[Pisztoly] = 12;
        }

        jatek->eger.gomb[SDL_BUTTON_RIGHT] = 0;
    }
}


void jatekFrissites(Peldany *jatekos, Jatek *jatek, Palya *palya, SDL_Texture *texture, Lovedek **lovedek) {
    jatekosFrissites(jatekos, jatek, palya, texture, lovedek);
    peldanyFrissites(jatekos);
}