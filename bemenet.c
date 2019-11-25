//
// Created by Rakolcza Peter on 2019. 11. 16..
//
#include "bemenet.h"

void doKeyUp(SDL_KeyboardEvent *event, Jatek* jatek)
{
    if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
    {
        jatek->billentyuzet[event->keysym.scancode] = 0;
    }
}

void doKeyDown(SDL_KeyboardEvent *event, Jatek* jatek)
{
    if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
    {
        jatek->billentyuzet[event->keysym.scancode] = 1;
    }
}

void doInput(Jatek *jatek)
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                exit(0);
                break;

            case SDL_KEYDOWN:
                doKeyDown(&event.key, jatek);
                break;

            case SDL_KEYUP:
                doKeyUp(&event.key, jatek);
                break;

            default:
                break;
        }
    }

    SDL_GetMouseState(&jatek->eger.x, &jatek->eger.y);
}


