//
// Created by Rakolcza Peter on 2019. 11. 16..
//

#ifndef BME_SCHOOTER_KOZOS_H
#define BME_SCHOOTER_KOZOS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define MAX_KEYBOARD_KEYS 400
#define MAX_LINE_LENGTH 1000

typedef struct Eger {
    int x;
    int y;
    int gorgo;
} Eger;

typedef struct Texture {
    char name[300];
    SDL_Texture *texture;
    struct Texture *next;
} Texture;

typedef struct Jatek {
    Eger eger;
    int billentyuzet[MAX_KEYBOARD_KEYS];
    Texture textureHead, *textureTail;
    char beSzoveg[MAX_LINE_LENGTH];
} Jatek;

typedef struct Peldany {
    float x;
    float y;
    int w;
    int h;
    float dx;
    float dy;
    int elet;
    int szog;
    SDL_Texture *texture;
    struct Entity *kov;
} Peldany;

#endif //BME_SCHOOTER_KOZOS_H
