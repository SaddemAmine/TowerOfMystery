
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include<SDL/SDL_audio.h>


struct Background
{
  int x,y;
  SDL_Surface *image;
  SDL_Surface *screen;
  SDL_Surface *backgroundCollide;
  SDL_Rect pos;
  SDL_Rect camera;
  
};
typedef struct Background Background;


int loadBackground(Background*Backg);
void initBackground(Background*Backg);
void freeBackground(Background *Backg);
void blitBackground(Background*Backg,SDL_Surface *screen);


#endif // JEU_H_INCLUDED  
