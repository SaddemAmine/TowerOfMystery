#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>

void main(){
    SDL_Surface *screen = NULL; int x = 0,y = 0; SDL_Event event; int test;
    SDL_Surface *BG = NULL; SDL_Rect pos,posb,posb2; SDL_Surface *BG1 = NULL; SDL_Surface *BG2 = NULL;
    SDL_Surface *BGH = NULL; Mix_Music *SFX;

    if(SDL_Init(SDL_INIT_VIDEO)!=0){
        printf("Error: %s\n",SDL_GetError());
        return;
    }
    if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024)==-1)
        printf("Error : %s",Mix_GetError());
  
    SFX = Mix_LoadMUS("Menu_Res/CSFX.wav");


    int i = 0;
    BG = IMG_Load("Menu_Res/menu.png"); BG1 = IMG_Load("Menu_Res/1.png"); 
    BG2 = IMG_Load("Menu_Res/2.png"); BGH = IMG_Load("Menu_Res/c.png");
    pos.x = 0; pos.y = 0; pos.w = BG->w; pos.h = BG->h;
    posb.x = 240; posb.y = 125; posb.w = BG1->w; posb.h = BG1->h;
    posb2.x = 240; posb2.y = 250; posb2.w = BG1->w; posb2.h = BG1->h;  
    screen = SDL_SetVideoMode(500,500,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
    SDL_BlitSurface(BG,NULL,screen,&pos);
    SDL_Flip(screen);
     while(1){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    Mix_FreeMusic(SFX);
                    SDL_FreeSurface(BG);
                    SDL_FreeSurface(BG1);
                    SDL_FreeSurface(BG2);
                    SDL_FreeSurface(BGH);
                    return;
                break;
                case SDL_MOUSEMOTION:
                    SDL_GetMouseState(&x,&y);
                    printf("%d,%d ::%d\n",x,y,i); i++;
                    if((x>240&&x<395)&&(y>125&&y<190)){
                        SDL_BlitSurface(BG1,NULL,screen,&posb); printf("Yes//1\n"); test = 1;
                        //SDL_Flip(screen);
                    }
                    else{
                         if((x>240&&x<395)&&(y>250&&y<350)){
                        SDL_BlitSurface(BG2,NULL,screen,&posb2); printf("Yes//2\n"); test = 2;
                        //SDL_Flip(screen);
                    }
                    else{
                        SDL_BlitSurface(BG,NULL,screen,&pos); printf("No\n");
                        //SDL_Flip(screen);
                    }
                    }
                    SDL_Flip(screen);
                break;
                case SDL_MOUSEBUTTONDOWN:
                    if(test == 1 && event.button.button == SDL_BUTTON_LEFT){
                        SDL_BlitSurface(BGH,NULL,screen,&posb); Mix_PlayMusic(SFX,1);
                    }
                    else{
                        if(test == 2 && event.button.button == SDL_BUTTON_LEFT){
                        SDL_BlitSurface(BGH,NULL,screen,&posb2); Mix_PlayMusic(SFX,1);
                    }
                    else{
                        SDL_BlitSurface(BG,NULL,screen,&pos);
                    }
                    }
                    SDL_Flip(screen);
                break;
            } 
        }
    }
}