//
// Created by Rakolcza Peter on 2019. 11. 16..
//


/*TODO: peldanyok egymassal valo collisionjet nem nezem!
 *
 *
 * */

#include "kozos.h"
#include "init.h"
#include "bemenet.h"
#include "jatekmenet.h"
#include "rajzolas.h"

static void capFrameRate(long *then, float *remainder) {
    //FPS 9ms
    long wait = 16 + *remainder;
    *remainder -= (int)*remainder;
    long frameTime = SDL_GetTicks() - *then;

    wait -= frameTime;

    if (wait < 1) {
        wait = 1;
    }

    SDL_Delay(wait);

    *remainder += 0.667;
    *then = SDL_GetTicks();
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    SDL_Renderer *renderer;
    SDL_Window *window;

    Jatek jatek;
    Palya palya;
    Peldany *jatekos = NULL;
    Lovedek *lovedek = NULL;
    PowerUp *powerup = NULL;

    init(&renderer, &window);
    initPalya(renderer, &jatekos, &palya, &jatek);

    SDL_Texture *lovedekTexture = loadImage(renderer, "gfx/bullet2.png");
    SDL_Texture *celzo = loadImage(renderer, "gfx/targetter.png");
    SDL_Texture *grid = loadImage(renderer, "gfx/grid01.png");
    TTF_Font *font = initTTF("gfx/LiberationSerif-Regular.ttf", 32);
    SDL_Texture *hatter = loadImage(renderer, "gfx/background.png");
    SDL_Texture *ellenseg = loadImage(renderer, "gfx/enemy01.png");
    SDL_Texture *elet = loadImage(renderer, "gfx/health.png");
    SDL_Texture *tolteny = loadImage(renderer, "gfx/uzi.png");

    /*Peldany *e;
    int db = 0;
    for (e = jatekos; e != NULL ; e = e->kov) {
        printf("%d ", e->elet);
        db++;
    }
    printf("%d", db);*/

    long most = SDL_GetTicks();
    float maradt = 0;

    /* varunk a kilepesre */
    while (true) {
        felkeszites(renderer);

        //iranyitas(&jatek);
        SDL_Event esemeny;

        while (SDL_PollEvent(&esemeny)) {
            switch (esemeny.type) {
                case SDL_QUIT:
                    felszabaditas(jatekos, lovedek, powerup);
                    /* ablak bezarasa */
                    torles(renderer, window);
                    exit(0);
                    break;

                case SDL_KEYDOWN:
                    lenyomva(&esemeny.key, &jatek);
                    break;

                case SDL_KEYUP:
                    elengedve(&esemeny.key, &jatek);
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    gombLe(&esemeny.button, &jatek);
                    break;

                case SDL_MOUSEBUTTONUP:
                    gombFel(&esemeny.button, &jatek);
                    break;

                case SDL_MOUSEWHEEL:
                    jatek.eger.gorgo = esemeny.wheel.y;
                    break;

                default:
                    break;
            }
        }

        SDL_GetMouseState(&jatek.eger.x, &jatek.eger.y);
        //printf("%d %d", jatek->eger.x, jatek->eger.y);

        jatekFrissites(jatekos, &jatek, &palya, lovedekTexture, ellenseg, elet, &lovedek, &powerup);

        rajz(celzo, grid, hatter, &jatek, jatekos, lovedek, powerup, &palya, renderer, font);

        kepernyo(renderer);

        capFrameRate(&most, &maradt);

        //printf("%d ", jatekos->fegyver);
        //printf("%d ", jatekos->ujratoltIdo);
        //printf("%d ", jatekos->szog);
    }

    return 0;
}