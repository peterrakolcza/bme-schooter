//
// Created by Rakolcza Peter on 2019. 11. 16..
//

#ifndef BME_SCHOOTER_INIT_H
#define BME_SCHOOTER_INIT_H

#include "kozos.h"

void init(SDL_Renderer **renderer1, SDL_Window **window1);
SDL_Texture* loadImage(SDL_Renderer *renderer, char path[]);
void felkeszites(SDL_Renderer *renderer);
void kepernyo(SDL_Renderer *renderer);
void torles(SDL_Renderer *renderer, SDL_Window *window);
void initPalya(SDL_Renderer *renderer, Peldany **jatekos, Palya *palya, Jatek *jatek);
void felszabaditas(Peldany *jatekos, Lovedek *lovedek, PowerUp *powerUp);
TTF_Font* initTTF(char path[], int meret);

#endif //BME_SCHOOTER_INIT_H
