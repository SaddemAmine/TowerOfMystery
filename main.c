#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "fn.h"

    SDL_Surface *screen = NULL; 
    SDL_Surface *BG = NULL; SDL_Surface *BG1 = NULL; SDL_Surface *BG2 = NULL;
    SDL_Surface *BGH = NULL; Mix_Music *SFX;

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