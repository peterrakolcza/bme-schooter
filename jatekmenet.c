//
// Created by Rakolcza Peter on 2019. 11. 25..
//

#include "jatekmenet.h"

////////////////////////////////////////////////////////////////
//////////////////////  Segédfüggvények
////////////////////////////////////////////////////////////////

/** Két pont közötti távolságot számolja ki Pithagorasz-tétellel és visszatér azzal.*/
int getDistance(int x1, int y1, int x2, int y2) {
    int x, y;

    x = x2 - x1;
    y = y2 - y1;

    return sqrt(x * x + y *y);
}

/** Két pont által bezárt szöget számolja ki és visszatér azzal. */
float szog(int x1, int y1, int x2, int y2) {
    float angle = -90 + atan2(y1 - y2, x1 - x2) * (180 / PI);
    return angle >= 0 ? angle : 360 + angle;
}

/** Kiszámolja, hogy maximum hány lépés szükséges, hogy elérjünk az egyik pontból a másikba, így frissítve a pédányok láncolt lista delta X;Y értékeit. */
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

////////////////////////////////////////////////////////////////
//////////////////////  Segédfüggvények vége
////////////////////////////////////////////////////////////////

/** Hozzáfűzi az újonnan kilőlt lövedékeket a láncolt listához és beállítja azok kezdőértékeit. Inicializálja a lövedékeket.*/
void loves(Peldany *peldany, SDL_Texture *texture, Lovedek **lovedek, Jatek *jatek, Peldany *jatekos) {
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

    l->x = peldany->x;
    l->y = peldany->y;
    l->oldal = peldany->oldal;
    l->hatokor = peldany->hatokor;
    l->texture = texture;
    l->elet = 120;
    l->szog = peldany->szog;

    if (peldany == jatekos) {
        calcSlope(jatek->eger.x, jatek->eger.y, l->x, l->y, &l->dx, &l->dy);
        if (jatekos->fegyver == GepFegyver)
            jatekos->ujratoltIdo = 4;
        else jatekos->ujratoltIdo = 16;
    }
    else {
        peldany->ujratoltIdo = 100;
        calcSlope(jatekos->x, jatekos->y, peldany->x, peldany->y, &l->dx, &l->dy);
    }

    l->dx *= 16;
    l->dy *= 16;
}

/** Létrehoz egy ilyne "powerup" elemet és inicializálja azt. */
void powerupLetrehoz(int x, int y, PowerUp **powerup, SDL_Texture *texture, int tipus) {
    PowerUp *e;
    e = malloc(sizeof(PowerUp));
    memset(e, 0, sizeof(PowerUp));

    e->x = x;
    e->y = y;
    e->elet = 60 * 5;
    e->hatokor = 32;
    e->oldal = 2;
    e->tipus = tipus;

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

    e->texture = texture;
}

/** Randomszám generásával eldönti, hogy egy ellenség lelövése esetén dobjon-e el "powerup" elemet avagy ne.*/
void hozzaadRandomPowerup(int x, int y, PowerUp **powerup, SDL_Texture *elet, SDL_Texture *tolteny) {
    int veletlen;

    veletlen = rand() % 5;

    if (veletlen == 0) {
        powerupLetrehoz(x, y, powerup, elet, 0);
    }
    else if (veletlen == 1) {
        powerupLetrehoz(x, y, powerup, tolteny, 1);
    }
}

/** Ellenség lelövése esetén növeli a pontszámot, illetve 50%-50% valószínűséggel meghívja a "powerup sorsoló" függvényt, így tovább randomizálja az esélyét, hogy "powerup" elem keletkezik.*/
void halal(Palya *palya, Peldany *e, PowerUp **powerup, SDL_Texture *elet, SDL_Texture *tolteny) {
    if (rand() % 2 == 0) {
        hozzaadRandomPowerup(e->x, e->y, powerup, elet, tolteny);
    }

    palya->pont += 10;
}

/** Beállítja az ellenség célzási irányát a játékosra és elmozgatja abba az irányba.*/
void tick(Peldany* peldany, Peldany *jatekos) {
    peldany->szog = szog(peldany->x, peldany->y, jatekos->x, jatekos->y);

    calcSlope(jatekos->x, jatekos->y, peldany->x, peldany->y, &peldany->dx, &peldany->dy);
}

