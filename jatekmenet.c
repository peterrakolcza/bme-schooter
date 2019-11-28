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

void addHealthPowerup(int x, int y, PowerUp **powerup, SDL_Texture *elet)
{
    PowerUp *e;
    e = malloc(sizeof(PowerUp));
    memset(e, 0, sizeof(PowerUp));

    e->x = x;
    e->y = y;
    e->elet = 60 * 5;
    e->hatokor = 16;
    e->oldal = 2;

    e->dx = -200 + (rand() % 400);
    e->dy = -200 + (rand() % 400);

    e->dx /= 100;
    e->dy /= 100;

    if (*powerup == NULL)
        *powerup = e;
    else {
        PowerUp *mozgo = *powerup;
        while (mozgo->kov != NULL) mozgo = mozgo->kov;
        mozgo->kov = e;
    }
    e->kov = NULL;

    e->texture = elet;
}

void hozzaadRandomPowerup(int x, int y, PowerUp **powerup, SDL_Texture *elet) {
    int veletlen;

    veletlen = rand() % 5;

    if (veletlen == 0) {
        addHealthPowerup(x, y, powerup, elet);
    }
    else if (veletlen == 1) {
        //addUziPowerup(x, y);
    }
}

void halal(Palya *palya, Peldany *e, PowerUp **powerup, SDL_Texture *elet) {
    if (rand() % 2 == 0) {
        hozzaadRandomPowerup(e->x, e->y, powerup, elet);
    }

    palya->pont += 10;
}


void tick(Peldany* peldany, Peldany *jatekos) {
    peldany->szog = szog(peldany->x, peldany->y, jatekos->x, jatekos->y);

    calcSlope(jatekos->x, jatekos->y, jatekos->x, jatekos->y, &peldany->dx, &peldany->dy);
}

void peldanyFrissites(Peldany *jatekos, Palya *palya, SDL_Texture *elet, PowerUp **powerup) {
    Peldany *p;
    Peldany *lemarado = NULL;

    for (p = jatekos ; p != NULL ; p = p->kov) {
        p->x += p->dx;
        p->y += p->dy;

        p->ujratoltIdo = MAX(p->ujratoltIdo - 1, 0);

        if (p == jatekos) {
            p->x = MIN(MAX(p->x, p->w / 2), SCREEN_WIDTH - p->w / 2);
            p->y = MIN(MAX(p->y, p->h / 2), SCREEN_HEIGHT - p->h / 2);
        }

        if (p != jatekos) {
            tick(p, jatekos);
        }

    }



    p = jatekos;
    while (p != NULL && p->elet != 0) {
        lemarado = p;
        p = p->kov;
    }
    if (p == NULL) {
        return;
    }
    else {
        lemarado->kov = p->kov;
        halal(palya, p, powerup, elet);
        free(p);
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


void ellensegHozzaad(int x, int y, Peldany *jatekos, SDL_Texture *ellenseg, Palya *palya) {
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
    e->dx = 0;
    e->dy = 0;
    SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
    e->hatokor = 32;
}

void spawnEllenseg(SDL_Texture *ellenseg, Peldany *jatekos, Palya *palya) {
    int x, y;

    if (--palya->spawnIdozito <= 0) {
        /*switch (rand() % 4) {
            case 0:
                x = -100;
                y = rand() % 720;
                break;

            case 1:
                x = 1280 + 100;
                y = rand() % 720;
                break;

            case 2:
                x = rand() % 1280;
                y = -100;
                break;

            case 3:
                x = rand() % 1280;
                y = 720 + 100;
                break;
        }*/

        x = rand() % 1000 + 100;
        y = rand() % 500 + 100;

        //printf("%d %d ", x, y);
        ellensegHozzaad(x, y, jatekos, ellenseg, palya);

        palya->spawnIdozito = 60 + (rand() % 60);
    }
}

void powerupFrissites(PowerUp **powerup) {
    PowerUp *p;
    PowerUp *lemarado = NULL;

    for (p = *powerup ; p != NULL ; p = p->kov) {
        p->elet--;
    }

    p = *powerup;
    while (p != NULL && p->elet != 0) {
        lemarado = p;
        p = p->kov;
    }
    if (p == NULL) {
        return;
    }
    else if (lemarado == NULL) { /* az első elemet kell törölni */
        PowerUp *ujeleje = p->kov;
        free(p);
        *powerup = ujeleje;
    }
    else {
        lemarado->kov = p->kov;
        free(p);
    }
}

void jatekFrissites(Peldany *jatekos, Jatek *jatek, Palya *palya, SDL_Texture *texture, SDL_Texture *ellenseg, SDL_Texture *elet, Lovedek **lovedek, PowerUp **powerup) {
    jatekosFrissites(jatekos, jatek, palya, texture, lovedek);
    peldanyFrissites(jatekos, palya, elet, powerup);
    lovedekFrissites(lovedek, jatekos);

    powerupFrissites(powerup);

    spawnEllenseg(ellenseg, jatekos, palya);
}