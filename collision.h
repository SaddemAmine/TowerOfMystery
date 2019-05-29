
#include<SDL/SDL.h>
#include<stdio.h>
#include<stdlib.h>
#include<SDL/SDL_audio.h>
#include<SDL/SDL_mixer.h>
#include<SDL/SDL_image.h>

SDL_Color GetPixel (SDL_Surface* pSurface , int x , int y);
int collisioncheck(SDL_Surface* img,SDL_Rect pos,int z,int type);
