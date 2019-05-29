#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include<SDL/SDL_audio.h>

#include "bg.h"
#define SCREEN_W 1000
#define SCREEN_H 560

int loadBackground(Background *Backg)
{
	// load background
	Backg->image = SDL_LoadBMP("../Pictures/bg.bmp");
	if (Backg->image == NULL) {
		printf("Unable to load: %s\n", SDL_GetError());
		return (-1);
	}

	Backg->backgroundCollide = SDL_LoadBMP("../Pictures/bgm.bmp");
	if (Backg->backgroundCollide == NULL) {
		printf("Unable to load: %s\n", SDL_GetError());
		return (-1);
	}
	return (0);
}


void initBackground(Background *Backg)
{
	Backg->pos.x=0;
	Backg->pos.y=0;
	Backg->pos.w=SCREEN_W;
	Backg->pos.h=SCREEN_H;
}

void blitBackground(Background*Backg,SDL_Surface *screen)
{

	if(Backg->pos.x>Backg->image->w-SCREEN_W)
		Backg->pos.x=0;
	if(Backg->pos.x<0)
		Backg->pos.x=Backg->image->w-SCREEN_W;
	SDL_BlitSurface(Backg->image, &(Backg->pos), screen,NULL); 

}

void freeBackground(Background *Backg)
{
	SDL_FreeSurface(Backg->image);
}
