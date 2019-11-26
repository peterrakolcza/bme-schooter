//
// Created by Rakolcza Peter on 2019. 11. 16..
//

#ifndef BME_SCHOOTER_INIT_H
#define BME_SCHOOTER_INIT_H

#include "kozos.h"

void init(SDL_Renderer **renderer1, SDL_Window **window1);
void rajz(Jatek* jatek, Peldany *jatekos, SDL_Renderer *renderer);
SDL_Texture* loadImage(SDL_Renderer *renderer, char path[]);
//void blit(SDL_Texture *texture, int x, int y, int center, SDL_Renderer *renderer);
void felkeszites(SDL_Renderer *renderer);
void kepernyo(SDL_Renderer *renderer);
void torles(SDL_Renderer *renderer, SDL_Window *window);
void initPalya(SDL_Renderer *renderer, Peldany **jatekos, Palya *palya);
//void blitRotated(SDL_Texture *texture, int x, int y, float angle, SDL_Renderer *renderer);

#endif //BME_SCHOOTER_INIT_H
