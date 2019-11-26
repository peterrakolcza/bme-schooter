//
// Created by Rakolcza Peter on 2019. 11. 16..
//

#include "kozos.h"
#include "init.h"
#include "bemenet.h"
#include "jatekmenet.h"

Uint32 idozit(Uint32 ms, void *param) {
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;   /* ujabb varakozas */
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

    //long most = SDL_GetTicks();
    //float maradt = 0;

    /* idozito hozzaadasa: 20 ms; 1000 ms / 20 ms -> 50 fps */
    SDL_TimerID id = SDL_AddTimer(20, idozit, NULL);

    /* varunk a kilepesre */
    bool kilep = false;
    while (!kilep) {
        felkeszites(renderer);

        //iranyitas(&jatek, &kilep);
        SDL_Event esemeny;
        SDL_WaitEvent(&esemeny);

        switch (esemeny.type) {
            /* felhasznaloi esemeny: ilyeneket general az idozito fuggveny */

                case SDL_USEREVENT:
                    break;

                case SDL_QUIT:
                    kilep = true;
                    //exit(0);
                    break;

                case SDL_KEYDOWN:
                    lenyomva(&esemeny.key, &jatek);
                    break;

                case SDL_KEYUP:
                    elengedve(&esemeny.key, &jatek);
                    break;

                default:
                    break;

        }

        SDL_GetMouseState(&jatek.eger.x, &jatek.eger.y);
        //printf("%d %d", jatek->eger.x, jatek->eger.y);

        jatekFrissites(jatekos, &jatek);

        rajz(&jatek, jatekos, renderer);

        kepernyo(renderer);
    }
    /* idozito torlese */
    SDL_RemoveTimer(id);
    /* ablak bezarasa */
    torles(renderer, window);

    return 0;
}