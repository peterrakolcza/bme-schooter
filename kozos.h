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

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define PI 3.141592653589793238

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

typedef enum Fegyver {GepFegyver = 1, Pisztoly = 0} Fegyver;

typedef struct Eger {
    int x;
    int y;
    int gomb[6];
    int gorgo;
} Eger;

typedef struct Palya {
    int pont;
    int spawnIdozito;
    int tolteny[2];
} Palya;

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
    //0 barát, 1 ellenség, 2 semmi
    int oldal;
    int hatokor;
    Fegyver fegyver;
    SDL_Texture *texture;
    struct Peldany *kov;
} Peldany;

typedef struct PowerUp {
    float x;
    float y;
    int w;
    int h;
    float dx;
    float dy;
    int elet;
    //0 barát, 1 ellenség, 2 semmi
    int oldal;
    int hatokor;
    SDL_Texture *texture;
    struct PowerUp *kov;
} PowerUp;

typedef struct Lovedek {
    float x;
    float y;
    int w;
    int h;
    float dx;
    float dy;
    int elet;
    int oldal;
    int hatokor;
    int szog;
    SDL_Texture *texture;
    struct Lovedek *kov;
} Lovedek;


typedef struct Jatek {
    Eger eger;
    int billentyuzet[400];
    char beSzoveg[1000];
} Jatek;


#endif //BME_SCHOOTER_KOZOS_H
