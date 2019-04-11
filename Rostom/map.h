#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
typedef struct BackGround
{
  SDL_Surface *image;
  SDL_Surface *calque;
  SDL_Rect position;
  SDL_Rect camera;
}BackGround;
typedef struct vie
{
  int nbr;
  SDL_Rect position;
  SDL_Surface *image;
}vie;

BackGround InitBackGround(BackGround map,char lvl[50],char calque[50]);
void AfficherBackGround(BackGround map,SDL_Surface *screen);
int collision_Parfaite(SDL_Surface *calque,SDL_Surface *perso,SDL_Rect posperso,int decalage,int d);
void  afficher_vie(vie v,SDL_Surface *screen);
void temps(SDL_Surface *ecran);	
