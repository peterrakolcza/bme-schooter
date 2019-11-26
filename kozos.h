//
// Created by Rakolcza Peter on 2019. 11. 16..
//

#ifndef BME_SCHOOTER_KOZOS_H
#define BME_SCHOOTER_KOZOS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>

//#include "debugmalloc.h"

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

typedef struct Texture {
    char name[300];
    SDL_Texture *texture;
    struct Texture *next;
} Texture;

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
    Fegyver fegyver;
    SDL_Texture *texture;
    struct Peldany *kov;
} Peldany;

typedef struct Lovedek {
    float x;
    float y;
    int w;
    int h;
    float dx;
    float dy;
    int elet;
    int szog;
    SDL_Texture *texture;
    struct Lovedek *kov;
} Lovedek;

typedef struct {
    int tolteny[2];
} Palya;

typedef struct Jatek {
    Eger eger;
    int billentyuzet[400];
    char beSzoveg[1000];
} Jatek;


#endif //BME_SCHOOTER_KOZOS_H
