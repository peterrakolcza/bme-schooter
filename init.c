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

void rajz(Jatek* jatek, SDL_Renderer *renderer) {
    blit(celzo, jatek->eger.x, jatek->eger.y, 1, renderer);
}

SDL_Texture* loadImage(SDL_Renderer *renderer, char path[]) {
    /* kep betoltese */
    SDL_Texture *kep = IMG_LoadTexture(renderer, path);
    if (kep == NULL) {
        SDL_Log("Nem nyithato meg a kepfajl: %s", IMG_GetError());
        return NULL;
    }
    else SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Kep betoltese %s ...", path);

    return kep;
}

void blit(SDL_Texture *texture, int x, int y, int center, SDL_Renderer *renderer)
{
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

    if (center)
    {
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
    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);

    SDL_Quit();
}

void initPalya(SDL_Renderer *renderer) {
    celzo = loadImage(renderer, "gfx/targetter.png");
}


