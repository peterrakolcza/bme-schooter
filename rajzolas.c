//
// Created by Rakolcza Peter on 2019. 11. 27..
//

#include "rajzolas.h"

void blit(SDL_Texture *texture, int x, int y, int center, SDL_Renderer *renderer) {
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

    if (center) {
        dest.x -= dest.w / 2;
        dest.y -= dest.h / 2;
    }

    SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void blitRotated(SDL_Texture *texture, int x, int y, float angle, SDL_Renderer *renderer) {
    SDL_Rect dstRect;

    dstRect.x = x;
    dstRect.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dstRect.w, &dstRect.h);
    dstRect.x -= (dstRect.w / 2);
    dstRect.y -= (dstRect.h / 2);

    SDL_RenderCopyEx(renderer, texture, NULL, &dstRect, angle, NULL, SDL_FLIP_NONE);
}

void szovegRajzolas(SDL_Renderer *renderer, TTF_Font *font, int x, int y, char mit[], int R, int G, int B) {
    SDL_Surface *felirat;
    SDL_Texture *felirat_t;

    SDL_Color szin = {R, G, B};

    SDL_Rect hova = { 0, 0, 0, 0 };

    felirat = TTF_RenderUTF8_Blended(font, mit, szin);
    felirat_t = SDL_CreateTextureFromSurface(renderer, felirat);

    hova.x = x;
    hova.y = y;
    hova.w = felirat->w;
    hova.h = felirat->h;

    SDL_RenderCopy(renderer, felirat_t, NULL, &hova);
    SDL_FreeSurface(felirat);
    SDL_DestroyTexture(felirat_t);
}

void HUDrajzolas(SDL_Renderer *renderer, TTF_Font *font, Peldany *jatekos, Palya *palya) {
    char mit[4];

    sprintf(mit, "%d", jatekos->elet);
    szovegRajzolas(renderer, font, 20, 10, "Élet: ", 255, 255, 255);
    szovegRajzolas(renderer, font, 120, 10, mit, 255, 255, 255);

    sprintf(mit, "%d", palya->pont);
    szovegRajzolas(renderer, font, 340, 10, "Pont: ", 255, 255, 255);
    szovegRajzolas(renderer, font, 440, 10, mit, 255, 255, 255);

    if (jatekos->fegyver == Pisztoly) {
        sprintf(mit, "%d", palya->tolteny[0]);
        szovegRajzolas(renderer, font, 660, 10, "Pisztoly: ", 255, 0, 0);
        szovegRajzolas(renderer, font, 810, 10, mit, 255, 0, 0);

        sprintf(mit, "%d", palya->tolteny[1]);
        szovegRajzolas(renderer, font, 980, 10, "Gépfegyver: ", 255, 255, 255);
        szovegRajzolas(renderer, font, 1180, 10, mit, 255, 255, 255);
    }
    else {
        sprintf(mit, "%d", palya->tolteny[0]);
        szovegRajzolas(renderer, font, 660, 10, "Pisztoly: ", 255, 255, 255);
        szovegRajzolas(renderer, font, 810, 10, mit, 255, 255, 255);

        sprintf(mit, "%d", palya->tolteny[1]);
        szovegRajzolas(renderer, font, 980, 10, "Gépfegyver: ", 255, 0, 0);
        szovegRajzolas(renderer, font, 1180, 10, mit, 255, 0, 0);
    }
}

void mintazat(SDL_Texture *grid, SDL_Renderer *renderer)
{
    int x, y;
    for (y = 0 ; y < 720 ; y += 64) {
        for (x = 0 ; x < 1280 ; x += 64) {
            blit(grid, x, y, 0, renderer);
        }
    }
}

void rajz(SDL_Texture *celzo, SDL_Texture *grid, SDL_Texture *hatter, Jatek* jatek, Peldany *jatekos, Lovedek *lovedek, PowerUp *powerup, Palya *palya, SDL_Renderer *renderer, TTF_Font *font) {

    mintazat(grid, renderer);
    blit(hatter, 0, 0, 0, renderer);

    blit(celzo, jatek->eger.x, jatek->eger.y, 1, renderer);

    Peldany *e;
    for (e = jatekos ; e != NULL ; e = e->kov) {
        blitRotated(e->texture, e->x, e->y, e->szog, renderer);
    }

    Lovedek *l;
    for (l = lovedek ; l != NULL ; l = l->kov) {
        blitRotated(l->texture, l->x, l->y, l->szog, renderer);
    }

    PowerUp *p;
    for (p = powerup ; p != NULL ; p = p->kov) {
        blit(p->texture, p->x, p->y, 1, renderer);
    }

    HUDrajzolas(renderer, font, jatekos, palya);
}