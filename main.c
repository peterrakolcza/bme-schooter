//
// Created by Rakolcza Peter on 2019. 11. 16..
//

#include "kozos.h"
#include "init.h"
#include "bemenet.h"
#include "jatekmenet.h"

static void capFrameRate(long *then, float *remainder)
{
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

    printf("LEFUT!");
    SDL_Renderer *renderer;
    SDL_Window *window;

    Jatek jatek;
    Palya palya;
    Peldany *jatekos;

    init(&renderer, &window);
    initPalya(renderer, &jatekos, &palya);

    long most = SDL_GetTicks();
    float maradt = 0;

    /* varunk a kilepesre */
    SDL_Event ev;
    while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT) {

        felkeszites(renderer);

        doInput(&jatek);

        //jatekFrissites(&palya, jatekos, &jatek);

        rajz(&jatek, &palya, renderer);

        kepernyo(renderer);

        capFrameRate(&most, &maradt);
    }

    /* ablak bezarasa */
    torles(renderer, window);

    return 0;
}