//
// Created by Rakolcza Peter on 2019. 11. 16..
//

#include "kozos.h"
#include "init.h"
#include "bemenet.h"

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
    SDL_Renderer *renderer;
    SDL_Window *window;

    init(&renderer, &window);
    initPalya(renderer);

    Jatek jatek;

    long most = SDL_GetTicks();
    float maradt = 0;

    /* varunk a kilepesre */
    SDL_Event ev;
    while (SDL_WaitEvent(&ev) && ev.type != SDL_QUIT) {

        felkeszites(renderer);

        doInput(&jatek);

        rajz(&jatek, renderer);

        kepernyo(renderer);

        capFrameRate(&most, &maradt);
    }

    /* ablak bezarasa */
    torles(renderer, window);

    return 0;
}