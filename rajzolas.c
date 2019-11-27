//
// Created by Rakolcza Peter on 2019. 11. 27..
//

#include "rajzolas.h"

void blit(SDL_Texture *texture, int x, int y, int center, SDL_Renderer *renderer)
{
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
    szovegRajzolas(renderer, font, 10, 10, "Élet: ", 255, 255, 255);
    szovegRajzolas(renderer, font, 110, 10, mit, 255, 255, 255);

    //sprintf(elet, "%d", jatekos->elet);
    szovegRajzolas(renderer, font, 330, 10, "Pont: ", 255, 255, 255);
    szovegRajzolas(renderer, font, 430, 10, "0", 255, 255, 255);

    if (jatekos->fegyver == Pisztoly) {
        sprintf(mit, "%d", palya->tolteny[0]);
        szovegRajzolas(renderer, font, 650, 10, "Pisztoly: ", 255, 0, 0);
        szovegRajzolas(renderer, font, 800, 10, mit, 255, 0, 0);

        sprintf(mit, "%d", palya->tolteny[1]);
        szovegRajzolas(renderer, font, 970, 10, "Gépfegyver: ", 255, 255, 255);
        szovegRajzolas(renderer, font, 1170, 10, mit, 255, 255, 255);
    }
    else {
        sprintf(mit, "%d", palya->tolteny[0]);
        szovegRajzolas(renderer, font, 650, 10, "Pisztoly: ", 255, 255, 255);
        szovegRajzolas(renderer, font, 800, 10, mit, 255, 255, 255);

        sprintf(mit, "%d", palya->tolteny[1]);
        szovegRajzolas(renderer, font, 970, 10, "Gépfegyver: ", 255, 0, 0);
        szovegRajzolas(renderer, font, 1170, 10, mit, 255, 0, 0);
    }
}

void rajz(SDL_Texture *celzo, Jatek* jatek, Peldany *jatekos, Lovedek *lovedek, Palya *palya, SDL_Renderer *renderer, TTF_Font *font) {
    blit(celzo, jatek->eger.x, jatek->eger.y, 1, renderer);

    Peldany *e;
    for (e = jatekos ; e != NULL ; e = e->kov) {
        blitRotated(e->texture, e->x, e->y, e->szog, renderer);
    }

    Lovedek *l;
    for (l = lovedek ; l != NULL ; l = l->kov) {
        blitRotated(l->texture, l->x, l->y, l->szog, renderer);
    }

    HUDrajzolas(renderer, font, jatekos, palya);
}