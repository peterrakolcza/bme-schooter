//
// Created by Rakolcza Peter on 2019. 11. 25..
//

#ifndef BME_SCHOOTER_JATEKMENET_H
#define BME_SCHOOTER_JATEKMENET_H

#include "kozos.h"

void jatekFrissites(Peldany *jatekos, Jatek *jatek, Palya *palya, SDL_Texture *texture, SDL_Texture *ellenseg, Lovedek **lovedek);
void ellensegHozzaad(int x, int y, Peldany *jatekos, SDL_Texture *ellenseg, Palya *palya);

#endif //BME_SCHOOTER_JATEKMENET_H
