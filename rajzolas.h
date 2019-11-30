//
// Created by Rakolcza Peter on 2019. 11. 27..
//

#ifndef BME_SCHOOTER_RAJZOLAS_H
#define BME_SCHOOTER_RAJZOLAS_H

#include "kozos.h"

void rajz(SDL_Texture *celzo, SDL_Texture *grid, SDL_Texture *hatter, Jatek* jatek, Peldany *jatekos, Lovedek *lovedek, PowerUp *powerup, Palya *palya, SDL_Renderer *renderer, TTF_Font *font);
void fokepernyo(SDL_Renderer *renderer, TTF_Font *font, SDL_Texture *celzo, Jatek *jatek, SDL_Texture *fokepernyoTexture, SDL_Texture *grid);
void legjobbEredmenyekKepernyo(SDL_Renderer *renderer, TTF_Font *font, SDL_Texture *celzo, Jatek *jatek, SDL_Texture *fokepernyoTexture, SDL_Texture *grid);

#endif //BME_SCHOOTER_RAJZOLAS_H
