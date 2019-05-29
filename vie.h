
	
	#include<SDL/SDL.h>
	#include<stdio.h>
	#include<stdlib.h>
	#include<SDL/SDL_audio.h>
	#include<SDL/SDL_mixer.h>
	#include<SDL/SDL_image.h>
       
typedef struct vie 
{
SDL_Rect position ;  
int val ;
SDL_Surface*image[]; 
personnage perso;
} vie ;        
	
	

       

void init_vie(personnage *perso);

void displayvie(personnage perso ,SDL_Surface *ecran);
