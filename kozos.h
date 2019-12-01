//
// Created by Rakolcza Peter on 2019. 11. 16..
//

#ifndef BME_SCHOOTER_KOZOS_H
#define BME_SCHOOTER_KOZOS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>

#include "debugmalloc.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>

/** Képernyő hossza */
#define SCREEN_WIDTH 1280
/** Képernyő magassága */
#define SCREEN_HEIGHT 720
#define PI 3.141592653589793238

/** Makró 2 szám minimumámara. (https://stackoverflow.com/) */
#define MIN(a,b) (((a)<(b))?(a):(b))
/** Makró 2 szám maxmimumára. (https://stackoverflow.com/) */
#define MAX(a,b) (((a)>(b))?(a):(b))

/** Fegyver típusának tárolása.*/
typedef enum Fegyver {GepFegyver = 1, Pisztoly = 0} Fegyver;

/** @brief Az egér adatainak eltárolása.
 *
 *Az egér X;Y koordinátájának, illetve a lenyomott gombok és a görgő megváltozásának eltárolása.
 */
typedef struct Eger {
    int x;
    int y;
    int gomb[6];
    int gorgo;
} Eger;

/** @brief A játék menetének fontos adatainek eltárolása.
 *
 *A játékos pontszámát, az ellenség hozzáadásából fennmaradó időt és a töltények számát tartalmazza.
 */
typedef struct Palya {
    int pont;
    int spawnIdozito;
    int tolteny[2];
} Palya;

/** @brief A játékost és az ellenségeket tartalmazó láncolt lista.
 *
 *Tartalmazza az összes szükséges adatot, ami elengedhetetlen, ahhoz hogy ütközést vizsgáljunk, lövést adjunk le, illetve a fegyverek típúsánal tárolása is itt történik.
 */
typedef struct Peldany {
    float x;
    float y;
    int w;
    int h;
    float dx;
    float dy;
    int ujratoltIdo;
    int elet;
    int szog;
    /**0 barát, 1 ellenség, 2 semmi */
    int oldal;
    int hatokor;
    /** Fegyver típusa */
    Fegyver fegyver;
    SDL_Texture *texture;
    struct Peldany *kov;
} Peldany;

/** @brief Az ellenségek által "elhagyott" elemek tárolása. Ez is egy láncolt lista.
 *
 *Tartalmazza, hogy ha esetleg az ellenség eldob egy ilyen elemet, akkor hova fog kerülni, milyen a típusa, illetve mennyi ideig fog még látszódni a pályán.
 */
typedef struct PowerUp {
    float x;
    float y;
    int w;
    int h;
    float dx;
    float dy;
    /**0 az elet, 1 a tolteny */
    int tipus;
    /** Mennyi idő múlva fog megsemmisülni. */
    int elet;
    int oldal;
    int hatokor;
    SDL_Texture *texture;
    struct PowerUp *kov;
} PowerUp;

/** @brief A játékos és az ellenségek által kilőtt lövedékek tárolása láncolt listával.
 *
 *
 */
typedef struct Lovedek {
    float x;
    float y;
    int w;
    int h;
    float dx;
    float dy;
    /** Mennyi idő múlva fog megsemmisülni. */
    int elet;
    int oldal;
    int hatokor;
    int szog;
    SDL_Texture *texture;
    struct Lovedek *kov;
} Lovedek;

/** @brief A játék bemeneteinek regisztrására, a beírt név elmentésére szolgáló adatszerkezet. Itt tároljuk az egér adatait is a könnyebb átlhatóság érdekében.
 *
 *
 */
typedef struct Jatek {
    Eger eger;
    int billentyuzet[400];
    /** Felhasználó által gépelt szöveg tárolás.*/
    char beSzoveg[42];
} Jatek;

/** @brief A legjobb eredmények tárolására szolgáló adatszerkezet. Ezeket majd egy 10 elemű tömbben raktázozza el a játék.
 *
 *
 */
typedef struct Eredmenyek {
    char nev[42];
    int pontSzam;
} Eredmenyek;


#endif //BME_SCHOOTER_KOZOS_H
