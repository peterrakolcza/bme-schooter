//
// Created by Rakolcza Peter on 2019. 11. 25..
//

#include "jatekmenet.h"

int getDistance(int x1, int y1, int x2, int y2) {
    int x, y;

    x = x2 - x1;
    y = y2 - y1;

    return sqrt(x * x + y *y);
}

float szog(int x1, int y1, int x2, int y2) {
    float angle = -90 + atan2(y1 - y2, x1 - x2) * (180 / PI);
    return angle >= 0 ? angle : 360 + angle;
}

void calcSlope(int x1, int y1, int x2, int y2, float *dx, float *dy) {
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




static void loves(Peldany *jatekos, SDL_Texture *texture, Lovedek **lovedek, Jatek *jatek) {
    Lovedek *l;

    l = malloc(sizeof(Lovedek));
    memset(l, 0, sizeof(Lovedek));

    if(*lovedek == NULL) {
        (*lovedek) = l;
    }
    else {
        Lovedek *mozgo = *lovedek;
        while (mozgo->kov != NULL) mozgo = mozgo->kov;
        mozgo->kov = l;
    }
    l->kov = NULL;

    l->x = jatekos->x;
    l->y = jatekos->y;
    l->oldal = jatekos->oldal;
    l->hatokor = jatekos->hatokor;
    l->texture = texture;
    l->elet = 120;
    l->szog = jatekos->szog;

    calcSlope(jatek->eger.x, jatek->eger.y, l->x, l->y, &l->dx, &l->dy);

    l->dx *= 16;
    l->dy *= 16;

    if (jatekos->fegyver == GepFegyver)
        jatekos->ujratoltIdo = 4;
    else jatekos->ujratoltIdo = 16;
}


void peldanyFrissites(Peldany *jatekos) {
    Peldany *p;

    for (p = jatekos ; p != NULL ; p = p->kov) {
        p->x += p->dx;
        p->y += p->dy;

        p->ujratoltIdo = MAX(p->ujratoltIdo - 1, 0);

        if (p == jatekos) {
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

    if (jatekos->ujratoltIdo == 0 && palya->tolteny[jatekos->fegyver] > 0 && jatek->eger.gomb[SDL_BUTTON_LEFT] && (jatek->eger.x != jatekos->x && jatek->eger.y != jatekos->y)) {
        loves(jatekos, texture, lovedek, jatek);
        /*for (int i = 0; i < 6; ++i) {
            printf("%d ", jatek->eger.gomb[i]);
        }*/

        palya->tolteny[jatekos->fegyver]--;
    }

    if (jatek->eger.gorgo != 0) {
        if (jatekos->fegyver == Pisztoly)
            jatekos->fegyver = GepFegyver;
        else
            jatekos->fegyver = Pisztoly;

        jatek->eger.gorgo = 0;
    }

    if (jatek->eger.gomb[SDL_BUTTON_RIGHT]) {
        if (jatekos->fegyver == Pisztoly && palya->tolteny[Pisztoly] == 0) {
            palya->tolteny[Pisztoly] = 12;
        }

        jatek->eger.gomb[SDL_BUTTON_RIGHT] = 0;
    }
}

void lovedekTalaltE(Lovedek *l, Peldany *jatekos) {
    Peldany *e;
    int tavolsag;

    if (l != NULL) {
        for (e = jatekos; e != NULL; e = e->kov) {
            if (e->oldal != 2 && e->oldal != l->oldal) {
                tavolsag = getDistance(e->x, e->y, l->x, l->y);

                if (tavolsag < e->hatokor + l->hatokor) {
                    l->elet = 0;
                    e->elet--;
                    return;
                }
            }
        }
    }
}

void lovedekFrissites(Lovedek **lovedek, Peldany *jatekos) {
    Lovedek *l = *lovedek;
    Lovedek *lemarado = NULL;

    for (l = *lovedek; l != NULL; l = l->kov) {
        l->x += l->dx;
        l->y += l->dy;
        lovedekTalaltE(l, jatekos);
        l->elet--;
    }

    l = *lovedek;
    while (l != NULL && l->elet > 0) {
        lemarado = l;
        l = l->kov;
    }
    if (l == NULL) {
        return;
    }
    else if (lemarado == NULL) { /* az első elemet kell törölni */
        Lovedek *ujeleje = l->kov;
        free(l);
        *lovedek = ujeleje;
    }
    else {                       /* a közepéről/végéről törlünk */
        lemarado->kov = l->kov;
        free(l);
    }
}

void tick(Peldany* peldany, Peldany *jatekos) {
    peldany->szog = szog(peldany->x, peldany->y, jatekos->x, jatekos->y);

    calcSlope(jatekos->x, jatekos->y, jatekos->x, jatekos->y, &peldany->dx, &peldany->dy);
}

void halal(Palya *palya) {
    if (rand() % 2 == 0) {
        //addRandomPowerup(self->x, self->y);
    }

    palya->pont += 10;
}

void ellensegHozzaad(int x, int y, Peldany *jatekos, SDL_Texture *ellenseg, Palya *palya)
{
    Peldany *e;

    e = malloc(sizeof(Peldany));
    memset(e, 0, sizeof(Peldany));
    Peldany *mozgo = jatekos;
    while (mozgo->kov != NULL) mozgo = mozgo->kov;
    mozgo->kov = e;
    e->kov = NULL;

    e->oldal = 1;
    e->texture = ellenseg;
    e->elet = 2;
    e->x = x;
    e->y = y;
    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
    e->hatokor = 32;
}



void jatekFrissites(Peldany *jatekos, Jatek *jatek, Palya *palya, SDL_Texture *texture, SDL_Texture *ellenseg, Lovedek **lovedek) {
    jatekosFrissites(jatekos, jatek, palya, texture, lovedek);
    peldanyFrissites(jatekos);
    lovedekFrissites(lovedek, jatekos);
    ellensegHozzaad(100, 100, jatekos, ellenseg, palya);
}