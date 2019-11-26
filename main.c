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
    SDL_Renderer *renderer;
    SDL_Window *window;

    Jatek jatek;
    Palya *palya;
    Peldany *jatekos;

    init(&renderer, &window);
    initPalya(renderer, &jatekos);

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

        iranyitas(&jatek);

        jatekFrissites(jatekos, &jatek);

        rajz(&jatek, jatekos, renderer);

        kepernyo(renderer);

        capFrameRate(&most, &maradt);
    }

    /* ablak bezarasa */
    torles(renderer, window);

    return 0;
}