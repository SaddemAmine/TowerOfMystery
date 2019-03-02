#ifndef FN_H_INCLUDED
#define FN_H_INCLUDED 

typedef struct{
    SDL_Surface* MBG;
    SDL_Surface* B1;
    SDL_Surface* B2;
    SDL_Surface* B3;
    SDL_Surface* B1C;
    SDL_Surface* B2C;
    SDL_Surface* B3C;
}Menu;

void init_res();
void free_res();
void menu();


#endif