#include "map.h"
#include "temps.h"


BackGround InitBackGround(BackGround map,char lvl[50],char calque[50])
{
  map.image=IMG_Load(lvl);
  map.position.x=0;
  map.position.y=0;
  map.camera.x=0;
  map.camera.y=0;
  map.camera.h=0;
  map.camera.w=0;
  map.calque=IMG_Load(calque);
  return map;
}

 

void AfficherBackGround(BackGround map,SDL_Surface *screen)
{
  SDL_BlitSurface(map.image,&map.camera,screen,&map.position);
}


int collision_Parfaite(SDL_Surface *calque,SDL_Surface *perso,SDL_Rect posperso,int decalage,int d)
{

  SDL_Color col;
  if(d==0)
  {
    col=GetPixel(calque,posperso.y+perso->w +decalage,posperso.x+(perso->h/2));
  }
else  if(d==1)
  {
    col=GetPixel(calque,posperso.y +decalage,posperso.x+(perso->h/2));
  }
else  if(d==2)
  {
    col=GetPixel(calque,posperso.y+(perso->w/2)+decalage ,posperso.x);
  }
else  if(d==3)
  {
    col=GetPixel(calque,posperso.y+(perso->w/2) +decalage,posperso.x+perso->h);
  }
  
if ((col.r==255)&&(col.b==255)&&(col.g==255))
{
  return 1;
}
else return 0;
}

void  afficher_vie(vie v,SDL_Surface *screen)
{
  int i;
  SDL_Rect position;
  for(i=0;i<v.nbr;i++)
  {
    position.y=v.position.y+(v.image->w*i);
    position.y=20;
    SDL_BlitSurface(v.image,NULL,screen,&position);
  }
}

void temps(SDL_Surface *ecran);	
{ 
SDL_Surface *texte=NULL;
SDL_Rect position;
SDL_Event event;
TTF_Font *police=NULL;
SDL_Color couleurNoire = {0, 0, 0}, couleurBlanche = {255, 255, 255};
	
	    int continuer = 1;
	
	    int tempsActuel = 0, tempsPrecedent = 0, compteur = 0;
	
	    char temps[20] = ""; 
	
	
	   
	
	    TTF_Init();
	
	
	 
	    SDL_WM_SetCaption("Gestion du texte avec SDL_ttf", NULL);
	
	
	   
	    police = TTF_OpenFont("	&.ttf", 65);
	
	
	
	    tempsActuel = SDL_GetTicks();
	
	    sprintf(temps, "Temps : %d", compteur);
	
	    texte = TTF_RenderText_Shaded(police, temps, couleurNoire, couleurBlanche);
	
	
	    while (continuer)
	
	    {
	
	        SDL_PollEvent(&event);
	
	        switch(event.type)
	
	        {
	
	            case SDL_QUIT:
	
	                continuer = 0;
	
	                break;
	
	        }
	
	
	      
	
	
	        tempsActuel = SDL_GetTicks();
	
	        if (tempsActuel - tempsPrecedent >= 1000) /* Si 100 ms au moins se sont écoulées */
	
	        {
	
	            compteur += 1; // On rajoute 100
	//
	            sprintf(temps, "Temps : %d", compteur); 
	
	            SDL_FreeSurface(texte); 
	
	            texte = TTF_RenderText_Shaded(police, temps, couleurNoire, couleurBlanche); 
	
	            tempsPrecedent = tempsActuel; /* On met à jour le tempsPrecedent */
	
	        }
	else 
	{
	SDL_Delay(1000-(tempsActuel - tempsPrecedent));
	}
	
	        position.y = 180;
	
	        position.x = 210;
	
	        SDL_BlitSurface(texte, NULL, ecran, &position); 
	      //  SDL_Flip(ecran);
	
	
	    }
	
	
	    TTF_CloseFont(police);
	
	    TTF_Quit();
	
	
	    SDL_FreeSurface(texte);
	
	    SDL_Quit();
	
	
	
	
	}




