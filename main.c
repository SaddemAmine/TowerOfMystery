#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "fn.h"

    SDL_Surface *screen = NULL; 
    Menu M; Mix_Music *sfx; Mix_Music *mm; SDL_Surface* scr;

void main(){

    if(SDL_Init(SDL_INIT_VIDEO)!=0){
        printf("Error: %s\n",SDL_GetError());
        return;
    }
    if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024)==-1){
        printf("Error : %s",Mix_GetError());
        return;
    }
    init_res();
    menu();
}