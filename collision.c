#include<SDL/SDL.h>
#include<stdio.h>
#include<stdlib.h>
#include<SDL/SDL_audio.h>
#include<SDL/SDL_mixer.h>
#include<SDL/SDL_image.h>
#include "collision.h"


SDL_Color GetPixel(SDL_Surface* pSurface,int x,int y){
  SDL_Color color;
  Uint32 col = 0 ;

  //determine position
  char* pPosition = ( char* ) pSurface->pixels ;

  //offset by y
  pPosition += ( pSurface->pitch * y ) ;

  //offset by x
  pPosition += ( pSurface->format->BytesPerPixel * x ) ;

  //copy pixel data
  memcpy ( &col , pPosition , pSurface->format->BytesPerPixel ) ;

  //convert color
  SDL_GetRGB ( col , pSurface->format , &color.r , &color.g , &color.b ) ;
  return ( color ) ;
}

int collisioncheck(SDL_Surface* img,SDL_Rect pos,int z,int type){
    SDL_Color C;
    if(type)
        C = GetPixel(img,pos.x+70,pos.y+228+z);
    else
        C = GetPixel(img,pos.x+70+z,pos.y+228);
    //printf("--printf("--%d-- --%d-- --%d--  %d\n",C.r,C.g,C.b,C.r && C.g && C.b);
    if(C.r == 237 && C.g == 28 && C.b == 36)
        return 2;
    else
        if(C.r && C.g && C.b)
            return 1;
    return 0;
}
