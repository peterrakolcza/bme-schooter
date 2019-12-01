//
// Created by Rakolcza Peter on 2019. 11. 16..
//

#include "kozos.h"
#include "init.h"
#include "bemenet.h"
#include "jatekmenet.h"
#include "rajzolas.h"
#include "eredmenyek.h"

/**
 *Ez a függvény a képkocka számot hívatott limitálni, hogy ne pörögjön feleslgesen a CPU,
 * ezt minden képkocka renderer-ésénél meg van hívva, így ki tudja számolni, hogy mennnyit kell
 * késletetnie, hogy kb. 60 FPS legyen a képckockaszám.
 */
void capFrameRate(long *then, float *remainder) {
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

/**
 *Itt történik a játék vezérlése, változók létrehozása.
 *
 * Először létre kell hozni az ablakot és inicializáni a válotzókat. Utána egy while ciklus vezérli a játékot, aminek különböző állapotai vannak.
 * Lehet:
 * <ul>
 *  <li>-főképernyőn vagyunk, várunk a kezdésre
 *  <li>-fut a játék
 *  <li>-meghalt a játékosunk: frissítjük a legjobb eredményeket és visszaállítjuk a játék alap állapotába
 *  <li>-dicsőséglista nézetben vagyunk
 *</ul>
 */
int main(int argc, char *argv[]) {
    //A random függvény seed-jének betöltése.
    srand(time(NULL));
    SDL_Renderer *renderer;
    SDL_Window *window;

    //A "fő" változók, illetve a láncolt listák első elemeinek pointereinek létrehozása.
    Jatek jatek;
    Palya palya;
    Peldany *jatekos = NULL;
    Lovedek *lovedek = NULL;
    PowerUp *powerup = NULL;

    //SDL inicializásása, ablak létrehozása
    init(&renderer, &window);
    //Játék inicializása, láncolt listák első elemeinek létrehozása, bemenetek kinullázása
    initPalya(renderer, &jatekos, &palya, &jatek);

    /*Nem a legelegánsabb megoldás, de mivel nincs sok textúra a játékban, megoldható volt, hogy mindegyiket csak
    egy változóba kelljen tárolni, ami utána megkönnyítette a továbbiakat, mivel paraméterként kellett mindig csak átadni. (https://opengameart.org/content/top-down-2d-rpg)(https://www.parallelrealities.co.uk/tutorials/bad/bad1.php)*/
    SDL_Texture *lovedekTexture = loadImage(renderer, "gfx/bullet2.png");
    SDL_Texture *celzo = loadImage(renderer, "gfx/targetter.png");
    SDL_Texture *grid = loadImage(renderer, "gfx/grid01.png");
    TTF_Font *font = initTTF("gfx/LiberationSerif-Regular.ttf", 32);
    SDL_Texture *hatter = loadImage(renderer, "gfx/background.png");
    SDL_Texture *ellenseg = loadImage(renderer, "gfx/enemy01.png");
    SDL_Texture *elet = loadImage(renderer, "gfx/health.png");
    SDL_Texture *tolteny = loadImage(renderer, "gfx/uzi.png");
    SDL_Texture *fokepernyoTexture = loadImage(renderer, "gfx/fokepernyo1.png");
    Eredmenyek legjobb[10]; /* Ebben a változóban van eltárolva a top 10 eredmény, amit utána kilépéskor a játék fáljbaír.*/

    //Ha létezik a "legjobberedmenyek.tx", akkor ez a függvény beolvassa az adatokat a "legjobb" 10 elemű tömbbe.
    beolvasas(legjobb);

    long most = SDL_GetTicks();
    float maradt = 0;

    //A játék nézeteit segítő bool változók.
    bool start = false;
    bool topPontok = false;
    bool bevanIrva = false;

    /* Várunk a kilépésre. */
    while (true) {
        //A képernyő tölrése és a háttérszín beállítása.
        felkeszites(renderer);

        SDL_Event esemeny;

        while (SDL_PollEvent(&esemeny)) {
            switch (esemeny.type) {
                case SDL_QUIT:
                    //A legjobb eredményeket kiírja egy fájlba.
                    kiiras(legjobb);
                    //Felszabadítjuk az összes láncolt listát.
                    felszabaditas(&jatekos, &lovedek, &powerup);
                    /* Ablak bezárása. */
                    torles(renderer, window);
                    exit(0);
                    break;

                case SDL_KEYDOWN:
                    //Ha a felhazsnáló lenyomott egy gombot, azt a "billentyűzet" tömbben regisztráljuk: a megfelelő értéket 1-re változatjuk.
                    lenyomva(&esemeny.key, &jatek);
                    break;

                case SDL_KEYUP:
                    //A felengedett billentyűt visszaállítjuk 0-ra.
                    elengedve(&esemeny.key, &jatek);
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    //A felhasználó által lenyomott egérgombok regisztrása.
                    gombLe(&esemeny.button, &jatek);
                    break;

                case SDL_MOUSEBUTTONUP:
                    //A felengedett egérgombók visszaállítása 0-ra.
                    gombFel(&esemeny.button, &jatek);
                    start = true;
                    topPontok = false;
                    break;

                case SDL_MOUSEWHEEL:
                    //Az egér görgőjének elmozulásának regisztrása.
                    jatek.eger.gorgo = esemeny.wheel.y;
                    break;

                default:
                    break;
            }
        }
        //Beolvassuk az egér X;Y koordinátáját.
        SDL_GetMouseState(&jatek.eger.x, &jatek.eger.y);

        //Meghalt a játekos.
        if (jatekos->elet == 0) {
            if (palya.pont == 0)
                bevanIrva = true;

            int index = -1;
            int i = 0;
            while (legjobb[i].nev[0] != '\0' && i < 10) {
                if (palya.pont > legjobb[i].pontSzam) {
                    index = i;
                    break;
                }
                i++;
            }

            if (i == 10 && index == -1)
                bevanIrva = true;

            while (!bevanIrva) {
                SDL_Event ev;

                while (SDL_PollEvent(&ev)) {
                    switch (ev.type) {
                        case SDL_KEYDOWN:
                            lenyomva(&ev.key, &jatek);
                            break;

                        case SDL_KEYUP:
                            elengedve(&ev.key, &jatek);
                            break;

                        case SDL_TEXTINPUT:
                            if (strlen(jatek.beSzoveg) <= 41)
                                strcat(jatek.beSzoveg, ev.text.text);
                            break;

                        default:
                            break;
                    }
                }

                szovegBeirasa(&jatek, &bevanIrva);

                felkeszites(renderer);
                legjobbNev(renderer, font, jatek.beSzoveg);
                kepernyo(renderer);
            }
            bevanIrva = false;

            if(!((i == 10 && index == -1) || palya.pont == 0))
                feluliras(legjobb, palya.pont, jatek.beSzoveg, i, index);

            topPontok = true;
            start = false;
            felszabaditas(&jatekos, &lovedek, &powerup);
            initPalya(renderer, &jatekos, &palya, &jatek);
        }

        //Dicsőséglista rajzolása.
        if (topPontok) {
            legjobbEredmenyekKepernyo(renderer, font, celzo, &jatek, fokepernyoTexture, grid, legjobb);
        } // Fut a játék.
        else if (start) {

            jatekFrissites(jatekos, &jatek, &palya, lovedekTexture, ellenseg, elet, tolteny, &lovedek, &powerup);

            rajz(celzo, grid, hatter, &jatek, jatekos, lovedek, powerup, &palya, renderer, font);
        } //Főképernyő rajzolása.
        else fokepernyo(renderer, font, celzo, &jatek, fokepernyoTexture, grid);

        kepernyo(renderer);

        capFrameRate(&most, &maradt);
    }

    return 0;
}