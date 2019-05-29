/*! \mainpage Welcome!
*
* \section intro_sec Introduction
*
* This website is all about testing doxygen in hopes of efficiently documenting our game.  
*
* \section whatis_rec What is MyGame?
* ToM is a work of art. Don't overthink it just embrace it. 
*
*/

/*!
*  @file main.c
*  @brief This is a testing program to check if everything works.
*/

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "fn.h"
 

void main(){
    Menu M; Music m; CC cc; SDL_Surface* scr = NULL; int T[20] = {0}; Player p;

    if(SDL_Init(SDL_INIT_VIDEO)!=0){
        printf("Error: %s\n",SDL_GetError());
        return;
    }
    if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,1,1024)==-1){
        printf("Error : %s",Mix_GetError());
        return;
    }
    intro(&scr);
    init_res(&M,&m,&cc);
    savefile_to_array(T);
    menu(M,m,&scr,T,cc);
    array_to_savefile(T);
}
