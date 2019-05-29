#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include<SDL/SDL_audio.h>

void BlitTime(int x,SDL_Surface* T[],SDL_Surface** scr){
    int t[3];
    
    SDL_Rect p1,p2,p3; p1.y = 40; p2.y = 40; p3.y = 40; p1.x = 1160; p2.x = 1186; p3.x = 1212; 
    t[0] = x/100; t[1] = (x/10)%10; t[2] = (x%100)%10;
    
    SDL_BlitSurface(T[t[0]],NULL,(*scr),&p1);
    SDL_BlitSurface(T[t[1]],NULL,(*scr),&p2);
    SDL_BlitSurface(T[t[2]],NULL,(*scr),&p3);
       
}

void BlitScore(int x,SDL_Surface* T[],SDL_Surface** scr){
    int t[3];
    
    SDL_Rect p1,p2,p3; p1.y = 95; p2.y = 95; p3.y = 95; p1.x = 1160; p2.x = 1186; p3.x = 1212; 
    t[0] = x/100; t[1] = (x/10)%10; t[2] = (x%100)%10;
    
    SDL_BlitSurface(T[t[0]],NULL,(*scr),&p1);
    SDL_BlitSurface(T[t[1]],NULL,(*scr),&p2);
    SDL_BlitSurface(T[t[2]],NULL,(*scr),&p3);
       
}

