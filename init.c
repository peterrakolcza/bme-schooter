//
// Created by Rakolcza Peter on 2019. 11. 16..
//

#include "init.h"

static SDL_Texture *celzo;

void init(SDL_Renderer **renderer1, SDL_Window **window1) {
    /* SDL inicializálása és ablak megnyitása */
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }

    SDL_Window *window = SDL_CreateWindow("BME SCHooter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (window == NULL) {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }

    SDL_ShowCursor(0);

    *renderer1 = renderer;
    *window1 = window;

}

SDL_Texture* loadImage(SDL_Renderer *renderer, char path[]) {
    /* kep betoltese */
    SDL_Texture *kep = IMG_LoadTexture(renderer, path);
    if (kep == NULL) {
        SDL_Log("Nem nyithato meg a kepfajl: %s", IMG_GetError());
        return NULL;
    }
    //else SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Kep betoltese %s ...", path);

    return kep;
}

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

void felkeszites(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 32, 32, 32, 255);
    SDL_RenderClear(renderer);
}

void kepernyo(SDL_Renderer *renderer) {
    SDL_RenderPresent(renderer);
}

void torles(SDL_Renderer *renderer, SDL_Window *window) {
    printf("TORLESSSSSS");
    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);

    SDL_Quit();
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

void initJatekos(Peldany **jatekos, SDL_Renderer *renderer, Palya *palya)
{
    *jatekos = malloc(sizeof(Peldany));
    memset(*jatekos, 0, sizeof(Peldany));
    (*jatekos)->kov = NULL;

    (*jatekos)->texture = loadImage(renderer, "gfx/donk.png");
    (*jatekos)->elet = 5;

    palya->tolteny[Pisztoly] = 12;
    palya->tolteny[GepFegyver] = 100;


    (*jatekos)->x = SCREEN_WIDTH / 2;
    (*jatekos)->y = SCREEN_HEIGHT / 2;

    SDL_QueryTexture((*jatekos)->texture, NULL, NULL, &(*jatekos)->w, &(*jatekos)->h);
}

void initPalya(SDL_Renderer *renderer, Peldany **jatekos, Palya *palya) {
    celzo = loadImage(renderer, "gfx/targetter.png");
    initJatekos(jatekos, renderer, palya);
}

void rajz(Jatek* jatek, Peldany *jatekos, Lovedek *lovedek, SDL_Renderer *renderer) {
    blit(celzo, jatek->eger.x, jatek->eger.y, 1, renderer);

    Peldany *e;
    for (e = jatekos ; e != NULL ; e = e->kov) {
        blitRotated(e->texture, e->x, e->y, e->szog, renderer);
    }

    Lovedek *l;
    for (l = lovedek ; l != NULL ; l = l->kov) {
        blitRotated(l->texture, l->x, l->y, l->szog, renderer);
    }
}


