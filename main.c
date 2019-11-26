//
// Created by Rakolcza Peter on 2019. 11. 16..
//


/*TODO: kell-e dupla indirekció jatekosnal?
 *
 *
 * */

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
    Lovedek *lovedek;
    SDL_Texture *lovedekTexture = loadImage(renderer, "gfx/donkBullet.png");

    init(&renderer, &window);
    initPalya(renderer, &jatekos, palya);

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
            switch (esemeny.type)
            {
                case SDL_QUIT:
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

        jatekFrissites(jatekos, &jatek, palya, lovedekTexture);

        rajz(&jatek, jatekos, renderer);

        kepernyo(renderer);

        capFrameRate(&most, &maradt);
    }

    return 0;
}