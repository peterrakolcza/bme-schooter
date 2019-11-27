//
// Created by Rakolcza Peter on 2019. 11. 16..
//

#include "init.h"

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

void initPalya(SDL_Renderer *renderer, Peldany **jatekos, Palya *palya, Jatek *jatek) {
    initJatekos(jatekos, renderer, palya);

    for (int i = 0; i < 6; ++i) {
        jatek->eger.gomb[i] = 0;
    }
    jatek->eger.gorgo = 0;

    for (int i = 0; i < 400; ++i) {
        jatek->billentyuzet[i] = 0;
    }
}

TTF_Font* initTTF(char path[], int meret) {
    TTF_Init();
    TTF_Font *font = TTF_OpenFont(path, meret);
    if (!font) {
        SDL_Log("Nem sikerult megnyitni a fontot! %s\n", TTF_GetError());
    }

    return font;
}

void felszabaditas(Peldany *jatekos, Lovedek *lovedek) {
    Peldany *e = jatekos;
    while (e != NULL) {
        Peldany *temp = e->kov;
        free(e);
        e = temp;
    }

    Lovedek *e2 = lovedek;
    while (e2 != NULL) {
        Lovedek *temp = e2->kov;
        free(e2);
        e2 = temp;
    }
}


