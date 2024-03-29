//
// Created by Rakolcza Peter on 2019. 11. 16..
//

#include "init.h"

/** A renderer és az ablak létrehozása. Error kiírása konzolra hiba esetén. */
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

/** Ez a függvény a képek, mint textúra beolvasásáért felelős. */
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

/** Beállítja a háttérszínt és felkészíti a renderer-t a rajzolásra. */
void felkeszites(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 32, 32, 32, 255);
    SDL_RenderClear(renderer);
}

/** Frissíti a képernyőt az azóta kirajzolt elemekkel.*/
void kepernyo(SDL_Renderer *renderer) {
    SDL_RenderPresent(renderer);
}

/** Megsemmísiti a renderer-t és bezárja az ablakot. */
void torles(SDL_Renderer *renderer, SDL_Window *window) {
    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);

    SDL_Quit();

    printf("Minden fel lett szabaditva!");
}

/** A játékos létrehozása, mint a láncolt lista első eleme. A játékos mindig a lista első eleme és az ellenségeket csak hozzáfűzi a játék. */
void initJatekos(Peldany **jatekos, SDL_Renderer *renderer, Palya *palya)
{
    *jatekos = malloc(sizeof(Peldany));
    memset(*jatekos, 0, sizeof(Peldany));
    (*jatekos)->kov = NULL;

    (*jatekos)->texture = loadImage(renderer, "gfx/donk.png");
    (*jatekos)->elet = 5;
    (*jatekos)->hatokor = 0;
    (*jatekos)->oldal = 0;

    palya->tolteny[Pisztoly] = 12;
    palya->tolteny[GepFegyver] = 100;


    (*jatekos)->x = SCREEN_WIDTH / 2;
    (*jatekos)->y = SCREEN_HEIGHT / 2;

    SDL_QueryTexture((*jatekos)->texture, NULL, NULL, &(*jatekos)->w, &(*jatekos)->h);
}

/** Pálya inicializásása. Kinullázzuk a megfelelő adatokat, illetve beállítjuk a kezdő bemeneti adatokat 0-ra.*/
void initPalya(SDL_Renderer *renderer, Peldany **jatekos, Palya *palya, Jatek *jatek) {
    initJatekos(jatekos, renderer, palya);

    palya->pont = 0;
    palya->spawnIdozito = 0;
    jatek->beSzoveg[0] = '\0';


    for (int i = 0; i < 6; ++i) {
        jatek->eger.gomb[i] = 0;
    }
    jatek->eger.gorgo = 0;

    for (int i = 0; i < 400; ++i) {
        jatek->billentyuzet[i] = 0;
    }
}

/** Font betöltése. */
TTF_Font* initTTF(char path[], int meret) {
    TTF_Init();
    TTF_Font *font = TTF_OpenFont(path, meret);
    if (!font) {
        SDL_Log("Nem sikerult megnyitni a fontot! %s\n", TTF_GetError());
    }

    return font;
}

/** Az összes láncolt lista felszabadítása kilépés vagy halál esetén. */
void felszabaditas(Peldany **jatekos, Lovedek **lovedek, PowerUp **powerup) {
    Peldany *e = *jatekos;
    while (e != NULL) {
        Peldany *temp = e->kov;
        free(e);
        e = temp;
    }
    *jatekos = NULL;

    Lovedek *e2 = *lovedek;
    while (e2 != NULL) {
        Lovedek *temp = e2->kov;
        free(e2);
        e2 = temp;
    }
    *lovedek = NULL;

    PowerUp *e3 = *powerup;
    while (e3 != NULL) {
        PowerUp *temp = e3->kov;
        free(e3);
        e3 = temp;
    }
    *powerup = NULL;
}


