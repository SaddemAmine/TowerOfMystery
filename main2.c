#include<stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include<SDL/SDL_audio.h>
#include <SDL/SDL_ttf.h>
#include "bg.c"

#define WIDTH 1000
#define HEIGHT 560

int main (int argc , char *argv[])
{
SDL_Surface *screen=NULL ;
SDL_Surface *image=NULL ;
SDL_Rect positionscreen ,positionimage ;
positionscreen.x=-90;
positionscreen.y=-3300;
positionscreen.w=1280;
positionscreen.h=4400;
positionimage.x = -5000;
positionimage.y = -10000;

SDL_Init(SDL_INIT_VIDEO);

screen=SDL_SetVideoMode(1920, 1080, 32 , SDL_HWSURFACE| SDL_DOUBLEBUF);

int loadBackground(Background*Backg);

SDL_BlitSurface(image, NULL , screen, &positionscreen);

SDL_Flip(screen);

SDL_Init(SDL_INIT_VIDEO);

SDL_Flip(screen);

SDL_FreeSurface(image);

SDL_FreeSurface(screen);




}

{
      
SDL_Event event;
int gameover = 1;
int test;
vie v;
init_vie(&v);
SDL_Init(SDL_INIT_VIDEO);
screen = SDL_SetVideoMode(SCREEN_W,SCREEN_H, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
SDL_WM_SetCaption("vie", NULL);
SDL_EnableKeyRepeat(.5,.5);
while(gameover)
{
test=0;
 if(SDL_WaitEvent(&event))
   {
    switch(event.type)
    {
     case SDL_QUIT:
     gameover = 0;
     break;
     case SDL_KEYDOWN:
    switch(event.key.keysym.sym)
{
                                
   case SDLK_RIGHT:
   test=1;
   break;
}
break;
}

SDL_FillRect(screen, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
updatevie(&v,test);  
displayvie(v ,screen) ;	
SDL_Flip(screen);
 }
}
vie_freevie(&v);
SDL_Quit();
















































return 0;