/** Minden képkocka esetén frissíti a láncolt lista összes elemét, ezzel lehetővé téve a mozgatást, találat vizsgálatát és a "meghalt" ellenségek törlését.*/
void peldanyFrissites(Peldany *jatekos, Palya *palya, SDL_Texture *elet, SDL_Texture *tolteny, SDL_Texture *golyo, PowerUp **powerup, Lovedek **lovedek, Jatek *jatek) {
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
            int tavolsag = getDistance(p->x, p->y, jatekos->x, jatekos->y);
            if (tavolsag < 300) {
                p->dx = 0;
                p->dy = 0;
                if (p->ujratoltIdo == 0)
                    loves(p, golyo, lovedek, jatek, jatekos);
            }
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
    else if (p == jatekos && p->elet == 0) {
        return;
    }
    else {
        lemarado->kov = p->kov;
        halal(palya, p, powerup, elet, tolteny);
        free(p);
    }
}

/** Játékos bemeneteinek olvasása és annak megfelelő mozgatása. Ezenkívül a játékos célzási irányát frissíti az egér által mutatott pozícióra. Az egérgombot is olvassa a függvény és ennek megfelően vagy újratölt, lő vagy fegyvert vált.*/
void jatekosFrissites(Peldany *jatekos, Jatek *jatek, Palya *palya, SDL_Texture *texture, Lovedek **lovedek) {
    jatekos->dx *= 0.8; //reset
    jatekos->dy *= 0.8;

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
        loves(jatekos, texture, lovedek, jatek, jatekos);

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

/** Adott lövedék pozíciójának és hatókörének összehasonlítása az összes példánnyal, így vizsgálva a találatot.*/
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

/** Frissíti a lövedékek láncolt listát. Mozgatja a lövedékeket a megfelelő irányba és sebességgel, illetve viszgálja, hogy az adott golyó eltalált-e valakit. FRIENDLYFIRE nincs! Ha egy golyó nem talált el senkit és "lejárt" az élettartama, akkor felszabadítja azt.*/
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

/** Ellenség példányt hoz létre és inicializája azt. Hozzáfűzi a láncolt listához.*/
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

/** Az ellenséget elhelyezi a képernyő egy random, kívüleső pontjára és beállítja az időzítőt a következő ellenség sorsolásáig.*/
void spawnEllenseg(SDL_Texture *ellenseg, Peldany *jatekos, Palya *palya) {
    int x, y;

    if (--palya->spawnIdozito <= 0) {
        switch (rand() % 4) {
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
        }

        //x = rand() % 1000 + 100;
        //y = rand() % 500 + 100;

        ellensegHozzaad(x, y, jatekos, ellenseg, palya);

        palya->spawnIdozito = 60 + (rand() % 60);
    }
}

/** Frissíti a "powerup" elemeket minden képkockára. Ha hozzáér a játékos, akkor típustól függően megnöveli az életét vagy a töltények számát, majd törli az elemet. */
void powerupFrissites(PowerUp **powerup, Peldany *jatekos, Palya *palya) {
    PowerUp *p;
    PowerUp *lemarado = NULL;

    int tavolsag;

    for (p = *powerup ; p != NULL ; p = p->kov) {
        p->elet--;

        tavolsag = getDistance(p->x, p->y, jatekos->x, jatekos->y);
        if (tavolsag < p->hatokor + jatekos->hatokor) {
            p->elet = 0;

            if (p->tipus == 0 && jatekos->elet < 5)
                jatekos->elet += 1;
            else palya->tolteny[1] += 50;
        }
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

/** "Fő" frissiítő függvény, ami összefogja az összes frissitést és minden képkockára frissíti azokat.*/
void jatekFrissites(Peldany *jatekos, Jatek *jatek, Palya *palya, SDL_Texture *golyo, SDL_Texture *ellenseg, SDL_Texture *elet, SDL_Texture *tolteny, Lovedek **lovedek, PowerUp **powerup) {
    jatekosFrissites(jatekos, jatek, palya, golyo, lovedek);
    peldanyFrissites(jatekos, palya, elet, tolteny, golyo, powerup, lovedek, jatek);
    lovedekFrissites(lovedek, jatekos);

    powerupFrissites(powerup, jatekos, palya);

    spawnEllenseg(ellenseg, jatekos, palya);
}